1、功能说明
    通过EXTI线来触发时间戳。

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
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、RTC时钟源：LSE
        4、EXTI中断IO：PB8
        5、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率：115200

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、PC13连接到PB8，上电后，串口每隔1S会打印时间戳输出。

4、注意事项
    无


1. Function description

    Trigger timestamp through EXTI line.

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
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. RTC clock source: LSE
        4. EXTI interrupt IO: PB8
        5. Serial port configuration:
                    - Serial port: USART1 (TX: PA9  RX: PA10)
                    - Data bit: 8
                    - Stop bit: 1
                    - Parity check: None
                    - Baud rate: 115200

    Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. Connect PC13 to PB8. After power-on, the serial port prints timestamp output every 1S.

4. Notes
    None
