1、功能说明
    SPI DMA单线发送和单线接收数据。
    SPI1配置为主机，通过DMA发送数据（单线TX模式）。
    SPI2配置为从机，通过DMA接收数据（单线RX模式）。
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
    1、时钟源：HSI+PLL
    2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
    3、SPI1（主）：NSS--PA4、SCK--PA5、MOSI--PA7
    4、SPI2（从）：NSS--PB12、SCK--PB13、MISO--PB14
    5、USART1（Log输出）：TX--PA9  波特率115200
    6、测试步骤与现象
        a. 编译并烧录程序
        b. 连接SPI1和SPI2对应引脚: PA5<-->PB13, PA7<-->PB14, PA4<-->PB12
        c. 通过串口助手查看输出，显示"Test PASS!!"表示数据传输正确

4、注意事项
    无

1. Function Description
    SPI DMA single-line transmit and single-line receive data.
    SPI1 is configured as master, transmitting data via DMA (single-line TX mode).
    SPI2 is configured as slave, receiving data via DMA (single-line RX mode).
    After DMA transfer is complete, compare transmitted and received data, and output test result via USART.

2. Environment
    Software:
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Chip support: 
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    1. Clock source: HSI+PLL
    2. Clock frequency: N32G412:80MHz   N32G415:96MHz
    3. SPI1 (Master): NSS--PA4, SCK--PA5, MOSI--PA7
    4. SPI2 (Slave): NSS--PB12, SCK--PB13, MISO--PB14
    5. USART1 (Log output): TX--PA9  baudrate 115200
    6. Test steps and phenomena
        a. Compile and flash the program
        b. Connect SPI1 and SPI2 pins: PA5<-->PB13, PA7<-->PB14, PA4<-->PB12
        c. Check USART output via serial assistant, "Test PASS!!" indicates correct data transfer

4. Notes
    None
