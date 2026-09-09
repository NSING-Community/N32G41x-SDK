1、功能说明
    1、ADC1规则通道采样PA1、PB1引脚的模拟电压，注入通道采样PC0、PC1引脚的模拟电压
    2、其中规则转换结果通过DMA通道读取到变量ADC_RegularConvertedValueTab[64]数组
       注入转换结果通过转换结束中断读取到变量ADC_InjectedConvertedValueTab[32]数组
2、使用环境
        IDE工具:  KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：
        基于N32G41x开发板开发

3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、中断：
            ADC1注入转换结果完成中断打开，优先级分组为2，抢断优先级0，子优先级0
            中断处理接收注入转换结果到ADC_InjectedConvertedValueTab[32]数组
        4、端口配置：
            PA0选择为模拟功能（ADC1_IN0）
            PA1选择为模拟功能（ADC1_IN1）
            PA2选择为模拟功能（ADC1_IN2）
            PA2选择为模拟功能（ADC1_IN3）
            PA12选择为外部EXTI事件上升沿触发
            PA11选择为外部EXTI事件上升沿触发
        5、DMA：
            DMA通道1循环模式搬运64个半字的ADC1规则通道转换结果到ADC_RegularConvertedValueTab[64]数组
        6、ADC：
            ADC1规则通道独立工作模式、扫描间断模式、EXTI12触发、12位数据右对齐，转换通道PA0和PA1的模拟电压数据
            ADC1注入通道独立工作模式、扫描模式、EXTI11触发、12位数据右对齐，转换通道PA2和PA3的模拟电压数据
    使用方法：
        1、编译后打开调试模式，将变量ADC_RegularConvertedValueTab[64],ADC_InjectedConvertedValueTab[32]添加到watch窗口观察
        2、通过PC10给上升沿可以触发规则通道数据采样，PC11给上升沿可以触发注入通道数据采样
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16)只能配置为HSI


1. Function description
    1. The ADC1 regular channel samples the analog voltage of the PA1 and PB1 pins, and the injection channel samples the analog voltage of the PC0 and PC1 pins.
    2. The regular conversion result is read into the variable ADC_RegularConvertedValueTab[64] array through the DMA channel.
       The injected conversion result is read into the variable ADC_InjectedConvertedValueTab[32] array through the conversion end interrupt.
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
        3. Interrupt:
            ADC1 injected conversion result complete interrupt on, priority group is 2, preemptive priority 0, sub priority 0
            The interrupt handler receives the injected conversion result into the ADC_InjectedConvertedValueTab[32] array
        4. Port configuration:
            PA1 is selected as the analog function (ADC1_IN0)
            PA1 is selected as the analog function (ADC1_IN1)
            PA2 is selected as the analog function (ADC1_IN2)
            PA3 is selected as the analog function (ADC1_IN3)
            PA12 is selected as external EXTI event rising edge trigger
            PA11 is selected as external EXTI event rising edge trigger
        5. DMA:
            DMA Channel 1 circular mode transfers 64 halfwords of ADC1 regular channel conversion results to ADC_RegularConvertedValueTab[64] array
        6. ADC:
            ADC1 regular channel independent working mode, scan intermittent mode, EXTI12trigger, 12-bit data right-aligned, convert the analog voltage data of channels PA0 and PA1
            ADC1 injected channel independent working mode, scan mode, EXTI11 trigger, 12-bit data right-aligned, and converts the analog voltage data of channels PA2 and PA3
    Instructions:
        1. Open the debug mode after compiling, and add the variables ADC_RegularConvertedValueTab[64], ADC_InjectedConvertedValueTab[32] to the watch window for observation
        2. The rising edge of PA12 can trigger regular channel data sampling, and the rising edge of PA11 can trigger the injection channel data sampling
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16) can only be configured as HSI
