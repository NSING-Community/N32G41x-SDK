1、功能说明
    1、ADC1采样，使能偏移补偿功能
    2、通过DMA将ADC1转换结果传输到变量ADCConvertedValue
    3、偏移补偿配置：正方向偏移0x400，使能饱和功能
    4、转换结果 = ADC原始值 + 0x400（饱和到0x000~0xFFF范围）
2、使用环境
        IDE工具:  KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：
        基于N32G41x开发板开发

3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、端口配置：
            PB1选择为模拟功能（ADC1_IN9）
        4、ADC：
            ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换PB1的模拟电压数据
            偏移寄存器1配置：监控PB1通道，正方向偏移0x400，使能饱和
        5、DMA：
            DMA通道1循环模式搬运ADC1转换结果到ADCConvertedValue变量
    使用方法：
        1、编译下载代码到芯片，全速运行
        2、通过调试器观察ADCConvertedValue变量值，该值为ADC原始转换值加上偏移量0x400
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16)只能配置为HSI


1. Function description
    1. ADC1 sampling with offset compensation enabled
    2. ADC1 conversion results transferred to variable ADCConvertedValue via DMA
    3. Offset compensation configuration: positive direction offset 0x400, saturation enabled
    4. Conversion result = ADC raw value + 0x400 (saturated to 0x000~0xFFF range)
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
        3. Port configuration:
            PB1 is selected as the analog function (ADC1_IN9)
        4. ADC:
            ADC1 independent working mode, continuous conversion, software trigger, 12-bit data right-aligned, converts PB1 analog voltage data
            Offset register 1 configuration: monitors PB1 channel, positive direction offset 0x400, saturation enabled
        5. DMA:
            DMA channel 1 circular mode transfers ADC1 conversion results to ADCConvertedValue variable
    Instructions:
        1. Compile and download the code to the chip, then run at full speed
        2. Observe the ADCConvertedValue variable value through the debugger, which is the ADC raw conversion value plus offset 0x400
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16) can only be configured as HSI
