1、功能说明
    1、ADC1采样转换PB1引脚的模拟电压
    2、采用DMA循环模式将ADC1转换结果自动传输到变量ADCConvertedValue
    3、ADC1配置为连续转换模式，软件触发启动后自动循环采集
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
        4、DMA：
            DMA通道1配置为循环模式，外设到内存方向，半字传输
            DMA请求源选择为ADC1（DMA_REMAP_ADC1）
        5、ADC：
            ADC1独立工作模式、软件触发、连续转换、12位数据右对齐，转换PB1的模拟电压数据

    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、通过改变PB1引脚的电压，可以看到转换结果变量同步改变
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16)只能配置为HSI


1. Function description
    1. ADC1 samples and converts the analog voltage of PB1 pin.
    2. DMA circular mode is used to automatically transfer ADC1 conversion results to the variable ADCConvertedValue.
    3. ADC1 is configured in continuous conversion mode, automatically cycling after software trigger start.
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
        4. DMA:
            DMA Channel 1 is configured in circular mode, peripheral-to-memory direction, half-word transfer
            DMA request source is selected as ADC1 (DMA_REMAP_ADC1)
        5. ADC:
            ADC1 independent working mode, software-triggered, continuous conversion, 12-bit data is right-aligned, and analog voltage data of PB1 is converted

    Instructions:
        1. Open the debug mode after compiling, add the variable ADCConvertedValue to the watch window for observation
        2. By changing the voltage of PB1 pin, you can see that the conversion result variable changes synchronously
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16) can only be configured as HSI
