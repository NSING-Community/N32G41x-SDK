1、功能说明
    此例程展示了I2C模块作从设备使用中断方式的读写操作。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    硬件开发环境：
        基于N32G41x开发板开发

3、使用说明
    1、时钟源：HSI+PLL
    2、时钟频率：N32G412:80MHz   N32G415:96MHz
    3、I2C1配置：
        时钟：100KHz
        地址：0x10（7bit）
        引脚：SCL--PA4、SDA--PA5
    4、USART：TX - PA9，波特率115200
    5、测试步骤与现象
        a，连接I2C主设备
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果

4、注意事项
    无

1. Function description
    This routine shows the read/write operation of the I2C module as the slave device using interrupt mode.

2. Use environment
    Software development environment:
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on N32G41x evaluation board

3. Instructions for use
    1. Clock source: HSI+PLL
    2. Clock frequency: N32G412:80MHz   N32G415:96MHz
    3. I2C1 configuration:
        Clock: 100KHz
        Address: 0x10 (7bit)
        Pinout: SCL--PA4, SDA--PA5
    4. USART: TX - PA9, baud rate 115200
    5. Test steps and phenomenon
        a. Connect the I2C master device
        b. Compile and download the code, reset and run
        c. View the print information from the serial port and verify the result

4. Attention
    None
