1、功能说明
    此例程演示了Flash编程功能。先擦除一个页，然后逐字写入数据，最后验证
    写入的数据是否正确。

2、使用环境
    硬件环境：N32G41x开发板
    软件环境：
        - Keil MDK-ARM V5.34
        - IAR EWARM V8.50

3、使用说明
    系统配置：
        1. 时钟源：HSI + PLL
        2. 时钟频率：N32G412:80MHz   N32G415:96MHz
        3. USART1用于log输出（波特率115200）

    使用方法：
        1. 编译并下载程序到N32G41x开发板
        2. 打开串口终端，查看Flash编程结果

4、注意事项
    - 编程地址范围为0x08008000 ~ 0x08008200
    - 页大小为512字节 (0x200)
    - 编程前必须先擦除对应页
    - 请确保编程区域不与应用代码重叠

1. Function Description
    This demo demonstrates Flash programming. It erases a page, programs words
    into it, and then verifies the written data.

2. Environment
    Hardware: N32G41x evaluation board
    Software:
        - Keil MDK-ARM V5.34
        - IAR EWARM V8.50

3. Instructions
    System Configuration:
        1. Clock: HSI + PLL
        2. Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. USART1 for log output (baud rate 115200)
    Usage:
        1. Compile and download to N32G41x evaluation board
        2. Open serial terminal to view Flash programming results

4. Notes
    - Program address range: 0x08008000 ~ 0x08008200
    - Page size: 512 bytes (0x200)
    - Page must be erased before programming
    - Ensure the target area does not overlap with application code
