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
#include "log.h"

/** COMP_OUT **/

void RCC_Configuration(void);
void GPIO_Configuration(void);
void COMP_Configuration(void);
void NVIC_Configuration(void);
void ChangeVmVp(void);

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    //log_info("COMP_OUT demo start\n");

    /* System clocks configuration */
    RCC_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();

    /* GPIO configuration */
    GPIO_Configuration();

    /* COMP configuration */
    COMP_Configuration();
    

    while (1)
    {
        ChangeVmVp();
    }
}

/**
*\*\name    ChangeVmVp.
*\*\fun     Toggle pulse generator pins to produce test signal for COMP inputs.
*\*\param   none
*\*\return  none
**/
void ChangeVmVp(void)
{
    uint32_t i;

    /* INP high, INM low -> COMP1 OUT = high */
    GPIO_SetBits(PULSE_INP_GPIO, PULSE_INP_PIN);
    GPIO_ResetBits(PULSE_INM_GPIO, PULSE_INM_PIN);
    for (i = 0; i < 1000; i++)
        ;

    /* INP low, INM high -> COMP1 OUT = low */
    GPIO_ResetBits(PULSE_INP_GPIO, PULSE_INP_PIN);
    GPIO_SetBits(PULSE_INM_GPIO, PULSE_INM_PIN);
    for (i = 0; i < 1000; i++)
        ;
}

/**
*\*\name    COMP_Configuration.
*\*\fun     Configure COMP1 module.
*\*\param   none
*\*\return  none
**/
void COMP_Configuration(void)
{
    COMP_InitType COMP_Initial;

    /* Set internal reference voltage (VREF_VC1) */
    COMP_SetRefScl(0, false, 0, false, 32, true);

    /* Initialize COMP1 */
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_INPSEL_PB10;
    COMP_Initial.InmSel     = COMP1_INMSEL_PB1;
    COMP_Initial.SampWindow = 30;       /* (0~31) */
    COMP_Initial.Threshold  = 18;       /* should be > SampWindow/2 and < SampWindow */
    COMP_Init(COMP1, &COMP_Initial);

    /* Enable COMP1 interrupt */
    COMP_SetIntEn(COMP_INTEN_CMP1IEN, ENABLE);

    /* Enable COMP1 */
    COMP_Enable(COMP1, ENABLE);
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configure system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable COMP and COMP filter clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMPFILT, ENABLE);

    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure GPIO pins for COMP1.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* COMP1 INP: PB10 - analog input */
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pin       = COMP1_INP_PIN;
    GPIO_InitPeripheral(COMP1_INP_GPIO, &GPIO_InitStructure);

    /* COMP1 INM: PB1 - analog input */
    GPIO_InitStructure.Pin = COMP1_INM_PIN;
    GPIO_InitPeripheral(COMP1_INM_GPIO, &GPIO_InitStructure);

    /* COMP1 OUT: PA11 - alternate push-pull */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pin            = COMP1_OUT_PIN;
    GPIO_InitStructure.GPIO_Alternate = COMP1_OUT_AF;
    GPIO_InitPeripheral(COMP1_OUT_GPIO, &GPIO_InitStructure);

    /* Pulse generator: PB2, PB3 - push-pull output */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0;
    GPIO_InitStructure.Pin            = PULSE_INP_PIN;
    GPIO_InitPeripheral(PULSE_INP_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = PULSE_INM_PIN;
    GPIO_InitPeripheral(PULSE_INM_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configure NVIC and EXTI for COMP1 interrupt.
*\*\param   none
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;

    /* Clear COMP1 EXTI pending bit */
    EXTI_ClrITPendBit(EXTI_LINE21);

    /* Configure EXTI Line21 (COMP1) */
    EXTI_InitStruct(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE21;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /* Configure COMP1/2/3 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = COMP123_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

#ifdef USE_FULL_ASSERT
/**
*\*\name    assert_failed.
*\*\fun     Assert failure handler for debug.
*\*\param   expr: failed expression string
*\*\param   file: source file name
*\*\param   line: line number
*\*\return  none
**/
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif
