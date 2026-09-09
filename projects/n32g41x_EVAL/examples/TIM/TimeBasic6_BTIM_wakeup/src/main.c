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
#include <stdio.h>




/**
*\*\name    main.
*\*\fun     BTIM1 wakeup from STOP mode demo.
*\*\        BTIM1 uses LSI as clock source, generates periodic update interrupts
*\*\        through EXTI Line 20 to wake up the MCU from STOP mode.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    uint32_t timeout = 0x10000;
    
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* NVIC Configuration */
    NVIC_Configuration();
    
    /* Reconfig TIM6 */
    TIM_Configuration();
    RCC_ConfigBtim1Clk(RCC_BTIM1_CLKSEL_LSI);
    /* TIM6 enable counter */
    TIM_Enable(BTIM1, ENABLE);
    
    while (1)
    {
        SysTick_Delay_Ms(500);
        /* Enter STOP mode */
        PWR_EnterSTOPMode(PWR_STOPENTRY_WFI);
        /* Wait PLL ready, check sysclk source */
        while(RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL)
        {
            if(--timeout == 0) 
            {
                break;
            }
        }
        GPIO_TogglePin(GPIOA, GPIO_PIN_7);
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

    /* Enable BTIM1 clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BTIM1, ENABLE);
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

    /* PA7 as push-pull output for LED */
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures the nested vectored interrupt controller.
*\*\param   none
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_Struct;

    /* Enable the BTIM1 Interrupt (IRQ20, shared with EXTI Line 20) */
    EXTI_ClrStatusFlag(EXTI_LINE20);
    EXTI_Struct.EXTI_Line    = EXTI_LINE20;
    EXTI_Struct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_Struct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Struct.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_Struct);
    
    NVIC_InitStructure.NVIC_IRQChannel                   = BTIM1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



/**
*\*\name    BTIM1_Configuration.
*\*\fun     Configures BTIM1 as periodic timer with LSI clock source.
*\*\note    LSI ~40kHz, Prescaler=39 -> 1kHz, Period=1999 -> 2s update interrupt.
*\*\param   none
*\*\return  none
**/
void TIM_Configuration(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period      = 3200;
    TIM_TimeBaseStructure.Prescaler   = 0;
    TIM_TimeBaseStructure.ClkDiv      = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(BTIM1, &TIM_TimeBaseStructure);

    /* Clear update interrupt flag before enabling */
    TIM_ClrIntPendingBit(BTIM1, TIM_INT_UPDATE);

    /* Enable BTIM1 update interrupt */
    TIM_ConfigInt(BTIM1, TIM_INT_UPDATE, ENABLE);

}

