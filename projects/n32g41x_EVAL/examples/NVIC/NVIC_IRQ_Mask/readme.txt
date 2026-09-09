1、功能说明
    此例程演示NVIC中断屏蔽功能。通过__disable_irq()和__enable_irq()控制全局中断的
    使能和禁止，展示中断屏蔽对定时器中断和外部按键中断的影响。

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
        5、GTIM3：定时器周期中断，用于产生周期性中断
        6、NVIC：
            EXTI4中断抢占优先级1，子优先级0
            GTIM3中断抢占优先级0，子优先级0

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、正常运行时，串口周期性打印GTIM3定时器中断信息。
        3、按下按键触发外部中断，Key_Status切换为ENABLE，
           随后调用__disable_irq()屏蔽所有中断，此时定时器中断停止打印。
        4、再次按下并释放按键后，调用__enable_irq()恢复中断，
           定时器中断恢复打印。

4、注意事项
    无


1. Function description

    This example demonstrates NVIC interrupt mask functionality. It uses
    __disable_irq() and __enable_irq() to control global interrupt enable and
    disable, showing the effect of interrupt masking on timer interrupt and
    external key interrupt.

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
        5. GTIM3: Timer periodic interrupt, used to generate periodic interrupts
        6. NVIC:
            EXTI4 interrupt preemption priority 1, sub-priority 0
            GTIM3 interrupt preemption priority 0, sub-priority 0

    Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. During normal operation, GTIM3 timer interrupt information is periodically
           printed via serial port.
        3. Press the key to trigger external interrupt, Key_Status toggles to ENABLE,
           then __disable_irq() is called to mask all interrupts, timer interrupt
           printing stops.
        4. Press and release the key again, __enable_irq() is called to restore
           interrupts, timer interrupt printing resumes.

4. Notes
    None
