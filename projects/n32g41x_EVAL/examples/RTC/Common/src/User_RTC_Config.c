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
*\*\file User_RTC_Config.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "n32g41x_rcc.h"
#include "n32g41x_rtc.h"
#include "n32g41x_exti.h"
#include "n32g41x_dbg.h"
#include "misc.h"
#include "User_RTC_Config.h"
#include "delay.h"


RTC_DateType  RTC_DateStructure;
RTC_DateType  RTC_DateDefault;
RTC_TimeType  RTC_TimeStructure;
RTC_TimeType  RTC_TimeDefault;
RTC_InitType  RTC_InitStructure;
RTC_AlarmType RTC_AlarmStructure;
RTC_AlarmType RTC_AlarmDefault;
uint32_t SynchPrediv, AsynchPrediv;

/**
*\*\name    RTC_AlarmShow.
*\*\fun     Display the current alarm time on the Hyperterminal.
*\*\param   AlarmX
*\*\            - 1: ALARM-A
*\*\            - 2: ALARM-B
*\*\return  none
*\*\
**/
void RTC_AlarmShow(uint8_t AlarmX)
{
    /* Get the current Alarm */
    if (AlarmX == 0x01)
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_A_ALARM, &RTC_AlarmStructure);
    else
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_B_ALARM, &RTC_AlarmStructure);
    printf("\n\r //=========== Current Alarm Display ==============// \n\r");
    printf("\n\r The current alarm is :  %02u:%02u:%02u \n\r",\
           RTC_AlarmStructure.AlarmTime.Hours,\
           RTC_AlarmStructure.AlarmTime.Minutes,\
           RTC_AlarmStructure.AlarmTime.Seconds);
}

/**
*\*\name    RTC_DateShow.
*\*\fun     Display the current Date on the Hyperterminal.
*\*\param   none
*\*\return  none
*\*\
**/
void RTC_DateShow(void)
{
    /* Get the current Date */
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStructure);
    log_info("\n\r //=========== Current Date Display ==============// \n\r");
    log_info("\n\r The current date (WeekDay-Date-Month-Year) is :  %02u-%02u-%02u-%02u \n\r",\
             RTC_DateStructure.WeekDay,\
             RTC_DateStructure.Date,\
             RTC_DateStructure.Month,\
             RTC_DateStructure.Year);
}

/**
*\*\name    RTC_TimeShow.
*\*\fun     Display the current time on the Hyperterminal.
*\*\param   none
*\*\return  none
*\*\
**/
void RTC_TimeShow(void)
{
    /* Get the current Time and Date */
    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStructure);
    log_info("\n\r //============ Current Time Display ===============// \n\r");
    log_info("\n\r The current time (Hour-Minute-Second) is :  %02u:%02u:%02u \n\r",\
             RTC_TimeStructure.Hours,\
             RTC_TimeStructure.Minutes,\
             RTC_TimeStructure.Seconds);
    /* Unfreeze the RTC DAT Register */
    (void)RTC->DATE;
}

/**
*\*\name    RTC_DateAndTimeDefaultVale.
*\*\fun     RTC initalize default value.
*\*\param   none
*\*\return  none
*\*\
**/
void RTC_DateAndTimeDefaultVale(uint32_t AlarmMask)
{  
    RTC_TimeStructInit(&RTC_TimeDefault);
    RTC_DateStructInit(&RTC_DateDefault);
    RTC_AlarmStructInit(&RTC_AlarmDefault);

    // Date
    RTC_DateDefault.WeekDay = 4;
    RTC_DateDefault.Date    = 16;
    RTC_DateDefault.Month   = 11;
    RTC_DateDefault.Year    = 23;
    // Time
    RTC_TimeDefault.H12     = RTC_AM_H12;
    RTC_TimeDefault.Hours   = 4;
    RTC_TimeDefault.Minutes = 22;
    RTC_TimeDefault.Seconds = 55;
    // Alarm
    RTC_AlarmDefault.AlarmTime.H12     = RTC_AM_H12;
    RTC_AlarmDefault.AlarmTime.Hours   = 4;
    RTC_AlarmDefault.AlarmTime.Minutes = 23;
    RTC_AlarmDefault.AlarmTime.Seconds = 00;
    RTC_AlarmDefault.DateWeekMode      = RTC_ALARM_SEL_WEEKDAY_DATE;
    RTC_AlarmDefault.DateWeekValue     = 16;
    RTC_AlarmDefault.AlarmMask         = AlarmMask;
}

/**
*\*\name    RTC_AlarmRegulate.
*\*\fun     RTC alarm regulate with the default value.
*\*\param   RTC_Alarm
*\*\            - RTC_A_ALARM
*\*\            - RTC_B_ALARM
*\*\return  ErrorStatus
*\*\            - SUCCESS
*\*\            - ERROR
*\*\
**/
ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    /* Disable the AlarmX */
    RTC_EnableAlarm(RTC_Alarm, DISABLE);
    printf("\n\r //==============Alarm X Settings================// \n\r");
    RTC_AlarmStructure.AlarmTime.H12 = RTC_AlarmDefault.AlarmTime.H12;
    RTC_TimeStructure.H12            = RTC_TimeDefault.H12;
    printf("\n\r Please Set Alarm Hours \n\r");
    tmp_hh = RTC_AlarmDefault.AlarmTime.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Hours = tmp_hh;
    }
    printf(": %02u\n\r", tmp_hh);
    printf("\n\r Please Set Alarm Minutes \n\r");
    tmp_mm = RTC_AlarmDefault.AlarmTime.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Minutes = tmp_mm;
    }
    printf(": %02u\n\r", tmp_mm);
    printf("\n\r Please Set Alarm Seconds \n\r");
    tmp_ss = RTC_AlarmDefault.AlarmTime.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Seconds = tmp_ss;
    }
    printf(": %02u\n\r", tmp_ss);
    /* Set the Alarm X */
    RTC_AlarmStructure.DateWeekValue = RTC_AlarmDefault.DateWeekValue;
    RTC_AlarmStructure.DateWeekMode = RTC_AlarmDefault.DateWeekMode;
    RTC_AlarmStructure.AlarmMask = RTC_AlarmDefault.AlarmMask;
    /* Configure the RTC Alarm A register */
    RTC_SetAlarm(RTC_FORMAT_BIN, RTC_Alarm, &RTC_AlarmStructure);
    printf("\n\r>> !! RTC Set Alarm_X success. !! <<\n\r");
    if (RTC_Alarm == RTC_A_ALARM)
    {
        /* Enable the RTC Alarm A Interrupt */
        RTC_ConfigInt(RTC_INT_ALRA, ENABLE);
        RTC_AlarmShow(1);
    }
    else
    {
        /* Enable the RTC Alarm B Interrupt */
        RTC_ConfigInt(RTC_INT_ALRB, ENABLE);
        RTC_AlarmShow(2);
    }
    /* Enable the alarm   */
    RTC_EnableAlarm(RTC_Alarm, ENABLE);
    return SUCCESS;
}

/**
*\*\name    RTC_DateRegulate.
*\*\fun     RTC date regulate with the default value.
*\*\param   none
*\*\return  ErrorStatus
*\*\            - SUCCESS
*\*\            - ERROR
*\*\
**/
ErrorStatus RTC_DateRegulate(void)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //=============Date Settings================// \n\r");
    log_info("\n\r Please Set WeekDay (01-07) \n\r");
    tmp_hh = RTC_DateDefault.WeekDay;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.WeekDay = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    tmp_hh = 0xFF;
    log_info("\n\r Please Set Date (01-31) \n\r");
    tmp_hh = RTC_DateDefault.Date;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Date = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    log_info("\n\r Please Set Month (01-12)\n\r");
    tmp_mm = RTC_DateDefault.Month;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Month = tmp_mm;
    }
    log_info(": %02u\n\r", tmp_mm);
    log_info("\n\r Please Set Year (00-99)\n\r");
    tmp_ss = RTC_DateDefault.Year;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Year = tmp_ss;
    }
    log_info(": %02u\n\r", tmp_ss);
    /* Configure the RTC date register */
    if (RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Date failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Date success. !! <<\n\r");
        RTC_DateShow();
        return SUCCESS;
    }
}

/**
*\*\name    RTC_TimeRegulate.
*\*\fun     RTC time regulate with the default value.
*\*\param   none
*\*\return  ErrorStatus
*\*\            - SUCCESS
*\*\            - ERROR
*\*\
**/
ErrorStatus RTC_TimeRegulate(void)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //==============Time Settings=================// \n\r");
    RTC_TimeStructure.H12 = RTC_TimeDefault.H12;
    log_info("\n\r Please Set Hours \n\r");
    tmp_hh = RTC_TimeDefault.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Hours = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    log_info("\n\r Please Set Minutes \n\r");
    tmp_mm = RTC_TimeDefault.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Minutes = tmp_mm;
    }
    log_info(": %02u\n\r", tmp_mm);
    log_info("\n\r Please Set Seconds \n\r");
    tmp_ss = RTC_TimeDefault.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Seconds = tmp_ss;
    }
    log_info(": %02u\n\r", tmp_ss);
    /* Configure the RTC time register */
    if (RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Time failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Time success. !! <<\n\r");
        RTC_TimeShow();
        return SUCCESS;
    }
}

/**
*\*\name    RTC_PrescalerConfig.
*\*\fun     RTC prescaler config.
*\*\param   none
*\*\return  none
*\*\
**/
void RTC_PrescalerConfig(void)
{
    RTC_StructInit(&RTC_InitStructure);
  
    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;
    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        log_info("\r\n //******* RTC Prescaler Config failed **********// \r\n");
    }
}

/**
*\*\name    RTC_CLKSourceConfig.
*\*\fun     Clk_Src_Type specifies RTC Source Clock Type.
*\*\param   RTC_CLK_SRC_TYPE
*\*\            - RTC_CLK_SRC_TYPE_HSE_DIV128
*\*\            - RTC_CLK_SRC_TYPE_LSE
*\*\            - RTC_CLK_SRC_TYPE_LSI
*\*\param   Is_First_Cfg_RCC specifies Is First Config RCC Module.
*\*\            - true
*\*\            - false
*\*\return  ErrorStatus
*\*\            - SUCCESS: RTC clock configure success
*\*\            - ERROR: RTC clock configure failed
*\*\
**/
ErrorStatus RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC)
{
    uint8_t lse_ready_count=0;
    ErrorStatus Status=SUCCESS;

    /* Disable RTC clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_RTC, DISABLE);
    
    if (RTC_CLK_SRC_TYPE_HSE_DIV128 == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set HSE/128! \r\n");
        if (true == Is_First_Cfg_RCC)
        {
            /* Enable HSE */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigHse(RCC_HSE_ENABLE);
            while (RCC_WaitHseStable() == ERROR)
            {
            }
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_HSE_DIV128);
        }
        else
        {
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_HSE_DIV128);
            /* Enable HSE */
            RCC_ConfigHse(RCC_HSE_ENABLE);
            while (RCC_WaitHseStable() == ERROR)
            {
            }
        }
        SynchPrediv  = 0x270; // 8M/128 = 62500Hz / 100 = 625Hz  625Hz / 625 = 1Hz
        AsynchPrediv = 0x63;  // value range: 0-7F  8M/128 = 62500Hz / 100 = 625Hz 
    }
    else if (RTC_CLK_SRC_TYPE_LSE == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSE! \r\n");
        if (true == Is_First_Cfg_RCC)
        {
            /* Disable the LSI */
            RCC_EnableLsi(DISABLE);
            
#if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS);
#else
            RCC_ConfigLse(RCC_LSE_ENABLE);
#endif
            lse_ready_count=0;
            /****Waite LSE Ready *****/
            while((RCC_GetFlagStatus(RCC_CTRL_FLAG_LSERDF) == RESET) && (lse_ready_count<RTC_LSE_TRY_COUNT))
            {
                lse_ready_count++;
                SysTick_Delay_Ms(10);
                /****LSE Ready failed or timeout*****/
                if(lse_ready_count>=RTC_LSE_TRY_COUNT)
                {
                    Status = ERROR;
                    log_info("\r\n RTC_ClkSrc Set LSE Failed! \r\n");
                    break;
                }
            }
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_LSE);
        }
        else
        {
            /* Disable the LSI */
            RCC_EnableLsi(DISABLE);
            
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_LSE);
#if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS);
#else
            RCC_ConfigLse(RCC_LSE_ENABLE);
#endif
            lse_ready_count=0;
            /****Waite LSE Ready *****/
            while((RCC_GetFlagStatus(RCC_CTRL_FLAG_LSERDF) == RESET) && (lse_ready_count<RTC_LSE_TRY_COUNT))
            {
                lse_ready_count++;
                SysTick_Delay_Ms(10);
                /****LSE Ready failed or timeout*****/
                if(lse_ready_count>=RTC_LSE_TRY_COUNT)
                {
                   Status = ERROR;
                   log_info("\r\n RTC_ClkSrc Set LSE Failed! \r\n");
                   break;
                }
            }
        }
        SynchPrediv  = 0xFF; // 32.768KHz  256Hz / 256 = 1Hz
        AsynchPrediv = 0x7F; // value range: 0-7F  32.768KHz / 128 = 256Hz
    }
    else if (RTC_CLK_SRC_TYPE_LSI == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSI! \r\n");
        if (true == Is_First_Cfg_RCC)
        {
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF) == RESET)
            {
            }
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_LSI);
        }
        else
        {
            RCC_ConfigRTCClk(RCC_RTC_CLKSEL_LSI);
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF) == RESET)
            {
            }
        }
        SynchPrediv  = 0xF9; // 32KHz  250Hz / 250 = 1Hz
        AsynchPrediv = 0x7F;  // value range: 0-7F  32KHz / 128 = 250Hz
    }
    else
    {
        log_info("\r\n RTC_ClkSrc Value is error! \r\n");
    }
    /* Enable the RTC Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_RTC, ENABLE);
    
    while((Status = RTC_WaitForSynchro()) != SUCCESS)
    {
    }
    return Status;
}

