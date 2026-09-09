1、功能说明
    该示例演示USART1重定向printf输出到串口。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1

    硬件环境：
        - N32G41x评估板

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明

    系统时钟配置如下：
        - HSI+PLL
        - 系统时钟: N32G412:80MHz   N32G415:96MHz

    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 16倍过采样  
    
    UART引脚连接如下：  
        - USART1_TX: PA9
        - USART1_RX: PA10

    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看串口打印信息

4、注意事项


1. Function description
    This example demonstrates redirecting printf to USART1.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1

    Hardware:
        - N32G41x evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    System configuration:
        HSI+PLL
        SystemClock: N32G412:80MHz   N32G415:96MHz

    USART configuration:
        - Baud rate = 115200 baud
        - Word length = 8 data bits
        - Stop bits = 1
        - Parity = none
        - Hardware flow control disabled
        - RX and TX enabled
        - Oversampling = 16
    
    The UART pin connections are as follows:
            - USART1_TX: PA9
            - USART1_RX: PA10
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Reset and run. Check the serial port information

4. Notes
