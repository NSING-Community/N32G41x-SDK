1、功能说明
    演示SPI2的9位数据帧格式收发功能。SPI2通过SPI_CTRL2.DATFF9=1使能9位数据帧格式，
    此时无论SPI_CTRL1.DATFF配置成什么值，SPI2数据帧格式均为9bit。9位模式不支持CRC。
    缓冲器为9位，发送和接收时只用到SPI_DAT[8:0]，接收时SPI_DAT[15:9]被强制为0。
    包含两个子工程：
        SPI_9Bit_Master：SPI2配置为主机，发送9位数据并接收从机回传数据
        SPI_9Bit_Slave：SPI2配置为从机，接收主机数据并回传9位数据
    需要两块开发板分别烧录主机和从机程序进行对测。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    芯片支持：(需要两块开发板)
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统配置；
        1、时钟源：
            HSI+PLL
        2、SPI2配置：
            数据帧格式：9位（SPI_DATA_SIZE_9BITS，自动设置CTRL2.DATFF9=1）
            全双工模式，软件NSS，CPOL=0，CPHA=0，MSB优先
            CRC：不使用（9位模式不支持CRC）
        3、端口配置：
            PB13选择为SPI2_SCK(AF1)
            PB14选择为SPI2_MISO(AF1)
            PB15选择为SPI2_MOSI(AF1)
            PA1选择为LED1指示灯
        4、测试数据：
            主机发送：0x101~0x120（使用bit[8]验证9位传输）
            从机发送：0x151~0x170（使用bit[8]验证9位传输）
    接线方法：
        板A（主机）PB13(SCK)  <--> 板B（从机）PB13(SCK)
        板A（主机）PB14(MISO) <--> 板B（从机）PB14(MISO)
        板A（主机）PB15(MOSI) <--> 板B（从机）PB15(MOSI)
        板A GND               <--> 板B GND
    使用方法：
        1、将SPI_9Bit_Slave程序烧录到从机开发板并复位
        2、将SPI_9Bit_Master程序烧录到主机开发板并复位
        3、主机先烧录，等从机就绪后再复位主机开始传输
        4、传输完成后，通过串口或LED1观察测试结果：
           LED1亮表示测试通过，串口输出详细结果

4、注意事项
    1、仅SPI2支持9位数据帧格式，SPI1不支持
    2、9位数据帧格式不支持CRC功能
    3、设置DataLen=SPI_DATA_SIZE_9BITS时，SPI_Init()自动配置SPI_CTRL2.DATFF9
    4、9位数据缓冲器只使用SPI_DAT[8:0]，接收时SPI_DAT[15:9]强制为0
    5、必须先启动从机再启动主机，否则从机会丢失首字节
    6、两块开发板间的连线需要尽可能短和直


1. Function description
    Demonstrates the 9-bit data frame format transmit/receive function of SPI2.
    SPI2 enables 9-bit data frame format by setting SPI_CTRL2.DATFF9=1. When enabled,
    regardless of the SPI_CTRL1.DATFF configuration, the SPI2 data frame format is 9-bit.
    9-bit mode does not support CRC. The buffer is 9-bit, only SPI_DAT[8:0] is used
    for transmit and receive. On receive, SPI_DAT[15:9] is forced to 0.
    Contains two sub-projects:
        SPI_9Bit_Master: SPI2 configured as master, sends 9-bit data and receives slave response
        SPI_9Bit_Slave: SPI2 configured as slave, receives master data and sends 9-bit response
    Two development boards are required, each programmed with master and slave respectively.

2. Use environment
    Software: (two boards required)
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Chip support: 
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSI+PLL
        2. SPI2 configuration:
            Data frame format: 9-bit (SPI_DATA_SIZE_9BITS, automatically sets CTRL2.DATFF9=1)
            Full-duplex mode, software NSS, CPOL=0, CPHA=0, MSB first
            CRC: not used (9-bit mode does not support CRC)
        3. Port configuration:
            PB13 is selected as SPI2_SCK (AF1)
            PB14 is selected as SPI2_MISO (AF1)
            PB15 is selected as SPI2_MOSI (AF1)
            PA1 is selected as LED1 indicator
        4. Test data:
            Master sends: 0x101~0x120 (bit[8] used to verify 9-bit transfer)
            Slave sends: 0x151~0x170 (bit[8] used to verify 9-bit transfer)
    Wiring:
        Board A (Master) PB13(SCK)  <--> Board B (Slave) PB13(SCK)
        Board A (Master) PB14(MISO) <--> Board B (Slave) PB14(MISO)
        Board A (Master) PB15(MOSI) <--> Board B (Slave) PB15(MOSI)
        Board A GND                 <--> Board B GND
    Instructions:
        1. Flash SPI_9Bit_Slave program to slave board and reset
        2. Flash SPI_9Bit_Master program to master board and reset
        3. Flash master first, wait for slave to be ready, then reset master to start transfer
        4. After transfer completes, observe test results via serial port or LED1:
           LED1 ON indicates test passed, serial port outputs detailed results

4. Attention
    1. Only SPI2 supports 9-bit data frame format, SPI1 does not support it
    2. 9-bit data frame format does not support CRC function
    3. When setting DataLen=SPI_DATA_SIZE_9BITS, SPI_Init() automatically configures SPI_CTRL2.DATFF9
    4. 9-bit data buffer only uses SPI_DAT[8:0], SPI_DAT[15:9] is forced to 0 on receive
    5. Slave must be started before master, otherwise slave will miss the first byte
    6. The connection between the two development boards should be as short and straight as possible.
