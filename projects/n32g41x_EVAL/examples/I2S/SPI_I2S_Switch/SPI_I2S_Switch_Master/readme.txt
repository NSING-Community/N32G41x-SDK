1、功能说明
    此例程演示SPI与I2S模式切换的主机端功能，配合SPI_I2S_Switch_Slave从机端
    实现两块开发板对测。
    测试流程：
        步骤1：I2S主机发送模式 - 通过I2S1以轮询方式发送32个16位数据
        步骤2：切换为SPI主机发送模式 - 通过SPI1单线发送方式发送32个16位数据
        步骤3：再次切换回I2S主机发送模式 - 重复步骤1的发送
    主机端启动前延时1秒，确保从机端先就绪。
    通过串口输出各步骤执行状态。

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
        3、SPI1/I2S1配置（主机端）：
            I2S模式：Phillips标准，16位扩展数据格式，48KHz采样率
            SPI模式：单线发送，16位，CPOL=LOW，CPHA=2Edge，软件NSS
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
    1、主机端启动延时1秒，确保从机端先进入接收就绪状态。
    2、主机在每个步骤之间延时100ms，确保从机完成模式切换。
    3、N32G41x仅SPI1支持I2S功能，SPI2不支持I2S。
    4、两块板使用相同的SPI1引脚（PA4/PA5/PA7），通过飞线直连。


1. Function description
    This example demonstrates the master side of SPI/I2S mode switching,
    working with SPI_I2S_Switch_Slave for board-to-board testing.
    Test flow:
        Step 1: I2S master TX mode - send 32x16-bit data via I2S1 by polling
        Step 2: Switch to SPI master TX mode - send 32x16-bit data via SPI1 single-line TX
        Step 3: Switch back to I2S master TX mode - repeat step 1
    Master has a 1s startup delay to ensure slave is ready.
    Test status is output via USART.

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
        3. SPI1/I2S1 configuration (Master):
            I2S mode: Phillips standard, 16-bit extended data format, 48KHz sample rate
            SPI mode: Single-line TX, 16-bit, CPOL=LOW, CPHA=2Edge, software NSS
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
    1. Master has a 1s startup delay to ensure slave is in receive-ready state.
    2. Master adds 100ms delay between steps for slave mode switching.
    3. Only SPI1 supports I2S on N32G41x, SPI2 does not support I2S.
    4. Both boards use the same SPI1 pins (PA4/PA5/PA7), connected via jumper wires.
