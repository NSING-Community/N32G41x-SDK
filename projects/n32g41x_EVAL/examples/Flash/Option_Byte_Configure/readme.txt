1、功能说明
    /* 简单描述工程功能 */
        这个例程配置并演示如何配置选项字节

2、使用环境
    硬件环境：N32G41x开发板
    软件环境：
        - Keil MDK-ARM V5.x
        - IAR EWARM V8.50

3、使用说明
    系统配置：
        1. 时钟源：HSI + PLL
        2. 时钟频率：N32G412:80MHz   N32G415:96MHz
        3. USART1用于log输出（波特率115200）
    使用方法：
        1. 编译并下载程序到N32G41x开发板
        2. 打开串口终端，查看Option Byte操作结果

4、注意事项
    - 修改Option Byte后可能需要系统复位才能生效
    - 请谨慎操作RDP（读保护）相关配置
    - 开启RDP2后无法撤销，请勿在调试阶段使用
    - 写保护配置后，相关页将无法编程和擦除

1. Function Description
    /* Briefly describe the project function */
         This routine configures and demonstrates how to configure option bytes

2. Environment
    Hardware: N32G41x evaluation board
    Software:
        - Keil MDK-ARM V5.x
        - IAR EWARM V8.50

3. Instructions
    System Configuration:
        1. Clock: HSI + PLL
        2. Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. USART1 for log output (baud rate 115200)
    Usage:
        1. Compile and download to N32G41x evaluation board
        2. Open serial terminal to view Option Byte operation results

4. Notes
    - System reset may be required after Option Byte modification
    - Be careful with RDP (read protection) configuration
    - RDP2 cannot be reverted once enabled, do not use during debugging
    - Write-protected pages cannot be programmed or erased
