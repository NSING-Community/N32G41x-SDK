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
#include "n32g41x.h"
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "log.h"
#include "n32g41x_rcc.h"
#include "n32g41x_rtc.h"
#include "n32g41x_gpio.h"
#include "n32g41x_exti.h"
#include "misc.h"
#include "User_RTC_Config.h"
#include "delay.h"

RTC_DateType  RTC_TimeStampDateStructure;
RTC_TimeType  RTC_TimeStampStructure;

/**
*\*\name    RTC_TimeStampShow.
*\*\fun     Display the current TimeStamp (time and date) on the Hyperterminal.
*\*\param   none
*\*\return  none
**/
void RTC_TimeStampShow(void)
{
    /* Get the current TimeStamp */
    RTC_GetTimeStamp(RTC_FORMAT_BIN, &RTC_TimeStampStructure, &RTC_TimeStampDateStructure);
    printf("\n\r //=========TimeStamp Display (Time and Date)============// \n\r");
    printf("\n\r The current time stamp time (Hour-Minute-Second) is :  %02u:%02u:%02u \n\r",\
           RTC_TimeStampStructure.Hours,\
           RTC_TimeStampStructure.Minutes,\
           RTC_TimeStampStructure.Seconds);
    printf("\n\r The current timestamp date (WeekDay-Date-Month) is :  %02u-%02u-%02u \n\r",\
           RTC_TimeStampDateStructure.WeekDay,\
           RTC_TimeStampDateStructure.Date,\
           RTC_TimeStampDateStructure.Month);
}

/**
*\*\name    EXTI_PB8_TimeStamp_Configuration.
*\*\fun     EXTI PB8 I/O config and use the EXTI interrupt to trigger time stamp.
*\*\param   none
*\*\return  none
**/
void EXTI_PB8_TimeStamp_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);
    
    /* Configure PB8 in input mode */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Connect EXTI8 to RTC_TimeStamp */
    EXTI_RTCTimeStampSel(EXTI_TSSEL_LINE8);
    /* Connect EXTI8 Line to PB8 pin */
    GPIO_ConfigEXTILine(GPIOB_PORT_SOURCE, GPIO_PIN_SOURCE8);
}

/**
*\*\name    EXTI18_STAMP_IRQn_Configuration.
*\*\fun     Initialize Timestamp NVIC and EXIT LINE.
*\*\param   NewState
*\*\            - ENABLE
*\*\            - DISABLE
*\*\param   TSEdgeSel
*\*\            - 0x01: Rising
*\*\            - 0x02: Falling
*\*\return  none
**/
void EXTI18_STAMP_IRQn_Configuration(FunctionalState NewState, uint32_t TSEdgeSel)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    
    EXTI_ClrITPendBit(EXTI_LINE18);
    
    EXTI_InitStruct(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line                          = EXTI_LINE18;
    EXTI_InitStructure.EXTI_Mode                          = EXTI_Mode_Interrupt;
    if(TSEdgeSel == 0x01)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Rising;  
    else if(TSEdgeSel == 0x02)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Falling;
    else
        printf("\r\n The TSEdgeSel value is error! \r\n");
    EXTI_InitStructure.EXTI_LineCmd                       = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* Enable the RTC Stamp Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = RTC_STAMP_LSECSS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = NewState;
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
    log_info("\r\n RTC Init \r\n");
    /* RTC date and time default value*/
    RTC_DateAndTimeDefaultVale(RTC_ALARMMASK_ALL);
    /* RTC clock source select */
    if(SUCCESS==RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true))
    {
        if (RTC_GetFlagStatus(RTC_FLAG_INITSF) != SET)
        {
            RTC_DeInit();
            RTC_PrescalerConfig();
            /* Adjust time by values entered by the user on the hyperterminal */
            RTC_DateRegulate();
            RTC_TimeRegulate();
            log_info("\r\n RTC Init Success\r\n");
        }
        else
        {
            log_info("\r\n RTC has already been initialized before\r\n");
        }
    }
    else
    {
        log_info("\r\n RTC Init Failed\r\n");
    }
    /* Adjust time by values entered by the user on the hyperterminal */
    RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_1HZ);
    /* Calibrate output config,push pull */
    RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    /* Calibrate output enable*/
    RTC_EnableCalibOutput(ENABLE);
    /* Configure EXTI PB8 pin  connected to RTC TimeStamp
    (while externally feeding PB8 with 1HZ signal output from PC13)
    */
    EXTI_PB8_TimeStamp_Configuration();
    EXTI_ClrITPendBit(EXTI_LINE18);
    EXTI18_STAMP_IRQn_Configuration(ENABLE, 1);
    /* clear RTC time stamp flag  */
    RTC_ClrFlag(RTC_FLAG_TISF);
    RTC_ClrFlag(RTC_FLAG_TISOVF);
    RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_FALLING, ENABLE);
    RTC_ConfigInt(RTC_INT_TS, ENABLE);
    while (1)
    {
    }
}
