1、功能说明
    该测例演示了通过USART1低功耗唤醒事件从STOP模式唤醒MCU。
    STOP模式下系统时钟关闭，USART1使用LSI时钟保持工作。
    USART1接收到一帧数据后，RXDNE产生唤醒事件至EXTI_LINE24，
    MCU通过WFE指令退出STOP模式。
    唤醒后重新配置GPIO和USART1，LED1点亮1秒作为唤醒指示。

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
    - 波特率 = 1200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    - 低功耗时钟源 = LSI

    USART引脚连接如下：
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA10  -> USART1_RX   (GPIO_AF4)

    外部连线：
        USART1_TX(PA9)  <-------> PC_RX
        USART1_RX(PA10) <-------> PC_TX

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位后LED1保持点亮5秒，作为上电提示和下载窗口；随后熄灭
    - MCU配置USART1低功耗唤醒后进入STOP模式
    - 串口工具配置为1200-8-N-1，下发0x55
    - MCU退出STOP模式，LED1点亮1秒
    - LED1熄灭后MCU再次进入STOP模式

4、注意事项
    

1. Function Description
    This example demonstrates waking up the MCU from STOP mode through the USART1 low-power wakeup event.
    In STOP mode the system clock is stopped and USART1 keeps running with the LSI clock.
    After USART1 receives one frame of data, RXDNE generates a wakeup event to EXTI_LINE24,
    and the MCU exits STOP mode through the WFE instruction.
    After wakeup, GPIO and USART1 are reconfigured and LED1 turns on for one second as wakeup indication.

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
    - BaudRate = 1200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled
    - Receiver and transmitter enabled
    - 16x oversampling
    - Low-power clock source = LSI

    Pin connections:
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA10  -> USART1_RX   (GPIO_AF4)

    External wiring:
        USART1_TX(PA9)  <-------> PC_RX
        USART1_RX(PA10) <-------> PC_TX

    Test steps:
    - Compile the demo in KEIL, download to MCU
    - After reset, LED1 stays on for five seconds as the power-up indication and download window, then turns off
    - The MCU configures USART1 low-power wakeup and enters STOP mode
    - Configure the serial tool as 1200-8-N-1 and send 0x55
    - The MCU exits STOP mode and LED1 turns on for one second
    - After LED1 turns off, the MCU enters STOP mode again

4. Notes
    

