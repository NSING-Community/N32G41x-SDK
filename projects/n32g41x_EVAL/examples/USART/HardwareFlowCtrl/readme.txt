1. 功能说明
    USART硬件流控模式示例。
    USARTy(USART1)和USARTz(USART2)使用CTS/RTS硬件流控进行双向数据传输。
    - 连接方式：USARTy_RTS -> USARTz_CTS, USARTz_RTS -> USARTy_CTS
    - USARTy发送TxBuffer1到USARTz，USARTz发送TxBuffer2到USARTy
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

    系统时钟配置：
        HSI+PLL
        SystemClock: N32G412:80MHz   N32G415:96MHz
            
    USARTy配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - CTS硬件流控制使能
    - 发送器使能   
    
    USARTz配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - RTS硬件流控制使能
    - 接收器使能   
    
    连接方式：
        - USARTy_TX(PA9)   -> USARTz_RX(PA3)
        - USARTz_TX(PA2)   -> USARTy_RX(PA10)
        - USARTy_RTS(PA12) -> USARTz_CTS(PA0)
        - USARTz_RTS(PA1)  -> USARTy_CTS(PA11)
            
    测试步骤与现象：
    - 编译并下载程序到评估板，运行后检查TransferStatus1和TransferStatus2的值。
    - 若均为PASSED，则说明硬件流控传输成功。

4. 注意事项
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开
    需要连接4根数据线(TX/RX)和4根流控线(RTS/CTS)。


1. Function Description
    USART Hardware Flow Control mode example.
    USARTy(USART1) and USARTz(USART2) perform bidirectional data transfer
    using CTS/RTS hardware flow control.
    - Connections: USARTy_RTS -> USARTz_CTS, USARTz_RTS -> USARTy_CTS
    - USARTy sends TxBuffer1 to USARTz, USARTz sends TxBuffer2 to USARTy
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

3. Usage
    System Clock Configuration:
        HSI+PLL
        SystemClock: N32G412:80MHz   N32G415:96MHz
               
    USARTy is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - CTS hardware flow control enabled
    - Transmitter enable
    
    USARTz is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - RTS hardware flow control enabled
    - Receiver enable
    
    Connections:
        - USARTy_TX(PA9)   -> USARTz_RX(PA3)
        - USARTz_TX(PA2)   -> USARTy_RX(PA10)
        - USARTy_RTS(PA12) -> USARTz_CTS(PA0)
        - USARTz_RTS(PA1)  -> USARTy_CTS(PA11)
        
    Test steps and phenomena:
    - Compile and download the program to the evaluation board. After running,
      check the values of TransferStatus1 and TransferStatus2.
    - If both are PASSED, the hardware flow control transfer was successful.

4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
    Requires 4 data lines (TX/RX) and 4 flow control lines (RTS/CTS).
