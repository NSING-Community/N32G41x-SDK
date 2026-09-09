1、功能说明
    此例程演示了SLEEP低功耗模式。系统进入SLEEP模式后，CPU停止执行。
    通过WKUP (PA0) 按键产生外部中断唤醒CPU，唤醒后无需重新配置
    时钟，立即恢复正常运行。

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
        3. WKUP (PA0) 配置为外部中断输入
        4. USART1：TX - PA9，波特率115200，用于log输出
    使用方法：
        1. 编译并下载程序到N32G41x开发板
        2. 打开串口终端
        3. 系统进入SLEEP模式
        4. 按下WKUP按键唤醒系统
        5. 观察串口输出唤醒信息

4、注意事项
    在评估功耗的时候，要注意去掉打印

1. Function Description
    This demo demonstrates SLEEP low-power mode. After entering SLEEP mode, the CPU stops . 
    The CPU is woken up by WKUP (PA0) key press (EXTI0 interrupt). No clock reconfiguration
    is needed after wakeup, the system resumes immediately.

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
        3. WKUP (PA0) configured as external interrupt input 
        4. USART1: TX - PA9, baud rate 115200, for log output
    Usage:
        1. Compile and download to N32G41x evaluation board
        2. Open serial terminal
        3. Then system enters SLEEP mode
        4. Press WKUP key to wake up the system
        5. Observe wakeup message on serial terminal

4. Notes
    When evaluating power consumption, pay attention to removing the printf
