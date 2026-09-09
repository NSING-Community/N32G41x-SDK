1、功能说明
    1、OPAMP1和OPAMP2配置为PGA模式，放大输入电压2倍
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
            PA7选择为模拟功能（OPAMP2 VP正向输入）
            PA2选择为模拟功能（OPAMP1 VOUT输出）
            PA6选择为模拟功能（OPAMP2 VOUT输出）
        4、OPAMP：
            OPAMP1和OPAMP2配置为PGA模式，增益2倍
    使用方法：
        1、编译后打开调试模式，用示波器观察OPAMP1和OPAMP2的输入和输出
        2、OPAMP输出 = 2 × OPAMP输入
4、注意事项
    G41x内嵌4个独立的OPAMP，本例程仅使用OPAMP1和OPAMP2
    PGA模式下VM引脚内部连接反馈网络，未使用的VM引脚可作为普通GPIO使用
    OPAMP输出范围为0.4V到VDDA-0.4V


1. Function description
    1. OPAMP1 and OPAMP2 configured in PGA mode, amplifying the input voltage by 2 times
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
            PA7 is selected as analog function (OPAMP2 VP positive input)
            PA2 is selected as analog function (OPAMP1 VOUT output)
            PA6 is selected as analog function (OPAMP2 VOUT output)
        4. OPAMP:
            OPAMP1 and OPAMP2 configured in PGA mode, gain x2
    Instructions:
        1. Open the debug mode after compiling, and observe the input and output of OPAMP1 and OPAMP2 with an oscilloscope
        2. OPAMP output = 2 x OPAMP input
4. Attention
    G41x has 4 independent OPAMPs, this example only uses OPAMP1 and OPAMP2
    In PGA mode, the VM pin is internally connected to the feedback network, unused VM pins can be used as general GPIO
    OPAMP output range is 0.4V to VDDA-0.4V
