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
__IO uint16_t ADC1ConvertedValue[3];
uint32_t gCnt = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
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
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIG_REG_CONV_SOFTWARE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel9 configuration */
    ADC_ConfigRegularChannel(ADC1, ADC_CH_CHANNEL, 1, ADC_SAMP_TIME_CYCLES_240);
    /* Configure high and low analog watchdog thresholds */
    ADC_ConfigAnalogWatchdogThresholds(ADC1, 0x0B00, 0x0300);
    /* Configure channel as the single analog watchdog guarded channel */
    ADC_ConfigAnalogWatchdogSingleChannel(ADC1, ADC_CH_CHANNEL);
    /* Enable analog watchdog on one regular channel */
    ADC_ConfigAnalogWatchdogWorkChannelType(ADC1, ADC_ANALOG_WTDG_SINGLEREG_ENABLE);
    /* Enable AWD interrupt */
    ADC_ConfigInt(ADC1, ADC_INT_AWDG, ENABLE);

    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY) == RESET)
        ;
}

/**
*\*\name    main.
*\*\fun     Main program. ADC analog watchdog demo.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ----------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration -------------------------------------------------------*/
    GPIO_Configuration();

    /* NVIC configuration -------------------------------------------------------*/
    NVIC_Configuration();

    /* ADC1 configuration -------------------------------------------------------*/
    ADC_Initial();

    /* Start ADC1 Software Conversion */
    ADC_EnableSoftwareStartConv(ADC1, ENABLE);

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

    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

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
    /* Configure PB1 as analog input -----------------------*/
    GPIO_InitStructure.Pin            = ADC_CH_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(ADC_CH_PORT, &GPIO_InitStructure);
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

    NVIC_InitStructure.NVIC_IRQChannel                   = ADC1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


