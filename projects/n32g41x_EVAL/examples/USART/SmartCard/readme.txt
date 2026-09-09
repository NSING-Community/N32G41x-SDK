1、功能说明
    本示例演示基于USART3 SmartCard模式的智能卡通信。
    USART3工作在SmartCard模式，通过T=0协议与PSAM卡进行数据交互，
    包括ATR（复位应答）接收、PPS协商、APDU命令收发，以及热复位操作。
    DMA用于加速数据传输。

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：N32G41x_EVAL评估板 + PSAM智能卡模块

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明
    系统配置：
    - 系统时钟
            HSI+PLL
            SystemClock: N32G412:80MHz   N32G415:96MHz
            智能卡工作时钟 = 3MHz

    USART3配置如下：
    - 波特率 =  (根据设置的智能卡工作时钟配置)
    - 字长 = 9数据位
    - 1.5停止位
    - 校验控制 even
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - DMA用于PPS数据收发（DMA_CH5=TX, DMA_CH6=RX）
    GPIO配置：
    - USART3: PB10(TX, AF0), PB12(CK, AF0)
    - 复位引脚: PB9(GPIO输出)

    使用方法：
        1. 编译并下载程序到评估板
        2. 连接PSAM智能卡模块：
           PB10(TX) <-------> 卡I/O引脚
           PB12(CK) <-------> 卡CLK引脚
           PB9      <-------> 卡RST引脚
        3. 串口1(PA9/PA10)以115200波特率输出调试信息
        4. 程序完成ATR接收、PPS协商、获取随机数命令后显示结果

4、注意事项
    SmartCard使用USART3(APB1)，调试输出使用USART1(APB2)。
    时钟分频值(Clk_Div=40)需根据实际PCLK1频率调整以满足卡要求。
    PB10/PB12在N32G412和N32G415上复用功能号相同(AF0)，无需条件编译。

-------------------------------------------------------------------------------
1. Function Description
    This example demonstrates smart card communication using USART3 SmartCard mode.
    USART3 operates in SmartCard mode, communicating with a PSAM card via T=0 protocol,
    including ATR (Answer To Reset) reception, PPS negotiation, APDU command exchange,
    and hot reset operation. DMA is used to accelerate data transfers.

2. Environment
    Software: KEIL MDK-ARM V5.34.0.0
              IAR EWARM 8.50.1
    Hardware: N32G41x_EVAL evaluation board + PSAM smart card module

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    System Configuration:
            HSI+PLL
            SystemClock: N32G412:80MHz   N32G415:96MHz
            Smartcard clock = 3MHz

	USART3 configuration is as follows:
	- Baud rate = (based on the set smart card working clock)
	- Word length = 9 data bits
	- 1.5 Stop bit
	- Parity control even
	- Hardware flow control disabled (RTS and CTS signals)
	- Enable receiver and transmitter
	- DMA for PPS data transfer (DMA_CH5=TX, DMA_CH6=RX)

	GPIO Configuration:
	   - USART3: PB10(TX, AF0), PB12(CK, AF0)
	   - Reset pin: PB9(GPIO output)

    Usage:
        1. Compile and download to evaluation board
        2. Connect PSAM smart card module:
           PB10(TX)  <------->Card I/O pin
           PB12(CK)  <------->Card CLK pin
           PB9       <------->Card RST pin
        3. USART1(PA9/PA10) outputs debug info at 115200 baud
        4. Program completes ATR reception, PPS negotiation, get-challenge command and displays the result

4. Notes
    SmartCard uses USART3(APB1), debug output uses USART1(APB2).
    Clock divider (Clk_Div=40) may need adjustment based on actual PCLK1 frequency.
    PB10/PB12 have the same AF number (AF0) on both N32G412 and N32G415.
