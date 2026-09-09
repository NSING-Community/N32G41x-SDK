1、功能说明
    IWDG复位功能。
    定义宏LSI_TIM_MEASURE可使能GTIM3捕获LSI，动态测量LSI频率用于IWDG超时计算。

2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统配置:
        1、时钟源：HSE+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、IWDG时钟源：LSI/32
        4、理论超时时间值：250ms
        5、指示灯：LED1(PA1) LED3(PB1)

    LSI频率测量(LSI_TIM_MEASURE):
        GTIM3 CH1通过tim_ti1_in2内部直连LSI，输入捕获方式测量LSI频率。
        定时器配置：PSC=1，IC DIV8(每8个LSI上升沿捕获一次)。
        分多段累加Capture计数值，最后一次性用64位运算计算频率，
        避免整数截断误差。默认测量128个LSI边沿(约4ms@32kHz)。
        相关宏定义见main.h：
          LSI_CAPTURE_INTERVALS — 每段捕获间隔数(默认2)
          LSI_MEASURE_COUNT     — 累加的段数(默认8)

    测试步骤及现象：
        1、编译后烧录到评估板，上电后，指示灯LED3不停的闪烁，说明IWDG正常喂狗。
        2、把SysTick_Delay_Ms(249)参数改成251以上，系统持续复位，LED1亮。

4、注意事项
    未启用LSI_TIM_MEASURE时，可通过MCO(PA8)输出LSI外部测量实际频率。
    启用后软件自动测量，无需外部测量。

1. Function description
    IWDG reset with optional LSI frequency measurement via GTIM3 input capture.
    Define LSI_TIM_MEASURE to enable dynamic LSI measurement for accurate IWDG timeout.

2. Use environment
    Software: KEIL MDK-ARM 5.34 / IAR EWARM 8.50.1
    Chip: N32G412x8L7, N32G412xBL7, N32G415x8L7, N32G415xBL7

3. Instructions
    System Configuration:
        1. Clock source: HSE+PLL
        2. SYSCLK: N32G412:80MHz, N32G415:96MHz
        3. IWDG clock: LSI/32
        4. Timeout: 250ms (nominal)
        5. LEDs: LED1(PA1), LED3(PB1)

    LSI measurement (LSI_TIM_MEASURE):
        GTIM3 CH1 captures LSI via internal tim_ti1_in2 connection.
        Timer config: PSC=1, rising edge, IC DIV8 (8 LSI edges per capture).
        Tick counts are accumulated over multiple segments, then frequency
        is computed once using 64-bit arithmetic to avoid integer truncation.
        Default: 128 LSI edges (~4ms @32kHz).
        See main.h for configurable macros:
          LSI_CAPTURE_INTERVALS — intervals per segment (default 2)
          LSI_MEASURE_COUNT     — segments to accumulate (default 8)

    Test:
        1. Normal: LED3 blinks continuously (IWDG fed before timeout).
        2. Change delay to ≥251ms: system resets repeatedly, LED1 stays on.

4. Notes
    Without LSI_TIM_MEASURE, measure LSI externally via MCO(PA8).
    With LSI_TIM_MEASURE, measurement is automatic — no external equipment needed.
