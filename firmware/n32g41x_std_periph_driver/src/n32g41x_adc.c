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
*\*\file n32g41x_adc.c
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/


#include "n32g41x_adc.h"
#include "n32g41x_rcc.h"

/* bit data handler */
#define BIT_JUDGE_AND_HANDLER(IS_ENABLE, BIT_MASK)    (((IS_ENABLE) != DISABLE ) ? (BIT_MASK) : (0x00000000U))

#define CTRL1_CLR_MASK          ((uint32_t)0x00000F81U)
#define CTRL2_CLR_MASK          ((uint32_t)0x013F0032U)

#define RSEQ3_CLR_MASK          ((uint32_t)0x1E000000U)

/** ADC Driving Functions Declaration **/ 

/**
*\*\name    ADC_DeInit.
*\*\fun     Reset the ADC registers.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\return  none
**/
void ADC_DeInit(const ADC_Module* ADCx)
{
    if (ADCx == ADC1)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC1);
    }
    else if (ADCx == ADC2)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC2);
    }
    else
    {
        /*no process*/
    }

}

/**
*\*\name    ADC_Init.
*\*\fun     Initializes the ADCx peripheral according to the specified parameters in the ADC_InitStruct.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_InitParam :
*\*\          - WorkMode
*\*\             - ADC_WORKMODE_INDEPENDENT                  
*\*\             - ADC_WORKMODE_DUAL_REG_INJECT_SIMULT  
*\*\             - ADC_WORKMODE_DUAL_INJ_SIMULT   
*\*\             - ADC_WORKMODE_DUAL_REG_SIMULT    
*\*\             - ADC_WORKMODE_DUAL_INTERL     
*\*\             - ADC_WORKMODE_DUAL_ALTER_TRIG  
*\*\          - MultiChEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - ContinueConvEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - ExtTrigSelect
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2 
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_CC1   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_CC2   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_CC3   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_CC1   
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM1_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM1_CC2   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM1_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM2_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM2_CC1   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM2_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_CC1   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_CC2   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_CC1   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_CC2   
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_CC4   
*\*\             - ADC_EXT_TRIG_REG_CONV_BTIM1_TRGO  
*\*\             - ADC_EXT_TRIG_REG_CONV_EXT_INT0_15 
*\*\             - ADC_EXT_TRIG_REG_CONV_SOFTWARE           
*\*\          - DatAlign
*\*\             - ADC_DAT_ALIGN_R
*\*\             - ADC_DAT_ALIGN_L
*\*\          - ChsNumber: This parameter must be between 1 to 16. 
*\*\return  none
**/
void ADC_Init(ADC_Module* ADCx, const ADC_InitType* ADC_InitParam)
{
    uint32_t tempreg1;
    uint8_t tempreg2;

    /*---------------------------- ADCx CTRL1 Configuration -----------------*/
    /* Get the ADCx CTRL1 value */
    tempreg1 = ADCx->CTRL1;
    /* Clear MUTIMODE and SCANMD bits */
    tempreg1 &= (~CTRL1_CLR_MASK);
    /* Configure ADCx: Muti mode and scan conversion mode */
    /* Set MUTIMOD bits according to WorkMode value */
    /* Set SCANMD bit according to MultiChEn value */
    tempreg1 |= (uint32_t)(ADC_InitParam->WorkMode | (uint32_t)ADC_InitParam->MultiChEn );
    /* Write to ADCx CTRL1 */
    ADCx->CTRL1 = tempreg1;

    /*---------------------------- ADCx CTRL2 Configuration -----------------*/
    /* Get the ADCx CTRL2 value */
    tempreg1 = ADCx->CTRL2;
    /* Clear CTU, ALIG ,EXTPRSEL and EXTRSEL bits */
    tempreg1 &= (~CTRL2_CLR_MASK);
    /* Set ALIGN bit according to DatAlign value */
    /* Set EXTSEL and EXTPRSEL bits according to ExtTrigSelect value */
    /* Set CTU bit according to ContinueConvEn value */
    tempreg1 |= (uint32_t)(ADC_InitParam->DatAlign | ADC_InitParam->ExtTrigSelect
                          | ((uint32_t)ADC_InitParam->ContinueConvEn << 1));
    /* Write to ADCx CTRL2 */
    ADCx->CTRL2 = tempreg1;

    /*---------------------------- ADCx RSEQ3 Configuration -----------------*/
    /* Get the ADCx RSEQ3 value */
    tempreg1 = ADCx->RSEQ3;
    /* Clear L bits */
    tempreg1 &= (~RSEQ3_CLR_MASK);
    /* Configure ADCx: regular channel sequence length */
    /* Set LEN bits according to ChsNumber value */
    tempreg2 = (uint8_t)(ADC_InitParam->ChsNumber - 1u);
    tempreg1 |= (uint32_t)tempreg2 << 25;
    /* Write to ADCx RSEQ3 */
    ADCx->RSEQ3 = tempreg1;
}

/**
*\*\name    ADC_InitStruct.
*\*\fun     Fills all ADC_InitStruct member with default value.
*\*\param   ADC_InitStructure :
*\*\          - WorkMode
*\*\          - MultiChEn
*\*\          - ContinueConvEn
*\*\          - ExtTrigSelect
*\*\          - DatAlign
*\*\          - ChsNumber
*\*\return  none
**/
void ADC_InitStruct(ADC_InitType* ADC_InitStructure)
{
    /* Reset ADC init structure parameters values */
    /* Initialize the WorkMode member */
	ADC_InitStructure->WorkMode = ADC_WORKMODE_INDEPENDENT;
    /* initialize the MultiChEn member */
	ADC_InitStructure->MultiChEn = DISABLE;
    /* Initialize the ContinueConvEn member */
	ADC_InitStructure->ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect member */
	ADC_InitStructure->ExtTrigSelect = ADC_EXT_TRIG_REG_CONV_SOFTWARE;
    /* Initialize the DatAlign member */
	ADC_InitStructure->DatAlign = ADC_DAT_ALIGN_R;
    /* Initialize the ChsNumber member */
	ADC_InitStructure->ChsNumber = 1;
}


/**
*\*\name    ADC_Enable.
*\*\fun     Configures the specified ADC enable or disable.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the AD_ON bit to wake up the ADC from power down mode */
        ADCx->CTRL2 |= ADC_ON_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->CTRL2 &= (~ADC_ON_EN_MASK);
    }
}
/**
*\*\name    ADC_EnableDMA.
*\*\fun     Enables or disables the specified ADC DMA request.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableDMA(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADCx->CTRL2 |= ADC_DMAEN_MASK;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADCx->CTRL2 &= (~ADC_DMAEN_MASK);
    }
}


/**
*\*\name    ADC_SetMultiTwoSamplingDelay.
*\*\fun     Set ADC multimode delay between 2 sampling phases.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   MultiTwoSamplingDelay 
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_1
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_2
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_3
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_4
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_5
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_6
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_7
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_8
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_9
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_10
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_11
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_12
*\*\return  none
**/
void ADC_SetMultiTwoSamplingDelay(ADC_Module* ADCx, uint32_t MultiTwoSamplingDelay)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the old delay number */
    tempreg &= (~ADC_ADC_MULTI_TWOSMP_DELAY_MASK);
    /* Set the delay number */
    tempreg |= MultiTwoSamplingDelay;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_ConfigDiscModeChannelCount.
*\*\fun     Configures the discontinuous numbers for the selected ADC regular
*\*\        group channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Number : specifies the discontinuous mode regular channel
 *          count value. This number must be range form 1 to 8.
*\*\return  none
**/
void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the old discontinuous mode channel count */
    tempreg &= (~ADC_DISC_NUM_MASK);
    /* Set the discontinuous mode channel count */
    tempreg |= (((uint32_t)Number - 1u) << 2);
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_EnableAutoInjectedConv.
*\*\fun     Enables or disables the selected ADC automatic injected group
*\*\        conversion after regular one
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 |= ADC_JAUTO_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 &= (~ADC_JAUTO_EN_MASK);
    }
}

/**
*\*\name    ADC_EnableDiscMode.
*\*\fun     Enables or disables the discontinuous mode on regular group
*\*         channel for the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 |= ADC_DISC_REG_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 &= (~ADC_DISC_REG_EN_MASK);
    }
}

/**
*\*\name    ADC_EnableInjectedDiscMode.
*\*\fun     Enables or disables the discontinuous mode on injected group
*\*         channel for the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 |= ADC_DISC_INJ_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 &= (~ADC_DISC_INJ_EN_MASK);
    }
}

/**
*\*\name    ADC_ConfigRegularChannel.
*\*\fun     Configures for the selected ADC regular channel its corresponding
*\*\        rank in the sequencer and its sample time.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_Channel :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\param   Rank : The rank in the regular group sequencer. This parameter must be between 1 to 16.
*\*\param   ADC_SampleTime : The sample time value to be set for the selected channel.
*\*\          - ADC_SAMP_TIME_CYCLES_4    
*\*\          - ADC_SAMP_TIME_CYCLES_6    
*\*\          - ADC_SAMP_TIME_CYCLES_8    
*\*\          - ADC_SAMP_TIME_CYCLES_14   
*\*\          - ADC_SAMP_TIME_CYCLES_29   
*\*\          - ADC_SAMP_TIME_CYCLES_42   
*\*\          - ADC_SAMP_TIME_CYCLES_56   
*\*\          - ADC_SAMP_TIME_CYCLES_72   
*\*\          - ADC_SAMP_TIME_CYCLES_88   
*\*\          - ADC_SAMP_TIME_CYCLES_120  
*\*\          - ADC_SAMP_TIME_CYCLES_182  
*\*\          - ADC_SAMP_TIME_CYCLES_240  
*\*\          - ADC_SAMP_TIME_CYCLES_300  
*\*\          - ADC_SAMP_TIME_CYCLES_400  
*\*\          - ADC_SAMP_TIME_CYCLES_480  
*\*\          - ADC_SAMP_TIME_CYCLES_600
*\*\return  none
**/
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tempreg1, tempreg2;
    if (ADC_Channel > ADC_CH_15)  /* if ADC_CH_16 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * (ADC_Channel - 16u));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * (ADC_Channel - 16u));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT3 = tempreg1;
    }
    else if (ADC_Channel > ADC_CH_7) /* if ADC_CH_8 ... ADC_CH_15 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * (ADC_Channel - 8u));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * (ADC_Channel - 8u));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tempreg1;
    }
    else /* if ADC_CH_0 ... ADC_CH_7 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * (ADC_Channel));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * (ADC_Channel));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tempreg1;
    }

    if (Rank < 7u)  /* For Rank 1 to 6 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5u * (Rank - 1u));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5u * (Rank - 1u));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ1 = tempreg1;
    }
    else if (Rank < 13u)   /* For Rank 7 to 12 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5u * (Rank - 7u));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5u * (Rank - 7u));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ2 = tempreg1;
    }
    else /* For Rank 13 to 16 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5u * (Rank - 13u));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5u * (Rank - 13u));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ3 = tempreg1;
    }
}

/**
*\*\name    ADC_GetDat.
*\*\fun     Get the last ADCx conversion result data for regular channel
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\return  The Data conversion value.
**/
uint16_t ADC_GetDat(const ADC_Module* ADCx)
{
    /* Return the selected ADC conversion value */
    return (uint16_t)ADCx->DAT;
}

/**
*\*\name    ADC_GetMutiModeConversionDat.
*\*\fun     Get the last ADC conversion result data in dual-ADC mode.
*\*\return  The Data conversion value in dual-ADC mode.
**/
uint32_t ADC_GetMutiModeConversionDat(void)
{
    return (uint32_t)ADC1->DAT;
}
/**
*\*\name    ADC_SetRegularTriggerEdge.
*\*\fun     Set ADCx group regular conversion trigger polarity.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ExternalRegularTriggerEdge :
*\*\          - ADC_REG_TRIG_EXT_SOFTWARE     
*\*\          - ADC_REG_TRIG_EXT_RISING     
*\*\          - ADC_REG_TRIG_EXT_FALLING    
*\*\          - ADC_REG_TRIG_EXT_RISINGFALLING      
*\*\return  none
**/
void ADC_SetRegularTriggerEdge(ADC_Module* ADCx, uint32_t ExternalRegularTriggerEdge)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external trigger polarity selection for regular group */
    tempreg &= (~ADC_REG_TRIG_EXT_MASK);
    /* Set the external trigger polarity selection for regular group */
    tempreg |= ExternalRegularTriggerEdge;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_SetInjectTriggerEdge.
*\*\fun     Set ADCx group injected conversion trigger polarity.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ExternalInjectTriggerEdge :
*\*\          - ADC_INJ_TRIG_EXT_SOFTWARE     
*\*\          - ADC_INJ_TRIG_EXT_RISING     
*\*\          - ADC_INJ_TRIG_EXT_FALLING    
*\*\          - ADC_INJ_TRIG_EXT_RISINGFALLING      
*\*\return  none
**/
void ADC_SetInjectTriggerEdge(ADC_Module* ADCx, uint32_t ExternalInjectTriggerEdge)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external trigger polarity selection for injected group */
    tempreg &= (~ADC_INJ_TRIG_EXT_MASK);
    /* Set the external trigger polarity selection for injected group */
    tempreg |= ExternalInjectTriggerEdge;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_ConfigExternalTrigRegularConv.
*\*\fun     Configures the ADCx external trigger source for regular channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_ExternalTrigRegularConv :
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2 
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_CC1   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_CC2   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_CC3   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_CC1   
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM1_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM1_CC2   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM1_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM2_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM2_CC1   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM2_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_CC1   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_CC2   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_CC1   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_CC2   
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_CC4   
*\*\          - ADC_EXT_TRIG_REG_CONV_BTIM1_TRGO  
*\*\          - ADC_EXT_TRIG_REG_CONV_EXT_INT0_15 
*\*\          - ADC_EXT_TRIG_REG_CONV_SOFTWARE  
*\*\return  none
**/
void ADC_ConfigExternalTrigRegularConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigRegularConv)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external event selection for regular group */
    tempreg &= (~ADC_EXT_TRIG_REG_CONV_MASK);
    /* Set the external event selection for regular group */
    tempreg |= ADC_ExternalTrigRegularConv;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_ConfigExternalTrigInjectedConv.
*\*\fun     Configures the ADCx external trigger source for injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_ExternalTrigInjecConv :
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO2  
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_CC1    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_CC2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_CC3    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_CC1    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM1_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM1_CC2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM1_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM2_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM2_CC1    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM2_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_CC1   
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_CC2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_CC1    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_CC2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_CC4    
*\*\          - ADC_EXT_TRIG_INJ_CONV_BTIM1_TRGO   
*\*\          - ADC_EXT_TRIG_INJ_CONV_EXT_INT0_15           
*\*\          - ADC_EXT_TRIG_INJ_CONV_SOFTWARE  
*\*\return  none
**/
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external event selection for injected group */
    tempreg &= (~ADC_EXT_TRIG_INJ_CONV_MASK);
    /* Set the external event selection for injected group */
    tempreg |= ADC_ExternalTrigInjecConv;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}

/**
*\*\name    ADC_EnableSoftwareStartConv.
*\*\fun     Enables or disables the selected ADC software start conversion ..
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event and start the selected
           ADC conversion */
        ADCx->CTRL2 |= ADC_REG_SWSTART_MASK;
    }
    else
    {
        /* Disable the selected ADC conversion on external event and stop the selected
           ADC conversion */
        ADCx->CTRL2 &= (~ADC_REG_SWSTART_MASK);
    }
}
/**
*\*\name    ADC_GetSoftwareStartConvStatus.
*\*\fun     Gets the selected ADC Software start conversion Status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2 
*\*\return The new state of ADC software start conversion (SET or RESET). 
**/ 
FlagStatus ADC_GetSoftwareStartConvStatus(const ADC_Module* ADCx)
{
    FlagStatus bitstatus ;
    
    if ((ADCx->CTRL2 & ADC_REG_SWSTART_MASK) != (uint32_t)RESET)
    {
        /* SOFT_START bit is set */
        bitstatus = SET;
    }
    else
    {
        /* SOFT_START bit is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}
/**
*\*\name    ADC_EnableSoftwareStartInjectedConv.
*\*\fun    Enables or disables the selected ADC start of the injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion for injected group on external event and start the selected
           ADC injected conversion */
        ADCx->CTRL2 |= ADC_INJ_SWSTART_MASK;
    }
    else
    {
        /* Disable the selected ADC conversion on external event for injected group and stop the selected
           ADC injected conversion */
        ADCx->CTRL2 &= (~ADC_INJ_SWSTART_MASK);
    }
}
/**
*\*\name    ADC_GetSoftwareStartInjectedConvCmdStatus.
*\*\fun     Gets the selected ADC Software start injected conversion Status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2 
*\*\return The new state of ADC software start injected conversion (SET or RESET). 
**/ 
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(const ADC_Module* ADCx)
{
    FlagStatus bitstatus ;

    /* Check the status of INJ_SWSTART bit */
    if ((ADCx->CTRL2 & ADC_INJ_SWSTART_MASK) != (uint32_t)RESET)
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
*\*\name    ADC_StopInjectedConv.
*\*\fun     Stop ADC group injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2 
*\*\return  none 
**/ 
void ADC_StopInjectedConv(ADC_Module* ADCx)
{
    ADCx->CTRL2 |= ADC_INJ_SWSTOP_MASK;
}
/**
*\*\name    ADC_StopRegularConv.
*\*\fun     Stop ADC group regular channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2 
*\*\return  none 
**/ 
void ADC_StopRegularConv(ADC_Module* ADCx)
{
    ADCx->CTRL2 |= ADC_REG_SWSTOP_MASK;
}


/**
*\*\name    ADC_EnableTempSensorVrefint.
*\*\fun     Enables or disables the temperature sensor and Vrefint channel
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableTempSensorVrefint(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 |= ADC_TS_EN_MASK;
        ADC1->CTRL3 |= ADC_VREFINT_EN_MASK;
    }
    else
    {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 &= (~ADC_TS_EN_MASK);
        ADC1->CTRL3 &= (~ADC_VREFINT_EN_MASK);
    }
}

/**
*\*\name    ADC_ConfigInjectedChannel.
*\*\fun     Configures for the selected ADC injected channel its corresponding
*\*\        rank in the sequencer and its sample time.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_Channel :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\param   Rank : The rank in the injected group sequencer. This parameter must be between 1 to 4.
*\*\param   ADC_SampleTime : The sample time value to be set for the selected channel.
*\*\          - ADC_SAMP_TIME_CYCLES_4    
*\*\          - ADC_SAMP_TIME_CYCLES_6    
*\*\          - ADC_SAMP_TIME_CYCLES_8    
*\*\          - ADC_SAMP_TIME_CYCLES_14   
*\*\          - ADC_SAMP_TIME_CYCLES_29   
*\*\          - ADC_SAMP_TIME_CYCLES_42   
*\*\          - ADC_SAMP_TIME_CYCLES_56   
*\*\          - ADC_SAMP_TIME_CYCLES_72   
*\*\          - ADC_SAMP_TIME_CYCLES_88   
*\*\          - ADC_SAMP_TIME_CYCLES_120  
*\*\          - ADC_SAMP_TIME_CYCLES_182  
*\*\          - ADC_SAMP_TIME_CYCLES_240  
*\*\          - ADC_SAMP_TIME_CYCLES_300  
*\*\          - ADC_SAMP_TIME_CYCLES_400  
*\*\          - ADC_SAMP_TIME_CYCLES_480  
*\*\          - ADC_SAMP_TIME_CYCLES_600
*\*\return  none
**/
void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tempreg1, tempreg2, tempreg3;

    if (ADC_Channel > ADC_CH_15)  /* if ADC_CH_16 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * (ADC_Channel - 16u));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * (ADC_Channel - 16u));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT3 = tempreg1;
    }
    else if (ADC_Channel > ADC_CH_7) /* if ADC_CH_8 ... ADC_CH_15 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * (ADC_Channel - 8u));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * (ADC_Channel - 8u));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tempreg1;
    }
    else /* if ADC_CH_0 ... ADC_CH_7 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4u * ADC_Channel);
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4u * ADC_Channel);
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tempreg1;
    }
    /* Rank configuration */
    /* Get the old register value */
    tempreg1 = ADCx->JSEQ;
    /* Get JLEN value: Number = JLEN+1 */
    tempreg3 = (tempreg1 & ADC_JESQ_LEN_MASK) >> 25;
    /* Calculate the mask to clear: ((Rank-1)+(4-JLEN-1)) */
    tempreg2 = ADC_JESQ_SEQ_MASK << (5u * (((uint32_t)Rank + 3u) - (tempreg3 + 1u)));
    /* Clear the old JSEQx bits for the selected rank */
    tempreg1 &= ~tempreg2;
    /* Calculate the mask to set: ((Rank-1)+(4-JLEN-1)) */
    tempreg2 = (uint32_t)ADC_Channel << (5u * (((uint32_t)Rank + 3u) - (tempreg3 + 1u)));
    /* Set the JSEQx bits for the selected rank */
    tempreg1 |= tempreg2;
    /* Store the new register value */
    ADCx->JSEQ = tempreg1;
}

/**
*\*\name    ADC_ConfigInjectedSequencerLength.
*\*\fun     Configures the sequencer length for injected channels
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Length : The sequencer length. This parameter must be a number between 1 to 4.
**/
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length)
{
    uint32_t tempreg1,tempreg2;

    /* Get the old register value */
    tempreg1 = ADCx->JSEQ;
    /* Clear the old injected sequnence lenght JLEN bits */
    tempreg1 &= (~ADC_JESQ_LEN_MASK);
    /* Set the injected sequnence lenght JLEN bits */
    tempreg2 = (uint32_t)Length - 1u;
    tempreg1 |= tempreg2 << 25;
    /* Store the new register value */
    ADCx->JSEQ = tempreg1;
}

/**
*\*\name    ADC_SetOffsetConfig.
*\*\fun     Set the specified channel conversion offset configuration.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_Offset :
*\*\          - ADC_REGESTER_OFFSET_1
*\*\          - ADC_REGESTER_OFFSET_2
*\*\          - ADC_REGESTER_OFFSET_3
*\*\          - ADC_REGESTER_OFFSET_4
*\*\param   ADC_OffsetStruct :
*\*\          - OffsetData : Set the selected channel data offset .This parameter must be range from 0 to 0xfff.
*\*\          - OffsetChannel : Set the selected channel .This parameter must be range from 0 to 0x11. means CH0 - CH17.
*\*\          - OffsetDirPositiveEn : Enable or disable the selected channel offset positive direction.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetSatenEn : Enable or disable the selected channel offset saturation .
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetEn : Enable or disable the selected channel offset.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
**/
void ADC_SetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, const ADC_OffsetType* ADC_OffsetStruct)
{
    uint32_t tempreg, temp;

    tempreg = (uint32_t)(uintptr_t)ADCx;
    tempreg += ADC_Offset;
    /* Get register value */
    temp = *((__IO uint32_t*)(uintptr_t)tempreg);
    temp &= (~(ADC_OFFSET_DATA_MASK | ADC_OFFSET_EN_MASK | ADC_OFFSET_CH_MASK | ADC_OFFSET_SATEN_EN_MASK| ADC_OFFSET_DIR_MASK ));
    /* Set the selected channel offset direction and channel */
    temp |= ((uint32_t)ADC_OffsetStruct->OffsetData | (((uint32_t)ADC_OffsetStruct->OffsetChannel) << 26));

    /* Set the selected channel offset direction, saturation, enable or disable*/
    temp |= (BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetDirPositiveEn,ADC_OFFSET_DIR_MASK) | \
             BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetSatenEn,ADC_OFFSET_SATEN_EN_MASK) | \
             BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetEn,ADC_OFFSET_EN_MASK));

    *((__IO uint32_t*)(uintptr_t)tempreg) = temp;
}
/**
*\*\name    ADC_GetOffsetConfig.
*\*\fun     Get the specified channel conversion offset configuration.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_Offset :
*\*\          - ADC_REGESTER_OFFSET_1
*\*\          - ADC_REGESTER_OFFSET_2
*\*\          - ADC_REGESTER_OFFSET_3
*\*\          - ADC_REGESTER_OFFSET_4
*\*\param   ADC_OffsetStruct :
*\*\          - OffsetData : Set the selected channel data offset .This parameter must be range from 0 to 0xfff.
*\*\          - OffsetChannel : Set the selected channel .This parameter must be range from 0 to 0x11. means CH0 - CH17.
*\*\          - OffsetDirPositiveEn : Enable or disable the selected channel offset positive direction.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetSatenEn : Enable or disable the selected channel offset saturation .
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetEn : Enable or disable the selected channel offset.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
**/
void ADC_GetOffsetConfig(const ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct)
{
    uint32_t tempreg,temp;

    tempreg = (uint32_t)(uintptr_t)ADCx;
    tempreg += ADC_Offset;
    /* Get register value */
    temp = *((__IO uint32_t*)(uintptr_t)tempreg);
    ADC_OffsetStruct->OffsetEn = ((temp & ADC_OFFSET_EN_MASK) != 0U)? ENABLE: DISABLE;
    ADC_OffsetStruct->OffsetSatenEn = ((temp & ADC_OFFSET_SATEN_EN_MASK)!= 0U)? ENABLE: DISABLE;
    ADC_OffsetStruct->OffsetDirPositiveEn = ((temp & ADC_OFFSET_DIR_MASK) != 0U)? ENABLE: DISABLE;

    ADC_OffsetStruct->OffsetChannel = (uint8_t)((temp & ADC_OFFSET_CH_MASK) >>26);
    ADC_OffsetStruct->OffsetData = (uint16_t)(temp & ADC_OFFSET_DATA_MASK);
}

/**
*\*\name    ADC_ConfigAnalogWatchdogThresholds.
*\*\fun     Configures the high and low thresholds of the analog watchdog .
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   HighThreshold : the ADC analog watchdog high threshold value.
*\*\          - This parameter must be a 12bit value.
*\*\param   LowThreshold : the ADC analog watchdog low threshold value.
*\*\          - This parameter must be a 12bit value.
*\*\return  none
**/
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, uint16_t HighThreshold, uint16_t LowThreshold)
{
        /* Set the ADCx high threshold of AWDG1 */
        ADCx->AWDHIGH = HighThreshold;
        /* Set the ADCx low threshold of AWDG1 */
        ADCx->AWDLOW = LowThreshold;
}
/**
*\*\name    ADC_GetInjectedConversionDat.
*\*\fun     Get the ADC injected channel conversion result.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_InjectedChannelOffset :
*\*\          - ADC_INJECT_DATA_OFFSET_1
*\*\          - ADC_INJECT_DATA_OFFSET_2
*\*\          - ADC_INJECT_DATA_OFFSET_3
*\*\          - ADC_INJECT_DATA_OFFSET_4
*\*\return  The data conversion value. this date is range 0 - 0xFFFF.
**/
uint16_t ADC_GetInjectedConversionDat(const ADC_Module* ADCx, uint8_t ADC_InjectedChannelOffset)
{
    uint32_t tempreg;

    tempreg = (uint32_t)(uintptr_t)ADCx;
    tempreg += ADC_InjectedChannelOffset;

    /* Returns the selected injected channel conversion data value */
    return (uint16_t)(*((__IO uint32_t*)(uintptr_t)tempreg));
}

/**
*\*\name    ADC_ConfigAnalogWatchdogWorkChannelType.
*\*\fun     Enables or disables the analog watchdog on single/all regular or injected channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_AnalogWatchdog :
*\*\          - ADC_ANALOG_WTDG_NONE
*\*\          - ADC_ANALOG_WTDG_SINGLEREG_ENABLE
*\*\          - ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLREG_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLINJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE
*\*\return  none.
**/
void ADC_ConfigAnalogWatchdogWorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear AWDEJCH, AWDERCH and AWDSGLEN bits */
    tempreg &= (~(ADC_CTRL1_AWDERCH | ADC_CTRL1_AWDSGLEN | ADC_CTRL1_AWDEJCH));
    /* Set the analog watchdog enable mode */
    tempreg |= ADC_AnalogWatchdog;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_ConfigAnalogWatchdogSingleChannel.
*\*\fun     Configures the analog watchdog guarded on single channel.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_AnalogWatchdog :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\return  none.
**/
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the Analog watchdog 1 channel select bits */
    tempreg &= (~ADC_CH_MASK);
    /* Set the Analog watchdog channel */
    tempreg |= ((uint32_t)ADC_Channel) << 12;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_GetFlagStatus.
*\*\fun     Checks whether the specified ADC flag is set or not.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_EOC_ANY
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JEOC_ANY
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_OVERRUN
*\*\          - ADC_FLAG_RDY
*\*\          - ADC_FLAG_PDRDY
*\*\          - ADC_FLAG_EOSAMP
*\*\          - ADC_FLAG_TCFLAG
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_JSTR
*\*\          - ADC_FLAG_VREFRDY
*\*\return    The new state of ADC_FLAG (SET or RESET).
**/
FlagStatus ADC_GetFlagStatus(const ADC_Module* ADCx, uint16_t ADC_FLAG)
{
    FlagStatus bitstatus ;
    /* Check the status of the specified ADC flag */
    if ((ADCx->STS & ((uint32_t)ADC_FLAG)) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return bitstatus;
}

/**
*\*\name    ADC_ClearFlag.
*\*\fun     Clears pending flags of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_EOC_ANY
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JEOC_ANY
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_OVERRUN
*\*\          - ADC_FLAG_RDY
*\*\          - ADC_FLAG_PDRDY
*\*\          - ADC_FLAG_EOSAMP
*\*\          - ADC_FLAG_TCFLAG
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_JSTR
*\*\          - ADC_FLAG_VREFRDY
*\*\return    none.
**/
void ADC_ClearFlag(ADC_Module* ADCx, uint16_t ADC_FLAG)
{
    /* Clear the selected ADC flags */
    ADCx->STS = ((uint32_t)ADC_FLAG & ADC_FLAG_ALL_MASK) ;
}

/**
*\*\name    ADC_ConfigInt.
*\*\fun     Enables or disables the specified ADC interrupts.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_IT :
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWDG
*\*\          - ADC_INT_OVERRUN
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP

*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return    none.
**/
void ADC_ConfigInt(ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->INTEN |= (uint32_t)ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->INTEN &= (~(uint32_t)ADC_IT);
    }
}
/**
*\*\name    ADC_GetIntStatus.
*\*\fun     Checks whether the specified ADC interrupt has occurred or not.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_IT : specifies the ADC interrupt source to check.
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWDG
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP
*\*\          - ADC_INT_OVERRUN
*\*\return    The new state of ADC_IT (SET or RESET).
**/
INTStatus ADC_GetIntStatus(const ADC_Module* ADCx, uint16_t ADC_IT)
{
    INTStatus bitstatus;
    uint32_t enablestatus;

    /* Get the ADC_IT enable bit status */
    enablestatus = (ADCx->INTEN & (uint32_t)ADC_IT);
    /* Check the status of the specified ADC interrupt */
    if(((ADCx->STS & ADC_IT) != 0U) && (enablestatus != 0U))
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    ADC_ClearIntPendingBit.
*\*\fun     Clears  interrupt pending bits of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   ADC_IT :
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWDG
*\*\          - ADC_INT_OVERRUN
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP
*\*\return    none.
**/
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint16_t ADC_IT)
{
    /* Clear the selected ADC interrupt pending bits */
    ADCx->STS = ((uint32_t)ADC_IT & ADC_INTFLAG_ALL_MASK) ;
}

/**
*\*\name    ADC_ConfigOverSamplingRatioAndShift.
*\*\fun     Set ADC oversampling rate times and shift bit.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Ratio : ADC oversampling ratio times 
*\*\          - ADC_OVERSAMPE_RATE_TIMES_1  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_2  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_4   
*\*\          - ADC_OVERSAMPE_RATE_TIMES_8  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_16   
*\*\          - ADC_OVERSAMPE_RATE_TIMES_32 
*\*\          - ADC_OVERSAMPE_RATE_TIMES_64  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_128
*\*\          - ADC_OVERSAMPE_RATE_TIMES_256 
*\*\param   Shift : ADC oversampling data right shift 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_0 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_1 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_2 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_3  
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_4 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_5
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_6
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_7 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_8 
*\*\return  none
**/
void ADC_ConfigOverSamplingRatioAndShift(ADC_Module *ADCx, uint32_t Ratio, uint32_t Shift)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL3;
    /* Clear oversampling ratio and shift select bits */
    tempreg &= (~(ADC_OVERSAMPE_RATE_TIMES_MASK | ADC_OVERSAMPE_DATA_SHIFT_MASK));
    /* Set ADC oversampling ratio and shift bit */
    tempreg |= (Ratio | Shift);
    /* Store the new register value */
    ADCx->CTRL3 = tempreg;
}

/**
*\*\name    ADC_SetOverSamplingScope.
*\*\fun     Set ADC oversampling scope.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   OversampleScope :This parameter can be one of the following values 
*\*\          - ADC_OVERSAMPE_DISABLE  
*\*\          - ADC_OVERSAMPE_REGULAR_CONTINUED  
*\*\          - ADC_OVERSAMPE_REGULAR_RESUMED   
*\*\          - ADC_OVERSAMPE_INJECTED  
*\*\          - ADC_OVERSAMPE_REGULAR_INJECTED   
*\*\return  none
**/
void ADC_SetOverSamplingScope(ADC_Module *ADCx, uint32_t OversampleScope)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL3;
    /* Clear oversampling select bits */
    tempreg &= (~(ADC_OVERSAMPE_REG_EN_MASK | ADC_OVERSAMPE_INJ_EN_MASK | ADC_OVERSAMPE_MODE_MASK));
    /* Set ADC oversampling select bits */
    tempreg |= (OversampleScope);
    /* Store the new register value */
    ADCx->CTRL3 = tempreg;
}

/**
*\*\name    ADC_SetOverSamplingDiscont.
*\*\fun     Set ADC oversampling discontinuous mode (triggered mode).
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableOverSamplingDiscont(ADC_Module *ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_OVERSAMPE_TRIG_REG_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_OVERSAMPE_TRIG_REG_MASK);
    }
}



/**
 *\*\name   ADC_ConfigRegularExtLineTrigSource.
 *\*\fun    Configurate ADC external line trigger source for regular channel.
 *\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
 *\*\param  ADC_trigger : 
 *\*\          specifies the external line trigger source be configured.
 *\*\          - ADC_TRIG_EXTI_0
 *\*\          - ADC_TRIG_EXTI_1
 *\*\          - ADC_TRIG_EXTI_2
 *\*\          - ADC_TRIG_EXTI_3
 *\*\          - ADC_TRIG_EXTI_4
 *\*\          - ADC_TRIG_EXTI_5
 *\*\          - ADC_TRIG_EXTI_6
 *\*\          - ADC_TRIG_EXTI_7
 *\*\          - ADC_TRIG_EXTI_8
 *\*\          - ADC_TRIG_EXTI_9
 *\*\          - ADC_TRIG_EXTI_10
 *\*\          - ADC_TRIG_EXTI_11
 *\*\          - ADC_TRIG_EXTI_12
 *\*\          - ADC_TRIG_EXTI_13
 *\*\          - ADC_TRIG_EXTI_14
 *\*\          - ADC_TRIG_EXTI_15
 *\*\return none
 */
void ADC_ConfigRegularExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL4;
    
    /* clear ADC_CTRL4 register ETRRSEL bit */
    tempreg &= (~(ADC_CTRL4_EXTRRSEL_MASK));
    /* Set ETRRSEL select bits */
    tempreg |= (ADC_trigger << 16U);
     /* Store the new register value */
    ADCx->CTRL4 = tempreg;
}

/**
 *\*\name   ADC_ConfigInjectedExtLineTrigSource.
 *\*\fun    Configurate ADC external line trigger source for injected channel.
 *\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
 *\*\param  ADC_trigger : 
 *\*\          specifies the external line trigger source be configured.
 *\*\          - ADC_TRIG_EXTI_0
 *\*\          - ADC_TRIG_EXTI_1
 *\*\          - ADC_TRIG_EXTI_2
 *\*\          - ADC_TRIG_EXTI_3
 *\*\          - ADC_TRIG_EXTI_4
 *\*\          - ADC_TRIG_EXTI_5
 *\*\          - ADC_TRIG_EXTI_6
 *\*\          - ADC_TRIG_EXTI_7
 *\*\          - ADC_TRIG_EXTI_8
 *\*\          - ADC_TRIG_EXTI_9
 *\*\          - ADC_TRIG_EXTI_10
 *\*\          - ADC_TRIG_EXTI_11
 *\*\          - ADC_TRIG_EXTI_12
 *\*\          - ADC_TRIG_EXTI_13
 *\*\          - ADC_TRIG_EXTI_14
 *\*\          - ADC_TRIG_EXTI_15
 *\*\return none
 */
void ADC_ConfigInjectedExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL4;
    /* clear ADC_CTRL4 register ETRISEL bit */
    tempreg &= (~(ADC_CTRL4_EXTRISEL_MASK));
    /* Set ETRRSEL select bits */
    tempreg |= (ADC_trigger << 20U);
     /* Store the new register value */
    ADCx->CTRL4 = tempreg;
}


/**
*\*\name    Reference_VoltageSelect
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   Ref_Type:  Select reference voltage of ADC.
*\*\         - ADC_VREFSEL_VDDA            Select VDDA as reference voltage
*\*\         - ADC_VREFSEL_VREFP           Select VREF+ as reference voltage
*\*\         - ADC_VREFSEL_VREFBUFF_2_4V   Select VREFBUFF_2.4V as reference voltage
*\*\         - ADC_VREFSEL_OFF             All three switching transistors of VREFP are turned off
*\*\return  none
**/
void Reference_VoltageSelect(uint32_t Ref_Type)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADC1->CTRL3;
    /* clear ADC1_CTRL3 register BUFSEL bit */
    tempreg &= (~(ADC_VREFSEL_MASK));
    /* Set ETRRSEL select bits */
    tempreg |= Ref_Type;
     /* Store the new register value */
    ADC1->CTRL3 = tempreg;
}

/**
*\*\name    ADC_ClockModeConfig
*\*\fun     Configures the ADCCLK prescaler.
*\*\param   RCC_ADCCLKprescaler:
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
void ADC_ClockModeConfig(uint32_t RCC_ADCCLKprescaler)
{
	RCC_ConfigAdcSysclk(RCC_ADCCLKprescaler);
}





