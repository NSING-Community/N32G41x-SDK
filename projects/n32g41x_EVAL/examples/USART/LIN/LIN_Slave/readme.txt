1、功能说明

    该演示显示了USART模块LIN模式作为从节点，接收主节点发送的请求帧（0x3C）和从应答帧（0x3D）。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：N32G41x评估板

    芯片支持：
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3、使用说明

    系统时钟配置如下：
    - HSI+PLL
    - 系统时钟: N32G412:80MHz   N32G415:96MHz

    打印串口配置：
            USART1：TX - PA9，RX - PA10，波特率115200

    USART配置如下：
    - 波特率 = 9600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    - LIN模式使能

    USART引脚连接如下：
    - USART2_Tx.PA2   <------->   USART2_Rx.PA3
    - USART2_Rx.PA3   <------->   USART2_Tx.PA2

    测试步骤与现象：
    a、 跳线连接到主机的从属引脚
    b、 一个开发板编译并下载LIN_Master代码作为主代码
         另一个开发板编译并下载LIN_Slave代码作为从属代码
    c、 重置从设备，然后重置主设备
    d、 主轮询发送请求帧（0x3C）和应答帧（0x3D）
         发送请求帧（0x3C）：主设备向从设备发送一个8字节的0x0F，并打印相关信息
         发送应答帧（0x3D）：从机收到应答帧后，向主机回复8字节0x01消息，并且主控打印相关信息


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function description

    This demo shows that the USART module LIN mode as the slave node, receives the request frame (0x3C)
    and the slave reply frame (0x3D) sent by the master node.

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware: N32G41x evaluation board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. How to use

    The system clock configuration is as follows:
    - HSI+PLL
    - SystemClock: N32G412:80MHz   N32G415:96MHz

    Print Serial Port Configuration:
            USART1: TX - PA9, RX - PA10, Baud rate 115200

    The USART configuration is as follows:
    - Baud rate = 9600 baud
    - Word length = 8 data bits
    - 1 stop bit
    - Parity control disabled
    - Receiver and transmitter enabled
    - 16 times oversampling
    - LIN mode enable
    - Hardware flow control disabled

    The USART pin connections are as follows:
    - USART2_Tx.PA2   <------->   USART2_Rx.PA3
    - USART2_Rx.PA3   <------->   USART2_Tx.PA2

    Test steps and phenomena:
    a, the jumper connects to the slave pin of the master
    b, one development board compiles and downloads LIN_Master code as the master and
        the other development board compiles and downloads LIN_Slave code as the slave
    c, Reset the slave and then the master
    d, master polling sends request frame (0x3C) and reply frame (0x3D)
       Sending request frame (0x3C) : The master sends an 8-byte 0x0F to the slave and prints the related information
       Sending reply frame (0x3D) : After receiving a reply frame, the slave reply an 8-byte 0x01 message to the master,
        and the master prints the related information


4. Attention

    Disconnect the MCU_TX and MCU_RX jumper caps of the NS-LINK on the development board first
