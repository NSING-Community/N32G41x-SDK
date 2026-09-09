1、功能说明
    SPI全双工通信进行CRC校验。
    SPI1配置为主机，SPI2配置为从机，16位数据，双线全双工模式。
    主从机同时收发32个16位数据，传输完成后发送CRC值。
    比较收发数据并检查CRC错误标志，通过串口输出测试结果。

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
    3、SPI1（主）：SCK--PA5、MISO--PA6、MOSI--PA7
    4、SPI2（从）：SCK--PB13、MISO--PB14、MOSI--PB15
    5、USART1（Log输出）：TX--PA9  波特率115200
    6、测试步骤与现象
        a. 编译并烧录程序
        b. 连接SPI1和SPI2对应引脚: PA5<-->PB13, PA6<-->PB14, PA7<-->PB15
        c. 通过串口助手查看输出，显示"Test PASS!!"表示数据和CRC校验正确

4、注意事项
    无

1. Function Description
    SPI full-duplex communication with CRC verification.
    SPI1 is configured as master, SPI2 as slave, 16-bit data, double-line full-duplex mode.
    Master and slave simultaneously send and receive 32 x 16-bit data, CRC value is sent after transfer.
    Compare transmitted and received data, check CRC error flags, and output test result via USART.

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
    3. SPI1 (Master): SCK--PA5, MISO--PA6, MOSI--PA7
    4. SPI2 (Slave): SCK--PB13, MISO--PB14, MOSI--PB15
    5. USART1 (Log output): TX--PA9  baudrate 115200
    6. Test steps and phenomena
        a. Compile and flash the program
        b. Connect SPI1 and SPI2 pins: PA5<-->PB13, PA6<-->PB14, PA7<-->PB15
        c. Check USART output via serial assistant, "Test PASS!!" indicates correct data and CRC

4. Notes
    None
