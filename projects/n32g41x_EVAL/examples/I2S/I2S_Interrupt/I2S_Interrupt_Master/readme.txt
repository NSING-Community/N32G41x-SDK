1、功能说明
    此例程演示I2S通过中断方式发送数据。
    I2S1（SPI1）配置为主机发送模式，通过TxE中断发送32个16位数据。
    中断处理函数中逐个发送数据，发送完成后禁用中断。
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
        3、I2S1（主机TX）：WS--PA4、CK--PA5、SD--PA7
        4、I2S配置：Phillips标准，16位扩展数据格式，48KHz采样率
        5、中断配置：SPI1_IRQn，使用TxE中断发送数据
        6、USART1（Log输出）：TX--PA9  波特率115200

    使用方法：
        1、编译并烧录程序
        2、可通过逻辑分析仪或I2S接收设备观察I2S输出波形
        3、通过串口助手查看输出，显示"Test PASS!!"表示中断发送完成

    两块开发板对测（需配合I2S_Interrupt_Slave从机例程）：
        1、硬件连接：主机PA4(WS)、PA5(CK)、PA7(SD)分别与从机PA4、PA5、PA7相连，GND共地
        2、主机板烧录本程序，从机板烧录I2S_Interrupt_Slave
        3、同时上电或复位，主机启动后延时1秒再发送，从机串口显示"Test PASS!!"即对测成功

4、注意事项
    1、N32G41x仅SPI1支持I2S模式，SPI2不支持I2S。
    2、I2S时钟源配置为系统时钟。
    3、I2S引脚与SPI1引脚复用，使用AF0。
    4、两块开发板对侧时需要接线尽可能短


1. Function description
    This example demonstrates I2S data transmission via interrupt.
    I2S1 (SPI1) is configured as master TX mode, sending 32 half-words via TxE interrupt.
    The interrupt handler sends data one by one, and disables the interrupt after all data
    is sent. Test result is output via USART.

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
        3. I2S1 (Master TX): WS--PA4, CK--PA5, SD--PA7
        4. I2S configuration: Phillips standard, 16-bit extended data format, 48KHz sample rate
        5. Interrupt configuration: SPI1_IRQn, TxE interrupt for data transmission
        6. USART1 (Log output): TX--PA9  baudrate 115200

    Instructions:
        1. Compile and flash the program
        2. Use logic analyzer or I2S receiver to observe I2S output waveform
        3. Check USART output via serial assistant, "Test PASS!!" indicates interrupt TX complete

    Board-to-board test (with I2S_Interrupt_Slave):
        1. Connect Master PA4(WS), PA5(CK), PA7(SD) to Slave PA4, PA5, PA7; GND to GND
        2. Flash this program on Master, I2S_Interrupt_Slave on Slave
        3. Power or reset both; Master delays 1s before sending; Slave shows "Test PASS!!" if OK

4. Notes
    1. N32G41x only supports I2S mode on SPI1, SPI2 does not support I2S.
    2. I2S clock source is configured as system clock.
    3. I2S pins are multiplexed with SPI1 pins, using AF0.
    4. When the two development boards are opposite each other, the wiring needs to be as short as possible.
