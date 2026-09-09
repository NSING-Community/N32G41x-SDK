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
#include "delay.h"
#include "log.h"

/**
 *\*\name   LED_Initialize.
 *\*\fun    Initialize LED1 and LED2.
 *\*\param  none.
 *\*\return none.
 */
void LED_Initialize(void)
{
    /* Define a structure of type GPIO_InitType */
    GPIO_InitType GPIO_InitStructure;

    /* Clock enable */
    LED1_CLOCK_ENABLE;
    LED2_CLOCK_ENABLE;
    
    /* Assign default value to GPIO_InitStructure structure */
    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* LED1 Pin Initialize */
    GPIO_InitStructure.Pin          = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(LED1_PORT, &GPIO_InitStructure);
    
    /* LED2 Pin Initialize */
    GPIO_InitStructure.Pin          = LED2_PIN;
    GPIO_InitPeripheral(LED2_PORT, &GPIO_InitStructure);
}

/**
 *\*\name   LED_Toggle.
 *\*\fun    Toggle LED pin.
 *\*\param  GPIOx - GPIO port.
 *\*\param  pin - GPIO pin.
 *\*\return none.
 */
void LED_Toggle(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIO_TogglePin(GPIOx, pin);
}

/**
 *\*\name   LED_On.
 *\*\fun    Turn on LED by set GPIO pin.
 *\*\param  GPIOx - GPIO port.
 *\*\param  pin - GPIO pin.
 *\*\return none.
 */
void LED_On(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIO_SetBits(GPIOx, pin);
}

/**
 *\*\name   LED_Off.
 *\*\fun    Turn off LED by reset GPIO pin.
 *\*\param  GPIOx - GPIO port.
 *\*\param  pin - GPIO pin.
 *\*\return none.
 */
void LED_Off(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIO_ResetBits(GPIOx, pin);
}

/**
 *\*\name   Key_Input_Initialize.
 *\*\fun    Key input detection initialization.
 *\*\param  none.
 *\*\return none.
 */
void Key_Input_Initialize(void)
{
    /* Define a structure of type GPIO_InitType */
    GPIO_InitType GPIO_InitStructure;
    
    /* Clock enable */
    BUTTON_KEY1_CLK_ENABLE;

    /* Assign default value to GPIO_InitStructure structure */
    GPIO_InitStruct(&GPIO_InitStructure);
    
    GPIO_InitStructure.Pin       = BUTTON_KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull = BUTTON_KEY1_PULL;
    /* Initialize GPIO */
    GPIO_InitPeripheral(BUTTON_KEY1_PORT, &GPIO_InitStructure);
}

/**
 *\*\name   SWD_Function_Initialize.
 *\*\fun    Configures SWD pins as SWD function (restore debug).
 *\*\param  none.
 *\*\return none.
 */
void SWD_Function_Initialize(void)
{
    /* Define a structure of type GPIO_InitType */
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAHBPeriphClk(SWDIO_CLK, ENABLE);

    /* Assign default value to GPIO_InitStructure structure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Remap PA13 (SWDIO) to AF0 (SWD function) */
    GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE15, GPIO_AF0);
    
    /* Configure PA13 (SWDIO) as alternate output push-pull with pull-up */
    GPIO_InitStructure.Pin            = SWDIO_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitPeripheral(SWDIO_PORT, &GPIO_InitStructure);

    /* Remap PA14 (SWCLK) to AF0 (SWD function) */
    GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE14, GPIO_AF0);
    
    /* Configure PA14 (SWCLK) as alternate output push-pull with pull-down */
    GPIO_InitStructure.Pin            = SWCLK_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_DOWN;
    GPIO_InitPeripheral(SWCLK_PORT, &GPIO_InitStructure);
}

/**
 *\*\name   SWD_As_GPIO_Initialize.
 *\*\fun    Configures SWD pins as GPIO.
 *\*\param  none.
 *\*\return none.
 */
void SWD_As_GPIO_Initialize(void)
{
    /* Define a structure of type GPIO_InitType */
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAHBPeriphClk(SWDIO_CLK, ENABLE);

    /* Assign default value to GPIO_InitStructure structure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Remap PA13 (SWDIO) and PA14 (SWCLK) to GPIO_NO_AF (release from SWD) */
    GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE15, GPIO_NO_AF);
    GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE14, GPIO_NO_AF);

    /* Configure PA15 and PA14 as gpio output push-pull */
    GPIO_InitStructure.Pin            = SWDIO_PIN | SWCLK_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitPeripheral(SWDIO_PORT, &GPIO_InitStructure);
}

/**
 *\*\name   main.
 *\*\fun    Main program.
 *\*\param  none
 *\*\return none
 */
int main(void)
{
    log_init();
    printf("\r\n IO remaping demo!\r\n");

    LED_Initialize();
    Key_Input_Initialize();

    while(1)
    {
        if (GPIO_ReadInputDataBit(BUTTON_KEY1_PORT, BUTTON_KEY1_PIN) == BUTTON_KEY1_STATE)
        {
            /* Turn on Led1 */
            LED_On(LED1_PORT, LED1_PIN);
            
            /* Turn off Led2 */
            LED_Off(LED2_PORT, LED2_PIN);
            
            /* Disable the SWD Debug Port */
            SWD_As_GPIO_Initialize();
            
            while(1)
            {
                /* Toggle SWDIO pin */
                GPIO_TogglePin(SWDIO_PORT, SWDIO_PIN);
                    
                /* Insert delay */
                SysTick_Delay_Ms(50);
                
                /* Toggle SWCLK pin */
                GPIO_TogglePin(SWCLK_PORT, SWCLK_PIN);

                /* Insert delay */
                SysTick_Delay_Ms(50);
                
                if (GPIO_ReadInputDataBit(BUTTON_KEY1_PORT, BUTTON_KEY1_PIN) != BUTTON_KEY1_STATE)
                {
                    break;
                }
            }
        }
        else
        {
            /* Enable the SWD Debug Port */
            SWD_Function_Initialize();
            
            /* Turn on Led2 */
            LED_On(LED2_PORT, LED2_PIN);
            
            /* Turn off Led1 */
            LED_Off(LED1_PORT, LED1_PIN);
            
            while(1)
            {
                if (GPIO_ReadInputDataBit(BUTTON_KEY1_PORT, BUTTON_KEY1_PIN) == BUTTON_KEY1_STATE)
                {
                    break;
                }
            }
        }
    }
}
