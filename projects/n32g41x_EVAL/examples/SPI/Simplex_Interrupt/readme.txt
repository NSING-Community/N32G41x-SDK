1、功能说明
    此例程展示了SPI单线中断模式收发数据。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、SPI1配置（主机，单线发送）：
            SCK--PA5、MOSI--PA7
        4、SPI2配置（从机，单线接收）：
            SCK--PB13、MISO--PB14
        5、USART1：TX--PA9，波特率115200

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、SPI1主机通过TXE中断发送数据，SPI2从机通过RXNE中断接收数据。
        3、传输完成后，通过串口查看TransferStatus状态为PASSED。

4、注意事项
    1、"单线"数据线在主设备端为MOSI引脚，在从设备端为MISO引脚。
    2、主机MOSI连接从机MISO。


1. Function description
    This example demonstrates SPI simplex data transfer using interrupt mode.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Supported chips:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. SPI1 configuration (Master, single-line TX):
            SCK--PA5, MOSI--PA7
        4. SPI2 configuration (Slave, single-line RX):
            SCK--PB13, MISO--PB14
        5. USART1: TX--PA9, baud rate 115200

    Instructions:
        1. Compile and download the program to the development board, then reset and run.
        2. SPI1 master sends data via TXE interrupt, SPI2 slave receives data via RXNE interrupt.
        3. After transfer completes, view TransferStatus status as PASSED from serial port.

4. Attention
    1. The "single line" data line is MOSI pin on the master device side and MISO pin on the slave device side.
    2. Master MOSI connects to Slave MISO.
