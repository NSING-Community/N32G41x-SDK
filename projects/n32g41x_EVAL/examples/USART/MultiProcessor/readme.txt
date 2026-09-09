1、功能说明
    演示USART多处理器通信模式，通过地址标记实现接收端静默唤醒。
    USARTy(USART1)作为发送端，USARTz(USART2)作为接收端。
    USARTy地址设置为0x1，USARTz地址设置为0x2。
    USARTy持续向USARTz发送0x33数据，USARTz收到数据后LED1翻转。
    按下KEY1(PA4)，USARTz进入静默模式，LED1停止翻转。
    再次按下KEY1，USARTy发送地址匹配数据(0x102)唤醒USARTz，LED1恢复翻转。

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
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 9数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用
    - 接收器和发送器使能
    - 16倍过采样
    
    硬件连接：
        USARTy(USART1) TX  -- PA9  连接  USARTz(USART2) RX -- PA3
        LED1(PA8)
        KEY1(PA4)

    引脚复用配置：
        N32G412: PA9  -> USART1_TX  (GPIO_AF4)
        N32G415: PA9  -> USART1_TX  (GPIO_AF0)
        N32G412: PA3  -> USART2_RX  (GPIO_AF4)
        N32G415: PA3  -> USART2_RX  (GPIO_AF4)

    测试步骤与现象：
        1) 编译并下载程序到开发板
        2) 程序运行后，LED1持续闪烁(USARTy发送数据，USARTz接收并翻转LED)
        3) 按下KEY1，USARTz进入静默模式，LED1停止闪烁
        4) 再次按下KEY1，USARTy发送地址唤醒数据(0x102)，USARTz被唤醒，LED1恢复闪烁

4、注意事项  
    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


-------------------------------------------------------------------------------
1. Function Description
    Demonstrates USART multi-processor communication using address-mark wakeup.
    USARTy (USART1) acts as transmitter, USARTz (USART2) acts as receiver. 
    USARTy address is set to 0x1, USARTz address is set to 0x2.
    USARTy continuously sends 0x33 to USARTz, LED1 toggles on each reception.
    Press KEY1 (PA4) to put USARTz into mute mode (LED1 stops toggling).
    Press KEY1 again to send address-matching data (0x102) to wake up USARTz.

2. Environment
    Software: KEIL MDK-ARM V5.34.0.0
              IAR EWARM 8.50.1
    Hardware: N32G41x Evaluation Board

    Chip Support:
        N32G412x8L7
        N32G412xBL7
        N32G415x8L7
        N32G415xBL7

3. Instructions
    System Clock Configuration:
        - HSI+PLL
        - SystemClock: N32G412:80MHz   N32G415:96MHz
    
    USARTy is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 9 data bits
    - 1 stop bit
    - Parity control disabled
    - Hardware flow control disabled
    - Receiver and transmitter enable
    - 16 times oversampling
    
    Hardware Connection:
        USARTy(USART1) TX  -- PA9  connect to  USARTz(USART2) RX -- PA3
        LED1(PA8)
        KEY1(PA4)

    Pin Alternate Function:
        N32G412: PA9  -> USART1_TX  (GPIO_AF4)
        N32G415: PA9  -> USART1_TX  (GPIO_AF0)
        N32G412: PA3  -> USART2_RX  (GPIO_AF4)
        N32G415: PA3  -> USART2_RX  (GPIO_AF4)

    Test steps and phenomena:
        1) Compile and download the program to the evaluation board
        2) After running, LED1 blinks continuously (USARTy sends data, USARTz receives and toggles LED)
        3) Press KEY1, USARTz enters mute mode, LED1 stops blinking
        4) Press KEY1 again, USARTy sends address wakeup data (0x102), USARTz wakes up, LED1 resumes blinking

4. Notes
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first

