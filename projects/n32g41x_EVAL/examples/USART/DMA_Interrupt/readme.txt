1、功能说明
    USART DMA中断模式示例。
    USARTy(USART1)和USARTz(USART2)通过DMA发送数据，接收方式不同：
    - USARTy通过DMA发送TxBuffer1到USARTz，USARTz通过RXDNE中断接收到RxBuffer2
    - USARTz通过DMA发送TxBuffer2到USARTy，USARTy通过轮询RXDNE标志接收到RxBuffer1
    - 传输完成后比较接收数据与发送数据是否一致

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
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控禁用
    - 接收器和发送器使能
    - 16倍过采样
    
    USART引脚连接如下：
        - USARTy_TX(PA9)  -> USARTz_RX(PA3)
        - USARTz_TX(PA2)  -> USARTy_RX(PA10)
    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常

4. 注意事项
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function Description
    USART DMA Interrupt mode example.
    USARTy(USART1) and USARTz(USART2) send data via DMA with different receive methods:
    - USARTy sends TxBuffer1 to USARTz via DMA, USARTz receives into RxBuffer2 via RXDNE interrupt
    - USARTz sends TxBuffer2 to USARTy via DMA, USARTy receives into RxBuffer1 by polling RXDNE flag
    - After transfer, compares received data with sent data for verification

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
    
    The UART configuration is as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - Hardware flow control disabled
    - Receiver and transmitter enable
    - 16 times oversampling
    
    The UART pin connections are as follows:
        - USARTy_TX(PA9)  -> USARTz_RX(PA3)
        - USARTz_TX(PA2)  -> USARTy_RX(PA10)
        
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal

4. Attention

    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
