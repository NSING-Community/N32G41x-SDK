1、功能说明

    该测例演示了USARTy与USARTz间通过查询检测标识，实现半双工模式的基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz接收数据存至RxBuffer2。
    随后，USARTz发送TxBuffer2数据至USARTy，USARTy接收数据存至RxBuffer1。
    最后，分别比较两组接收数据与发送数据，比较结果存入TransferStatus1变量和TransferStatus2变量。
    USARTy和USARTz可以是USART1和USART2。


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
    - USART1_Tx.PA9   <------->   USART2_Tx.PA2

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function description

    This test example demonstrates the basic communication between USARTy and USARTz
    by querying and detecting flags in half-duplex mode.
    First, USARTy sends TxBuffer1 data to USARTz, and USARTz receives data and stores it in RxBuffer2.
    Subsequently, USARTz sends TxBuffer2 data to USARTy, and USARTy receives data to RxBuffer1.
    Finally, compare the two groups of received data and sent data respectively,
    and store the comparison results in the TransferStatus1 variable and the TransferStatus2 variable.
    USARTy and USARTz can be USART1 and USART2.


2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware: N32G41x evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    The system clock configuration is as follows:
        - HSI+PLL
        - SystemClock: N32G412:80MHz   N32G415:96MHz

    The USART configuration is as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
	- Hardware flow control disabled
    - Receiver and transmitter enabled
    - 16 times oversampling

    The USART pin connections are as follows:
    - USART1_Tx.PA9   <------->   USART2_Tx.PA2

    Test steps and phenomena:
    - After the Demo is compiled in the KEIL environment, download it to the MCU
    - Reset and run, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal


4. Attention

    The MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
