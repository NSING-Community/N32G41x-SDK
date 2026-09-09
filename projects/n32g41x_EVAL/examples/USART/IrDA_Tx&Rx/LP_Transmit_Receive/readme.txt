1、功能说明

    该测例演示了USARTy与USARTz间实现串行IrDA低功耗模式红外解码功能的基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz通过中断接收数据存至RxBuffer1。
    随后，比较接收数据与发送数据，比较结果存入TransferStatus变量。


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
    - HSI
    - 系统时钟: 16MHz

    USART配置如下：
    - 波特率 = 600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 发送器/接收器使能
    - 16倍过采样
    - IrDA低功耗模式使能

    USART引脚连接如下：
    - USART1_Tx.PA9    <------->   IrDA Transmitter
    - USART2_Rx.PA3    <------->   IrDA Receiver

    - GPIO.PB4         <------->   38kHz carrier

    测试步骤与现象：
    - 复位运行MCU，查看变量TransferStatus，其中，PASSED为测试通过，FAILED为测试异常


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function description

    This test example demonstrates the basic communication between USARTy and USARTz to realize the infrared
    decoding function of serial IrDA low-power mode.
    First, USARTy sends TxBuffer1 data to USARTz, and USARTz receives data through interrupt and stores it in RxBuffer1.
    Subsequently, compare the received data with the sent data, and the result of the comparison is stored in the
    TransferStatus variable.


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
    - HSI
    - SystemClock: 16MHz

    The USART configuration is as follows:
    - Baud rate = 600 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - Hardware flow control disabled
    - Transmitter/receiver enable
    - 16 times oversampling
    - IrDA low-power mode enable

    The USART pin connections are as follows:
    - USART1_Tx.PA9    <------->   IrDA Transmitter
    - USART2_Rx.PA3    <------->   IrDA Receiver

    - GPIO.PB4         <------->   38kHz carrier

    Test steps and phenomena:
    - Reset and run the MCU, check the variable TransferStatus, where PASSED means the test passed and FAILED means the test is abnormal


4. Attention

    The MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
