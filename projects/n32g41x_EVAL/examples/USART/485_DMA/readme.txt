1、功能说明
    该测例演示了USARTy与USARTz间通过DMA实现的RS485通信。
    USARTy和USARTz均使能RS485 DE信号自动控制。
    DMA传输TxBuffer1数据至USARTy发送数据寄存器，随后数据发送至USARTz。
    USARTz通过DMA接收数据存至RxBuffer2。
    比较收、发数据，比较结果存入TransferStatus2变量。

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
        HSI+PLL
        系统时钟: N32G412:80MHz   N32G415:96MHz

    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能
    - 硬件流控制禁用
    - 16倍过采样
    - RS485 DE信号使能，DE极性低有效

    DMA通道分配：
        - DMA_CH1: USART1_TX
        - DMA_CH4: USART2_RX

    USART引脚连接如下：
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA12  -> USART1_DE   (GPIO_AF4)
        PA3   -> USART2_RX   (GPIO_AF4)
        PA1   -> USART2_DE   (GPIO_AF4)

    外部连线：
        USART1_TX(PA9) <-------> USART2_RX(PA3)

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看变量TransferStatus2，其中，PASSED为测试通过，FAILED为测试异常

4、注意事项
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开

1. Function Description
    This example demonstrates RS485 communication between USARTy and USARTz via DMA.
    Both USARTy and USARTz have RS485 DE signal auto-control enabled.
    DMA transfers TxBuffer1 data to USARTy transmit data register, then data is sent to USARTz.
    USARTz receives data via DMA into RxBuffer2.
    The received data is compared with the sent data, and the result is stored in TransferStatus2.

2. Environment
    Software: KEIL MDK-ARM V5.34.0.0
              IAR EWARM 8.50.1
    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    The system clock configuration is as follows:
        - HSI+PLL
        - SystemClock: N32G412:80MHz   N32G415:96MHz
    
    USART configuration:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled
    - Receiver and transmitter enabled
    - 16 times oversampling
    - RS485 DE signal enabled, DE polarity active low

    DMA channel assignment:
        - DMA_CH1: USART1_TX
        - DMA_CH4: USART2_RX

    Pin connections:
        PA9   -> USART1_TX   (GPIO_AF4/AF0)
        PA12  -> USART1_DE   (GPIO_AF4)
        PA3   -> USART2_RX   (GPIO_AF4)
        PA1   -> USART2_DE   (GPIO_AF4)

    External wiring:
        USART1_TX(PA9) <-------> USART2_RX(PA3)

    Test steps:
    - Compile the demo in KEIL, download to MCU
    - Reset and run, check variable TransferStatus2: PASSED means test OK, FAILED means test error

4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
