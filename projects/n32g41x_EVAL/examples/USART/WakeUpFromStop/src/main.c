/**
*     Copyright (c) 2026, NSING Technologies Inc.
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
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/

/* USART1 STOP wakeup validation using interrupt + WFI. */
#include "main.h"
#include "delay.h"
#include "n32g41x_stb.h"

static USART_InitType USART_InitStructure;
static EXTI_InitType EXTI_InitStructure;
volatile uint8_t UsartWakeupFlag;

/* Configure PA1 as the wakeup indication LED output. */
static void LED1_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    LED1_CLOCK_ENABLE;
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(LED1_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(LED1_PORT, LED1_PIN);
}

void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin            = USARTy_TxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Tx_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = USARTy_RxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);
}

/* Configure all low-power USART settings before entering STOP. */
static void USART1_PrepareStopWakeup(void)
{
    /* Configure USART on APB2, then make LSI the last clock-source change. */
    /* Reconfigure only while USART1 is clocked from APB2. */

    /** requires UEN=0: CTRL1.OSPM and BRCF are only writable while the
   USART is disabled, so a running port must be quiesced first. The baud rate
   change also aborts the frame being transmitted/received. **/
    USART_Enable(USARTy, DISABLE);
    RCC_ConfigUsart1Clk(RCC_USART1_CLKSEL_APB2);
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    USART_Init(USARTy, &USART_InitStructure);

    if (USART_GetFlagStatus(USARTy, USART_FLAG_RXDNE) != RESET)
    {
        (void)USART_ReceiveData(USARTy);
    }

    /* The ISR sets this flag after the WFI wakeup interrupt occurs. */
    UsartWakeupFlag = 0U;
    USART_CfgWakeUpDataClr(USARTy, USART_WAKEUP_NOTCLRDATA);
    USART_EnableWakeUp(USARTy, ENABLE);
    /* RXDNE is the interrupt source that wakes WFI through EXTI24. */
    USART_ConfigInt(USARTy, USART_INT_RXDNE, ENABLE);
    /* USART_Init() above derived BRCF from the APB2 clock, where 1200 baud is
   below the minimum rate the divider can represent, so it must be overwritten.
   All USART configuration must be completed before the clock source is switched
   to LSI, so the switch remains the last step. LSI divisor: 32000/(16*1200)=1.667 -> 0x1A.*/
    USARTy->BRCF = 0x1AU;
    EXTI_ClrITPendBit(USARTy_WKUP_EXTI_LINE);
    USART_Enable(USARTy, ENABLE);
    RCC_ConfigUsart1Clk(RCC_USART1_CLKSEL_LSI);
}

/* Restore the GPIO and normal APB2 USART configuration after STOP exit. */
static void USART1_RestoreAfterStop(void)
{
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);
    LED1_Init();

    /* Reconfigure only while USART1 is clocked from APB2. */
    USART_Enable(USARTy, DISABLE);
    RCC_ConfigUsart1Clk(RCC_USART1_CLKSEL_APB2);
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    USART_Init(USARTy, &USART_InitStructure);
    USART_ConfigInt(USARTy, USART_INT_RXDNE, DISABLE);
    USART_EnableWakeUp(USARTy, DISABLE);
    USART_Enable(USARTy, ENABLE);
}

int main(void)
{
    NVIC_InitType NVIC_InitStructure;

    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);
    GPIO_Configuration();
    LED1_Init();

    /* Keep LED1 on for the single 5 s power-up/download window. */
    GPIO_SetBits(LED1_PORT, LED1_PIN);
    SysTick_Delay_Ms(5000);
    GPIO_ResetBits(LED1_PORT, LED1_PIN);

    /* LSI must keep running because USART1 uses it during STOP. */
    RCC_EnableLsi(ENABLE);
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF) == RESET)
    {
    }
    RCC_ConfigLowPowerClk(RCC_LP_CLKSEL_LSI);

    /* USART1_IRQn also carries the USART1 low-power EXTI24 interrupt. */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* WFI requires an interrupt source: EXTI24 routes to USART1_IRQn. */
    EXTI_InitStructure.EXTI_Line    = USARTy_WKUP_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate     = 1200;
    USART_InitStructure.WordLength   = USART_WL_8B;
    USART_InitStructure.StopBits     = USART_STPB_1;
    USART_InitStructure.Parity       = USART_PE_NO;
    USART_InitStructure.OverSampling = USART_16OVER;
    USART_InitStructure.Mode         = USART_MODE_RX | USART_MODE_TX;

    while (1)
    {
        GPIO_ResetBits(LED1_PORT, LED1_PIN);
        USART1_PrepareStopWakeup();
        PWR_EnterSTOPMode(PWR_STOPENTRY_WFI);

        /* Only process the STOP exit after USART1_IRQHandler confirms it. */
        if (UsartWakeupFlag != 0U)
        {
            USART1_RestoreAfterStop();
            GPIO_SetBits(LED1_PORT, LED1_PIN);
            SysTick_Delay_Ms(1000);
        }
    }
}



