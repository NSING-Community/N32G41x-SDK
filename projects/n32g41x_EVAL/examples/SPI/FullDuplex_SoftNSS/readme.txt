1、功能说明
    此例程展示了SPI全双工软件NSS模式收发数据。

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
        3、SPI1配置（主机）：
            SCK--PA5、MISO--PA6、MOSI--PA7
        4、SPI2配置（从机）：
            SCK--PB13、MISO--PB14、MOSI--PB15
        5、USART1：TX--PA9，波特率115200

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、第一阶段：SPI1作为主机，SPI2作为从机，全双工传输数据，传输完成后检查数据正确性。
        3、第二阶段：SPI1作为从机，SPI2作为主机，全双工传输数据，传输完成后检查数据正确性。
        4、通过串口查看打印信息，验证TransferStatus1~4状态为PASSED。

4、注意事项
    1、SPI1的SCK、MISO、MOSI与SPI2的SCK、MISO、MOSI需要交叉连接。


1. Function description
    This example demonstrates SPI full-duplex data transfer with software NSS mode.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Chip support: 
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. SPI1 configuration (Master):
            SCK--PA5, MISO--PA6, MOSI--PA7
        4. SPI2 configuration (Slave):
            SCK--PB13, MISO--PB14, MOSI--PB15
        5. USART1: TX--PA9, baud rate 115200

    Instructions:
        1. Compile and download the program to the development board, then reset and run.
        2. Phase 1: SPI1 as master, SPI2 as slave, full-duplex data transfer, check data correctness after transfer.
        3. Phase 2: SPI1 as slave, SPI2 as master, full-duplex data transfer, check data correctness after transfer.
        4. View the print information from the serial port and verify that TransferStatus1~4 are PASSED.

4. Attention
    1. SCK, MISO, MOSI of SPI1 and SPI2 need to be cross-connected.
