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
#include "n32g41x_rcc.h"
#include "n32g41x_gpio.h"
#include "n32g41x_exti.h"
#include "misc.h"
#include "log.h"
#include "delay.h"
#include <stdio.h>

uint32_t exti_int = 1;
uint32_t key_cnt = 0;

GPIO_Module* LedPort[MAX_LED_KEY_CNT] = {LED1_PORT, LED2_PORT};
uint16_t     LedPin[MAX_LED_KEY_CNT]  = {LED1_PIN,  LED2_PIN};

char *str[MAX_LED_KEY_CNT] = {"KEY1(PA4)", "KEY2(PA5)"};

/**
*\*\name    EXTI_KEY_Configuration.
*\*\fun     Configure KEY1(PA4)->EXTI4 and KEY2(PA5)->EXTI5 interrupts.
*\*\param   none
*\*\return  none
**/
void EXTI_KEY_Configuration(void)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    
    EXTI_InitStruct(&EXTI_InitStructure);

    /* Configure KEY1 PA4 -> EXTI_LINE4 */
    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE4);
    
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE4;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /* Configure KEY2 PA5 -> EXTI_LINE5 */
    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE5);
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE5;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /* Enable EXTI4 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY_0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY_0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable EXTI5_9 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI5_9_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* Initialize USART */
    log_init();

    SysTick_Delay_Ms(500);
    printf("\r\nEXTI key interrupt demo!\r\n");

    /* Initialize LEDs */
    LED_Init(LED1_PORT, LED1_PIN, LED1_CLOCK);
    LED_Init(LED2_PORT, LED2_PIN, LED2_CLOCK);

    /* Initialize KEYs */
    KEY_Init(BUTTON_KEY1_PORT, BUTTON_KEY1_PIN, BUTTON_KEY1_CLK, BUTTON_KEY1_PULL);
    KEY_Init(BUTTON_KEY2_PORT, BUTTON_KEY2_PIN, BUTTON_KEY2_CLK, BUTTON_KEY2_PULL);

    /* Configure EXTI interrupts for keys */
    EXTI_KEY_Configuration();

    LED_Off(LED1_PORT, LED1_PIN);
    LED_Off(LED2_PORT, LED2_PIN);

    while (1)
    {
        if(exti_int != 0)
        {
            printf("Current key: %s, LED%lu blinking\r\n", str[key_cnt], (unsigned long)(key_cnt + 1));
            exti_int = 0;
        }
        LED_Blink(LedPort[key_cnt], LedPin[key_cnt]);
        SysTick_Delay_Ms(500);
    }
}

/**
*\*\name    LED_Init.
*\*\fun     Initialize LED GPIO.
*\*\param   GPIOx
*\*\param   Pin
*\*\param   clock
*\*\return  none
**/
void LED_Init(GPIO_Module* GPIOx, uint16_t Pin, uint32_t clock)
{
    GPIO_InitType InitStruct;
    
    GPIO_InitStruct(&InitStruct);
    
    RCC_EnableAHBPeriphClk(clock, ENABLE);
    
    InitStruct.Pin            = Pin;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    InitStruct.GPIO_Alternate = GPIO_AF0;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(GPIOx, &InitStruct);
}

/**
*\*\name    LED_On.
*\*\fun     Turn on LED by set GPIO pin.
*\*\param   GPIOx - GPIO port
*\*\param   Pin - GPIO pin
*\*\return  none
**/
void LED_On(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_SetBits(GPIOx, Pin);
}

/**
*\*\name    LED_Off.
*\*\fun     Turn off LED by reset GPIO pin.
*\*\param   GPIOx - GPIO port
*\*\param   Pin - GPIO pin
*\*\return  none
**/
void LED_Off(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_ResetBits(GPIOx, Pin);
}

/**
*\*\name    LED_Blink.
*\*\fun     Blink LED by toggle GPIO pin.
*\*\param   GPIOx - GPIO port
*\*\param   Pin - GPIO pin
*\*\return  none
**/
void LED_Blink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_TogglePin(GPIOx, Pin);
}

/**
*\*\name    KEY_Init.
*\*\fun     Initialize KEY GPIO.
*\*\param   GPIOx
*\*\param   Pin
*\*\param   clock
*\*\param   pull
*\*\return  none
**/
void KEY_Init(GPIO_Module* GPIOx, uint16_t Pin, uint32_t clock, uint32_t pull)
{
    GPIO_InitType InitStruct;
    
    GPIO_InitStruct(&InitStruct);
    
    RCC_EnableAHBPeriphClk(clock, ENABLE);
    
    InitStruct.Pin            = Pin;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct.GPIO_Alternate = GPIO_NO_AF;
    InitStruct.GPIO_Pull      = pull;
    InitStruct.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(GPIOx, &InitStruct);
}
