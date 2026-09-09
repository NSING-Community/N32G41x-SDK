/**
*     Copyright (c) 2025, NSING Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of NSING Technologies Inc. (Hereinafter 
* referred to as NSING). This software, and the product of NSING described herein 
* (Hereinafter referred to as the Product) are owned by NSING under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NSING does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NSING reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NSING and obtain 
* the latest version of this software before placing orders.

*     Although NSING has attempted to provide accurate and reliable information, NSING assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NSING be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NSING Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NSING and hold NSING 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NSING, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NSING products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, NSING Technologies Inc. All rights reserved.
**/

#include "main.h"
#include "delay.h"

__IO uint32_t LsiFreq = 32000;

/**
*\*\name    MCO_Configuration.
*\*\fun     Configure MCO pin (PA8) and select clock source with prescaler.
*\*\param   MCO_source: 
*\*\param      RCC_MCO_SYSCLK
*\*\param      RCC_MCO_HSI
*\*\param      RCC_MCO_HSE
*\*\param      RCC_MCO_PLL
*\*\param      RCC_MCO_LSE
*\*\param      RCC_MCO_LSI
*\*\param   MCO_prescaler
*\*\param      RCC_MCO_CLK_DIV1
*\*\param      RCC_MCO_CLK_DIV2
*\*\param      RCC_MCO_CLK_DIV4
*\*\param      RCC_MCO_CLK_DIV8
*\*\param      RCC_MCO_CLK_DIV16
*\*\return  none
*\*\note    MCO output must not exceed 20MHz.
**/
void MCO_Configuration(uint32_t MCO_source, uint32_t MCO_prescaler)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Configure MCO pin as alternate push-pull */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = MCO_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = MCO_AF;
    GPIO_InitPeripheral(MCO_GPIO, &GPIO_InitStructure);

    /* Configure MCO prescaler */
    RCC_ConfigMcoClkPre(MCO_prescaler);

    /* Select MCO clock source */
    RCC_ConfigMco(MCO_source);
}

/**
*\*\name    LedInit.
*\*\fun     Configures LED GPIO.
*\*\param   GPIOx
*\*\param   Pin
*\*\return  none
**/
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

/**
*\*\name    LedOn.
*\*\fun     Turn on LED.
*\*\param   GPIOx: GPIO module
*\*\param   Pin: GPIO pin
*\*\return  none
**/
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}

/**
*\*\name    LedOff.
*\*\fun     Turn off LED.
*\*\param   GPIOx: GPIO module
*\*\param   Pin: GPIO pin
*\*\return  none
**/
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
*\*\name    LedBlink.
*\*\fun     Toggle LED state.
*\*\param   GPIOx: GPIO module
*\*\param   Pin: GPIO pin
*\*\return  none
**/
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
*\*\name    main.
*\*\fun     Main program. IWDG watchdog reset demo.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    DBG_ConfigPeriph(DBG_IWDG_STOP, ENABLE);

    /* Enable LSI Clock */
    RCC_EnableLsi(ENABLE);
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF) != SET)
    {
    }

#ifdef LSI_TIM_MEASURE
    /* Configure GTIM3 to capture LSI via tim_ti1_in2 and measure frequency.
     * ISR accumulates Capture ticks over LSI_MEASURE_COUNT segments,
     * then computes LsiFreq in one shot with 64-bit arithmetic. */
    GTIM3_ConfigForLSI();

    /* Wait for measurement to complete */
    while (CaptureNumber != (LSI_CAPTURE_INTERVALS + 1))
    {
    }

    TIM_ConfigInt(GTIM3, TIM_INT_CC1, DISABLE);
#endif /* LSI_TIM_MEASURE */

    /* Config MCO Output */
    MCO_Configuration(RCC_MCO_LSI, RCC_MCO_CLK_DIV1);

    log_init();
    log_info("--- IWDG demo reset ---\n");

    /* Led Initialize */
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED3_PORT, LED3_PIN);
    LedOff(LED1_PORT, LED1_PIN);
    LedOff(LED3_PORT, LED3_PIN);

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Delay_Ms(1000);

    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET)
    {
        /* IWDGRST flag set */
        LedOn(LED1_PORT, LED1_PIN);
        log_info("reset by IWDG\n");
        /* Clear reset flags */
        RCC_ClearResetFlag();
    }
    else
    {
        /* IWDGRST flag is not set */
        LedOff(LED1_PORT, LED1_PIN);
    }

    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/32)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128 */
    log_debug("LsiFreq is: %d\n", LsiFreq);

    IWDG_CntReload(LsiFreq / 128);
    /* Reload IWDG counter */
    IWDG_ReloadKey();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    while (1)
    {
        /* Toggle LED3 */
        LedBlink(LED3_PORT, LED3_PIN);
        /* Insert 249 ms delay (exceeds IWDG timeout -> reset) */
        SysTick_Delay_Ms(249);
        /* Reload IWDG counter */
        IWDG_ReloadKey();
    }
}

#ifdef LSI_TIM_MEASURE
/**
*\*\name   GTIM3_ConfigForLSI.
*\*\fun    Configures GTIM3 CH1 to measure the LSI oscillator frequency.
*\*\       The LSI is internally connected to GTIM3 tim_ti1_in2,
*\*\       which is routed to TI1 (CH1) via the INSEL register.
*\*\param  none.
*\*\return none.
**/
void GTIM3_ConfigForLSI(void)
{
    NVIC_InitType NVIC_InitStructure;
    TIM_ICInitType TIM_ICInitStructure;

    /* Enable GTIM3 clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM3, ENABLE);

    /* Configure NVIC for GTIM3 interrupt */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel                   = GTIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure GTIM3 prescaler: counter clock = SystemCoreClock / (1 + 1) = SystemCoreClock / 2 */
    TIM_ConfigPrescaler(GTIM3, 1, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /*
     * GTIM3 CH1 configuration: Input Capture mode
     * The LSI oscillator is internally connected to GTIM3 tim_ti1_in2,
     * which is routed to CH1 via the TI1 input selection.
     * Rising edge is used as active edge, capture every 8th edge (DIV8).
     * CCDAT1 register is used to compute the frequency value.
     */
    TIM_ICInitStructure.Channel     = TIM_CH_1;
    TIM_ICInitStructure.ICPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.ICSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_IC_PSC_DIV8;
    TIM_ICInitStructure.ICFilter    = 0x0;
    TIM_ICInit(GTIM3, &TIM_ICInitStructure);

    /* Select tim_ti1_in2 (LSI) as the TI1 input source for GTIM3 */
    GTIM3->INSEL = (GTIM3->INSEL & ~TIM_INSEL_TI1S) | TIM_CAPCH1SEL_2;

    /* Enable GTIM3 counter */
    TIM_Enable(GTIM3, ENABLE);

    /* Clear all status flags */
    GTIM3->STS = 0;

    /* Enable CC1 interrupt for capture event */
    TIM_ConfigInt(GTIM3, TIM_INT_CC1, ENABLE);
}
#endif /* LSI_TIM_MEASURE */
