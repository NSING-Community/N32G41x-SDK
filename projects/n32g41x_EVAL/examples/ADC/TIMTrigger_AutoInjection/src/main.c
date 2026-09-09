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
DMA_InitType DMA_InitStructure;
__IO uint16_t ADC_RegularConvertedValueTab[32], ADC_InjectedConvertedValueTab[32];
uint32_t gCnt = 0;
uint32_t PrescalerValue = 0;
uint32_t Pluse_Val      = 800;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Config(void);
void TIM_Configuration(void);
void NVIC_Configuration(void);

/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    ADC_InitStruct(&ADC_InitStructure);
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIG_REG_CONV_GTIM1_CC4;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* ADC1 regular channel configuration */
    ADC_ConfigRegularChannel(ADC1, ADC_REG_CH_CHANNEL, 1, ADC_SAMP_TIME_CYCLES_240);
    /* Set injected sequencer length */
    ADC_ConfigInjectedSequencerLength(ADC1, 1);
    /* ADC1 injected channel configuration */
    ADC_ConfigInjectedChannel(ADC1, ADC_INJ_CH_CHANNEL, 1, ADC_SAMP_TIME_CYCLES_240);
    /* Enable automatic injected conversion start after regular one */
    ADC_EnableAutoInjectedConv(ADC1, ENABLE);

    /* Enable JENDC interrupt */
    ADC_ConfigInt(ADC1, ADC_INT_JENDC, ENABLE);

    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY) == RESET)
        ;
    /* Enable ADC1 DMA */
    ADC_EnableDMA(ADC1, ENABLE);
}

/**
*\*\name    main.
*\*\fun     Main program. ADC TIM trigger and auto injection demo.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ----------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration -------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration -------------------------------------------------------*/
    GPIO_Configuration();

    /* TIM configuration -------------------------------------------------------*/
    TIM_Configuration();

    /* DMA channel1 configuration -----------------------------------------------*/
    DMA_Config();

    /* ADC1 configuration -------------------------------------------------------*/
    ADC_Initial();

    /* GTIM1 counter enable */
    TIM_Enable(GTIM1, ENABLE);

    while (1)
    {
        gCnt++;
    }
}


/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable GTIM1 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM1, ENABLE);

    /* Enable ADC1 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);

    /* RCC_ADCSYSCLK_DIV16 */
    ADC_ClockModeConfig(RCC_ADCSYSCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16);  /* select HSI as RCC ADC1M CLK Source */
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure PA1 as analog input (ADC regular channel) ---------------------*/
    GPIO_InitStructure.Pin            = ADC_REG_CH_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(ADC_REG_CH_PORT, &GPIO_InitStructure);

    /* Configure PB1 as analog input (ADC injected channel) --------------------*/
    GPIO_InitStructure.Pin            = ADC_INJ_CH_PIN;
    GPIO_InitPeripheral(ADC_INJ_CH_PORT, &GPIO_InitStructure);

    /* Configure PA3 as GTIM1 CH4 PWM output -----------------------------------*/
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = TIM_CH4_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = TIM_CH4_AF;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(TIM_CH4_PORT, &GPIO_InitStructure);

    /* Configure PC6 as output -------------------------------------------------*/
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = GPIO_TOGGLE_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(GPIO_TOGGLE_PORT, &GPIO_InitStructure);
}

/**
*\*\name    TIM_Configuration.
*\*\fun     Configures the GTIM1 timer.
*\*\return  none
**/
void TIM_Configuration(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;

    /* GTIM1 configuration -----------------------------------------------------*/
    /* Time Base configuration */
    PrescalerValue = (uint32_t)(SystemCoreClock / 16000000) - 1;
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period      = 1600;
    TIM_TimeBaseStructure.Prescaler   = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv      = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(GTIM1, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = Pluse_Val;
    TIM_OCInitStructure.OCPolarity  = TIM_OC_POLARITY_HIGH;
    TIM_InitOc1(GTIM1, &TIM_OCInitStructure);
    TIM_ConfigOc1Preload(GTIM1, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel4 */
    TIM_InitOc4(GTIM1, &TIM_OCInitStructure);
    TIM_ConfigOc4Preload(GTIM1, TIM_OC_PRE_LOAD_ENABLE);

    TIM_ConfigArPreload(GTIM1, ENABLE);
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
    DMA_InitStructure.MemAddr        = (uint32_t)ADC_RegularConvertedValueTab;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 32;
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
*\*\name    NVIC_Configuration.
*\*\fun     Configures NVIC and Vector Table base location.
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = ADC1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
