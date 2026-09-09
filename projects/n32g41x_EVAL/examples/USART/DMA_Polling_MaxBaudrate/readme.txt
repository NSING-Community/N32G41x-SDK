1. 功能说明
    USART DMA轮询模式示例。
    USARTy(USART1)和USARTz(USART4)通过DMA方式进行双向数据传输。
    - USARTy通过DMA发送TxBuffer1数据到USARTz
    - USARTz通过DMA发送TxBuffer2数据到USARTy
    - 轮询等待DMA传输完成标志
    - 比较接收数据与发送数据是否一致

2. 使用环境
    软件开发环境：
        - KEIL MDK-ARM V5.34.0.0
        - IAR EWARM 8.50.1
    硬件环境：
        - N32G41x评估板

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. 使用说明
    系统时钟配置如下：
        - HSI+PLL
        - 系统时钟: N32G412:80MHz   N32G415:96MHz
    
    UART配置如下：
    - 波特率 = 10000000 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 8倍过采样
    
    DMA通道分配：
        - DMA_CH1: USART1_TX
        - DMA_CH2: USART1_RX
        - DMA_CH3: USART4_TX
        - DMA_CH4: USART4_RX
    
    连接方式：
        - USARTy_TX(PA9)  -> USARTz_RX(PA0)
        - USARTz_TX(PA1)  -> USARTy_RX(PA10)
    编译并下载程序到评估板，运行后检查TransferStatus1和TransferStatus2的值。
    若均为PASSED，则说明DMA传输成功。

4. 注意事项 
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function Description
    USART DMA Polling mode example.
    USARTy(USART1) and USARTz(USART4) perform bidirectional data transfer via DMA.
    - USARTy sends TxBuffer1 to USARTz via DMA
    - USARTz sends TxBuffer2 to USARTy via DMA
    - Polls DMA transfer complete flags
    - Compares received data with sent data for verification

2. Environment
    Software:
        - KEIL MDK-ARM V5.34.0.0
        - IAR EWARM 8.50.1
    Hardware:
        - N32G41x evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use
    The system clock configuration is as follows:
        - HSI+PLL
        - SystemClock: N32G412:80MHz   N32G415:96MHz

    USART configuration:
    - BaudRate = 10000000 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled
    - Receiver and transmitter enabled
    - 8 times oversampling
    
    DMA channel assignment:
        - DMA_CH1: USART1_TX
        - DMA_CH2: USART1_RX
        - DMA_CH3: USART4_TX
        - DMA_CH4: USART4_RX
        
    Connections:
        - USARTy_TX(PA9)  -> USARTz_RX(PA0)
        - USARTz_TX(PA1)  -> USARTy_RX(PA10)
    Compile and download the program to the evaluation board. After running,
    check the values of TransferStatus1 and TransferStatus2.
    If both are PASSED, the DMA transfer was successful.
    
4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
