1、功能说明
    此例程演示COMP1的输出功能。COMP1的输出PA11受输入INP PB10和INM PB1的影响。
    通过PB2和PB3软件交替输出高低电平，经外部飞线连接到COMP1的INP和INM引脚，
    COMP1比较后在PA11输出比较结果。同时配置COMP1中断（EXTI Line21），在比较
    结果变化时触发中断。

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1

    芯片支持：
        N32G412
        N32G415

3、使用说明
    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、COMP1配置：
            INP：PB10（模拟输入）
            INM：PB1（模拟输入）
            OUT：PA11（复用推挽输出，N32G412: AF7, N32G415: AF7）
            滤波窗口：18，阈值：12
        4、脉冲发生引脚：PB2（推挽输出），PB3（推挽输出）
        5、中断：COMP1通过EXTI Line21，上升沿触发
        6、USART1（Log输出）：TX--PA9  波特率115200

    使用方法：
        1、编译后将程序下载到开发板并复位运行
        2、用飞线连接PB2到PB10（INP），PB3到PB1（INM）
        3、用示波器或逻辑分析仪观察PA11的输出波形
        4、当PB2输出高电平（INP > INM）时，PA11输出高电平；
           当PB2输出低电平（INP < INM）时，PA11输出低电平

4、注意事项
    1、COMP1的INP和INM引脚需配置为模拟输入模式。
    2、COMP1的OUT引脚需配置为复用推挽输出，并选择正确的AF功能。
    3、滤波阈值需大于滤波窗口的一半且小于滤波窗口。


1. Function description
    This example demonstrates the COMP1 output function. The output PA11 of
    COMP1 is affected by the input INP PB10 and INM PB1.
    PB2 and PB3 alternate between high and low levels by software. They are
    connected to COMP1 INP and INM pins via jumper wires. COMP1 compares the
    inputs and outputs the result on PA11. COMP1 interrupt (EXTI Line21) is
    also configured to trigger on comparison result changes.

2. Development environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Supported chips:
        N32G412
        N32G415

3. How to use
    System Configuration:
        1. Clock source: HSI+PLL
        2. System clock frequency: N32G412:80MHz   N32G415:96MHz
        3. COMP1 configuration:
            INP: PB10 (analog input)
            INM: PB1 (analog input)
            OUT: PA11 (alternate push-pull, N32G412: AF7, N32G415: AF7)
            Filter window: 18, Threshold: 12
        4. Pulse generator pins: PB2 (push-pull output), PB3 (push-pull output)
        5. Interrupt: COMP1 via EXTI Line21, rising edge trigger
        6. USART1 (Log output): TX--PA9  baudrate 115200

    Instructions:
        1. Compile and flash the program to the development board, then reset
        2. Connect PB2 to PB10 (INP) and PB3 to PB1 (INM) via jumper wires
        3. Use an oscilloscope or logic analyzer to observe the output waveform on PA11
        4. When PB2 outputs high (INP > INM), PA11 outputs high;
           When PB2 outputs low (INP < INM), PA11 outputs low

4. Notes
    1. COMP1 INP and INM pins must be configured as analog input mode.
    2. COMP1 OUT pin must be configured as alternate push-pull with the correct AF function.
    3. Filter threshold must be greater than half of filter window and less than filter window.
