1、功能说明
    此例程演示I2S通过中断方式接收数据，配合I2S_Interrupt（主机）实现两块开发板对测。
    I2S1（SPI1）配置为从机接收模式，通过RxNE中断接收32个16位数据。
    接收完成后与预期数据比对，通过串口输出测试结果。

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
        3、I2S1（从机RX）：WS--PA4、CK--PA5、SD--PA7（与主机引脚一致）
        4、I2S配置：Phillips标准，16位扩展数据格式，48KHz采样率（与主机一致）
        5、中断配置：SPI1_IRQn，使用RxNE中断接收数据
        6、USART1（Log输出）：TX--PA9  波特率115200

    两块开发板对测步骤：
        1、硬件连接（两块板互联）：
           板1(主机) I2S_Interrupt    板2(从机) I2S_Interrupt_Slave
           PA4(WS)  <--------------->  PA4(WS)
           PA5(CK)  <--------------->  PA5(CK)
           PA7(SD)  <--------------->  PA7(SD)
           GND      <--------------->  GND

        2、板1烧录I2S_Interrupt（主机TX），板2烧录I2S_Interrupt_Slave（从机RX）

        3、同时上电或复位两块板。主机启动后延时1秒再发送，确保从机已就绪。

        4、从机串口显示"Test PASS!!"表示接收数据正确；"Test FAIL!!"表示数据校验失败。

4、注意事项
    1、N32G41x仅SPI1支持I2S模式，SPI2不支持I2S。
    2、主从配置必须一致：Phillips、16位扩展、48KHz。
    3、从机必须先使能I2S并等待接收，主机延时1秒后发送，确保对测成功。
	4、两块开发板对侧时需要接线尽可能短


1. Function description
    This example demonstrates I2S data reception via interrupt. Use with I2S_Interrupt (Master)
    for board-to-board testing. I2S1 (SPI1) is configured as slave RX mode, receiving 32
    half-words via RxNE interrupt. After reception, data is compared with expected values
    and the result is output via USART.

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
        3. I2S1 (Slave RX): WS--PA4, CK--PA5, SD--PA7 (same as Master)
        4. I2S config: Phillips, 16-bit extended, 48KHz (must match Master)
        5. Interrupt: SPI1_IRQn, RxNE for reception
        6. USART1 (Log): TX--PA9, 115200 baud

    Board-to-board test:
        1. Wire connection:
           Board1(Master) I2S_Interrupt    Board2(Slave) I2S_Interrupt_Slave
           PA4(WS)  <----------------->    PA4(WS)
           PA5(CK)  <----------------->    PA5(CK)
           PA7(SD)  <----------------->    PA7(SD)
           GND      <----------------->    GND

        2. Flash I2S_Interrupt on Board1, I2S_Interrupt_Slave on Board2

        3. Power or reset both boards. Master delays 1s before sending to ensure Slave is ready.

        4. Slave USART shows "Test PASS!!" if data matches; "Test FAIL!!" if mismatch.

4. Notes
    1. N32G41x only SPI1 supports I2S, SPI2 does not.
    2. Master and Slave config must match: Phillips, 16-bit extended, 48KHz.
    3. Slave must be enabled and waiting before Master sends; Master has 1s delay for sync.
	4. When the two development boards are opposite each other, the wiring needs to be as short as possible.
