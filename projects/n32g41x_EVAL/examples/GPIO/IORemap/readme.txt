1、功能说明
    此例程展示了SWD GPIO 用作普通IO。

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
            LED1(PA1) LED2(PA7) KEY1(PA4)

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、检查KEY1:
           如果KEY1按下, LED1常亮, PA13/PA14依次翻转，可接LED3观察闪烁;
           如果KEY1未按下, 则LED2常亮

4、注意事项
    N32G41x没有JTAG接口，仅支持SWD调试（PA14 SWCLK, PA13 SWDIO）。
    N32G41x通过per-pin的AF映射方式(GPIO_ConfigPinRemap)来实现SWD引脚的释放与恢复。
    下载代码后需要将J5上的SWDIO和SWDCLK跳线帽取下。
    
1. Function description

    This example shows SWD GPIOs used as general IO.

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
            LED1(PA1) LED2(PA7) KEY1(PA4)

     Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. Check KEY1: 
           If KEY1 is pressed, LED1 stays on, and PA13/PA14 toggle in sequence, connect LED3 to observe blinking; 
           if KEY1 is not pressed, LED2 stays on

4. Notes
    N32G41x does not have a JTAG interface, only SWD debugging is supported (PA14 SWCLK, PA13 SWDIO).
    N32G41x uses per-pin AF mapping (GPIO_ConfigPinRemap) to release and restore SWD pins.
    After downloading the code, you need to remove the jumper caps from SWDIO and SWDCLK on J5.
