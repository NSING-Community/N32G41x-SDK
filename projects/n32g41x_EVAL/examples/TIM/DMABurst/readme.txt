 1、功能说明
    1、ATIM1 一个周期后同时改变周期和占空比

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
            PA8选择为ATIM1 CH1输出
        4、TIM：
            ATIM1 CH1 输出，周期触发DMA burst传输，加载CCDAT1，CCDAT2，CCDAT3，CCDAT4，CCDAT5，CCDAT6，PSC, AR寄存器，改变占空比和周期和重复计数器
        5、DMA：
            DMA1_CH5通道非循环模式搬运8个字SRC_Buffer[8]变量到ATIM1寄存器
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1 CH1的波形
        2、ATIM1的第一个周期结束后，后面的波形为DMA搬运的改变周期和占空比的波形
        3、调试状态下修改DmaAgain=1会再次搬运8个字SRC_Buffer[8]变量到TIM1 DMA寄存器

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1. ATIM1 changes the period and duty cycle at the same time after one cycle

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
            PA8 selected as ATIM1 CH1 Output
        4. TIM:
            ATIM1 CH1 output, periodically triggered DMA burst transmission, loading CCDAT1，CCDAT2，CCDAT3，CCDAT4，CCDAT5，CCDAT6，PSC, AR registers, changing duty cycle, period and repeat counter
        5. DMA:
            DMA1_CH5 channel normal mode carry 8 words SRC_Buffer[8] variable to ATIM1 registers
     Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveform of ATIM1 CH1
         2. After the first cycle of ATIM1 is over, the following waveforms are the waveforms of changing cycle and duty cycle of DMA transport
         3. Modifying DmaAgain=1 in the debug state will again carry the 8 word SRC_Buffer[8] variable to the TIM1 DMA register

4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
