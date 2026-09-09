1、功能说明
    此例程展示了IO控制LED闪烁。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1 

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、GPIO：
            LED1(PA1) LED2(PA7) LED3(PB1)

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、LED1和LED3先闪烁4次，然后LED1、LED2、LED3依次轮流点亮循环。

4、注意事项
    无

    
1. Function description

    This example shows IO control LED blinking.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1 

    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. GPIO:
            LED1(PA1) LED2(PA7) LED3(PB1)

     Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. LED1 and LED3 blink 4 times first, then LED1, LED2, LED3 light up in sequence and repeat.

4. Notes
    None