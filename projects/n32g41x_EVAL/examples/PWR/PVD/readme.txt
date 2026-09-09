1、功能说明
    此例程演示了电源电压检测(PVD)功能。当VDD电压跨过设定的PVD阈值时，
    触发中断，并通过串口输出提示信息。

2、使用环境
    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7
    软件环境：
        - Keil MDK-ARM V5.34
        - IAR EWARM V8.50.1

3、使用说明
    系统配置：
        1. 时钟源：HSI + PLL
        2. 系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3. PVD阈值设置为2.4V
        4. PVD输出连接到EXTI Line 16
        5. USART1：TX - PA9，波特率115200，用于log输出
    使用方法：
        1. 编译并下载程序到N32G41x开发板
        2. 打开串口终端
        3. 调节VDD电压使其跨过2.4V阈值，观察串口输出变化

4、注意事项
    - PVD阈值可通过修改PWR_PVD_LEVEL_2V4参数调整

1. Function Description
    This demo demonstrates the Programmable Voltage Detector (PVD) feature.
    When VDD crosses the configured PVD threshold, an interrupt is triggered,
    and messages are printed via USART.

2. Environment
    Chip support: 
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7
    Software:
        - Keil MDK-ARM V5.34
        - IAR EWARM V8.50.1

3. Instructions
    System Configuration:
        1. Clock: HSI + PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. PVD threshold set to 2.4V
        4. PVD output mapped to EXTI Line 16
        5. USART1: TX - PA9, baud rate 115200, for log output
    Usage:
        1. Compile and download to N32G41x evaluation board
        2. Open serial terminal
        3. Adjust VDD to cross 2.4V threshold, observe serial output

4. Notes
    - PVD threshold can be adjusted by changing PWR_PVD_LEVEL_2V4 parameter
