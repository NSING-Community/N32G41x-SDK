1、功能说明
    本示例演示USART同步模式与SPI从机之间的数据通信。
    USART1工作在同步模式（时钟输出），SPI1工作在从机模式。
    USART1先发送数据给SPI1，再从SPI1接收数据，最后比较收发结果。

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：N32G41x_EVAL评估板

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
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - 时钟使能
    - 时钟极性：不对外发送时保持低电平
    - 时钟相位：在第二个时钟边沿采样第一个数据
    - 最后一位时钟脉冲：最后一位数据的时钟脉冲从CK输出
 
    SPI配置如下：
    - 方向 = “双线双向”模式
    - 模式 = 从模式
    - 数据大小 = 8位数据帧
    - CPOL = 空闲状态时，时钟保持低电平
    - CPHA = 数据采样从第二个时钟边沿开始
    - NSS = 启用软件从设备管理
    - 第1位 = 第1位为LSB

        USART引脚连接如下： 
    - USART1_Tx.PA9 <-------> SPI1_MOSI.PA7
    - USART1_Rx.PA10 <-------> SPI1_MISO.PA6
    - USART1_Clk.PA8 <-------> SPI1_SCK.PA5 

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 将串口打印跳帽拔除
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常

4、注意事项
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开

1. Function Description
    This example demonstrates data communication between USART synchronous mode and SPI slave.
    USART1 operates in synchronous mode (clock output), SPI1 operates in slave mode.
    USART1 first sends data to SPI1, then receives data from SPI1, and finally compares results.

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
            HSI+PLL
            SystemClock: N32G412:80MHz   N32G415:96MHz

 USART is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enabled
    - Clock enable
    - Clock polarity: keep low when not sending out
    - Clock Phase: The first data is sampled on the second clock edge
    - Last bit clock pulse: The clock pulse of the last bit of data is output from CK
    
    The SPI configuration is as follows:
    - Direction = "Two-Line Bidirectional" mode
    - mode = slave mode
    - data size = 8-bit data frame
    - CPOL = when idle, the clock remains low
    - CPHA = data sampling starts on second clock edge
    - NSS = Enable Software Slave Device Management
    - 1st bit = 1st bit is LSB
  
    The USART pins are connected as follows:
    - USART1_Tx.PA9 <-------> SPI1_MOSI.PA7
    - USART1_Rx.PA10 <-------> SPI1_MISO.PA6
    - USART1_Clk.PA8 <-------> SPI1_SCK.PA5

    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Remove the serial print jump cap
    - Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, where,
      PASSED is the test passed, FAILED is the test abnormal

4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first

