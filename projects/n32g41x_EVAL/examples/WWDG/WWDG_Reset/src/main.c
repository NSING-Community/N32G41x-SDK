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
**/
#include "main.h"
#include "n32g41x_stb.h"
#include "delay.h"

/**
*\*\name    LedInit.
*\*\fun     Initialize LED GPIO.
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
    GPIO_SetBits(GPIOx, Pin);
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
    GPIO_ResetBits(GPIOx, Pin);
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
    GPIO_TogglePin(GPIOx, Pin);
}

/**
*\*\name    main.
*\*\fun     Main program. WWDG watchdog reset demo.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* Initialize USART */
    log_init();
    log_info("--- WWDG demo reset ---\n");

    /* Clear WWDG early wakeup interrupt flag */
    WWDG_ClrEWINTF();

    /* Initialize LED1 and LED3 */
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED3_PORT, LED3_PIN);
    LedOff(LED1_PORT, LED1_PIN);
    LedOff(LED3_PORT, LED3_PIN);

    /* Check if the system has resumed from WWDG reset */
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_WWDGRSTF) != RESET)
    {
        /* WWDG reset flag set */
        LedOn(LED1_PORT, LED1_PIN);
        log_info("reset by WWDG\n");
        RCC_ClearResetFlag();
    }
    else
    {
        LedOff(LED1_PORT, LED1_PIN);
    }

    SysTick_Delay_Ms(1000);

    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_WWDG, ENABLE);
    
#ifdef N32G412
    /*********************** For N32G412 ***********************/
    /* WWDG clock counter = (PCLK1(40MHz)/4096)/8 = 1220Hz (~0.82ms per count)
       WWDG timeout = ~0.82ms * (127-63) = ~52ms
       WWDG window  = ~0.82ms * (127-80) = ~38ms
       Allowed feed window: counter 80~63 (38ms~52ms after last feed) */
    WWDG_SetPrescalerDiv(WWDG_PRESCALER_DIV8);
    WWDG_SetWValue(80);
    WWDG_Enable(127);
#endif /* N32G412 */
    
#ifdef N32G415
    /*********************** For N32G415 ***********************/
    /* WWDG clock counter = (PCLK1(48MHz)/4096)/8 = 1464.8Hz (~683us per count)
       WWDG timeout = ~683us * (127-63) = ~43.7ms
       WWDG window  = ~683us * (127-80) = ~32.1ms
       Allowed feed window: counter 80~63 (32.1ms~43.7ms after last feed) */
    WWDG_SetPrescalerDiv(WWDG_PRESCALER_DIV8);
    WWDG_SetWValue(80);
    WWDG_Enable(127);
#endif /* N32G412 */

    while (1)
    {
        /* Feed the watchdog within the window */
        LedBlink(LED3_PORT, LED3_PIN);
#ifdef N32G412
        SysTick_Delay_Ms(45);
#endif /* N32G412 */
        
#ifdef N32G415
        SysTick_Delay_Ms(35);
#endif /* N32G415 */
        
        WWDG_SetCnt(127);
    }
}
