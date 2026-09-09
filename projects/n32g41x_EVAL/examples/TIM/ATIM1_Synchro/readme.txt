1、功能说明
    GTIM3 GTIM4在ATIM1周期下计数

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M,GTIM3_CLK=80M,GTIM4_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M,GTIM3_CLK=96M,GTIM4_CLK=96M
        3、端口配置：
            PA8选择为ATIM1 CH1输出
            PA6选择为GTIM3 CH1输出
            PB0选择为GTIM4 CH1输出
        4、TIM：
            ATIM1 CH1 周期触发GTIM3 GTIM4的门控
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1 CH1、GTIM3 CH1、GTIM4 CH1的波形
        2、程序运行后，GTIM3 15倍周期ATIM1，GTIM4 10倍周期ATIM1

4、注意事项
    无


1. Function description
    1. GTIM3 GTIM4 counts under the ATIM1 cycle

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M,GTIM3_CLK=80M,GTIM4_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M,GTIM3_CLK=96M,GTIM4_CLK=96M
        3. Port configuration:
            PA8 is selected as the CH1 output of ATIM1
            PA6 is selected as the CH1 output of GTIM3
            PB0 is selected as the CH1 output of GTIM4
        4. TIM:
            ATIM1 CH1 period triggers the gating of GTIM3 GTIM4
    Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of ATIM1 CH1, GTIM3 CH1, and GTIM4 CH1
         2. After the program runs, GTIM3 15 times cycle ATIM1, GTIM4 10 times cycle ATIM1

4. Attention
    none
