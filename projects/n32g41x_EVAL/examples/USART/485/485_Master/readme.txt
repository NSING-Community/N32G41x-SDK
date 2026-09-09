1、功能说明
    该测例演示了两块开发板之间通过USART2 RS485模式（DE信号自动控制）进行中断通信。
    Master端通过中断方式发送TxBuffer2数据至Slave端，Slave端接收数据存至RxBuffer2。
    接收完成后比较接收数据与发送数据，比较结果通过串口打印输出。

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1

    硬件环境：N32G41x评估板 x2 + RS485收发器模块 x2

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统时钟配置：
            HSI+PLL
            SystemClock: N32G412:80MHz   N32G415:96MHz
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - RS485 DE信号使能，DE极性低有效

    USART引脚连接如下：
    Master与Slave使用相同引脚配置：
        PA2  -> USART2_TX   (GPIO_AF4)
        PA3  -> USART2_RX   (GPIO_AF4)
        PA1  -> USART2_DE   (GPIO_AF4)

    485模块连接：
        Master A <---> Slave A
        Master B <---> Slave B

    测试步骤与现象：
    - 分别将Master与Slave的Demo编译后下载至两块开发板
    - 先复位Slave开发板，再复位Master开发板
    - 查看串口打印信息，PASSED为测试通过，FAILED为测试异常

4、注意事项
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开
    Slave开发板需先上电运行，然后Master再上电

1. Function Description
    This example demonstrates RS485 communication between two evaluation boards
    using USART2 RS485 mode (automatic DE signal control) with interrupt-driven transfer.
    The Master sends TxBuffer2 data to the Slave via interrupt. The Slave receives
    data into RxBuffer2. After reception, the received data is compared with the
    sent data, and the result is printed via serial port.

2. Environment
    Software : KEIL MDK-ARM V5.34.0.0
               IAR EWARM 8.50.1
    Hardware: N32G41x_EVAL evaluation board x2 + RS485 transceiver module x2

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    The system clock configuration is as follows:
        -HSI+PLL
        -SystemClock: N32G412:80MHz   N32G415:96MHz
	
    USART configuration:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled
    - Receiver and transmitter enabled
    - RS485 DE signal enabled, DE polarity active low

    Pin connections (same for both Master and Slave):
        PA2  -> USART2_TX   (GPIO_AF4)
        PA3  -> USART2_RX   (GPIO_AF4)
        PA1  -> USART2_DE   (GPIO_AF4)

    RS485 module connections:
        Master A <---> Slave A
        Master B <---> Slave B

   Test steps and phenomena:
    - Compile and download the Master and Slave demos to two separate boards
    - Reset the Slave board first, then reset the Master board
    - Check the serial output: PASSED means test OK, FAILED means test error

4. Notes
    Disconnect the NS-LINK MCU_TX and MCU_RX jumpers on the evaluation board
    The Slave board must be powered on first before the Master
