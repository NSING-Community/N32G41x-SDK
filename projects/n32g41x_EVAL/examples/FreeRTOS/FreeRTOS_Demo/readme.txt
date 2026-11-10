1、功能说明
    此例程是N32G41x的FreeRTOS最小移植模板，创建LED闪烁任务和串口打印任务。
    内核版本：FreeRTOS Kernel V11.3.1（FreeRTOSv202604.01-LTS）。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34（ARM Compiler 5/6均可）
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
            LED1(PA1)
        4、串口：USART1，PA9(TX) PA10(RX)，115200

    任务说明
        1、LedTask   优先级2，栈128字，每500ms翻转一次LED1。
        2、PrintTask 优先级3，栈256字，每1000ms打印一次计数与剩余栈。

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、LED1以500ms周期闪烁。
        3、串口115200每秒输出一行PrintTask计数与栈余量。

4、注意事项
    1、FreeRTOS配置在inc/FreeRTOSConfig.h，heap大小等参数在此调整。
    2、任务中必须使用vTaskDelay()让出CPU，不能使用bsp的SysTick_Delay_Ms()/
       SysTick_Delay_Us()，后者会改写SysTick并关闭其中断，导致系统节拍丢失。
    3、SVC_Handler/PendSV_Handler由FreeRTOS port提供，src/n32g41x_it.c中不要
       定义，否则重复定义导致链接失败；SysTick_Handler保留，转发给
       xPortSysTickHandler。
    4、N32G41x无FPU无MPU，必须使用ARM_CM3 port。src/port_select.c与
       inc/portmacro.h按编译器自动分发port（已覆盖MDK V5/V6、IAR、GCC四套），
       MDK的ARM Compiler下拉框可在AC5/AC6之间自由切换；工程中不要再把具体
       port目录加入include路径。
    5、调用...FromISR系列API的中断，其抢占优先级数值必须不小于5
       （configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY），且NVIC使用
       NVIC_PriorityGroup_4。
    6、configCHECK_FOR_STACK_OVERFLOW设为2、configUSE_MALLOC_FAILED_HOOK设为1，
       两个钩子函数已在src/main.c中实现。


1. Function description

    This example is a minimal FreeRTOS porting template for N32G41x. It creates
    an LED blinking task and a USART printing task.
    Kernel version: FreeRTOS Kernel V11.3.1 (FreeRTOSv202604.01-LTS).

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34 (ARM Compiler 5 or 6)
                                      IAR EWARM 8.50.1

    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System clock frequency: N32G412:80MHz   N32G415:96MHz
        3. GPIO:
            LED1(PA1)
        4. USART: USART1, PA9(TX) PA10(RX), 115200

    Tasks:
        1. LedTask   priority 2, stack 128 words, toggles LED1 every 500ms.
        2. PrintTask priority 3, stack 256 words, prints counter and stack every 1000ms.

     Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. LED1 blinks at 500ms period.
        3. The serial port outputs one line per second at 115200.

4. Notes
    1. The FreeRTOS configuration is in inc/FreeRTOSConfig.h; the heap size and
       other parameters are adjusted there.
    2. Always use vTaskDelay() to give up the CPU inside a task. Do NOT use the BSP
       SysTick_Delay_Ms() / SysTick_Delay_Us(): they reprogram SysTick and disable
       its interrupt, which would break the FreeRTOS tick.
    3. SVC_Handler / PendSV_Handler are provided by the FreeRTOS port and must not
       be defined in src/n32g41x_it.c, otherwise the link fails with duplicate
       symbols. SysTick_Handler is kept and forwards to xPortSysTickHandler.
    4. N32G41x has no FPU and no MPU, so the ARM_CM3 port must be used.
       src/port_select.c and inc/portmacro.h dispatch the port automatically by
       compiler (covering MDK V5/V6, IAR and GCC), so the Keil ARM Compiler
       drop-down can be switched freely between AC5 and AC6; do not add a
       concrete port directory to the include path.
    5. Interrupts that call the ...FromISR API must have a preemption priority
       numerically >= 5 (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY), and the
       NVIC must be configured with NVIC_PriorityGroup_4.
    6. configCHECK_FOR_STACK_OVERFLOW is 2 and configUSE_MALLOC_FAILED_HOOK is 1;
       both hook functions are implemented in src/main.c.
