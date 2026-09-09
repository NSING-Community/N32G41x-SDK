1、功能说明
    1、COMP1的输出刹车ATIM1信号，COMP OUT变低后恢复ATIM1波形
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.06 / IAR EWARM V8.50
    硬件环境：      基于N32G41x-STB开发
3、使用说明
    系统配置；
        1、时钟源：HSI+PLL
        2、系统时钟频率：N32G412:80MHz   N32G415:96MHz
        3、端口配置：
            PB10选择为模拟功能COMP1 INP
            PB1选择为模拟功能COMP1 INM
            PB6选择为COMP1 OUT输出(AF7)
            PB2选择为IO输出(脉冲发生器连接INP)
            PB3选择为IO输出(脉冲发生器连接INM)
            PA8选择为ATIM1 CH1输出(N32G412:AF2, N32G415:AF1)
        4、TIM：
            ATIM1开启CH1输出,COMP作为刹车输入
        5、COMP：
            COMP1通过TIM_BreakInputSourceEnable触发ATIM1刹车，无输出时恢复ATIM1输出
    使用方法：
        1、编译后打开调试模式，将PB2连接到PB10，PB3连接到PB1，利用示波器或者逻辑分析仪观察ATIM1输出波形
        2、当软件输出PB2电平大于PB3时，TIM波形消失，相反时，波形正常输出
4、注意事项
    1、ATIM1通道1、2、3、4均支持互补输出
    2、PA8和PA9的ATIM1复用功能AF值在N32G412和N32G415之间有差异，已通过条件编译宏切换
    3、G41x使用TIM_BreakInputSourceEnable()将COMP连接到定时器刹车输入，不使用COMP_SetOutTrig()


1. Function description
    1. The output of COMP1 brakes the complementary signals of ATIM1 . After COMP OUT becomes low, the waveforms of ATIM1 are restored.
2. Use environment
    Software development environment: KEIL MDK-ARM V5.06 / IAR EWARM V8.50
    Hardware environment: Developed based on the evaluation board N32G41x-STB
3. Instructions for use
    System Configuration;
        1. Clock source: HSI+PLL
        2. System Clock frequency: N32G412:80MHz   N32G415:96MHz
        3. Port configuration:
            PB10 is selected as analog function, COMP1 INP
            PB1 is selected as analog function, COMP1 INM
            PB6 is selected as COMP1 OUT output (AF7)
            PB2 is selected as IO output (pulse generator connected to INP)
            PB3 is selected as IO output (pulse generator connected to INM)
            PA8 is selected as ATIM1 CH1 output (N32G412:AF2, N32G415:AF1)
        4.TIM:
            ATIM1 turns on CH1 output, COMP is used as brake input
        5. COMP:
            COMP1 triggers ATIM1 brake via TIM_BreakInputSourceEnable, output of ATIM1 is restored when there is no output
    Instructions:
        1. Open the debug mode after compiling, connect PB2 to PB10, connect PB3 to PB1, and use an oscilloscope or logic analyzer to observe the output waveforms of ATIM1 and ATIM2
        2. When the software output PB2 level is greater than PB3, the TIM waveform disappears, on the contrary, the waveform is output normally
4. Attention
    1. ATIM1 channels 1, 2, 3, 4 all support complementary output,
    2. The ATIM1 alternate function AF values of PA8 and PA9 differ between N32G412 and N32G415, switched via conditional compilation macros
    3. G41x uses TIM_BreakInputSourceEnable() to connect COMP to timer break input, does not use COMP_SetOutTrig()
