1、功能说明
    此例程演示SPI单线模式下，主机轮询发送数据，从机通过DMA接收数据。
    SPI1配置为主机，单线TX模式，通过轮询方式发送32字节数据。
    SPI2配置为从机，单线RX模式，通过DMA接收数据。
    DMA传输完成后比较收发数据，通过串口输出测试结果。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
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
        3、SPI1（主机）：NSS--PA4、SCK--PA5、MOSI--PA7（单线TX模式）
        4、SPI2（从机）：NSS--PB12、SCK--PB13、MISO--PB14（单线RX模式）
        5、DMA配置：DMA_CH2用于SPI2_RX
        6、USART1（Log输出）：TX--PA9  波特率115200

    使用方法：
        1、编译并烧录程序
        2、连接SPI1和SPI2对应引脚: PA5<-->PB13, PA7<-->PB14, PA4<-->PB12
        3、通过串口助手查看输出，显示"Test PASS!!"表示数据传输正确

4、注意事项
    1、主机使用单线TX模式，数据从MOSI引脚发出。
    2、从机使用单线RX模式，数据从MISO引脚接收。
    3、连接时需将主机MOSI(PA7)与从机MISO(PB14)相连。


1. Function description
    This example demonstrates SPI simplex mode where the master sends data by polling
    and the slave receives data via DMA.
    SPI1 is configured as master in single-line TX mode, sending 32 bytes by polling.
    SPI2 is configured as slave in single-line RX mode, receiving data via DMA.
    After DMA transfer is complete, compare transmitted and received data, and output
    test result via USART.

2. Development environment
    Software:
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Chip support: 
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use
    System Configuration:
        1. Clock source: HSI+PLL
        2. Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. SPI1 (Master): NSS--PA4, SCK--PA5, MOSI--PA7 (single-line TX mode)
        4. SPI2 (Slave): NSS--PB12, SCK--PB13, MISO--PB14 (single-line RX mode)
        5. DMA configuration: DMA_CH2 for SPI2_RX
        6. USART1 (Log output): TX--PA9  baudrate 115200

    Instructions:
        1. Compile and flash the program
        2. Connect SPI1 and SPI2 pins: PA5<-->PB13, PA7<-->PB14, PA4<-->PB12
        3. Check USART output via serial assistant, "Test PASS!!" indicates correct data transfer

4. Notes
    1. Master uses single-line TX mode, data is sent from MOSI pin.
    2. Slave uses single-line RX mode, data is received from MISO pin.
    3. Connect master MOSI(PA7) to slave MISO(PB14).
