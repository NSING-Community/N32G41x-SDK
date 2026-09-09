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
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
 */
#include "main.h"

ADC_InitType ADC_InitStructure;
__IO uint16_t ADCTempValue;
DMA_InitType DMA_InitStructure;

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;

uint32_t CCR6_Val       = 500;
uint32_t PrescalerValue = 0;

__IO uint16_t ADCConvertedValue[4] = {0};

void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPAMP_Configuration(void);
void TIM_Configuration(void);
void ADC_Initial(void);
void DMA_Config(void);
/**
*\*\name    main.
*\*\fun     Main program. Test PGA mode, OPAMP output can be viewed by oscilloscope.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();
    
    /* DMA configuration -------------------------------------------------------*/
    DMA_Config();
    
    /* OPAMP configuration -----------------------------------------------------*/
    OPAMP_Configuration();
    
    /* ADC configuration -------------------------------------------------------*/
    ADC_Initial();
    
    /* TIM Configuration */
    TIM_Configuration();
    
    /* TIMx enable counter */
    TIM_EnableCtrlPwmOutputs(ATIM1, ENABLE);
    TIM_Enable(ATIM1, ENABLE);
    
    while (1)
    {
    }
}

/**
*\*\name    DMA_Config.
*\*\fun     DMA_Initial program.
*\*\return  none
**/
void DMA_Config(void)
{
    DMA_DeInit(DMA_CH1);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC1->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)&ADCConvertedValue;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 4;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);

    DMA_RequestRemap(DMA_REMAP_ADC1, DMA, DMA_CH1, ENABLE);

    /* Enable DMA channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);
}

/**
*\*\name    OPAMP_Configuration.
*\*\fun     Configures OPAMP1 and OPAMP2 in PGA mode with gain x2.
*\*\param   none
*\*\return  none
**/
void OPAMP_Configuration(void)
{
    OPAMP_InitType OPAMP_InitStructure;

    OPAMP_StructInit(&OPAMP_InitStructure);
    OPAMP_InitStructure.Gain = OPAMP_CS_PGA_GAIN_2;
    OPAMP_InitStructure.Mode = OPAMP_CS_PGA_EN;
    OPAMP_InitStructure.OPAMP_Vpsel = OPAMP1_CS_VPSEL_PA1;
    OPAMP_InitStructure.OPAMP_Vpssel = OPAMP1_CS_VPSSEL_PA7;

    /* Configure OPAMP1: PGA mode, gain x2*/
    OPAMP_Init(OPAMP1, &OPAMP_InitStructure);
    OPAMP_Enable(OPAMP1, ENABLE);

    /* OPAMP output pin is automatically enabled when OPAMPx is enabled */
}

/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    /* ADCx configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_02_PA2, 1, ADC_SAMP_TIME_CYCLES_6);

    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);
    /*Check ADC1 Ready*/
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_RDY) == RESET)
        ;
    /* Enable ADC1 DMA */
    ADC_EnableDMA(ADC1, ENABLE);
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable OPAMP clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_OPAMP, ENABLE);
    
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
    
    /* Enable ADC1 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
    
    /* Enable ATIM1 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_ATIM1, ENABLE);
    
}

/**
*\*\name    TIM_Configuration.
*\*\fun     Configures the ATIM1.
*\*\param   none
*\*\return  none 
**/
void TIM_Configuration(void)
{
    TIM_DeInit(ATIM1);
    /* Compute the prescaler value */
    PrescalerValue = (uint32_t)((SystemCoreClock) / 12000) - 1;
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 1000;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_CENTER_ALIGN3;

    TIM_InitTimeBase(ATIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(ATIM1, TIM_FLAG_UPDATE);
    /* PWM1 Mode configuration: Channel1 */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 200;
    TIM_OCInitStructure.OCPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(ATIM1, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(ATIM1, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel6 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR6_Val;
    TIM_InitOc6(ATIM1, &TIM_OCInitStructure);

    TIM_ConfigOc6Preload(ATIM1, TIM_OC_PRE_LOAD_ENABLE);

    TIM_SelectOutputTrig(ATIM1,TIM_TRGO_SRC_UPDATE);

    TIM_ConfigArPreload(ATIM1, ENABLE);

}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure OPAMP1_VP (PA1) and OPAMP1_VPS (PA7) as analog inputs */
    GPIO_InitStructure.Pin            = OPAMP1_VP_PIN | OPAMP1_VPS_PIN | GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure OPAMP1_OUT (PA2) as analog outputs */
    GPIO_InitStructure.Pin = OPAMP1_OUT_PIN;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
