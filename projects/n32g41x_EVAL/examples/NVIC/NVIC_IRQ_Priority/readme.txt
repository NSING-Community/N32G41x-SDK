1、功能说明
    此例程配置并演示NVIC优先级设置。通过按键外部中断和SysTick中断的优先级抢占关系，
    展示NVIC中断优先级的配置和动态调整。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1

    芯片支持：
        N32G412
        N32G415

3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、GPIO：
            KEY(PA4) 配置为输入模式，外部中断线EXTI_LINE4
        4、EXTI：PA4外部中断，下降沿触发
        5、NVIC：EXTI4中断抢占优先级1，SysTick初始抢占优先级0

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、正常运行时，串口打印SysTick中断信息和Key_Status状态。
        3、按下按键触发外部中断，当EXTI4中断和SysTick中断同时触发时，
           修改SysTick中断优先级为2，并打印相关信息。

4、注意事项
    无


1. Function description

    This example configures and demonstrates NVIC priority settings. It shows
    the configuration and dynamic adjustment of NVIC interrupt priorities through
    the preemption relationship between key external interrupt and SysTick interrupt.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Supported chips:
        N32G412
        N32G415

3. How to use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. GPIO:
            KEY(PA4) configured as input mode, external interrupt line EXTI_LINE4
        4. EXTI: PA4 external interrupt, falling edge trigger
        5. NVIC: EXTI4 interrupt preemption priority 1, SysTick initial preemption priority 0

    Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. During normal operation, SysTick interrupt information and Key_Status are printed via serial port.
        3. Press the key to trigger external interrupt. When both EXTI4 and SysTick interrupts
           are triggered simultaneously, the SysTick interrupt priority is changed to 2 and
           related information is printed.

4. Notes
    None
