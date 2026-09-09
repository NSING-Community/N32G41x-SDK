1、功能说明
    此例程演示SPI与I2S模式切换的从机端功能，配合SPI_I2S_Switch_Master主机端
    实现两块开发板对测。
    测试流程：
        步骤1：I2S从机接收模式 - 通过I2S1以轮询方式接收32个16位数据，与预期数据比较
        步骤2：切换为SPI从机接收模式 - 通过SPI1双线只读方式接收32个16位数据，与预期数据比较
        步骤3：再次切换回I2S从机接收模式 - 重复步骤1的接收和比较
    从机端无延时，始终先就绪等待主机数据。
    通过串口输出各步骤接收结果和数据比较结果。

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
        3、SPI1/I2S1配置（从机端）：
            I2S模式：Phillips标准，16位扩展数据格式，48KHz采样率，从机接收
            SPI模式：双线只读，16位，CPOL=LOW，CPHA=2Edge，软件NSS
            引脚：NSS/WS--PA4, SCK/CK--PA5, MOSI/SD--PA7 (AF0)
        4、USART1（Log输出）：TX--PA9  波特率115200

    使用方法：
        1、准备两块N32G41x开发板
        2、Board A烧录SPI_I2S_Switch_Master程序
        3、Board B烧录SPI_I2S_Switch_Slave程序
        4、连线：Board A PA4 <-> Board B PA4 (NSS/WS)
                 Board A PA5 <-> Board B PA5 (SCK/CK)
                 Board A PA7 <-> Board B PA7 (MOSI/SD)
                 Board A GND <-> Board B GND
        5、先上电Board B（从机），再上电Board A（主机），或同时上电（主机有1秒延时）
        6、通过串口助手查看两块板的输出结果

4、注意事项
    1、从机端必须先于主机端就绪，主机有1秒启动延时保证此时序。
    2、N32G41x仅SPI1支持I2S功能，SPI2不支持I2S。
    3、两块板使用相同的SPI1引脚（PA4/PA5/PA7），通过飞线直连。
    4、SPI从机使用双线只读模式（SPI_DIR_DOUBLELINE_RONLY），接收主机MOSI数据。


1. Function description
    This example demonstrates the slave side of SPI/I2S mode switching,
    working with SPI_I2S_Switch_Master for board-to-board testing.
    Test flow:
        Step 1: I2S slave RX mode - receive 32x16-bit data via I2S1 by polling, compare with expected data
        Step 2: Switch to SPI slave RX mode - receive 32x16-bit data via SPI1 double-line RX only, compare
        Step 3: Switch back to I2S slave RX mode - repeat step 1 receive and compare
    Slave has no delay and is always ready before master starts.
    Receive results and data comparison results are output via USART.

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
        3. SPI1/I2S1 configuration (Slave):
            I2S mode: Phillips standard, 16-bit extended data format, 48KHz sample rate, slave RX
            SPI mode: Double-line RX only, 16-bit, CPOL=LOW, CPHA=2Edge, software NSS
            Pins: NSS/WS--PA4, SCK/CK--PA5, MOSI/SD--PA7 (AF0)
        4. USART1 (Log output): TX--PA9  baudrate 115200

    Instructions:
        1. Prepare two N32G41x development boards
        2. Flash Board A with SPI_I2S_Switch_Master program
        3. Flash Board B with SPI_I2S_Switch_Slave program
        4. Wiring: Board A PA4 <-> Board B PA4 (NSS/WS)
                   Board A PA5 <-> Board B PA5 (SCK/CK)
                   Board A PA7 <-> Board B PA7 (MOSI/SD)
                   Board A GND <-> Board B GND
        5. Power on Board B (slave) first, then Board A (master), or power on simultaneously (master has 1s delay)
        6. Check USART output on both boards for test results

4. Notes
    1. Slave must be ready before master starts. Master has 1s startup delay to ensure this.
    2. Only SPI1 supports I2S on N32G41x, SPI2 does not support I2S.
    3. Both boards use the same SPI1 pins (PA4/PA5/PA7), connected via jumper wires.
    4. SPI slave uses double-line RX only mode (SPI_DIR_DOUBLELINE_RONLY) to receive master MOSI data.
