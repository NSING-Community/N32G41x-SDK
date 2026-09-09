1、功能说明
    此例程配置并演示NVIC中断向量表重定位功能。通过按键触发外部中断，
    将中断向量表从FLASH重定位到SRAM，展示NVIC中断向量表的动态调整。

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
        5、NVIC：EXTI4中断抢占优先级0

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、初始状态下，中断向量表位于FLASH中。
        3、按下按键触发外部中断，程序将中断向量表重定位到SRAM，
           并通过串口打印相关信息。

4、注意事项
    无


1. Function description

    This example configures and demonstrates NVIC interrupt vector table relocation.
    By pressing the key to trigger an external interrupt, the interrupt vector table
    is relocated from FLASH to SRAM, demonstrating the dynamic adjustment of the
    NVIC interrupt vector table.

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
        5. NVIC: EXTI4 interrupt preemption priority 0

    Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. Initially, the interrupt vector table is located in FLASH.
        3. Press the key to trigger external interrupt, the program relocates the
           interrupt vector table to SRAM and prints related information via serial port.

4. Notes
    None
