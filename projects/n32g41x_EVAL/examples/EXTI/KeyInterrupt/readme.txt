1、功能说明
    演示GPIO外部中断功能，KEY1(PA4)触发EXTI4中断，KEY2(PA5)触发EXTI5中断，
    按下不同按键切换不同LED闪烁。

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
        1、时钟源：HSI+PLL
        2、时钟频率：N32G412:80MHz   N32G415:96MHz
        3、GPIO：
            PA1(LED1), PA7(LED2), PA4(KEY1), PA5(KEY2)
        4、打印：PA9 - baud rate 115200

    测试步骤与现象：
        1、编译后将程序下载到开发板并复位运行，LED1闪烁，串口打印"EXTI key interrupt demo!"。
        2、按下KEY1(PA4)触发EXTI4中断，LED1闪烁。
        3、按下KEY2(PA5)触发EXTI5中断，LED2闪烁。
        4、每次按键触发中断时，串口打印当前按键和LED信息。

4、注意事项
    KEY1(PA4) -> EXTI_LINE4 -> EXTI4_IRQn
    KEY2(PA5) -> EXTI_LINE5 -> EXTI5_9_IRQn


1. Function description
    Demonstrates the GPIO external interrupt function. KEY1(PA4) triggers the EXTI4
    interrupt, KEY2(PA5) triggers the EXTI5 interrupt. Pressing different keys switches
    different LEDs to blink.

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Chip support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions for use
    System Configuration:
        1. Clock source: HSI+PLL
        2. Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. GPIO:
            PA1(LED1), PA7(LED2), PA4(KEY1), PA5(KEY2)
        4. printf: PA9 - baud rate 115200

    Test steps and phenomenon:
        1. Compile and download the program to the development board and reset.
           LED1 blinks and the serial port prints "EXTI key interrupt demo!".
        2. Press KEY1(PA4) to trigger the EXTI4 interrupt, LED1 blinks.
        3. Press KEY2(PA5) to trigger the EXTI5 interrupt, LED2 blinks.
        4. Each time a key triggers an interrupt, the serial port prints the current
           key and LED information.

4. Attention
    KEY1(PA4) -> EXTI_LINE4 -> EXTI4_IRQn
    KEY2(PA5) -> EXTI_LINE5 -> EXTI5_9_IRQn
