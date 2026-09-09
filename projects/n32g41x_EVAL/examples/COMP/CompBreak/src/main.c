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

/** CompBreak **/

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

void RCC_Configuration(void);
void GPIO_CompConfiguration(void);
void GPIO_TimConfiguration(void);
void COMP_Configuration(void);
void TIM_Initial(TIM_Module* TIMx);
void ChangeVmVp(void);

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration */
    RCC_Configuration();

    /* GPIO configuration */
    GPIO_CompConfiguration();
    GPIO_TimConfiguration();

    /* ATIM1 & ATIM2 PWM configuration */
    TIM_Initial(ATIM1);

    /* COMP configuration */
    COMP_Configuration();

    while (1)
    {
        ChangeVmVp();
    }
}

/**
*\*\name    ChangeVmVp.
*\*\fun     Toggle pulse generator pins to produce test signal for COMP inputs.
*\*\param   none
*\*\return  none
**/
void ChangeVmVp(void)
{
    uint32_t i;

    GPIO_SetBits(PULSE_INP_GPIO, PULSE_INP_PIN);
    GPIO_ResetBits(PULSE_INM_GPIO, PULSE_INM_PIN);
    for (i = 0; i < 1000; i++)
        ;

    GPIO_ResetBits(PULSE_INP_GPIO, PULSE_INP_PIN);
    GPIO_SetBits(PULSE_INM_GPIO, PULSE_INM_PIN);
    for (i = 0; i < 1000; i++)
        ;
}

/**
*\*\name    COMP_Configuration.
*\*\fun     Configure COMP1 module as break source for ATIM1 and ATIM2.
*\*\param   none
*\*\return  none
**/
void COMP_Configuration(void)
{
    COMP_InitType COMP_Initial;

    /* Set internal reference voltage: Vv1Trim=32, Vv1En=true */
    COMP_SetRefScl(0, false, 0, false, 32, true);

    /* Initialize COMP1 */
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_INPSEL_PB10;
    COMP_Initial.InmSel     = COMP1_INMSEL_PB1;
    COMP_Initial.SampWindow = 30;       /* (0~31) */
    COMP_Initial.Threshold  = 18;       /* should be > SampWindow/2 and < SampWindow */
    COMP_Init(COMP1, &COMP_Initial);

    /* Enable COMP1 as break source for ATIM1 and ATIM2 */
    TIM_BreakInputSourceEnable(ATIM1, TIM_BREAK_COMP1, TIM_BREAK_COMP1P, ENABLE);
    TIM_BreakInputSourceEnable(ATIM2, TIM_BREAK_COMP1, TIM_BREAK_COMP1P, ENABLE);

    /* Enable COMP1 */
    COMP_Enable(COMP1, ENABLE);
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configure system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable COMP and COMP filter clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMPFILT, ENABLE);

    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable ATIM1 and ATIM2 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_ATIM1 | RCC_APB2_PERIPH_ATIM2, ENABLE);
}

/**
*\*\name    TIM_Initial.
*\*\fun     Configure ATIM for PWM output with break enabled.
*\*\param   TIMx: ATIM1 or ATIM2
*\*\return  none
**/
void TIM_Initial(TIM_Module* TIMx)
{
    TimerPeriod   = 50;
    /* CH1 duty cycle 50% */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Prescaler   = 0;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period      = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv      = 0;
    TIM_TimeBaseStructure.RepetCnt    = 0;
    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc1(TIMx, &TIM_OCInitStructure);

    /* Break and Dead Time configuration */
    TIM_InitBkdtStruct(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.OSSRState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OSSIState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LOCKLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStructure.DeadTime        = 1;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
    TIM_ConfigBkdt(TIMx, &TIM_BDTRInitStructure);

    /* Enable TIMx counter */
    TIM_Enable(TIMx, ENABLE);

    /* Enable TIMx Main Output */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);
}

/**
*\*\name    GPIO_CompConfiguration.
*\*\fun     Configure GPIO pins for COMP1.
*\*\param   none
*\*\return  none
**/
void GPIO_CompConfiguration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* COMP1 INP: PB10 - analog input */
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pin       = COMP1_INP_PIN;
    GPIO_InitPeripheral(COMP1_INP_GPIO, &GPIO_InitStructure);

    /* COMP1 INM: PB1 - analog input */
    GPIO_InitStructure.Pin = COMP1_INM_PIN;
    GPIO_InitPeripheral(COMP1_INM_GPIO, &GPIO_InitStructure);

    /* COMP1 OUT: PB6 - alternate push-pull (for observation) */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pin            = COMP1_OUT_PIN;
    GPIO_InitStructure.GPIO_Alternate = COMP1_OUT_AF;
    GPIO_InitPeripheral(COMP1_OUT_GPIO, &GPIO_InitStructure);

    /* Pulse generator: PB2, PB3 - push-pull output */
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin       = PULSE_INP_PIN;
    GPIO_InitPeripheral(PULSE_INP_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = PULSE_INM_PIN;
    GPIO_InitPeripheral(PULSE_INM_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    GPIO_TimConfiguration.
*\*\fun     Configure GPIO pins for ATIM1 and ATIM2 PWM output.
*\*\param   none
*\*\return  none
**/
void GPIO_TimConfiguration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;

    /* ---- ATIM1 CH1 ---- */
    /* ATIM1 CH1: PA8 */
    GPIO_InitStructure.Pin            = ATIM1_CH1_PIN;
    GPIO_InitStructure.GPIO_Alternate = ATIM1_CH1_AF;
    GPIO_InitPeripheral(ATIM1_CH1_GPIO, &GPIO_InitStructure);

}

#ifdef USE_FULL_ASSERT
/**
*\*\name    assert_failed.
*\*\fun     Assert failure handler for debug.
*\*\param   expr: failed expression string
*\*\param   file: source file name
*\*\param   line: line number
*\*\return  none
**/
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif
