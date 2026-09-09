1、功能说明
    1、ADC1采样转换PB1引脚的模拟电压，如果超过模拟看门狗定义的阈值范围，则跳入中断程序
2、使用环境
        IDE工具:  KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：
        基于N32G41x开发板开发

3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、ADC：
            ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换PB1引脚的模拟电压数据
        4、端口配置：
            PB1选择为模拟功能（ADC1_IN9）
        5、中断：
            ADC1模拟看门狗中断打开，优先级分组为2，抢断优先级0，子优先级0
        6、模拟看门狗：
            高阈值：0x0B00，低阈值：0x0300
    使用方法：
        1、编译后打开调试模式，将变量gCntAwdg添加到watch窗口观察
        2、改变PB1引脚电压值，当电压值超出模拟看门狗定义的阈值范围外，则进入一次中断，变量做累加操作
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16)只能配置为HSI


1. Function description
    1. ADC1 samples and converts the analog voltage of the PB1 pin. If it exceeds the threshold range defined by the analog watchdog, it will jump into the interrupt program.
2. Use environment
    Software development environment:
        IDE TOOLS:  KEIL MDK-ARM V5.34.0.0
                    IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the N32G41x evaluation board

3. Instructions for use
   System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. ADC:
            ADC1 independent working mode, continuous conversion, software trigger, 12-bit data right-aligned, convert the analog voltage data of PB1 pin
        4. Port configuration:
            PB1 is selected as the analog function (ADC1_IN9)
        5. Interrupt:
            ADC1 analog watchdog interrupt on, priority group is 2, preemptive priority 0, sub priority 0
        6. Analog watchdog:
            High threshold: 0x0B00, Low threshold: 0x0300
    Instructions:
        1. After compiling, open the debug mode and add the variable gCntAwdg to the watch window to observe
        2. Change the voltage value of the PB1 pin. When the voltage value exceeds the threshold range defined by the analog watchdog, it will enter an interrupt and the variable will be accumulated.
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16) can only be configured as HSI
