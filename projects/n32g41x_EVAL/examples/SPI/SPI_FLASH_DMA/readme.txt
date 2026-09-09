1、功能说明
    此例程演示通过SPI DMA方式读写W25Q128 Flash数据。
    通过SPI1读取W25Q128的ID，然后通过DMA写入数据，再通过DMA读出来，
    比较读写数据是否一致，验证DMA传输的正确性。

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
        1、时钟源：HSE+PLL
        2、系统时钟频率：72MHz
        3、SPI配置：
            SPI1配置：SCK--PA1、MISO--PA0、MOSI--PA2、CS--PA4(GPIO)
        4、DMA配置：
            DMA_CH2用于SPI1_RX，DMA_CH3用于SPI1_TX
        5、USART配置：
            TX--PA9，115200，8bit data，1bit stop

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、通过SPI1读取W25Q128的ID，然后通过DMA写数据，再通过DMA读出来，
           比较读写数据，查看TransferStatus1状态为PASSED，然后擦除扇区，
           检查擦除扇区正常。
        3、通过串口工具查看结果。

4、注意事项
    1、只在大批量读写数据时使用DMA。在用DMA读取数据时，设置SPI为只读模式，
       这样在读取数据时不需要一直发送0xFF，以此来提升性能。
    2、外接Flash芯片跳线尽可能短, 拔了LED1-PA1跳线帽。
    3、开发板无W25Q128，需外接W25Q128
    4、SPI以最大速率36MHz运行，系统时钟最高只能跑72MHz
    5、SCK--PA1、MISO--PA0、MOSI--PA2支持SPI最大速率36MHz


1. Function description

    This example demonstrates SPI DMA read and write W25Q128 Flash data.
    Read the ID of W25Q128 through SPI1, then write data through DMA, and
    then read it out through DMA, compare the read and write data to verify
    the correctness of DMA transfer.

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
        1. Clock source: HSE+PLL
        2. System Clock frequency: 72MHz
        3. SPI configuration:
            SPI1 configuration: SCK--PA1, MISO--PA0, MOSI--PA2, CS--PA4(GPIO)
        4. DMA configuration:
            DMA_CH2 for SPI1_RX, DMA_CH3 for SPI1_TX
        5. USART configuration:
            TX--PA9, 115200, 8bit data, 1bit stop

    Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. Read the ID of W25Q128 through SPI1, then write data through DMA, and
           then read it out through DMA, compare the read and write data, check that
           TransferStatus1 is PASSED, then erase the sector, and check that the erase
           is normal.
        3. View the results through the serial port tool.

4. Notes
    1. Only use DMA when reading and writing data in large batches. When DMA reads data,
       set SPI to read-only mode, so that 0xFF does not need to be sent all the time
       when reading data, so as to improve performance.
    2. Keep the jumper for the external Flash chip as short as possible, and remove the jumper cap from LED1-PA1.
    3. The development board doesn't have a W25Q128, you need to connect an external W25Q128.
    4. The SPI runs at a maximum speed of 36MHz, while the system clock can only go up to 72MHz.
    5. SCK--PA1, MISO--PA0, MOSI--PA2 support SPI maximum speed of 36MHz
