1、功能说明

    该测例演示了USARTy与USARTz间通过查询检测标志位实现的基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz接收数据存至RxBuffer2。
    随后，USARTz发送TxBuffer2数据至USARTy，USARTy接收数据存至RxBuffer1。
    程序通过TransferStatus1和TransferStatus2对比发送和接收缓冲区，
    PASSED表示测试通过，FAILED表示测试异常。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1

    硬件环境：
        - N32G41x评估板

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


    引脚连接：
    N32G412：
        - USART1_TX(PA9)  <------->  USART2_RX(PA3)
        - USART1_RX(PA10) <------->  USART2_TX(PA2)
    N32G415:
        - USART1_TX(PA9)  <------->  USART2_RX(PA3)
        - USART1_RX(PA8) <------->  USART2_TX(PA2)

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常

4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function description

    This test case demonstrates basic communication between USARTy and USARTz
    using polling flags.
    First, USARTy sends TxBuffer1 to USARTz, and USARTz stores the received
    data into RxBuffer2.
    Then, USARTz sends TxBuffer2 to USARTy, and USARTy stores the received
    data into RxBuffer1.
    TransferStatus1 and TransferStatus2 compare the sent/received buffers.
    PASSED means success, FAILED means mismatch.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1

    Hardware:
        - N32G41x evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System configuration:
        HSI+PLL
        SystemClock: N32G412:80MHz   N32G415:96MHz

    USART configuration:
        - Baud rate = 115200 baud
        - Word length = 8 data bits
        - Stop bits = 1
        - Parity = none
		- Hardware flow control disabled
        - RX and TX enabled
        - Oversampling = 16

    External wiring:
    N32G412：
        - USART1_TX(PA9)  <------->  USART2_RX(PA3)
        - USART1_RX(PA10) <------->  USART2_TX(PA2)
    N32G415:
        - USART1_TX(PA9)  <------->  USART2_RX(PA3)
        - USART1_RX(PA8) <------->  USART2_TX(PA2)

    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal

4. Notes

    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
