/**
*     Copyright (c) 2025, Nsing Technologies Inc.
*
*     All rights reserved.
*
*     This software is the exclusive property of Nsing Technologies Inc. (Hereinafter
* referred to as Nsing). This software, and the product of Nsing described herein
* (Hereinafter referred to as the Product) are owned by Nsing under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     Nsing does not grant any license under its patents, copyrights, trademarks, or other
* intellectual property rights. Names and brands of third party may be mentioned or referred
* thereto (if any) for identification purposes only.
*
*     Nsing reserves the right to make changes, corrections, enhancements, modifications, and
* improvements to this software at any time without notice. Please contact Nsing and obtain
* the latest version of this software before placing orders.

*     Although Nsing has attempted to provide accurate and reliable information, Nsing assumes
* no responsibility for the accuracy and reliability of this software.
*
*     It is the responsibility of the user of this software to properly design, program, and test
* the functionality and safety of any application made of this information and any resulting product.
* In no event shall Nsing be liable for any direct, indirect, incidental, special,exemplary, or
* consequential damages arising in any way out of the use of this software or the Product.
*
*     Nsing Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify Nsing and hold Nsing
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by Nsing, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     Nsing products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations.
* User shall comply with any applicable export control laws and regulations promulgated and administered by
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file      main.c
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "main.h"

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
RCC_ClocksType RCC_ClocksStructure;
/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System Clocks Configuration*/
    SetSysClockToPLL(RCC_PLL_SRC_HSE,72000000);
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /*
    TIMx Configuration to:

    1/ Generate 4 complementary PWM signals with 4 different duty cycles:
    TIMxCLK is fixed to SystemCoreClock, the TIMx Prescaler is equal to 0 so the
    TIMx counter clock used is PLL.

    The objective is to generate PWM signal at 16KHz:
    - TIMx_Period = (PLL / 16000) - 1

    The Four Duty cycles are computed as the following description:

    The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
    The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
    The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
    The channel 4 duty cycle is set to 12.5% so channel 4N is set to 87.5%.
    The Timer pulse is calculated as follows:
      - ChannelxPulse = DutyCycle * (TIMx_Period - 1) / 100

    2/ Insert a dead time
    3/ Configure the break feature, active at High level, and using the automatic
     output enable feature
    4/ Use the Locking parameters level off.
    */
    RCC_GetClocksFreqValue(&RCC_ClocksStructure);
    /* Compute the value to be set in AR register to generate signal frequency at 16KHz */
    TimerPeriod = (RCC_ClocksStructure.PllFreq / 16000) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT2 value to generate a duty cycle at 25% for channel 2 */
    Channel2Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);
    /* Compute CCDAT3 value to generate a duty cycle at 12.5% for channel 3 */
    Channel3Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000);
    /* Compute CCDAT4 value to generate a duty cycle at 12.5% for channel 4 */
    Channel4Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000);

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Prescaler   = 0;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period      = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv      = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.RepetCnt    = 0;
    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OCN_IDLE_STATE_RESET;

    TIM_InitOc1(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel4Pulse;
    TIM_InitOc4(TIMx, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration */
    TIM_InitBkdtStruct(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.OSSRState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OSSIState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LOCKLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStructure.DeadTime        = 10;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
    TIM_ConfigBkdt(TIMx, &TIM_BDTRInitStructure);

    TIM_BreakInputSourceEnable(TIMx, TIM_BREAK_IOM1, TIM_BREAK_SOURCE_POLARITY_NONINVERT, ENABLE);

    /* TIMx counter enable */
    TIM_Enable(TIMx, ENABLE);

    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Config ATIM1 clock source:PLL(144Mhz)*/
    RCC_ConfigAtim1Clk(RCC_ATIM1_CLKSEL_PLL);
    
    /* Enable ATIM1 clock */
    RCC_EnableAPB2PeriphClk(TIMx_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the GPIO pins.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* ATIM1 CH1: PA8 */
    GPIO_InitStructure.Pin            = TIMx_CH1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH1_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH1_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH2: PA9 */
    GPIO_InitStructure.Pin            = TIMx_CH2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH2_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH2_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH3: PA10 */
    GPIO_InitStructure.Pin            = TIMx_CH3_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH3_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH3_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH4: PA11 */
    GPIO_InitStructure.Pin            = TIMx_CH4_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH4_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH4_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH1N: PB13 */
    GPIO_InitStructure.Pin            = TIMx_CH1N_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH1N_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH1N_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH2N: PB14 */
    GPIO_InitStructure.Pin            = TIMx_CH2N_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH2N_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH2N_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH3N: PB15 */
    GPIO_InitStructure.Pin            = TIMx_CH3N_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH3N_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH3N_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 CH4N: PB2 */
    GPIO_InitStructure.Pin            = TIMx_CH4N_GPIO_PIN;
    GPIO_InitStructure.GPIO_Alternate = TIMx_CH4N_GPIO_AF;
    GPIO_InitPeripheral(TIMx_CH4N_GPIO_PORT, &GPIO_InitStructure);

    /* ATIM1 BKIN1: PA6 */
    GPIO_InitStructure.Pin            = TIMx_BKIN_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Alternate = TIMx_BKIN_GPIO_AF;
    GPIO_InitPeripheral(TIMx_BKIN_GPIO_PORT, &GPIO_InitStructure);
}

/**
*\*\name    SetSysClockToPLL.
*\*\fun     Selects PLL clock as System clock source and configure HCLK, PCLK2 and PCLK1.
*\*\param   PLL_src
*\*\         - RCC_PLL_SRC_HSI
*\*\         - RCC_PLL_SRC_HSE
*\*\param   SYS_freq
*\*\         - 72000000  (sysclk-72M, pll-144M, hclk-72M, pclk2-72M, pclk1-36M)
*\*\         - 80000000  (sysclk-80M, pll-80M, hclk-80M, pclk2-80M, pclk1-40M)
*\*\return  SUCCESS or ERROR
*\*\note    Fin frequency requirement is in the range of 8MHz ~ 32MHz,
*\*\        Fvco(=Fin/pllinpre*pllmul) frequency requirement is in the range of 100MHz ~ 160MHz,
*\*\        Fout(=Fvco/plloutdiv) frequency requirement is in the range of 64MHz ~ 160MHz. 
**/
ErrorStatus SetSysClockToPLL(uint32_t PLL_src, uint32_t SYS_freq)
{
    uint32_t timeout_value = 0xFFFFFFFF;
    ErrorStatus ClockStatus;
    uint32_t latency;
    uint32_t pllmul, pllinpre, plloutdiv;
    FunctionalState pllsysdiv;
    
    if ((PLL_src == RCC_PLL_SRC_HSE)&&(HSE_VALUE != 8000000))
    {
        /* HSE_VALUE == 8000000 is needed in this project! */
        return ERROR;
    }

    /* RCC system reset */
    FLASH_SetLatency(FLASH_LATENCY_2);
    RCC_DeInit();

    if (PLL_src == RCC_PLL_SRC_HSE)
    {
        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Wait till HSE is ready */
        ClockStatus = RCC_WaitHseStable();
    }
    else
    {
        /* Enable HSI */
        RCC_EnableHsi(ENABLE);

        /* Wait till HSI is ready */
        ClockStatus = RCC_WaitHsiStable();
    }

    if (ClockStatus != SUCCESS)
    {
        return ERROR;
    }

    /* Configure PLL input prescaler based on clock source
     * HSI = 16MHz -> PLLINPRES = /4 -> 4MHz 
     * HSE = 8MHz  -> PLLINPRES = /2 -> 4MHz  */
    if (PLL_src == RCC_PLL_SRC_HSI)
    {
        pllinpre = 4;
    }
    else
    {
        pllinpre = 2;
    }

    switch (SYS_freq)
    {
        case 72000000:
            /* 4MHz * 36 = 144MHz(FVCO) / 1(PLLOD) /1 = 144MHz(Fpll) */
            latency   = FLASH_LATENCY_1;   /* 36MHz < SYSCLK <= 72MHz */
            pllmul    = 36;
            plloutdiv = RCC_PLL_OD_DIV_1;
            pllsysdiv = ENABLE;
            break;
        case 80000000:
            /* 4MHz * 40 = 160MHz(FVCO) / 2(PLLOD) /1 = 80MHz(Fpll) */
            latency   = FLASH_LATENCY_2;   /* 72MHz < SYSCLK <= 80MHz */
            pllmul    = 40;
            plloutdiv = RCC_PLL_OD_DIV_2;
            pllsysdiv = DISABLE;
            break;
        default:
            return ERROR;
    }

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(RCC_HCLK_DIV1);

    /* PCLK1 = HCLK/2 */
    RCC_ConfigPclk1(RCC_HCLK_DIV2);

    /* Configure PLL: source, input prescaler, multiplier, output prescaler */
    RCC_ConfigPll(PLL_src, pllinpre, pllmul, plloutdiv);

    /* Enable PLL */
    RCC_EnablePll(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) != SET)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }
    
    /* Enable or Disable PLLSYSDIV (SYSCLK = FPLL / pllsysdiv) */
    RCC_EnablePllSysclkDiv(pllsysdiv);

    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL);

    /* Wait till PLL is used as system clock source */
    timeout_value = 0xFFFFFFFF;
    while (RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }

    FLASH_SetLatency(latency);
    return SUCCESS;
}


