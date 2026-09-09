1、功能说明
    1、GTIM1 利用CH1 CH2 CH3 CH4 CC值产生定时中断，翻转IO电平

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
        1、时钟源：
            HSI+PLL
        2、时钟频率：
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M
        3、中断：
            GTIM1 比较中断打开
        4、端口配置：
            PB0选择为IO输出
            PB1选择为IO输出
            PB2选择为IO输出
            PB3选择为IO输出
        5、TIM：
            GTIM1输出冻结模式，CH1 CH2 CH3 CH4比较值产生中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PB0、PB1、PB2、PB3的波形
        2、程序运行后，对应通道达到比较值后，比较值累加并翻转对应IO口电平

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1. GTIM1 uses the CH1 CH2 CH3 CH4 CC value to generate a timing interrupt and flip the IO level

2. Use environment
    Software development environment: KEIL MDK-ARM V5.06 / IAR EWARM V8.50
    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSI+PLL
        2. Clock frequency: 
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M
        3. Interruption:
            GTIM1 compare interrupt is turned on
        4. Port configuration:
            PB0 is selected as IO output
            PB1 is selected as IO output
            PB2 is selected as IO output
            PB3 is selected as IO output
        5. TIM:
            GTIM1 output freeze mode, CH1 CH2 CH3 CH4 compare value interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PB0, PB1, PB2, and PB3
        2. After the program runs, after the corresponding channel reaches the comparison value, the comparison value accumulates and flips the corresponding IO port level

4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
