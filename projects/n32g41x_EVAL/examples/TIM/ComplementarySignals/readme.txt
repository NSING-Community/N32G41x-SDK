1、功能说明
    1、ATIM1输出4对互补波形

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
            HSE+PLL
        2、时钟频率：
            HSE=8M,PLL=144M,AHB=72M,APB1=36M,APB2=72M,ATIM1_CLK=144M
        3、端口配置：
            PA8选择为ATIM1 CH1输出
            PA9选择为ATIM1 CH2输出
            PA10选择为ATIM1 CH3输出
            PA11选择为ATIM1 CH4输出
            PB13选择为ATIM1 CH1N输出
            PB14选择为ATIM1 CH2N输出
            PB15选择为ATIM1 CH3N输出
            PB2选择为ATIM1 CH4N输出
            PA6选择为刹车输入BKIN1
        4、TIM：
            ATIM1 4对互补输出带死区，PA6刹车
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1的波形
        2、PA6拉低可观察到4对互补PWM，PA6拉高PWM消失

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1. ATIM1 outputs 4 complementary waveforms

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                          IAR EWARM 8.50.1
    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions for use
    System Configuration;
        1. Clock source: 
            HSE+PLL
        2. Clock frequency: 
            HSE=8M,PLL=144M,AHB=72M,APB1=36M,APB2=72M,ATIM1_CLK=144M
        3. Port configuration:
            PA8 is selected as ATIM1 CH1 output
            PA9 is selected as ATIM1 CH2 output
            PA10 is selected as ATIM1 CH3 output
            PA11 is selected as ATIM1 CH4 output
            PB13 is selected as ATIM1 CH1N output
            PB14 is selected as ATIM1 CH2N output
            PB15 is selected as ATIM1 CH3N output
            PB2 is selected as ATIM1 CH4N output
            PA6 is selected as break input BKIN1
        4. TIM:
                ATIM1 4-pair complementary with dead zone, PA6 is brake input
    Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveform of ATIM1
         2. When PA6 is low, 4 complementary PWM can be observed, and when PA6 is high, PWM disappears

4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
