1、功能说明
    1、BTIM1 利用更新中断，唤醒STOP模式，LED（D2）闪烁。
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统配置；
        1、时钟源：
            HSI+PLL
        2、时钟频率：
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,LSI= 32K
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,LSI= 32K
        3、中断：
            BTIM1 更新中断打开
        4、端口配置：
            PA7选择为输出功能（LED2）
        5、TIM：
            BTIM1 使能周期中断
    使用方法：
        1、编译后下载程序复位运行；
        2、LED(D2) 闪烁；
4、注意事项
    STOP模式下系统时钟为LSI
    BTIM1在STOP模式下使用LSI时钟源保持运行
    EXTI20（BTIM1）仅支持上升沿触发


1. Function description
    1.BTIM1 uses the update interrupt to wake up from STOP mode, causing LED (D2) to blinking. 
2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions for use
   System Configuration:
        1. Clock source:
            HSI+PLL
        2. Clock frequency: 
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,LSI= 32K
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,LSI= 32K
        3. Interruption:
            BTIM1 update interrupt is turned on
        4. Port configuration:
            PA7 is selected as an I/O output to control LED (D2).
        5. TIM:
            BTIM1 enables periodic interrupts
    Instructions:
        1. After compiling, download the program to reset and run
        2. LED (D2) to blinking
4. Attention
    In STOP mode, the system clock source is LSI
    BTIM1 clock source is LSI in STOP mode
    EXTI20 (BTIM1) only supports rising edge trigger

