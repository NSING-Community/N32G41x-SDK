1、功能说明
    该测例演示了两块开发板之间通过USART2 RS485模式（DE信号自动控制）进行中断通信。
    Slave端等待接收Master端发送的数据，接收完成后比较接收数据与预期数据，
    比较结果通过串口打印输出。接收完成后Slave回传数据给Master。

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
    The Slave waits to receive data from the Master. After reception, the received
    data is compared with the expected data, and the result is printed via serial port.
    After receiving, the Slave echoes the data back to the Master.

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

    Test steps:
    - Compile and download the Master and Slave demos to two separate boards
    - Reset the Slave board first, then reset the Master board
    - Viewing Serial Port Printing Information, PASSED for the test passed, FAILED for the test exception

4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first
    The Slave board must be powered on first, then the Master.
