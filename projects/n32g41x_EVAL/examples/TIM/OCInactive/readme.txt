1、功能说明
    1、GTIM2 CH1 CH2 CH3 CH4 达到CC值后，对应拉低PA1 PA2 PA3 PA4的IO电平
    
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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM2_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM2_CLK=96M
        3、中断：
            GTIM2 比较中断打开
        4、端口配置：
            PA1选择为IO 输出
            PA2选择为IO 输出
            PA3选择为IO 输出
            PA4选择为IO 输出
        5、TIM：
            GTIM2 配置好CH1 CH2 CH3 CH4的比较值，并打开比较中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PA1 PA2 PA3 PA4的波形
        2、定时器运进入CC1 CC2 CC3 CC4中断后,对应拉低PA1 PA2 PA3 PA4的IO

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。

1. Function description
    1. After GTIM2 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PA1, PA2, PA3, and PA4

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
            HSI+PLL
        2. Clock frequency: 
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM2_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM2_CLK=96M
        3. Interruption:
            GTIM2 compare interrupt is turned on
        4. Port configuration:
            PA1 is selected as IO output
            PA2 is selected as IO output
            PA3 is selected as IO output
            PA4 is selected as IO output
        5. TIM:
            GTIM2 configures the comparison value of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PA1, PA2, PA3, and PA4
        2. After the timer enters the CC1 CC2 CC3 CC4 interrupt, it will correspondingly pull down the IO of PA1 PA2 PA3 PA4

4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
