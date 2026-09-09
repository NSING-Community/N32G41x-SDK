1、功能说明
    配置并演示CAN在环回测试模式下收发CAN报文情况。

2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    硬件开发环境：
        基于评估板N32G41x_STB V1.0开发

3、使用说明
    系统配置:
        1、时钟源：HSI+PLL
        2、时钟频率：N32G412:80MHz   N32G415:96MHz
        3、CAN：
            RX-PA11(AF1), TX-PA12(AF1)，波特率500K，环回测试模式
            引脚定义在can_config.h中通过宏定义配置，使用N32G412/N32G415预编译宏切换

    测试步骤与现象：
        1、编译后下载程序复位运行。
        2、CAN发送一帧消息，然后在验证通过后再发送另一帧消息。
           通过CAN设备，可以看到消息是在循环发送。

4、注意事项
    环回模式下无需外部CAN收发器，发送的数据会直接在内部回环接收。


1. Function description
    Configures and demonstrates CAN transceiving in loopback test mode.

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the evaluation board N32G41x_STB V1.0

3. Instructions for use
    System Configuration:
        1. Clock source: HSI+PLL
        2. Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. CAN:
            RX-PA11(AF1), TX-PA12(AF1), baud rate 500K, loopback test mode
            Pin definitions are configured via macros in can_config.h,
            switched by N32G412/N32G415 preprocessor defines

    Test steps and phenomenon:
        1. Compile and download the program to the development board and reset.
        2. CAN sends a frame, then sends another frame after the previous one
           is verified. Through CAN device, messages can be seen sending in a loop.

4. Attention
    In loopback mode, no external CAN transceiver is needed. The transmitted
    data is directly looped back and received internally.
