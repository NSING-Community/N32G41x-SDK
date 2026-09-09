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



void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPAMP_Configuration(void);

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

    /* OPAMP configuration -----------------------------------------------------*/
    OPAMP_Configuration();

    while (1)
    {
    }
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

    /* Configure OPAMP1: PGA mode, gain x2, VP = PA1 */
    OPAMP_Init(OPAMP1, &OPAMP_InitStructure);
    OPAMP_SetVpSel(OPAMP1, OPAMP1_CS_VPSEL_PA1);
    OPAMP_Enable(OPAMP1, ENABLE);

    /* Configure OPAMP2: PGA mode, gain x2, VP = PA7 */
    OPAMP_Init(OPAMP2, &OPAMP_InitStructure);
    OPAMP_SetVpSel(OPAMP2, OPAMP2_CS_VPSEL_PA7);
    OPAMP_Enable(OPAMP2, ENABLE);
    /* OPAMP output pin is automatically enabled when OPAMPx is enabled */
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

    /* Configure OPAMP1_VP (PA1) and OPAMP2_VP (PA7) as analog inputs */
    GPIO_InitStructure.Pin            = OPAMP1_VP_PIN | OPAMP2_VP_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure OPAMP1_OUT (PA2) and OPAMP2_OUT (PA6) as analog outputs */
    GPIO_InitStructure.Pin = OPAMP1_OUT_PIN | OPAMP2_OUT_PIN;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
