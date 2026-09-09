1、功能说明
    此例程提供了一种DMA MemtoMem模式用法，用于在FLASH与RAM之间传输数据。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    硬件开发环境：
        基于N32G41x开发板开发

3、使用说明
    1、时钟源：HSI+PLL
    2、时钟频率：N32G412:80MHz   N32G415:96MHz
    3、DMA通道：DMA_CH1
    4、USART：TX - PA9，RX - PA10，波特率115200
    5、测试步骤与现象
        a，编译下载代码复位运行
        b，DMA传输完成，串口打印"DMA Flash to RAM passed"，表示传输无误

4、注意事项
    无

1. Function description
    This routine provides a DMA MemtoMem mode usage for transferring data between FLASH and RAM.

2. Use environment
    Software development environment:
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on N32G41x evaluation board

3. Instructions for use
    1. Clock source: HSI+PLL
    2. Clock frequency: N32G412:80MHz   N32G415:96MHz
    3. DMA channel: DMA_CH1
    4. USART: TX - PA9, RX - PA10, baud rate 115200
    5. Test steps and phenomenon
        a. Compile and download the code, reset and run
        b. DMA transfer completed, serial port prints "DMA Flash to RAM passed", indicating no errors

4. Attention
    None
