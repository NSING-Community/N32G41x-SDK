1、功能说明
    1、ADC1采样转换内部温度传感器的模拟电压，并转换为温度值
    2、采用DMA循环模式将ADC1转换结果自动传输到变量ADCConvertedValue
    3、ADC1配置为连续转换模式，软件触发启动后自动循环采集
    4、通过串口输出实时温度值
2、使用环境
        IDE工具:  KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件环境：
        基于N32G41x开发板开发

3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、DMA：
            DMA通道1配置为循环模式，外设到内存方向，半字传输
            DMA请求源选择为ADC1（DMA_REMAP_ADC1）
        4、ADC：
            ADC1独立工作模式、连续转换、软件触发、12位数据右对齐，转换通道16即内部温度传感器的模拟电压数据
        5、Log配置：
            PA9选择为LOG的TX引脚
        6、USART：
            115200波特率、8位数据位、1位停止位、无奇偶校验位、无硬件流控、发送和接收使能
        7、功能函数：
            TempValue = TempratureCalculate(ADCConvertedValue)函数将温度ADC原始格式数据转为度的单位的格式

    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue,TempValue添加到watch窗口观察
        2、将串口工具连接到PA9引脚，并打开串口接收工具
        3、全速运行，可以看到温度变量的数值在常温下接近30度左右，同时串口工具显示实时芯片内的温度值
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16)只能配置为HSI
    温度传感器的采样时间需要足够长（建议不低于17.1us），本例程使用ADC_SAMP_TIME_CYCLES_600


1. Function description
    1. ADC1 samples and converts the analog voltage of the internal temperature sensor to the temperature value.
    2. DMA circular mode is used to automatically transfer ADC1 conversion results to the variable ADCConvertedValue.
    3. ADC1 is configured in continuous conversion mode, automatically cycling after software trigger start.
    4. Real-time temperature value is output through the serial port.
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
        3. DMA:
            DMA Channel 1 is configured in circular mode, peripheral-to-memory direction, half-word transfer
            DMA request source is selected as ADC1 (DMA_REMAP_ADC1)
        4. ADC:
            ADC1 independent working mode, continuous conversion, software-triggered, 12-bit data is right-aligned, conversion channel 16 is the analog voltage data of the internal temperature sensor
        5. Log Configuration:
            PA9 is the TX pin of LOG
        6. USART:
            115200 Baud rate, 8 data bits, 1 Stop bit, no parity bit, no hardware flow control, send and receive enabled
        7. Functions:
            The TempValue = TempratureCalculate(ADCConvertedValue) function converts temperature ADC raw format data into degrees

    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue, TempValue to the watch window for observation
        2. Connect the serial port tool to the PA9 pin and open the serial port receiver tool
        3. Running at full speed, it can be seen that the value of the temperature variable is close to 25 degrees at room temperature, and the serial port tool displays the real-time temperature value in the chip
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV16) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16) can only be configured as HSI
    The sampling time of the temperature sensor needs to be long enough (recommended no less than 17.1us), this example uses ADC_SAMP_TIME_CYCLES_600
