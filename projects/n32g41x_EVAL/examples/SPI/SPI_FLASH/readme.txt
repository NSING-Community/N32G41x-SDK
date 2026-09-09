1、功能说明
    此例程演示通过SPI轮询方式读写W25Q128 Flash数据。
    通过SPI1读取W25Q128的ID，然后通过轮询方式写入数据，再读出来，
    比较读写数据是否一致。然后擦除扇区，读取擦除后数据验证是否全为0xFF。
    通过串口输出测试结果。

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
        3、SPI配置：
            SPI1配置：SCK--PA5、MISO--PA6、MOSI--PA7、CS--PA4(GPIO)
            SPI模式：全双工主机模式，CPOL=HIGH，CPHA=2Edge，8bit，软件NSS
        4、USART1（Log输出）：TX--PA9  波特率115200

    使用方法：
        1、编译并烧录程序
        2、连接W25Q128 Flash模块到SPI1引脚
        3、通过串口助手查看输出，显示读取的Flash ID和读写测试结果

4、注意事项
    1、CS引脚（PA4）配置为GPIO输出模式，通过软件控制片选。
    2、SPI Flash支持W25Q128（ID: 0x00EF4018）。
    3、写入地址为0x700000，请确保该地址范围内无重要数据。
    4、开发板无W25Q128，需外接W25Q128


1. Function description
    This example demonstrates SPI polling read/write W25Q128 Flash data.
    Read the ID of W25Q128 through SPI1, then write data by polling, read it back,
    and compare the read and write data. Then erase the sector, read back to verify
    all data is 0xFF.
    Test results are output via USART.

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
        3. SPI configuration:
            SPI1: SCK--PA5, MISO--PA6, MOSI--PA7, CS--PA4(GPIO)
            SPI mode: Full-duplex master, CPOL=HIGH, CPHA=2Edge, 8-bit, software NSS
        4. USART1 (Log output): TX--PA9  baudrate 115200

    Instructions:
        1. Compile and flash the program
        2. Connect W25Q128 Flash module to SPI1 pins
        3. Check USART output via serial assistant for Flash ID and read/write test results

4. Notes
    1. CS pin (PA4) is configured as GPIO output for software chip-select control.
    2. SPI Flash supports W25Q128 (ID: 0x00EF4018).
    3. Write address is 0x700000, ensure no important data in that address range.
    4. The development board doesn't have a W25Q128, you need to connect an external W25Q128.
