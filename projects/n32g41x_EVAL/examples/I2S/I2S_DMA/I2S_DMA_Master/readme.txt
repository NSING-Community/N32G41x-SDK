1、功能说明
    此例程演示I2S通过DMA发送数据（主机端）。
    I2S1（SPI1）配置为主机发送模式，通过DMA发送32个16位数据。
    配合I2S_DMA_Slave（从机）实现两块开发板对测。

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
        4、DMA配置：DMA_CH3用于I2S1_TX
        5、I2S配置：Phillips标准，16位扩展数据格式，48KHz采样率
        6、USART1（Log输出）：TX--PA9  波特率115200

    两块开发板对测步骤：
        1、硬件连接（两块板互联）：
           板1(主机) I2S_DMA_Master     板2(从机) I2S_DMA_Slave
           PA4(WS)  <----------------->  PA4(WS)
           PA5(CK)  <----------------->  PA5(CK)
           PA7(SD)  <----------------->  PA7(SD)
           GND      <----------------->  GND

        2、板1烧录I2S_DMA_Master（主机TX），板2烧录I2S_DMA_Slave（从机RX）

        3、先复位从机板，再复位主机板。主机启动后延时1秒再发送，确保从机已就绪。

        4、主机串口显示"Test PASS!!"表示DMA发送完成。
           从机串口显示"Test PASS!!"表示接收数据正确。

4、注意事项
    1、N32G41x仅SPI1支持I2S模式，SPI2不支持I2S。
    2、I2S时钟源配置为系统时钟。
    3、I2S引脚与SPI1引脚复用，使用AF0。


1. Function description
    This example demonstrates I2S data transmission via DMA (Master side).
    I2S1 (SPI1) is configured as master TX mode, sending 32 half-words via DMA.
    Use with I2S_DMA_Slave for board-to-board testing.

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
        4. DMA configuration: DMA_CH3 for I2S1_TX
        5. I2S configuration: Phillips standard, 16-bit extended, 48KHz
        6. USART1 (Log): TX--PA9, 115200 baud

    Board-to-board test:
        1. Wire connection:
           Board1(Master) I2S_DMA_Master   Board2(Slave) I2S_DMA_Slave
           PA4(WS)  <----------------->    PA4(WS)
           PA5(CK)  <----------------->    PA5(CK)
           PA7(SD)  <----------------->    PA7(SD)
           GND      <----------------->    GND

        2. Flash I2S_DMA_Master on Board1, I2S_DMA_Slave on Board2

        3. Reset Slave first, then Master. Master delays 1s before sending.

        4. Master USART shows "Test PASS!!" when DMA TX complete.
           Slave USART shows "Test PASS!!" if received data matches.

4. Notes
    1. N32G41x only SPI1 supports I2S, SPI2 does not.
    2. I2S clock source is system clock.
    3. I2S pins are multiplexed with SPI1 pins, using AF0.
