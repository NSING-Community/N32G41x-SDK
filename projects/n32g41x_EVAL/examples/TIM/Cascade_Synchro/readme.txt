1、功能说明
    GTIM1周期门控GTIM2，GTIM2周期门控GTIM3。

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M,GTIM2_CLK=80M,GTIM3_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M,GTIM2_CLK=96M,GTIM3_CLK=96M
        3、端口配置：
            PA0选择为GTIM1的CH1输出
            PB4选择为GTIM2的CH1输出
            PA6选择为GTIM3的CH1输出
        4、TIM：
            GTIM1 的周期门控GTIM2，GTIM2的周期门控GTIM3
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PA0、PB4、PA6的波形
        2、GTIM2频率为GTIM1的1/4，GTIM3频率为GTIM2的1/4

4、注意事项


1. Function description
    GTIM1 periodically gates GTIM2, GTIM2 periodically gates GTIM3.

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M,GTIM2_CLK=80M,GTIM3_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M,GTIM2_CLK=96M,GTIM3_CLK=96M
        3. Port configuration:
            PA0 is selected as GTIM1 CH1 output 
            PB4 is selected as GTIM2 CH1 output 
            PA6 is selected as GTIM3 CH1 output 
        4. TIM:
            GTIM2 cycle gating GTIM5, GTIM5 cycle gating GTIM6
    Instructions:
        1. After compiling, turn on debug mode, use oscilloscope or logic analyzer to observe waveforms on PA0, PB4, PA6
        2. GTIM2 frequency is 1/4 of GTIM1, GTIM3 frequency is 1/4 of GTIM2

4. Attention

