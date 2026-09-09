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
*\*\file n32g41x_comp.c
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32g41x_comp.h"
#include "n32g41x_rcc.h"

#define COMP_FILTCR_MASK        ((uint32_t)0x000007FFU)


/**
*\*\name    COMP_DeInit.
*\*\fun     Reset the COMP registers.
*\*\return  none
**/
void COMP_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP);
}

/**
*\*\name    COMP_Init.
*\*\fun     Initializes the COMP peripheral according to the specified parameters in the COMP_InitStruct
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   COMP_Initstruct :
*\*\param   Clksel :
*\*\          - COMP_CLKSEL_SYSTEMCLK                           
*\*\          - COMP_CLKSEL_LSX                    
*\*\param   Pwrmd :
*\*\          - COMP_CTRL_PWRMD_NORMAL                   
*\*\          - COMP_CTRL_PWRMD_LOWPWR 
*\*\       -Blking :
*\*\            - COMP_BLKING_NO        
*\*\            - COMP_BLKING_ATIM1_OC5 
*\*\            - COMP_BLKING_ATIM2_OC5 
*\*\            - COMP_BLKING_ATIM1_OC4 
*\*\            - COMP_BLKING_GTIM1_OC3 
*\*\            - COMP_BLKING_GTIM2_OC3 
*\*\            - COMP_BLKING_ATIM2_OC1 
*\*\       -DoubleHyst :
*\*\            - COMP_DPUBLEHYST_EN
*\*\            - COMP_DPUBLEHYST_DIS
*\*\       -Hyst :
*\*\          - COMP_HYST_NO   
*\*\          - COMP_HYST_LOW  
*\*\          - COMP_HYST_MID     
*\*\          - COMP_HYST_HIGH 
*\*\       -PolRev :
*\*\          - COMP_OUTPOL_REV   
*\*\          - COMP_OUTPOL_NREV
*\*\       -InpSel :
*\*\           comp1 inp sel
*\*\            - COMP1_INPSEL_PA0   
*\*\            - COMP1_INPSEL_PA1   
*\*\            - COMP1_INPSEL_PA2   
*\*\            - COMP1_INPSEL_PA3   
*\*\            - COMP1_INPSEL_PA6   
*\*\            - COMP1_INPSEL_PA12  
*\*\            - COMP1_INPSEL_PB2   
*\*\            - COMP1_INPSEL_PB3   
*\*\            - COMP1_INPSEL_PB4   
*\*\            - COMP1_INPSEL_PB10  
*\*\            - COMP1_INPSEL_PC5   
*\*\            - COMP1_INPSEL_VREF_VC1 
*\*\           comp2 inp sel
*\*\            - COMP2_INPSEL_PA1     
*\*\            - COMP2_INPSEL_PA3     
*\*\            - COMP2_INPSEL_PA6     
*\*\            - COMP2_INPSEL_PA7     
*\*\            - COMP2_INPSEL_PA11    
*\*\            - COMP2_INPSEL_PA15    
*\*\            - COMP2_INPSEL_PB0     
*\*\            - COMP2_INPSEL_PB4     
*\*\            - COMP2_INPSEL_PB6     
*\*\            - COMP2_INPSEL_PB7     
*\*\            - COMP2_INPSEL_PB11    
*\*\            - COMP2_INPSEL_PB12    
*\*\            - COMP2_INPSEL_VREF_VC2
*\*\           comp3 inp sel
*\*\            - COMP3_INPSEL_PA5     
*\*\            - COMP3_INPSEL_PA11    
*\*\            - COMP3_INPSEL_PB0     
*\*\            - COMP3_INPSEL_PB1     
*\*\            - COMP3_INPSEL_PB11    
*\*\            - COMP3_INPSEL_PB12    
*\*\            - COMP3_INPSEL_PB14    
*\*\            - COMP3_INPSEL_VREF_VC3
*\*\       -InmSel :
*\*\          comp1 inm sel
*\*\            - COMP1_INMSEL_PA0  
*\*\            - COMP1_INMSEL_PA4  
*\*\            - COMP1_INMSEL_PA5  
*\*\            - COMP1_INMSEL_PB1  
*\*\            - COMP1_INMSEL_PB5  
*\*\            - COMP1_INMSEL_PC4  
*\*\            - COMP1_INMSEL_VREF_VC1
*\*\           comp2 inm sel
*\*\            - COMP2_INMSEL_PA4     
*\*\            - COMP2_INMSEL_PA2     
*\*\            - COMP2_INMSEL_PA5     
*\*\            - COMP2_INMSEL_PA6     
*\*\            - COMP2_INMSEL_PB3     
*\*\            - COMP2_INMSEL_PB7     
*\*\            - COMP2_INMSEL_VREF_VC2
*\*\           comp3 inm sel
*\*\            - COMP3_INMSEL_PA5     
*\*\            - COMP3_INMSEL_PA12    
*\*\            - COMP3_INMSEL_PB1     
*\*\            - COMP3_INMSEL_PB11    
*\*\            - COMP3_INMSEL_PB14    
*\*\            - COMP3_INMSEL_VREF_VC3
*\*\       -ClkPsc:
*\*\          Value can be set from 0 to 65535.
*\*\       -FilterEn:
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\       -Threshold:
*\*\          - this value must be greater than SAMPW / 2 .
*\*\       -SampWindow:
*\*\          - from 0 to 31.
*\*\       -En
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_Init(COMPX COMPx, const COMP_InitType* COMP_InitStruct)
{    
    COMP_SingleType* pCS = &COMP->Cmp[COMPx];
    __IO uint32_t tmp;
    // filter
    tmp = pCS->FILC;
    tmp &= ~COMP_FILTCR_MASK;
    tmp |= (( (uint32_t)COMP_InitStruct->SampWindow << 6) | ((uint32_t)COMP_InitStruct->Threshold << 1) | (uint32_t)(COMP_InitStruct->FilterEn));
    pCS->FILC = tmp;
        
    // filter psc
    pCS->FILP = COMP_InitStruct->ClkPsc;
        
    // ctrl
    tmp = pCS->CTRL;
    tmp &= (~(COMP_CLKSEL_LSX | COMP_CTRL_PWRMD_LOWPWR | COMP_DPUBLEHYST_MASK | COMP_BLANKING_MASK | COMP_HYST_MASK | COMP_POL_MASK | COMP_INPSEL_MASK | COMP_INMSEL_MASK | COMP_ENABLE_MASK));
    tmp |= ( (uint32_t)(COMP_InitStruct->ClockSelect) | (uint32_t)(COMP_InitStruct->LowPoweMode) | (uint32_t)(COMP_InitStruct->Blking) | (uint32_t)(COMP_InitStruct->DoubleHyst) | (uint32_t)(COMP_InitStruct->Hyst)
           |(uint32_t)(COMP_InitStruct->PolRev) | (uint32_t)(COMP_InitStruct->InpSel)     | (uint32_t)(COMP_InitStruct->InmSel));
        
    /*COMP enable or disable select*/
    if(COMP_InitStruct->En != DISABLE)
    {
        tmp |= COMP_ENABLE_MASK;
    }
    else
    {
        tmp &= (~COMP_ENABLE_MASK);
    }
        
    pCS->CTRL = tmp;
}

/**
*\*\name    COMP_StructInit.
*\*\fun     Fills all COMP_initstruct member with default value.
*\*\param   COMP_Initstruct :
*\*\          - Blking
*\*\          - DoubleHyst
*\*\          - Hyst
*\*\          - PolRev
*\*\          - InpSel
*\*\          - InmSel
*\*\          - FilterEn
*\*\          - SampWindow
*\*\          - Threshold
*\*\          - ClkPsc
*\*\          - En
*\*\return  none
**/
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
    /* Reset COMP init structure parameters values */ 
    /* Initialize the Blking */
    COMP_InitStruct->Blking        = COMP_BLKING_NO;
      /* Initialize the DoubleHyst */  
    COMP_InitStruct->DoubleHyst    = COMP_DPUBLEHYST_DIS;
    /* Initialize the Hyst */  
    COMP_InitStruct->Hyst          = COMP_HYST_NO;  
      /* Initialize the PolRev */
    COMP_InitStruct->PolRev        = COMP_OUTPOL_NREV; 
      /* Initialize the InpSel */
    COMP_InitStruct->InpSel        = COMP_INPSEL_RES;
    /* Initialize the InmSel */	
    COMP_InitStruct->InmSel        = COMP_INMSEL_RES;   
      /* Initialize the FilterEn */
    COMP_InitStruct->FilterEn      = DISABLE;
      /* Initialize the SampWindow */
    COMP_InitStruct->SampWindow    = 0;
      /* Initialize the Threshold */
    COMP_InitStruct->Threshold     = 0;
    /* Initialize the ClkPsc */
    COMP_InitStruct->ClkPsc        = 0;
     /* Initialize the ClockSelect */
    COMP_InitStruct->ClockSelect   = 0;
    /* Initialize the LowPowerMode */
    COMP_InitStruct->LowPoweMode   = 0;
    /* Initialize the En */
    COMP_InitStruct->En            = DISABLE;
}


/**
*\*\name    COMP_SetFilterControl.
*\*\fun     Configure the COMP filter value. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   FilEn:
*\*\          - ENABLE.
*\*\          - DISABLE.
*\*\param   TheresNum:
*\*\          - this value must be greater than SAMPW / 2 .
*\*\param   SampPW:
*\*\          - from 0 to 31.
*\*\return  none
**/
void COMP_SetFilterControl(COMPX COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].FILC;

    tmp &= (~COMP_FILTCR_MASK);
    tmp = (((uint32_t)SampPW << 6)|((uint32_t)TheresNum << 1)|((uint32_t)FilEn));
    
    COMP->Cmp[COMPx].FILC = tmp;
}

/**
*\*\name    COMP_SetFilterPrescaler.
*\*\fun     Configure The COMP low filter prescale.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   FilPreVal:
*\*\          -  Value can be set from 0 to 65535.
*\*\return  none
**/
void COMP_SetFilterPrescaler(COMPX COMPx, uint16_t FilPreVal)
{
    COMP->Cmp[COMPx].FILP = (uint16_t)FilPreVal;
}

/**
*\*\name    COMP_SetHyst.
*\*\fun     Configure COMP hysteresis level.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   HYST :
*\*\          - COMP_HYST_NO   
*\*\          - COMP_HYST_LOW  
*\*\          - COMP_HYST_MID     
*\*\          - COMP_HYST_HIGH 
*\*\return  none
**/
void COMP_SetHyst(COMPX COMPx, COMP_CTRL_HYST HYST)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;

    tmp &= ~COMP_HYST_MASK;
    tmp |= (uint32_t)HYST;

    COMP->Cmp[COMPx].CTRL = tmp;
}
/**
*\*\name    COMP_EnableDoubleHyst.
*\*\fun     Configure COMP hysteresis double enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_EnableDoubleHyst(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_DPUBLEHYST_EN;
    }
    else
    {
        COMP->Cmp[COMPx].CTRL &= (~COMP_DPUBLEHYST_EN);
    }
}
/**
*\*\name    COMP_OutputPolarityConfig.
*\*\fun     Configures COMP output signal polarity overturn or not.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   POL :
*\*\          - COMP_OUTPOL_REV
*\*\          - COMP_OUTPOL_NREV
*\*\return  none
**/
void COMP_OutputPolarityConfig(COMPX COMPx, uint32_t POL)
{
    if(POL != COMP_OUTPOL_NREV)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_OUTPOL_REV;
    }
    else
    {
        COMP->Cmp[COMPx].CTRL &= (~COMP_OUTPOL_REV);
    }
}

/**
*\*\name    COMP_SetInpSel.
*\*\fun     Configures COMP inpsel input selection.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Vpsel :
*\*\       comp1 inp sel
*\*\            - COMP1_INPSEL_PA0   
*\*\            - COMP1_INPSEL_PA1   
*\*\            - COMP1_INPSEL_PA2   
*\*\            - COMP1_INPSEL_PA3   
*\*\            - COMP1_INPSEL_PA6   
*\*\            - COMP1_INPSEL_PA12  
*\*\            - COMP1_INPSEL_PB2   
*\*\            - COMP1_INPSEL_PB3   
*\*\            - COMP1_INPSEL_PB4   
*\*\            - COMP1_INPSEL_PB10  
*\*\            - COMP1_INPSEL_PC5   
*\*\            - COMP1_INPSEL_VREF1 
*\*\       comp2 inp sel
*\*\            - COMP2_INPSEL_PA1     
*\*\            - COMP2_INPSEL_PA3     
*\*\            - COMP2_INPSEL_PA6     
*\*\            - COMP2_INPSEL_PA7     
*\*\            - COMP2_INPSEL_PA11    
*\*\            - COMP2_INPSEL_PA15    
*\*\            - COMP2_INPSEL_PB0     
*\*\            - COMP2_INPSEL_PB4     
*\*\            - COMP2_INPSEL_PB6     
*\*\            - COMP2_INPSEL_PB7     
*\*\            - COMP2_INPSEL_PB11    
*\*\            - COMP2_INPSEL_PB12    
*\*\            - COMP2_INPSEL_VREF_VC2
*\*\       comp3 inp sel
*\*\            - COMP3_INPSEL_PA5     
*\*\            - COMP3_INPSEL_PA11    
*\*\            - COMP3_INPSEL_PB0     
*\*\            - COMP3_INPSEL_PB1     
*\*\            - COMP3_INPSEL_PB11    
*\*\            - COMP3_INPSEL_PB12    
*\*\            - COMP3_INPSEL_PB14    
*\*\            - COMP3_INPSEL_VREF_VC3
*\*\return  none
**/
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;

    tmp &= ~COMP_INPSEL_MASK;
    tmp |= (uint32_t)VpSel;

    COMP->Cmp[COMPx].CTRL = tmp;
}

/**
*\*\name    COMP_SetInmSel.
*\*\fun     Configures COMP inmsel input selection..
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   VmSel :
*\*\          comp1 inm sel
*\*\            - COMP1_INMSEL_PA0  
*\*\            - COMP1_INMSEL_PA4  
*\*\            - COMP1_INMSEL_PA5  
*\*\            - COMP1_INMSEL_PB1  
*\*\            - COMP1_INMSEL_PB5  
*\*\            - COMP1_INMSEL_PC4  
*\*\            - COMP1_INMSEL_VREF1
*\*\           comp2 inm sel
*\*\            - COMP2_INMSEL_PA4     
*\*\            - COMP2_INMSEL_PA2     
*\*\            - COMP2_INMSEL_PA5     
*\*\            - COMP2_INMSEL_PA6     
*\*\            - COMP2_INMSEL_PB3     
*\*\            - COMP2_INMSEL_PB7     
*\*\            - COMP2_INMSEL_VREF_VC2
*\*\           comp3 inm sel
*\*\            - COMP3_INMSEL_PA5     
*\*\            - COMP3_INMSEL_PA12    
*\*\            - COMP3_INMSEL_PB1     
*\*\            - COMP3_INMSEL_PB11    
*\*\            - COMP3_INMSEL_PB14    
*\*\            - COMP3_INMSEL_VREF_VC3
*\*\return  none
**/
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel) 
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;

    tmp &= ~COMP_INMSEL_MASK;
    tmp |= (uint32_t)VmSel;

    COMP->Cmp[COMPx].CTRL = tmp;
}

/**
*\*\name    COMP_Enable.
*\*\fun     Configures COMPx enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Cmd new state of the COMP peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_Enable(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_ENABLE_MASK;
    }
    else
    {
        COMP->Cmp[COMPx].CTRL &= (~COMP_ENABLE_MASK);
    }
}

/**
*\*\name    COMP_SetIntEn.
*\*\fun     Configures COMPx interrupt enable or disable.
*\*\param   IntEn :
*\*\          -COMP_INTEN_CMP1IEN 
*\*\          -COMP_INTEN_CMP2IEN
*\*\          -COMP_INTEN_CMP3IEN
*\*\param   Cmd :
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->INTEN |= IntEn;
    }   
    else
    {
        COMP->INTEN &= ~IntEn;
    }
}

/**
*\*\name    COMP_GetOutStatus.
*\*\fun     Get COMPx output status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetOutStatus(COMPX COMPx)
{
    return (((COMP->Cmp[COMPx].CTRL & COMP_OUT_MASK)!= 0U) ? SET : RESET);
}

/**
*\*\name    COMP_GetIntStsOneComp.
*\*\fun     Get COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return 
*\*\          - RESET : COMPx Interrupt status is reset;
*\*\          - SET   : COMPx Interrupt status is set;
**/
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx)
{
    return ((COMP->INTSTS & ((uint32_t)0x01U << (uint32_t)COMPx)) != 0U) ? SET : RESET;
}

/**
*\*\name    COMP_ClearIntStsOneComp.
*\*\fun     Clear COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_ClearIntStsOneComp(COMPX COMPx)
{
    COMP->INTSTS = (0x01UL << (uint32_t)COMPx);
}
/**
*\*\name    COMP_SetLock.
*\*\fun     Configures which COMPx will be Locked.
*\*\param   Lock :
*\*\          - COMP1_LOCK
*\*\          - COMP2_LOCK
*\*\          - COMP3_LOCK
*\*\return  none
**/
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK = Lock;
}

/**
*\*\name    COMP_StopOrLowpower32KClkSel.
*\*\fun     Select LSx as COMPx operation clock enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Cmd :
*\*\          -ENABLE : Select LSx as COMPx operation clock;
*\*\          -DISABLE : Select high speed clock as COMPx operation clock;
*\*\return  none
**/
void COMP_StopOrLowpower32KClkSel(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_CLKSEL_LSX;
    }   
    else
    {
        COMP->Cmp[COMPx].CTRL &= ~COMP_CLKSEL_LSX;
    }
}
/**
*\*\name    COMP_StopOrLowpowerMode.
*\*\fun     Configures COMPx low power mode enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Cmd :
*\*\          -ENABLE : Select LSx as COMPx operation clock;
*\*\          -DISABLE : Select high speed clock as COMPx operation clock;
*\*\return  none
**/
void COMP_StopOrLowpowerMode(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_CTRL_PWRMD_NORMAL;
    }   
    else
    {
        COMP->Cmp[COMPx].CTRL &= ~COMP_CTRL_PWRMD_NORMAL;
    }
}
/**
*\*\name    COMP_SetRefScl.
*\*\fun     Configures the COMP reference voltage. 
*\*\param   Vv3Trim :
*\*\          - Value can be set from 0 to 255.
*\*\param   Vv3En :
*\*\          - false
*\*\          - true
*\*\param   Vv2Trim :
*\*\          - Value can be set from 0 to 255.
*\*\param   Vv2En :
*\*\          - false
*\*\          - true
*\*\param   Vv1Trim :
*\*\           - Value can be set from 0 to 255.     
*\*\param   Vv1En :
*\*\          - false
*\*\          - true
*\*\return  none
**/
void COMP_SetRefScl(uint8_t Vv3Trim, bool Vv3En, uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    COMP->INVREF1 =  (uint32_t)(Vv1En?1:0) + ((uint32_t)Vv1Trim << 1 );
    COMP->INVREF2 =  (uint32_t)(Vv2En?1:0) + ((uint32_t)Vv2Trim << 1 );
    COMP->INVREF3 =  (uint32_t)(Vv3En?1:0) + ((uint32_t)Vv3Trim << 1 );
}

/**
*\*\name    COMP_SetBlanking.
*\*\fun     Configures timer output signal to control COMP Blking. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   BLK :
*\*\            - COMP_BLKING_NO
*\*\            - COMP_BLKING_ATIM1_OC5 
*\*\            - COMP_BLKING_ATIM2_OC5 
*\*\            - COMP_BLKING_ATIM1_OC4 
*\*\            - COMP_BLKING_GTIM1_OC3 
*\*\            - COMP_BLKING_GTIM2_OC3 
*\*\            - COMP_BLKING_ATIM2_OC1 
*\*\return  none
**/
void COMP_SetBlanking(COMPX COMPx, COMP_CTRL_BLKING BLK)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    
    tmp &= ~COMP_BLANKING_MASK;
    tmp |= (uint32_t)BLK;
    
    COMP->Cmp[COMPx].CTRL = tmp;
}

/**
*\*\name    COMP_WindowModeEnable.
*\*\fun     Configures COMPx window mode enable or disable.
*\*\param   WinModeEn :
*\*\          - COMP_WINMODE_CMP12MD
*\*\          - COMP_WINMODE_CMP23MD
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->WINMODE |= WinModeEn;
    }
    else
    {
        COMP->WINMODE &= (~WinModeEn);
    }
}
