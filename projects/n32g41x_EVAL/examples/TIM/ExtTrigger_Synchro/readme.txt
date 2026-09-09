1、功能说明
     1、ATIM1 CH2作为外部触发输入，门控ATIM1 CH1和GTIM2，GTIM2门控GTIM3。

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M,GTIM2_CLK=80M,GTIM3_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M,GTIM2_CLK=96M,GTIM3_CLK=96M
        3、端口配置：
            PA8选择为ATIM1 CH1输出
            PA9选择为ATIM1 CH2输入
            PB4选择为GTIM2 CH1输出
            PA6选择为GTIM3 CH1输出
        4、TIM：
            ATIM1 CH2门控CH1和GTIM2, GTIM2门控GTIM3
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1 CH1,GTIM2 CH1,GTIM3 CH1的波形
        2、ATIM1 CH2高电平定时器开始计数，低电平停止

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。



1. Function description
     1. ATIM1 CH2 gated CH1 and GTIM2, GTIM2 gated GTIM3

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M,GTIM2_CLK=80M,GTIM3_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M,GTIM2_CLK=96M,GTIM3_CLK=96M
        3. Port configuration:
            PA8 is selected as ATIM1 CH1 output
            PA9 is selected as ATIM1 CH2 output
            PB4 is selected as GTIM2 CH1 output
            PA6 is selected as GTIM3 CH1 output
        4. TIM:
             ATIM1 CH2 gated CH1 and GTIM2, GTIM2 gated GTIM3
    Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of ATIM1 CH1, GTIM2 CH1, GTIM3 CH1
         2. ATIM1 CH2 high level timer starts counting, low level stops
4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
