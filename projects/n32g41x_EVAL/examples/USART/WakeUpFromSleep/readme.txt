1、功能说明
    该测例演示了通过USART1中断从SLEEP模式唤醒MCU。
    SLEEP模式下CPU停止，所有外设（包括USART1）保持运行。
    正常运行时，USART1每秒发送一个递增数据（115200 baud）。
    当接收到0x55时，使能USART1接收中断，通过WFI指令进入SLEEP模式。
    在SLEEP模式下，USART1接收到数据后产生RXDNE中断，通过NVIC唤醒CPU。
    唤醒后关闭接收中断，继续正常工作。

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1

    硬件环境：N32G41x评估板

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统时钟配置如下：
        - HSI+PLL
        - 系统时钟: N32G412:80MHz   N32G415:96MHz

    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 16倍过采样

    USART引脚连接如下：
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA10  -> USART1_RX   (GPIO_AF4)

    外部连线：
        USART1_TX(PA9)  <-------> PC_RX
        USART1_RX(PA10) <-------> PC_TX

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 通过串口工具可看到每秒打印递增数据
    - 下发0x55，打印暂停（进入SLEEP模式）
    - 再下发任意数据，USART1中断唤醒CPU，打印继续

4、注意事项
    SLEEP模式下所有时钟保持运行，唤醒无需重新配置系统时钟

1. Function Description
    This example demonstrates waking up the MCU from SLEEP mode via USART1 interrupt.
    In SLEEP mode the CPU stops, but all peripherals (including USART1) keep running.
    During normal operation, USART1 sends incremental data every second (115200 baud).
    When 0x55 is received, USART1 RXDNE interrupt is enabled and MCU enters SLEEP mode via WFI.
    In SLEEP mode, when USART1 receives data, the RXDNE interrupt wakes the CPU via NVIC.
    After wakeup, the RXDNE interrupt is disabled and normal operation resumes.

2. Environment
    Software: KEIL MDK-ARM V5.34.0.0
              IAR EWARM 8.50.1
    Hardware: N32G41x_EVAL evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    System Clock Configuration:
        - HSI+PLL
        - SystemClock: N32G412:80MHz   N32G415:96MHz

    USART configuration:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled
    - Receiver and transmitter enabled
    - 16x oversampling

    Pin connections:
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA10  -> USART1_RX   (GPIO_AF4)

    External wiring:
        USART1_TX(PA9)  <-------> PC_RX
        USART1_RX(PA10) <-------> PC_TX

    Test steps:
    - Compile the demo in KEIL, download to MCU
    - Use serial tool to observe incremental data printed every second
    - Send 0x55, printing pauses (MCU enters SLEEP mode)
    - Send any data, USART1 interrupt wakes CPU, printing resumes

4. Notes
    In SLEEP mode all clocks keep running, no system clock reconfiguration needed after wakeup
