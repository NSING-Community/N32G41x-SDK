1、功能说明
    1、OPAMP1通过ATIM1_CC6做切换，输出电压是输入电压的2倍.
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
            PA1选择为模拟功能（OPAMP1 VP正向输入）
            PA7选择为模拟功能（OPAMP1 VPS正向输入）
            PA2选择为模拟功能（OPAMP1 VOUT输出）
            PA2选择为模拟功能（ADC1通道2输入）
        4、OPAMP：
            OPAMP1配置为PGA模式，增益2倍
    使用方法：
        1、编译后打开调试模式，将PA1,PA7引脚接入一定的电压，ADCConvertedValue的数据分别是PA1,PA7放大2倍的值；
4、注意事项
    G41x内嵌4个独立的OPAMP，本例程仅使用OPAMP1
    PGA模式下VM引脚内部连接反馈网络，未使用的VM引脚可作为普通GPIO使用
    OPAMP输出范围为0.4V到VDDA-0.4V
    经过PGA放大后的电压不能超过(VDDA-0.3)V,且不能低于0.3V；
    需要确保PGA切换(ATIM1_CC6)速度大于ADC转换速率.

1. Function description
    1. OPAMP1 is switched by ATIM1_CC6, and the output voltage is twice the input voltage.
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
            PA1 is selected as analog function (OPAMP1 VP positive input)
            PA7 is selected as analog function (OPAMP1 VPS positive input)
            PA2 is selected as analog function (OPAMP1 VOUT output)
            PA2 is selected as analog function (input of ADC1 Channel 2).
        4. OPAMP:
            OPAMP1 configured in PGA mode, gain x2
    Instructions:
        1. After compilation, enable debug mode, apply a certain voltage to the PA1 and PA7 pins. The values of ADCConvertedValue are                 twice the amplified voltages of PA1 and PA7 respectively.
4. Attention
    G41x has 4 independent OPAMPs, this example only uses OPAMP1 and OPAMP2
    In PGA mode, the VM pin is internally connected to the feedback network, unused VM pins can be used as general GPIO
    OPAMP output range is 0.4V to VDDA-0.4V
    The amplified voltage of the PGA should not exceed (VDDA-0.3)V，and could not  below 0.3V；
    It is necessary to ensure that the switching speed(ATIM1_CC6) of PGA is greater than the ADC conversion rate.