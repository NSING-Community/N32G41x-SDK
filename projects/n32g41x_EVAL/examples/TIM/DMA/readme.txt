1、功能说明
    1、ATIM1 CH3 CH3N互补信号每6个周期改变一次占空比

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
        N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M
        N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M
    3、端口配置：
        PA10选择为ATIM1 CH3输出
        PB15选择为ATIM1 CH3N输出
    4、TIM：
        ATIM1 CH3 CH3N互补输出，每6个周期触发一次DMA传输
    5、DMA：
        DMA1_CH5通道循环环模式搬运3个字SRC_Buffer[3]变量到ATIM1 CCDAT3寄存器
使用方法：
    1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1 CH3 CH3N的波形
    2、ATIM1的6个周期改变一次CH3 CH3N的占空比，循环改变

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1. ATIM1 CH3 CH3N complementary signal changes duty cycle every 6 cycles

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,ATIM1_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,ATIM1_CLK=96M
        3. Port configuration:
            PA10 selected as ATIM1 CH3 Output
            PB15 selected as ATIM1 CH3N Output
        4. TIM:
            ATIM1 CH3 CH3N complementary output triggers DMA transmission every 6 cycles
        5. DMA:
            DMA1_ CH5 Channel circular mode handling 3 word SRC_ Buffer[3] variable to ATIM1 CCDAT3 register
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of ATIM1 CH3 CH3N
        2. Change the duty cycle of CH3 and CH3N once in 6 cycles of ATIM1, and change cyclically

4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
