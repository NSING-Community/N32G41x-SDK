1、功能说明
    1、GTIM1 CH2上升沿输入捕获计算频率。

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M
        3、中断：
            GTIM1 CH2 上升沿捕获中断打开
        4、端口配置：
            PA1选择为GTIM1 CH2输入
            PA3选择为IO 输出

    使用方法：
        1、编译后打开调试模式，连接PA3与PA1，将变量TIMxFreq添加到watch窗口
        2、通过调试窗口修改gOnePulsEn为1，PA3会有电平翻转
        3、程序控制PA3电平翻转后，查看TIMxFreq计算的频率值

4、注意事项
    1、默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。
       如果PA9和PA10未用作串行端口，必须拔掉串行端口跳线帽。


1. Function description
    1.GTIM1 CH2 rising edge input capture to calculate frequency.

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
            N32G412: HSI=16M,PLL=80M,AHB=80M,APB1=40M,APB2=80M,GTIM1_CLK=80M
            N32G415: HSI=16M,PLL=96M,AHB=96M,APB1=48M,APB2=96M,GTIM1_CLK=96M
         3. Interruption:
             GTIM1 CH2 rising edge interrupt is turned on
         4. Port configuration:
             PA1 is selected as GTIM1 CH2 input
             PA3 is selected as IO output
    Instructions:
         1. After compiling, open the debug mode, connect PA3 and PA1, and add the variable TIMxFreq to the watch window
         2. Modify gOnePulsEn to 1 in the debug mode and flip the PA3 pin level
         3. After the program controls the level of PA3 to flip, check the frequency value calculated by TIMxFreq
4. Attention
    1. By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK.
       If PA9 and PA10 are not used as serial ports, the serial port jumper caps must be unplugged.
