1、功能说明
    1、systick 100ms触发ATIM1输出6步换相波形

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
            HSE+PLL
        2、时钟频率：
            HSE=8M,PLL=144M,AHB=72M,APB1=36M,APB2=72M,ATIM1_CLK=144M
        3、中断：
            ATIM1 COM事件中断打开，抢断优先级1，子优先级1
            Systick 100ms中断，优先级0
        4、端口配置：
            PA8选择为ATIM1 CH1输出
            PA9选择为ATIM1 CH2输出
            PA10选择为ATIM1 CH3输出
            PB13选择为ATIM1 CH1N输出
            PB14选择为ATIM1 CH2N输出
            PB15选择为ATIM1 CH3N输出
        5、TIM：
            ATIM1 6路互补冻结输出模式，无刹车，开COM中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1的输出波形
        2、每隔100ms systick触发COM中断，在ATIM的COM中断里面输出AB AC BC BA CA CB的6步换相波形

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1. systick triggers ATIM1 for 100ms to output 6-step commutation waveform

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
        1. Clock source: HSE+PLL
        2. Clock frequency: 
            HSE=8M,PLL=144M,AHB=72M,APB1=36M,APB2=72M,ATIM1_CLK=144M
        3. Interrupt:
            ATIM1 COM event interrupt on, steal priority level 0, sub priority level 1
            Systick 100ms interrupt, priority 0
        4. Port configuration:
            PA8 is selected as ATIM1 CH1 output
            PA9 is selected as ATIM1 CH2 output
            PA10 is selected as ATIM1 CH3 output
            PB13 is selected as ATIM1 CH1N output
            PB14 is selected as ATIM1 CH2N output
            PB15 is selected as ATIM1 CH3N output
        5. TIM:
            ATIM1 6-channel complementary freeze output mode, no brake, open COM interrupt
    Instructions:
        1. Open the debug mode after compiling, and observe the output waveform of ATIM1 with an oscilloscope or logic analyzer
        2. The systick triggers the COM interrupt every 100ms, and outputs the 6-step commutation waveform of AB AC BC BA CA CB in the COM interrupt of the ATIM
4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
