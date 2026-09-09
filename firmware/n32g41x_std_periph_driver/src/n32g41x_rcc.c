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
*\*\file n32g41x_rcc.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32g41x_rcc.h"

/**
*\*\name    RCC_DeInit.
*\*\fun     Reset the RCC registers.
*\*\param   none 
*\*\return  none 
**/
void RCC_DeInit(void)  
{
    /* Set HSIEN bit */
    RCC->CTRL |= RCC_CTRL_HSIEN;
    /* Wait HSI ready */
    while((RCC->CTRL & RCC_CTRL_HSIRDF) != RCC_CTRL_HSIRDF)
    {}
        
    RCC->CTRL &= (uint32_t)(~RCC_CTRL_CLKSSEN);

    /* Config HSI as system clock */
    RCC->CFG &= (~RCC_CFG_SCLKSW);
    /* Wait system clock changed to HSI */
    while((RCC->CFG & RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSI)
    {}
        
    /* Reset HSEEN and PLLEN bits */
    RCC->CTRL &= (uint32_t)(~(RCC_CTRL_HSEEN | RCC_CTRL_PLLEN));
    while((RCC->CTRL & RCC_CTRL_HSERDF) == RCC_CTRL_HSERDF)
    {}
    /* Wait PLL disabled */
    while((RCC->CTRL & RCC_CTRL_PLLRDF) == RCC_CTRL_PLLRDF)
    {}
        
    /* Reset AHBPRES, APB1PRES, APB2PRES, PLLOD, PLLSRC, PLLMUL, PLLSYSDIV bits */
    RCC->CFG &= (uint32_t)0xFF000003U;
    /* crystal mode: disable bypass */
    RCC->CTRL &= (uint32_t)(~RCC_CTRL_HSEBP); 

    /* Reset PLLCTRL register (PLLINPRES) */
    RCC->PLLCTRL = 0x00000000U;

    /* Disable all interrupts and clear pending bits */
    RCC->CLKINT = (RCC_CLKINT_LSIRDICLR | RCC_CLKINT_HSIRDICLR | RCC_CLKINT_HSERDICLR
                  | RCC_CLKINT_LSERDICLR | RCC_CLKINT_PLLRDICLR | RCC_CLKINT_CLKSSICLR
                  | RCC_CLKINT_LSESSICLR);
}

/**
*\*\name    RCC_WaitHseStable.
*\*\fun     Waits for HSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSE oscillator is stable and ready to use
 *\*\         - ERROR      HSE oscillator not yet ready
**/
ErrorStatus RCC_WaitHseStable(void)
{
    __IO uint32_t counter_value = 0;
    FlagStatus status_value;
    ErrorStatus bitstatus;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF);
        counter_value++;
    } while ((counter_value != HSE_STARTUP_TIMEOUT) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}



/**
*\*\name    RCC_WaitHsiStable.
*\*\fun     Waits for HSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSI oscillator is stable and ready to use
 *\*\         - ERROR      HSI oscillator not yet ready
**/
ErrorStatus RCC_WaitHsiStable(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status;
    FlagStatus HSIStatus;

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF);
        StartUpCounter++;
    } while ((StartUpCounter != HSI_STARTUP_TIMEOUT) && (HSIStatus == RESET));

    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
*\*\name    RCC_SetHsiCalibValue.
*\*\fun     Adjusts the Internal High Speed oscillator (HSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x1FF
*\*\return  none
**/ 
void RCC_SetHsiCalibValue(uint16_t calibration_value)
{
    uint32_t temp_value;

    temp_value = RCC->CTRL;
	
    /* Clear HSITRIM[16:8] bits */
    temp_value &= CTRL_HSITRIM_MASK;
	
    /* Set the HSITRIM[16:8] bits according to calibration_value value */
    temp_value |= (uint32_t)calibration_value << 8;
	
    /* Store the new value */
    RCC->CTRL = temp_value;
}

/**
*\*\name    RCC_SetLsiCalibValue.
*\*\fun     Adjusts the Internal Low Speed oscillator (LSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x3F
*\*\return  none
**/ 
void RCC_SetLsiCalibValue(uint16_t calibration_value)
{
    uint32_t temp_value;

    temp_value = RCC->CTRL;
	
    /* Clear LSITRIM[7:2] bits */
    temp_value &= CTRL_LSITRIM_MASK;
	
    /* Set the LSITRIM[7:2] bits according to calibration_value value */
    temp_value |= (uint32_t)calibration_value << 2;
	
    /* Store the new value */
    RCC->CTRL = temp_value;
}

/**
*\*\name    RCC_EnableLsi.
*\*\fun     Enables the LSI.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/ 
void RCC_EnableLsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set LSIEN bit */
       RCC->CTRL |= RCC_LSI_ENABLE;
   }
   else
   {
       /* Reset LSIEN bit */
       RCC->CTRL &= (~RCC_LSI_ENABLE);
   }
}

/**
*\*\name    RCC_WaitLsiStable.
*\*\fun     Waits for LSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSI oscillator is stable and ready to use
 *\*\         - ERROR      LSI oscillator not yet ready
**/
ErrorStatus RCC_WaitLsiStable(void)
{
    __IO uint32_t counter_value = 0;
    FlagStatus status_value;
    ErrorStatus bitstatus;

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF);
        counter_value++;
    } while ((counter_value != LSI_STARTUP_TIMEOUT) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSIRDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ConfigLse.
*\*\fun     Configures the External High Speed oscillator (LSE).
*\*\param   RCC_LSE :
*\*\          - RCC_LSE_DISABLE    LSE oscillator OFF 
*\*\          - RCC_LSE_ENABLE     LSE oscillator ON
*\*\          - RCC_LSE_BYPASS     LSE oscillator bypassed with external clock
*\*\return  none.
*\*\note none.   
**/
void RCC_ConfigLse(uint32_t RCC_LSE)
{
    uint32_t temp_value;
    
    temp_value = RCC->CTRL;
    /* Reset LSEEN bit */
    temp_value &= (~RCC_LSE_ENABLE);
    /* Reset LSEBP bit */
    temp_value &= (~RCC_LSE_BYPASS);
    /* Configure LSE (RC_LSE_DISABLE is already covered by the code section above) */
    if(RCC_LSE == RCC_LSE_ENABLE)
    {
        /* Set LSEEN bit */
        temp_value |= RCC_LSE_ENABLE;
    }   
    else if (RCC_LSE == RCC_LSE_BYPASS)
    {
        /* Set LSEBP and LSEEN bits */
        temp_value |= RCC_LSE_BYPASS | RCC_LSE_ENABLE;
    }
    else
    {
        /* No process */
    }

    RCC->CTRL = temp_value;

}

/**
*\*\name    RCC_WaitLseStable.
*\*\fun     Waits for LSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSE oscillator is stable and ready to use
 *\*\         - ERROR      LSE oscillator not yet ready
**/
ErrorStatus RCC_WaitLseStable(void)
{
    __IO uint32_t counter_value = 0;
    FlagStatus status_value;
    ErrorStatus bitstatus;

    /* Wait till LSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_CTRL_FLAG_LSERDF);
        counter_value++;
    } while ((counter_value != LSE_STARTUP_TIMEOUT) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_LSERDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}


/**
*\*\name    RCC_EnableLSEClockSecuritySystem.
*\*\fun     Enables the LSE Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none. 
**/
void RCC_EnableLSEClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->CTRL |= RCC_LSECSS_ENABLE;
    }
    else
    {
        RCC->CTRL &= (~RCC_LSECSS_ENABLE);
    }
}

/**
*\*\name    RCC_EnableHSEClockSecuritySystem.
*\*\fun     Enables the HSE Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none. 
**/
void RCC_EnableHSEClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->CTRL |= RCC_CLKSS_ENABLE;
    }
    else
    {
        RCC->CTRL &= (~RCC_CLKSS_ENABLE);
    }
}

/**
*\*\name    RCC_EnablePll.
*\*\fun     Enables the PLL.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/ 
void RCC_EnablePll(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set PLLEN bit */
       RCC->CTRL |= RCC_PLL_ENABLE;
   }
   else
   {
       /* Reset PLLEN bit */
       RCC->CTRL &= (~RCC_PLL_ENABLE);
   }
}

/**
*\*\name    RCC_ConfigHse.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE :
*\*\          - RCC_HSE_DISABLE    HSE oscillator OFF 
*\*\          - RCC_HSE_ENABLE     HSE oscillator ON
*\*\          - RCC_HSE_BYPASS     HSE oscillator bypassed with external clock
*\*\return  none:
*\*\note    HSE can not be stopped if it is used directly or through the PLL as system clock
**/
void RCC_ConfigHse(uint32_t RCC_HSE)
{
    uint32_t temp_value;
    
    temp_value = RCC->CTRL;
    /* Reset HSEEN bit */
    temp_value &= (~RCC_HSE_ENABLE);
    /* Reset HSEBP bit */
    temp_value &= (~RCC_HSE_BYPASS);
    /* Configure HSE (RC_HSE_DISABLE is already covered by the code section above) */
    if(RCC_HSE == RCC_HSE_ENABLE)
    {
        /* Set HSEEN bit */
        temp_value |= RCC_HSE_ENABLE;
    }   
    else if (RCC_HSE == RCC_HSE_BYPASS)
    {
        /* Set HSEBP and HSEEN bits */
        temp_value |= RCC_HSE_BYPASS | RCC_HSE_ENABLE;
    }
    else
    {
        /* No process */
    }

    RCC->CTRL = temp_value;

}

/**
*\*\name    RCC_EnableHsi.
*\*\fun     Enables the Internal High Speed oscillator (HSI).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE  
*\*\return  none
*\*\note   HSI can not be stopped if it is used directly or through the PLL as system clock.
**/ 
void RCC_EnableHsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set HSIEN bit */
        RCC->CTRL |= RCC_HSI_ENABLE;
    }
    else
    {
        /* Reset HSIEN bit */
        RCC->CTRL &= (~RCC_HSI_ENABLE);
    }
}

/**
*\*\name    RCC_ConfigSysclk.
*\*\fun     Configures the system clock (SYSCLK).
*\*\param   sysclk_source(clock source used as system clock):
*\*\	      - RCC_SYSCLK_SRC_HSI       HSI selected as system clock
*\*\	      - RCC_SYSCLK_SRC_HSE       HSE selected as system clock
*\*\		  - RCC_SYSCLK_SRC_PLL	    PLL selected as system clock
*\*\return  none
**/
void RCC_ConfigSysclk(uint32_t sysclk_source)
{
    uint32_t temp_value;
	
    temp_value = RCC->CFG;
	
    /* Clear SW[1:0] bits */
    temp_value &= CFG_SCLKSW_MASK;
	
    /* Set SW[1:0] bits according to sysclk_source value */
    temp_value |= sysclk_source;
	
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPll.
*\*\fun     Configures the PLL clock source and multiplication factor.
*\*\param   PLL_source(PLL entry clock source):
*\*\   		  - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL clock entry
*\*\param   PLL_inpre(PLL input divider):
*\*\	      - 1 ~ 63(for div 1 ~ div 63)
*\*\param   PLL_mul(PLL multiplication factor):
*\*\	      - 2 ~ 127(for mul 2 ~ mul 127)
*\*\param   PLL_od(PLL OD):
*\*\	      - RCC_PLL_OD_DIV_1 
*\*\	      - RCC_PLL_OD_DIV_2
*\*\return  none
*\*\note    This function must be used only when the PLL is disabled. 
*\*\note    Fin frequency requirement is in the range of 8MHz ~ 32MHz,
*\*\	    Fin/PLL_inpre frequency requirement is in the range of 8MHz ~ 32MHz,
*\*\	    Fvco(=Fin/PLL_inpre*PLL_mul) frequency requirement is in the range of 96MHz ~ 160MHz,
*\*\	    Fout(=Fvco/PLL_od) frequency requirement is in the range of 64MHz ~ 160MHz. 
**/
void RCC_ConfigPll(uint32_t PLL_source, uint32_t  PLL_inpre, uint32_t PLL_mul, uint32_t PLL_od)
{
    uint32_t temp_value1,temp_value2;  
    
    /* get the pll value */
    temp_value1 = RCC->CFG;
    temp_value2 = RCC->PLLCTRL;

    /* Clear PLLSRC, PLLMUL, PLLOD bits */
    temp_value1 &= RCC_PLL_CFG_MASK;
	
    /* Clear PLLINPRES and PLLOUTPRES bits */
    temp_value2 &= RCC_PLL_PLLCTRL_MASK;

    /* Set PLLSRC, PLLHSEPRES, PLLHSIPRES and PLLMULFCT[5:0] bits */
    temp_value1 |= (PLL_source | (PLL_mul<<16) | PLL_od);
	
    /* Set PLLINPRES[1:0] bits */
    temp_value2 |= (PLL_inpre<<8) ;
    
    /* Store the new value */
    RCC->CFG  = temp_value1;
    RCC->PLLCTRL  = temp_value2;
}


/**
*\*\name    RCC_GetSysclkSrc.
*\*\fun     Returns the clock source used as system clock.
*\*\param   none
*\*\return  (The clock source used as system clock):
*\*\	      - RCC_SYSCLK_STS_HSI       HSI selected as system clock
*\*\	      - RCC_SYSCLK_STS_HSE       HSE selected as system clock
*\*\		  - RCC_SYSCLK_STS_PLL	     PLL selected as system clock
**/
uint32_t RCC_GetSysclkSrc(void)
{
    return ((uint32_t)(RCC->CFG & RCC_CFG_SCLKSTS));
}

/**
*\*\name    RCC_ConfigHclk.
*\*\fun     Configures the AHB clock (HCLK).
*\*\param   sysclk_div(AHB clock is derived from the system clock (SYSCLK)):
*\*\          - RCC_SYSCLK_DIV1      AHB clock = SYSCLK
*\*\          - RCC_SYSCLK_DIV2      AHB clock = SYSCLK/2
*\*\          - RCC_SYSCLK_DIV4      AHB clock = SYSCLK/4
*\*\          - RCC_SYSCLK_DIV8      AHB clock = SYSCLK/8
*\*\          - RCC_SYSCLK_DIV16     AHB clock = SYSCLK/16
*\*\          - RCC_SYSCLK_DIV64     AHB clock = SYSCLK/64
*\*\          - RCC_SYSCLK_DIV128    AHB clock = SYSCLK/128
*\*\return  none
**/
void RCC_ConfigHclk(uint32_t sysclk_div)
{
    uint32_t temp_value;
	
    temp_value = RCC->CFG;
	
    /* Clear HPRE[7:4] bits */
    temp_value &= RCC_SYSCLKPRE_MASK;
	
    /* Set HPRE[7:4] bits */
    temp_value |= sysclk_div;
	
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk1.
*\*\fun     Configures the Low Speed APB clock (PCLK1).
*\*\param   RCC_HCLK(APB1 clock is derived from the AHB clock (HCLK)):
*\*\          - RCC_HCLK_DIV1     APB1 clock = HCLK
*\*\          - RCC_HCLK_DIV2     APB1 clock = HCLK/2
*\*\          - RCC_HCLK_DIV4     APB1 clock = HCLK/4
*\*\          - RCC_HCLK_DIV8     APB1 clock = HCLK/8
*\*\          - RCC_HCLK_DIV16    APB1 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk1(uint32_t RCC_HCLK)
{
    uint32_t temp_value;

    temp_value = RCC->CFG;
	
    /* Clear APB1PRES[10:8] bits */
    temp_value &= RCC_APB1_DIV_MASK;
	
    /* Set APB1PRES[10:8] bits */
    temp_value |= RCC_HCLK;
	
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk2.
*\*\fun     Configures the Low Speed APB clock (PCLK2).
*\*\param   RCC_HCLK(APB2 clock is derived from the AHB clock (HCLK)):
*\*\          - RCC_HCLK_DIV1     APB2 clock = HCLK
*\*\          - RCC_HCLK_DIV2     APB2 clock = HCLK/2
*\*\          - RCC_HCLK_DIV4     APB2 clock = HCLK/4
*\*\          - RCC_HCLK_DIV8     APB2 clock = HCLK/8
*\*\          - RCC_HCLK_DIV16    APB2 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk2(uint32_t RCC_HCLK)
{
    uint32_t temp_value;
	
    temp_value = RCC->CFG;
	
    /* Clear APB2PRES[13:11] bits */
    temp_value &= RCC_APB2_DIV_MASK;
	
    /* Set APB2PRES[13:11] bits */
    temp_value |= (RCC_HCLK << 3);
	
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigAdc1mClk.
*\*\fun     Configures the ADCx 1M clock (ADC1MCLK).
*\*\param   ADC1M_clksrc(ADC1M clock source):
*\*\          - RCC_ADC1MCLK_SRC_HSI
*\*\          - RCC_ADC1MCLK_SRC_HSE
*\*\param   ADC1M_prescaler(ADC1M clock prescaler):
*\*\          - RCC_ADC1MCLK_DIV1 
*\*\          - RCC_ADC1MCLK_DIV2 
*\*\          - RCC_ADC1MCLK_DIV4 
*\*\          - RCC_ADC1MCLK_DIV6 
*\*\          - RCC_ADC1MCLK_DIV8 
*\*\          - RCC_ADC1MCLK_DIV10
*\*\          - RCC_ADC1MCLK_DIV12
*\*\          - RCC_ADC1MCLK_DIV16
*\*\          - RCC_ADC1MCLK_DIV32
*\*\return  none
**/
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADC1MSEL and ADC1MPRE[4:0] bits */
    temp_value &= RCC_ADC1MCLK_SRC_MASK;
    temp_value &= RCC_ADC1MCLK_DIV_MASK;
    /* Set ADC1MSEL bits according to ADC1M_clksrc value */
    temp_value |= ADC1M_clksrc;
    /* Set ADC1MPRE[4:0] bits according to ADC1M_prescaler value */
    temp_value |= ADC1M_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigAdcSysclk.
*\*\fun     Configures the ADCSysCLK prescaler.
*\*\param   sclk_prescaler(ADCSCLK prescaler):
*\*\         - RCC_ADCSYSCLK_DIV1     ADC clock = SYSCLK
*\*\         - RCC_ADCSYSCLK_DIV2     ADC clock = SYSCLK/2
*\*\         - RCC_ADCSYSCLK_DIV3     ADC clock = SYSCLK/3
*\*\         - RCC_ADCSYSCLK_DIV4     ADC clock = SYSCLK/4  
*\*\         - RCC_ADCSYSCLK_DIV5     ADC clock = SYSCLK/5 
*\*\         - RCC_ADCSYSCLK_DIV6     ADC clock = SYSCLK/6   
*\*\         - RCC_ADCSYSCLK_DIV8     ADC clock = SYSCLK/8   
*\*\         - RCC_ADCSYSCLK_DIV10    ADC clock = SYSCLK/10   
*\*\         - RCC_ADCSYSCLK_DIV12    ADC clock = SYSCLK/12   
*\*\         - RCC_ADCSYSCLK_DIV16    ADC clock = SYSCLK/16    
*\*\         - RCC_ADCSYSCLK_DIV32    ADC clock = SYSCLK/32   
*\*\         - RCC_ADCSYSCLK_DIV64    ADC clock = SYSCLK/64   
*\*\return  none
**/
void RCC_ConfigAdcSysclk(uint32_t sclk_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;

    /* Clear ADCHPRE[7:4] bits */
    temp_value &= RCC_ADCSPRE_MASK;
	
    /* Set ADCHPRE[7:4] bits */
    temp_value |= sclk_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_EnablePllBypass
*\*\fun     Enables the PLL Bypass.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnablePllBypass(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->CTRL |= (RCC_CTRL_PLLBP);
    }
    else
    {
        RCC->CTRL &= (~RCC_CTRL_PLLBP);
    }    
}

/**
*\*\name    RCC_ConfigHseReadyDly.
*\*\fun   	Configures the HSE RDF Time
*\*\param  
*\*\         - RCC_HSERDFDIV_1MS
*\*\         - RCC_HSERDFDIV_2MS
*\*\         - RCC_HSERDFDIV_3MS
*\*\         - RCC_HSERDFDIV_4MS
*\*\         - RCC_HSERDFDLY_128HSE
*\*\return  none
**/
void RCC_ConfigHseReadyDly(uint32_t hse_dlydiv)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG5;
	
    /* Clear HSERDFDIV and HSERDFDLY bits */
    tmpregister &= RCC_HSERDFDIV_MASK;
	
    /* Set HSERDFDIV and HSERDFDLY  bits */
    tmpregister |= hse_dlydiv;		
		
    /* Store the new value */
    RCC->CFG5 = tmpregister;
}

/**
*\*\name    RCC_GetClocksFreqValue.
*\*\fun     Returns the frequencies of different on chip clocks.
*\*\param   RCC_clocks pointer to a RCC_ClocksType structure which will hold
*\*\        the clocks frequencies.
*\*\return  none
**/
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_Clocks)
{
    uint32_t temp, pllclk, pllmull, pllinpre, pllod, pllsysdiv, pllsource;
    const uint8_t s_AhbPresTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 7, 7};
    const uint8_t s_ApbPresTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    /* Get SYSCLK source -------------------------------------------------------*/
    temp = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (temp)
    {
        case RCC_CFG_SCLKSTS_HSI: /* HSI used as system clock */
            RCC_Clocks->SysclkFreq = HSI_VALUE;
            break;
        case RCC_CFG_SCLKSTS_HSE: /* HSE used as system clock */
            RCC_Clocks->SysclkFreq = HSE_VALUE;
            break;
        case RCC_CFG_SCLKSTS_PLL: /* PLL used as system clock */
            /* Get PLL parameters */
            pllmull   = ((RCC->CFG & RCC_CFG_PLLMUL) >> 16);
            pllinpre  = ((RCC->PLLCTRL & RCC_PLLCTRL_PLLINPRES) >> 8);   /* register value = divider directly */
            pllod     = ((RCC->CFG & RCC_CFG_PLLOD) != 0U) ? 2U : 1U;
            pllsysdiv = ((RCC->CFG & RCC_CFG_PLLSYSDIV) != 0U) ? 2U : 1U;
            pllsource = RCC->CFG & RCC_CFG_PLLSRC;

            if (pllsource == 0x00U)
            {
                /* HSI selected as PLL clock entry */
                pllclk = HSI_VALUE;
            }
            else
            {
                /* HSE selected as PLL clock entry */
                pllclk = HSE_VALUE;
            }

            /* PLL = FIN / N * M / OD / P */
            if (pllinpre != 0U)
            {
                RCC_Clocks->PllFreq = pllclk / pllinpre * pllmull / pllod;
            }
            else
            {
                RCC_Clocks->PllFreq = pllclk;
            }
            RCC_Clocks->SysclkFreq = RCC_Clocks->PllFreq / pllsysdiv;
            break;
        default:
            RCC_Clocks->SysclkFreq = HSI_VALUE;
            break;
    }
    
    /* Compute HCLK, PCLK1, PCLK2 clocks frequencies ----------------*/
    /* Get HCLK prescaler */
    temp   = RCC->CFG & RCC_CFG_AHBPRES;
    temp   = temp >> 4;
    /* HCLK clock frequency */
    RCC_Clocks->HclkFreq = RCC_Clocks->SysclkFreq >> s_AhbPresTable[temp];
    
    /* Get PCLK1 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB1PRES;
    temp   = temp >> 8;
    /* PCLK1 clock frequency */
    RCC_Clocks->Pclk1Freq = RCC_Clocks->HclkFreq >> s_ApbPresTable[temp];

    /* Get PCLK2 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB2PRES;
    temp   = temp >> 11;
    /* PCLK2 clock frequency */
    RCC_Clocks->Pclk2Freq = RCC_Clocks->HclkFreq >> s_ApbPresTable[temp];

}

/**
*\*\name    RCC_EnableAHBPeriphClk.
*\*\fun     Enables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\          - RCC_AHB_PERIPH_ADC2 
*\*\          - RCC_AHB_PERIPH_ADC1  
*\*\          - RCC_AHB_PERIPH_CRC 
*\*\          - RCC_AHB_PERIPH_GPIO    
*\*\          - RCC_AHB_PERIPH_DMA 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE    
*\*\return  none
**/
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHBPCLKEN |= AHB_periph;
    }
    else
    {
        RCC->AHBPCLKEN &= ~AHB_periph;
    }
}

/**
*\*\name    RCC_EnableAPB1PeriphClk.
*\*\fun     Enables the High Speed APB1 peripheral clock.
*\*\param   APB1_periph (APB1 peripheral to gates its clock):
*\*\          - RCC_APB1_PERIPH_OPAMP    
*\*\          - RCC_APB1_PERIPH_CAN    
*\*\          - RCC_APB1_PERIPH_I2C2     
*\*\          - RCC_APB1_PERIPH_I2C1   
*\*\          - RCC_APB1_PERIPH_USART3   
*\*\          - RCC_APB1_PERIPH_USART2   
*\*\          - RCC_APB1_PERIPH_WWDG   
*\*\          - RCC_APB1_PERIPH_RTC    
*\*\          - RCC_APB1_PERIPH_COMPFILT    
*\*\          - RCC_APB1_PERIPH_COMP     
*\*\          - RCC_APB1_PERIPH_BTIM2     
*\*\          - RCC_APB1_PERIPH_BTIM1 
*\*\          - RCC_APB1_PERIPH_GTIM4
*\*\          - RCC_APB1_PERIPH_GTIM3
*\*\          - RCC_APB1_PERIPH_GTIM2
*\*\          - RCC_APB1_PERIPH_GTIM1
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
**/
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1PCLKEN |= APB1_periph;
    }
    else
    {
        RCC->APB1PCLKEN &= ~APB1_periph;
    }
}

/**
*\*\name    RCC_EnableAPB2PeriphClk.
*\*\fun     Enables the High Speed APB2 peripheral clock.
*\*\param   APB1_periph (APB2 peripheral to gates its clock):
*\*\          - RCC_APB2_PERIPH_SPI2    
*\*\          - RCC_APB2_PERIPH_USART4    
*\*\          - RCC_APB2_PERIPH_USART1     
*\*\          - RCC_APB2_PERIPH_ATIM2   
*\*\          - RCC_APB2_PERIPH_SPI1   
*\*\          - RCC_APB2_PERIPH_ATIM1   
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
**/
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2PCLKEN |= APB2_periph;
    }
    else
    {
        RCC->APB2PCLKEN &= ~APB2_periph;
    }
}

/**
*\*\name    RCC_EnableAHBPeriphReset.
*\*\fun     AHB peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.    
*\*\          - RCC_AHB_PERIPH_ADC2
*\*\          - RCC_AHB_PERIPH_ADC1
*\*\          - RCC_AHB_PERIPH_GPIO
*\*\return none.
**/
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph)
{
    RCC->AHBPRST |= AHB_periph;
    RCC->AHBPRST &= ~AHB_periph;   
}

/**
*\*\name    RCC_EnableAPB1PeriphReset.
*\*\fun     Low Speed APB1 peripheral reset.
*\*\param   APB1_periph specifies the APB1 peripheral to reset.
*\*\          - RCC_APB1_PERIPH_OPAMP
*\*\          - RCC_APB1_PERIPH_CAN
*\*\          - RCC_APB1_PERIPH_I2C2
*\*\          - RCC_APB1_PERIPH_I2C1
*\*\          - RCC_APB1_PERIPH_USART3
*\*\          - RCC_APB1_PERIPH_USART2
*\*\          - RCC_APB1_PERIPH_WWDG
*\*\          - RCC_APB1_PERIPH_RTC
*\*\          - RCC_APB1_PERIPH_COMP
*\*\          - RCC_APB1_PERIPH_BTIM2
*\*\          - RCC_APB1_PERIPH_BTIM1
*\*\          - RCC_APB1_PERIPH_GTIM4
*\*\          - RCC_APB1_PERIPH_GTIM3
*\*\          - RCC_APB1_PERIPH_GTIM2
*\*\          - RCC_APB1_PERIPH_GTIM1
*\*\return none. 
**/
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph)
{   
    RCC->APB1PRST |= APB1_periph;
    RCC->APB1PRST &= ~APB1_periph;
}


/**
*\*\name    RCC_EnableAPB2PeriphReset.
*\*\fun     Low Speed APB2 peripheral reset.
*\*\param   APB1_periph specifies the APB2 peripheral to reset.
*\*\          - RCC_APB2_PERIPH_SPI2    
*\*\          - RCC_APB2_PERIPH_USART4    
*\*\          - RCC_APB2_PERIPH_USART1     
*\*\          - RCC_APB2_PERIPH_ATIM2   
*\*\          - RCC_APB2_PERIPH_SPI1   
*\*\          - RCC_APB2_PERIPH_ATIM1
*\*\return none. 
**/
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph)
{  
    RCC->APB2PRST |= APB2_periph;
    RCC->APB2PRST &= ~APB2_periph;    
}


/**
*\*\name    RCC_ConfigMcoClkPre.
*\*\fun     Configures the MCO System and HSI clock prescaler.
*\*\param   MCO_PLL_prescaler specifies the MCO PLL clock prescaler.
*\*\        This parameter can be on of the following values:
*\*\          - RCC_MCO_CLK_DIV1   
*\*\          - RCC_MCO_CLK_DIV2    
*\*\          - RCC_MCO_CLK_DIV4    
*\*\          - RCC_MCO_CLK_DIV8
*\*\          - RCC_MCO_CLK_DIV16
*\*\return  none. 
 */
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG;
	
    /* Clear MCOPRE[30:28] bits */
    temp_value &= RCC_MCO_DIV_MASK;
	
    /* Set MCOPRE[30:28] bits */
    temp_value |= MCO_PLL_prescaler;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name   RCC_ConfigMco.
*\*\fun    Selects the clock source to output on MCO pin.
*\*\param  MCO_source(clock source to output): 
*\*\         - RCC_MCO_NOCLK       No clock selected
*\*\         - RCC_MCO_LSI         LSI oscillator clock selected
*\*\         - RCC_MCO_LSE		   LSE oscillator clock selected
*\*\         - RCC_MCO_SYSCLK      System clock selected
*\*\         - RCC_MCO_HSI         HSI oscillator clock selected
*\*\         - RCC_MCO_HSE         HSE oscillator clock selected
*\*\         - RCC_MCO_PLLDIV      PLL sysdiv clock selected
*\*\return  none. 
**/
void RCC_ConfigMco(uint32_t MCO_source)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG;
	
    /* Clear MCO[27:26] bits */
    tmpregister &= RCC_MCO_MASK;
	
    /* Set MCO[27:26] bits according to RCC_MCO value */
    tmpregister |= MCO_source;

    /* Store the new value */
    RCC->CFG = tmpregister;
}

/**
*\*\name    RCC_EnablePllSysclkDiv.
*\*\fun     Configure whether to enable Pll Clock Output Div2 to sysclk.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnablePllSysclkDiv(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->CFG |= (RCC_PLLSYSDIV2_ENABLE);
    }
    else
    {
        RCC->CFG &= (~RCC_PLLSYSDIV2_ENABLE);
    }    
}

/**
*\*\name    RCC_GetFlagStatus.
*\*\fun     Checks whether the specified RCC flag is set or not.
*\*\param   RCC_flag:
*\*\	      - RCC_CTRL_FLAG_HSIRDF       
*\*\	      - RCC_CTRL_FLAG_HSERDF       
*\*\          - RCC_CTRL_FLAG_PLLRDF       
*\*\	      - RCC_CTRL_FLAG_LSIRDF       
*\*\	      - RCC_CTRL_FLAG_LSERDF       
*\*\	      - RCC_CTRLSTS_FLAG_PORRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_PINRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_WWDGRSTF  
*\*\	      - RCC_CTRLSTS_FLAG_SFTRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_IWDGRSTF  
*\*\	      - RCC_CTRLSTS_FLAG_GLITCHRSTF
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBRSTF 
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBNRSTF
*\*\	      - RCC_CTRLSTS_FLAG_LKUPRSTF  
*\*\return  FlagStatus:    
*\*\      	  - SET 
*\*\  	      - RESET
**/
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag)
{
    uint32_t temp_value;
    uint32_t reg_value;
    FlagStatus bitstatus;

    /* Get the RCC register index */
    temp_value = (uint32_t)RCC_flag >> 5;
    switch(temp_value)
    {
        case 1: /* The flag to check is in CTRL register */
            reg_value = RCC->CTRL;
            break;
        case 3:/* The flag to check is in CTRLSTS register */
            reg_value = RCC->CTRLSTS;
            break;
        default:/* The flag to check is in CFG3 register */
            reg_value = RCC->CTRLSTS;
            break;
    }

    /* Get the flag position */
    temp_value = (uint32_t)RCC_flag & RCC_FLAG_MASK;
    if ((reg_value & ((uint32_t)1 << temp_value)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ClearResetFlag.
*\*\fun     Clears the RCC reset flags.
*\*\param   none
*\*\return  none
*\*\note  Clear the following flags:
*\*\	      - RCC_CTRLSTS_FLAG_PORRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_PINRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_WWDGRSTF  
*\*\	      - RCC_CTRLSTS_FLAG_SFTRSTF   
*\*\	      - RCC_CTRLSTS_FLAG_IWDGRSTF  
*\*\	      - RCC_CTRLSTS_FLAG_GLITCHRSTF
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBRSTF 
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBNRSTF
*\*\	      - RCC_CTRLSTS_FLAG_LKUPRSTF  
**/
void RCC_ClearResetFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    RCC->CTRLSTS |= RCC_CTRLSTS_FLAG_RMRSTF;
	
    /* RMVF bit should be reset */
    RCC->CTRLSTS &= ~RCC_CTRLSTS_FLAG_RMRSTF;
}


/**
*\*\name    RCC_ConfigInt.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_ENABLE_LSESSI
*\*\         - RCC_ENABLE_PLLRDI  
*\*\         - RCC_ENABLE_HSERDI    
*\*\         - RCC_ENABLE_HSIRDI    
*\*\         - RCC_ENABLE_LSERDI   
*\*\         - RCC_ENABLE_LSIRDI 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CLKINT |= Interrupt;
    }
    else
    {
        RCC->CLKINT &= ~Interrupt;
    }
}


/**
*\*\name    RCC_GetIntStatus.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\	    -  RCC_INT_LSESSIF    LSI ready interrupt
*\*\	    -  RCC_INT_CLKSSIF    HSI ready interrupt
*\*\	    -  RCC_INT_PLLRDIF    HSI ready interrupt
*\*\	    -  RCC_INT_HSERDIF    HSI ready interrupt
*\*\	    -  RCC_INT_HSIRDIF    HSI ready interrupt
*\*\	    -  RCC_INT_LSERDIF    HSI ready interrupt
*\*\	    -  RCC_INT_LSIRDIF    HSI ready interrupt
*\*\return  The new state of RccInt 
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag)
{
    INTStatus bitstatus;

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT & interrupt_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the RccInt status */
    return bitstatus;
}

/**
*\*\name    RCC_ClrIntPendingBit.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   RccInt specifies the interrupt pending bit to clear.
*\*\	      -  RCC_CLR_LSESSIF    Clear LSI ready interrupt flag
*\*\	      -  RCC_CLR_CLKSSIF    Clear HSI ready interrupt flag
*\*\	      -  RCC_CLR_PLLRDIF    Clear LSI ready interrupt flag
*\*\	      -  RCC_CLR_HSERDIF    Clear HSI ready interrupt flag
*\*\	      -  RCC_CLR_HSIRDIF    Clear LSI ready interrupt flag
*\*\	      -  RCC_CLR_LSERDIF    Clear HSI ready interrupt flag
*\*\	      -  RCC_CLR_LSIRDIF    Clear LSI ready interrupt flag
*\*\return  none. 
 */
void RCC_ClrIntPendingBit(uint32_t interrupt_clear)
{
   /* Software set this bit to clear INT flag. */
    RCC->CLKINT |= interrupt_clear;
}

/**
*\*\name    RCC_EnableEMCReset.
*\*\fun     Configure whether to generate a reset request when an EMC error occurs.
*\*\param   EMC_type:
*\*\          - RCC_EMC_GB
*\*\          - RCC_EMC_GBN
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCReset(uint32_t EMC_type, FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (EMC_type<<1);
    }
    else
    {
        RCC->EMCCTRL &= (~(EMC_type<<1));
    }   
}

/**
*\*\name    RCC_EnableEMCDetect.
*\*\fun     Configure whether to enable EMC detection.
*\*\param   EMC_type:
*\*\          - RCC_EMC_GB
*\*\          - RCC_EMC_GBN
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCDetect(uint32_t EMC_type, FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= EMC_type;
    }
    else
    {
        RCC->EMCCTRL &= ~EMC_type;
    }   
}

/**
*\*\name    RCC_EnableEMCSwitch.
*\*\fun     Configure whether to enable EMC switch.
*\*\param   EMC_type:
*\*\          - RCC_EMC_GB
*\*\          - RCC_EMC_GBN
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCSwitch(uint32_t EMC_type, FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (EMC_type<<2);
    }
    else
    {
        RCC->EMCCTRL &= (~(EMC_type<<2));
    }    
}

/**
*\*\name    RCC_ConfigEMCDetectLevel.
*\*\fun     Configures the voltage threshold detected by the EMC.
*\*\param   EMC_type:
*\*\          - RCC_EMC_GB
*\*\          - RCC_EMC_GBN
*\*\param   level (The input parameters must be the following values):
*\*\          - 0x0 ~ 0x3
*\*\return  none
**/
void RCC_ConfigEMCDetectLevel(uint32_t EMC_type, uint8_t level)
{
    uint32_t temp_value;
    
    temp_value = RCC->EMCCTRL;
    if(EMC_type == RCC_EMC_GB)
    {
        /* Clear GBDETSEL[9:8] bits bit */
        temp_value &= EMCCTRL_GBDETSEL_MASK;
		
        /* Set GBDETSEL[9:8] bits according to level value */
        temp_value |= ((uint32_t)level<<8);
    }
    else
    {
        /* Clear GBNDETSEL[17:16] bits bit */
        temp_value &= EMCCTRL_GBNDETSEL_MASK;
		
        /* Set GBNDETSEL[17:16] bits according to level value */
        temp_value |= ((uint32_t)level<<16);
        
    }
    /* Store the new value */
    RCC->EMCCTRL = temp_value;
}


/**
*\*\name    RCC_EnableGlitchDetect.
*\*\fun     Configure whether to enable Glitch.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableGlitchDetect(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GVDET);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GVDET);
    }    
}

/**
*\*\name    RCC_EnableGlitchReset.
*\*\fun     Configure whether to enable Glitch reset.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableGlitchReset(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GVRST);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GVRST);
    }    
}

/**
*\*\name    RCC_EnableGlitchSwitch.
*\*\fun     Configure whether to enable Glitch switch.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableGlitchSwitch(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GVSW);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GVSW);
    }    
}


/**
*\*\name    RCC_ConfigGlitchDetectLevel.
*\*\fun     Configures the voltage threshold detected by the Glitch.
*\*\param   level (The input parameters must be the following values):
*\*\        - 0x0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigGlitchDetectLevel(uint8_t level)
{
    uint32_t temp_value;
    
    temp_value = RCC->EMCCTRL;
	
	/* Clear GVDETSEL[4:0] bits bit */
	temp_value &= EMCCTRL_GVDETSEL_MASK;
	
	/* Set GVDETSEL[4:0] bits */
	temp_value |= (uint32_t)level ;
	
    /* Store the new value */
    RCC->EMCCTRL = temp_value;
}

/**
*\*\name    RCC_EnableM4LockupReset.
*\*\fun     Configure whether to enable M4 lockup reset.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableM4LockupReset(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_LKUPRSTEN);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_LKUPRSTEN);
    }    
}

/**
*\*\name    RCC_EnableEMCGBNInt.
*\*\fun     Configure whether to enable EMC GBN int.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCGBNInt(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GBNIEN);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GBNIEN);
    }    
}

/**
*\*\name    RCC_EnableEMCGBInt.
*\*\fun     Configure whether to enable EMC GB.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCGBInt(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GBIEN);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GBIEN);
    }    
}

/**
*\*\name    RCC_EnableGlitchInt.
*\*\fun     Configure whether to enable GLITCH int.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableGlitchInt(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (RCC_EMCCTRL_GLTIEN);
    }
    else
    {
        RCC->EMCCTRL &= (~RCC_EMCCTRL_GLTIEN);
    }    
}

/**
*\*\name    RCC_ConfigI2SClk.
*\*\fun     Configures the I2S clock source(I2SCLK).
*\*\param   I2s_clksrc(I2S clock source):
*\*\         - RCC_I2S_CLKSEL_SYS
*\*\         - RCC_I2S_CLKSEL_IOM  
*\*\return  none
**/
void RCC_ConfigI2SClk(uint32_t i2s_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear I2SCLK_SEL bits */
    temp_value &= RCC_I2S_CLKSEL_MASK;
    /* Set I2SMCLK_SEL */
    temp_value |= i2s_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigGtim1Clk.
*\*\fun     Configures the GTIM1 clock source(GTIM1CLK).
*\*\param   Gtimer_clksrc(GTIM1 clock source):
*\*\         - RCC_GTIM1_CLKSEL_SYS
*\*\         - RCC_GTIM1_CLKSEL_AHB  
*\*\return  none
**/
void RCC_ConfigGtim1Clk(uint32_t gtimer1_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear GTIM1CLK_SEL bits */
    temp_value &= RCC_GTIM1_CLKSEL_MASK;
    /* Set GTIM1CLK_SEL */
    temp_value |= gtimer1_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigGtim2Clk.
*\*\fun     Configures the GTIM2 clock source(GTIM2CLK).
*\*\param   Gtimer_clksrc(GTIM2 clock source):
*\*\         - RCC_GTIM2_CLKSEL_SYS
*\*\         - RCC_GTIM2_CLKSEL_AHB  
*\*\return  none
**/
void RCC_ConfigGtim2Clk(uint32_t gtimer2_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear GTIM2CLK_SEL bits */
    temp_value &= RCC_GTIM2_CLKSEL_MASK;
	
    /* Set GTIM2CLK_SEL bits */
    temp_value |= gtimer2_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigGtim3Clk.
*\*\fun     Configures the GTIM3 clock source(GTIM3CLK).
*\*\param   Gtimer_clksrc(GTIM3 clock source):
*\*\         - RCC_GTIM3_CLKSEL_SYS
*\*\         - RCC_GTIM3_CLKSEL_AHB  
*\*\return  none
**/
void RCC_ConfigGtim3Clk(uint32_t gtimer3_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear GTIM3CLK_SEL bits */
    temp_value &= RCC_GTIM3_CLKSEL_MASK;
	
    /* Set GTIM3CLK_SEL bits */
    temp_value |= gtimer3_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigGtim4Clk.
*\*\fun     Configures the GTIM4 clock source(GTIM4CLK).
*\*\param   Gtimer_clksrc(GTIM4 clock source):
*\*\         - RCC_GTIM4_CLKSEL_SYS
*\*\         - RCC_GTIM4_CLKSEL_AHB  
*\*\return  none
**/
void RCC_ConfigGtim4Clk(uint32_t gtimer4_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear GTIM4CLK_SEL bits */
    temp_value &= RCC_GTIM4_CLKSEL_MASK;
	
    /* Set GTIM4CLK_SEL bits */
    temp_value |= gtimer4_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigAtim1Clk.
*\*\fun     Configures the ATIM1 clock source(ATIM1CLK).
*\*\param   Gtimer_clksrc(ATIM1 clock source):
*\*\         - RCC_ATIM1_CLKSEL_SYS
*\*\         - RCC_ATIM1_CLKSEL_AHB  
*\*\         - RCC_ATIM1_CLKSEL_PLL
*\*\return  none
**/
void RCC_ConfigAtim1Clk(uint32_t atimer1_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear ATIM1CLK_SEL bits */
    temp_value &= RCC_ATIM1_CLKSEL_MASK;
	
    /* Set ATIM1CLK_SEL bits */
    temp_value |= atimer1_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigAtim2Clk.
*\*\fun     Configures the ATIM2 clock source(ATIM2CLK).
*\*\param   Gtimer_clksrc(ATIM2 clock source):
*\*\         - RCC_ATIM2_CLKSEL_SYS
*\*\         - RCC_ATIM2_CLKSEL_AHB  
*\*\         - RCC_ATIM2_CLKSEL_PLL
*\*\return  none
**/
void RCC_ConfigAtim2Clk(uint32_t atimer2_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear ATIM2CLK_SEL bits */
    temp_value &= RCC_ATIM2_CLKSEL_MASK;
	
    /* Set ATIM2CLK_SEL bits */
    temp_value |= atimer2_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigBtim1Clk.
*\*\fun     Configures the BTIM1 clock source(BTIM1CLK).
*\*\param   btimer1_clksrc(BTIM1 clock source):
*\*\         - RCC_BTIM1_CLKSEL_LSI
*\*\         - RCC_BTIM1_CLKSEL_LSE
*\*\         - RCC_BTIM1_CLKSEL_APB1
*\*\return  none
**/
void RCC_ConfigBtim1Clk(uint32_t btimer1_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear BTIM1CLK_SEL bits */
    temp_value &= RCC_BTIM1_CLKSEL_MASK;
	
    /* Set BTIM1CLK_SEL bits */
    temp_value |= btimer1_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigRTCClk.
*\*\fun     Configures the RTC clock source(RTCCLK).
*\*\param   Gtimer_clksrc(RTC clock source):
*\*\         - RCC_RTC_CLKSEL_LSI
*\*\         - RCC_RTC_CLKSEL_LSE  
*\*\         - RCC_RTC_CLKSEL_HSE_DIV128
*\*\return  none
**/
void RCC_ConfigRTCClk(uint32_t rtc_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear RTCCLK_SEL bits */
    temp_value &= RCC_RTC_CLKSEL_MASK;
	
    /* Set RTCCLK_SEL bits */
    temp_value |= rtc_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigUsart1Clk.
*\*\fun     Configures the UART1 clock source(UART1CLK).
*\*\param   uart1_clksrc(UART1 clock source):
*\*\         - RCC_USART1_CLKSEL_LSI
*\*\         - RCC_USART1_CLKSEL_LSE 
*\*\         - RCC_USART1_CLKSEL_APB2 
*\*\return  none
**/
void RCC_ConfigUsart1Clk(uint32_t usart1_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear USART1CLK_SEL bits */
    temp_value &= RCC_USART1_CLKSEL_MASK;
    /* Set USART1CLK_SEL bits */
    temp_value |= usart1_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigLowPowerClk.
*\*\fun     Configures the LP clock source(LPCLK).
*\*\param   LP_clksrc(LP clock source):
*\*\         - RCC_LP_CLKSEL_LSI
*\*\         - RCC_LP_CLKSEL_LSE 
*\*\return  none
**/
void RCC_ConfigLowPowerClk(uint32_t lp_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear LPCLK_SEL bits */
    temp_value &= RCC_LP_CLKSEL_MASK;
    /* Set LPCLK_SEL */
    temp_value |= lp_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigUsart4Clk.
*\*\fun     Configures the UART4 clock source(UART4CLK).
*\*\param   uart4_clksrc(UART4 clock source):
*\*\         - RCC_USART4_CLKSEL_LSI
*\*\         - RCC_USART4_CLKSEL_LSE 
*\*\         - RCC_USART4_CLKSEL_APB2 
*\*\return  none
**/
void RCC_ConfigUsart4Clk(uint32_t usart4_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
	
    /* Clear USART4CLK_SEL bits */
    temp_value &= RCC_USART4_CLKSEL_MASK;
	
    /* Set USART4CLK_SEL bits */
    temp_value |= usart4_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigIOFilter.
*\*\fun     Configures the Speed of GPIO fliter.
*\*\param   ioflitclk_div value:
*\*\        -0 ~ 0x3F
*\*\return  none
**/
void RCC_ConfigIOFilter(uint32_t ioflitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG5;
	
    /* Clear IOFLITCLK[5:0] bits */
    tmpregister &= RCC_IOMFILCLK_MASK;
	
    /* Set IOFLITCLK[5:0] bits*/
    tmpregister |= ioflitclk_div;
	
    /* Store the new value */
    RCC->CFG5 = tmpregister;
}

/**
*\*\name    RCC_ConfigGTIM4Filter.
*\*\fun     Configures the Speed of GTIM4 fliter.
*\*\param   gtim4flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigGTIM4Filter(uint32_t gtim4flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
    /* Clear GTIM4FILTCLK[4:0] bits */
    tmpregister &= RCC_GTIM4FILTCLK_MASK;
	
    /* Set GTIM4FILTCLK[4:0] bits */
    tmpregister |= gtim4flitclk_div;
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_ConfigGTIM3Filter.
*\*\fun     Configures the Speed of GTIM3 fliter.
*\*\param   gtim3flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigGTIM3Filter(uint32_t gtim3flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
   /* Clear GTIM3FILTCLK[9:5] bits */
    tmpregister &= RCC_GTIM3FILTCLK_MASK;
	
    /* Set GTIM3FILTCLK[9:5] bits */
    tmpregister |= (gtim3flitclk_div<<5);
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_ConfigGTIM2Filter.
*\*\fun     Configures the Speed of GTIM2 fliter.
*\*\param   gtim2flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigGTIM2Filter(uint32_t gtim2flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
   /* Clear GTIM3FILTCLK[14:10] bits */
    tmpregister &= RCC_GTIM2FILTCLK_MASK;
	
    /* Set GTIM3FILTCLK[14:10] bits */
    tmpregister |= (gtim2flitclk_div<<10);
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_ConfigGTIM1Filter.
*\*\fun     Configures the Speed of GTIM1 fliter.
*\*\param   gtim1flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigGTIM1Filter(uint32_t gtim1flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
   /* Clear GTIM1FILTCLK[19:16] bits */
    tmpregister &= RCC_GTIM1FILTCLK_MASK;
	
    /* Set GTIM1FILTCLK[19:16] bits */
    tmpregister |= (gtim1flitclk_div<<15);
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_ConfigATIM1Filter.
*\*\fun     Configures the Speed of ATIM1 fliter.
*\*\param   atim1flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigATIM1Filter(uint32_t atim1flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
   /* Clear ATIM1FILTCLK[19:16] bits */
    tmpregister &= RCC_ATIM1FILTCLK_MASK;
	
    /* Set ATIM1FILTCLK[19:16] bits */
    tmpregister |= (atim1flitclk_div<<25);
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_ConfigATIM2Filter.
*\*\fun     Configures the Speed of ATIM2 fliter.
*\*\param   atim1flitclk_div value:
*\*\        -0 ~ 0x1F
*\*\return  none
**/
void RCC_ConfigATIM2Filter(uint32_t atim2flitclk_div)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG3;
	
   /* Clear ATIM2FILTCLK[24:21] bits */
    tmpregister &= RCC_ATIM2FILTCLK_MASK;
	
    /* Set ATIM2FILTCLK[24:21] bits */
    tmpregister |= (atim2flitclk_div<<20);
	
    /* Store the new value */
    RCC->CFG3 = tmpregister;
}

/**
*\*\name    RCC_EnableLSECaptureRequest.
*\*\fun     Configure whether to enable LSE Timer Capture requests.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableLSECaptureRequest(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->CTRL |= (RCC_LSECAP_ENABLE);
    }
    else
    {
        RCC->CTRL &= (~RCC_LSECAP_ENABLE);
    }    
}

/**
*\*\name    RCC_EnableHSECaptureRequest.
*\*\fun     Configure whether to enable HSE Timer Capture requests .
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableHSECaptureRequest(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->CTRL |= (RCC_HSECAP_ENABLE);
    }
    else
    {
        RCC->CTRL &= (~RCC_HSECAP_ENABLE);
    }    
}

/**
*\*\name    RCC_ConfigLseGlitchFilter.
*\*\fun     Configure LSE glitch filter.
*\*\param   lse glitch filter select for  ad_lse_clkout
*\*\        RCC_LSE_GLITCHFILTER_25ns
\*\         RCC_LSE_GLITCHFILTER_50ns
\*\         RCC_LSE_GLITCHFILTER_100ns
\*\         RCC_LSE_GLITCHFILTER_250ns
*\*\return  none
**/
void RCC_ConfigLseGlitchFilter(uint32_t lsegliterflit)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG4;
	
    /* Clear GlitchFilter[12:9] bits */
    tmpregister &= RCC_LSE_GLITCHFILTER_MASK;
	
    /* Set GlitchFilter[12:9] bits*/
    tmpregister |= lsegliterflit;
	
    /* Store the new value */
    RCC->CFG4 = tmpregister;
}

/**
*\*\name    RCC_EnableLseNim.
*\*\fun     LSE noise immunity enable.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableLseNim(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->CFG4 |= (RCC_CFG4_LSENIMEN);
    }
    else
    {
        RCC->CFG4 &= (~RCC_CFG4_LSENIMEN);
    }   
 
}

/**
*\*\name    RCC_ConfigLseBuffOpt.
*\*\fun     Configure LSE buffer trimming signal.
*\*\param   lse buffer trimming
*\*\return  none
**/
void RCC_ConfigLseBuffOpt(uint32_t lsebuffopt)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG4;
	
    /* Clear LseBuffOpt[7:6] bits */
    tmpregister &= RCC_LSE_BUFFOPT_MASK;
	
    /* Set LseBuffOpt[7:6] bits*/
    tmpregister |= (lsebuffopt << 6);
	
    /* Store the new value */
    RCC->CFG4 = tmpregister;
}

/**
*\*\name    RCC_ConfigLseBiasTrim.
*\*\fun     Configure lse bias trimming signal.
*\*\param   lse bias trimming
*\*\return  none
**/
void RCC_ConfigLseBiasTrim(uint32_t LseBiasTrim)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG4;
	
    /* Clear LseBiasTrim[5:2] bits */
    tmpregister &= RCC_LSE_BIASTRIM_MASK;
	
    /* Set LseBiasTrim[5:2] bits*/
    tmpregister |= (LseBiasTrim << 2);
	
    /* Store the new value */
    RCC->CFG4 = tmpregister;
}

/**
*\*\name    RCC_ConfigLseDrvTrim.
*\*\fun     Configure LSE core trim ming signal.
*\*\param   lse drv trimming
*\*\return  none
**/
void RCC_ConfigLseDrvTrim(uint32_t lsedrvtrim)
{
    uint32_t tmpregister;

    tmpregister = RCC->CFG4;

    /* Clear LseDrvTrim[1:0] bits */
    tmpregister &= RCC_LSE_LSEDRVTRIM_MASK;

    /* Set LseDrvTrim[1:0] bits*/
    tmpregister |= lsedrvtrim;
	
    /* Store the new value */
    RCC->CFG4 = tmpregister;
}

/**
*\*\name    RCC_ConfigPwrUpStepWidth.
*\*\fun     Configure power up step width.
*\*\param   PWRUP STEP WIDTH (0<pwrupstepwidth<=1024)
*\*\return  none
**/
void RCC_ConfigPwrUpStepWidth(uint32_t pwrupstepwidth)
{
    uint32_t tmpregister;

    tmpregister = RCC->PWRCTRL;
	
    /* Clear PwrUpStepWidtht[31:22] bits */
    tmpregister &= RCC_PWRUP_STEPWID_MASK;
	
    /* Set PwrUpStepWidtht[31:22] bits*/
    tmpregister |= pwrupstepwidth<<22;
	
    /* Store the new value */
    RCC->PWRCTRL = tmpregister;
}

/**
*\*\name    RCC_ConfigPwrDownStepWidth.
*\*\fun     Configure power down step width.
*\*\param   power down step width (0<pwrdownstepwidth<=1024)
*\*\return  none
**/
void RCC_ConfigPwrDownStepWidth(uint32_t pwrdownstepwidth)
{
    uint32_t tmpregister;

    tmpregister = RCC->PWRCTRL;

    /* Clear PwrDownStepWidth[21:12] bits */
    tmpregister &= (~RCC_PWRCTRL_DOWNSTEPWID);

    /* Set PwrDownStepWidth[21:12] bits*/
    tmpregister |= pwrdownstepwidth<<12;
	
    /* Store the new value */
    RCC->PWRCTRL = tmpregister;
}

/**
*\*\name    RCC_EnablePwrDownStep.
*\*\fun     Powr down step width enable.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnablePwrDownStep(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->PWRCTRL |= (RCC_PWRDOWN_STEPWID_ENABLE);
    }
    else
    {
        RCC->PWRCTRL &= (~RCC_PWRDOWN_STEPWID_ENABLE);
    }   
 
}

/**
*\*\name    RCC_EnablePwrUpStep.
*\*\fun     Powr up step width enable.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnablePwrUpStep(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->PWRCTRL |= (RCC_PWRUP_STEPWID_ENABLE);
    }
    else
    {
        RCC->PWRCTRL &= (~RCC_PWRUP_STEPWID_ENABLE);
    }   
}

/**
*\*\name    RCC_PStepSfDiv.
*\*\fun   Software-Controlled Power-Saving Stages (Based on PLL Clock)	
*\*\param  
*\*\         - RCC_PWRUP_PSTEPSFDIV_1
*\*\         - RCC_PWRUP_PSTEPSFDIV_2
*\*\         - RCC_PWRUP_PSTEPSFDIV_4
*\*\         - RCC_PWRUP_PSTEPSFDIV_8
*\*\         - RCC_PWRUP_PSTEPSFDIV_16
*\*\return  none
**/
void RCC_PStepSfDiv(uint32_t pstepsfdiv)
{
    uint32_t tmpregister;

    tmpregister = RCC->PWRCTRL;
	
    /* Clear PSTEPSFDIV[9:7] bits */
    tmpregister &= RCC_PWRUP_PSTEPSFDIV_MASK;
	
    /* Set PSTEPSFDIV[9:7] bits */
    tmpregister |= pstepsfdiv;

    /* Store the new value */
    RCC->PWRCTRL = tmpregister;
}

/**
*\*\name    RCC_EnablePStepSf.
*\*\fun     Enable the software power step.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnablePStepSf(FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->PWRCTRL |= (RCC_PWRCTRL_PSTEPSFTEN);
    }
    else
    {
        RCC->PWRCTRL &= (~RCC_PWRCTRL_PSTEPSFTEN);
    }   
}

/**
*\*\name    RCC_GetPwrStepFsm.
*\*\fun     Get PLL Power Step Control FSM. 
*\*\return  Status:    
*\*\        0  - START
*\*\        1  - UP step1
*\*\        3  - UP step2
*\*\        7  - UP step3
*\*\        15 - UP step4
*\*\        14 - STOP
*\*\        12 - DOWN step1
*\*\        8  - DOWN step2
*\*\        9  - DOWN step3
*\*\        11 - DOWN step4
**/
uint32_t RCC_GetPwrStepFsm(void)
{ 
    uint32_t tmpregister;

    tmpregister = ((RCC->PWRCTRL & RCC_PWRCTRL_PSTEPST) >> 2);
    return tmpregister;	
}


/**
*\*\name    RCC_GetPwrDownStepFlag.
*\*\fun     Get PLL Power Step Control down step flag. 
*\*\return  FlagStatus:    
*\*\      	  - SET 
*\*\  	      - RESET 
**/
FlagStatus RCC_GetPwrDownStepFlag(void)
{ 
    FlagStatus bitstatus;;

    if((RCC->PWRCTRL & RCC_PWRCTRL_PSTEPDNF) != 0U)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;	
    }
    return bitstatus;
}

/**
*\*\name    RCC_ClearPwrDownStepFlag.
*\*\fun     Clear pstep downstep flag.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_ClearPwrDownStepFlag(void)
{ 
    RCC->PWRCTRL |= (RCC_PWRCTRL_RMVF);
    RCC->PWRCTRL &= (~RCC_PWRCTRL_RMVF); 
}


