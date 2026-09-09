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
*\*\file n32g41x_opamp.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32g41x_opamp.h"
#include "n32g41x_rcc.h"

/**
*\*\name    OPAMP_DeInit.
*\*\fun     Reset the OPAMP registers.
*\*\return  none
**/
void OPAMP_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_OPAMP);
}
/**
*\*\name    OPAMP_StructInit.
*\*\fun     Fills each OPAMP_initstruct member with its default value.
*\*\param   OPAMP_Initstruct :
*\*\          - Gain
*\*\          - Mode
*\*\          - OPAMP_Vpsel
*\*\          - OPAMP_Vmsel
*\*\          - OPAMP_Vpssel
*\*\          - OPAMP_Vmssel
*\*\          - VREFSEL
*\*\          - CALEN
*\*\return  none
**/
void OPAMP_StructInit(OPAMP_InitType* OPAMP_InitStruct)
{
    OPAMP_InitStruct->Gain           = OPAMP_CS_PGA_GAIN_2;
    OPAMP_InitStruct->Mode           = OPAMP_CS_EXT_OPAMP;
    OPAMP_InitStruct->OPAMP_Vpsel    = (OPAMP_CS_VPSEL)0U;
    OPAMP_InitStruct->OPAMP_Vmsel    = (OPAMP_CS_VMSEL)0U;
    OPAMP_InitStruct->OPAMP_Vpssel   = (OPAMP_CS_VPSSEL)0U;
    OPAMP_InitStruct->OPAMP_Vmssel   = (OPAMP_CS_VMSSEL)0U;
    OPAMP_InitStruct->VREFSEL        = OPAMP_VREF_SEL_0_1VDD;
    OPAMP_InitStruct->CALEN          = 0U;
}   

/**
*\*\name    OPAMP_Init.
*\*\fun     Initializes the OPAMP according to OPAMP_InitStruct.
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4   
*\*\param   OPAMP_InitStruct :
*\*\          - Mode :
*\*\            - OPAMP_CS_EXT_OPAMP  
*\*\            - OPAMP_CS_PGA_EN
*\*\            - OPAMP_CS_FOLLOW     
*\*\          - OPAMP_Vpsel : 
*\*\            - OPAMP1_CS_VPSEL_PA1  
*\*\            - OPAMP1_CS_VPSEL_PA5  
*\*\            - OPAMP1_CS_VPSEL_PA4  
*\*\            - OPAMP1_CS_VPSEL_PA7
*\*\                
*\*\            - OPAMP2_CS_VPSEL_PA7  
*\*\            - OPAMP2_CS_VPSEL_PA4  
*\*\            - OPAMP2_CS_VPSEL_PB0  
*\*\            - OPAMP2_CS_VPSEL_PB14 
*\*\                   
*\*\            - OPAMP3_CS_VPSEL_PB2  
*\*\            - OPAMP3_CS_VPSEL_PA1  
*\*\            - OPAMP3_CS_VPSEL_PA5  
*\*\            - OPAMP3_CS_VPSEL_PC3 
*\*\                    
*\*\            - OPAMP4_CS_VPSEL_PA4  
*\*\            - OPAMP4_CS_VPSEL_PC5  
*\*\            - OPAMP4_CS_VPSEL_PB13 
*\*\            - OPAMP4_CS_VPSEL_PA7  
*\*\          - OPAMP_Vmsel : 
*\*\            - OPAMP1_CS_VMSEL_PA3           
*\*\            - OPAMP1_CS_VMSEL_PC5           
*\*\            - OPAMP1_CS_VMSEL_PA0               
*\*\            - OPAMP1_CS_VMSEL_FLOAT
*\*\
*\*\            - OPAMP2_CS_VMSEL_PA5           
*\*\            - OPAMP2_CS_VMSEL_PC5           
*\*\            - OPAMP2_CS_VMSEL_PB0 
*\*\            - OPAMP2_CS_VMSEL_FLOAT
*\*\                                              
*\*\            - OPAMP3_CS_VMSEL_PC4           
*\*\            - OPAMP3_CS_VMSEL_PB10               
*\*\            - OPAMP3_CS_VMSEL_NC
*\*\            - OPAMP3_CS_VMSEL_FLOAT
*\*\                
*\*\            - OPAMP4_CS_VMSEL_PB10          
*\*\            - OPAMP4_CS_VMSEL_PB1           
*\*\            - OPAMP4_CS_VMSEL_PA5
*\*\            - OPAMP4_CS_VMSEL_FLOAT
*\*\          - OPAMP_Vpssel : 
*\*\            - OPAMP1_CS_VPSSEL_PA1  
*\*\            - OPAMP1_CS_VPSSEL_PA5  
*\*\            - OPAMP1_CS_VPSSEL_PA4  
*\*\            - OPAMP1_CS_VPSSEL_PA7
*\*\                
*\*\            - OPAMP2_CS_VPSSEL_PA7  
*\*\            - OPAMP2_CS_VPSSEL_PA4  
*\*\            - OPAMP2_CS_VPSSEL_PB0  
*\*\            - OPAMP2_CS_VPSSEL_PB14 
*\*\                   
*\*\            - OPAMP3_CS_VPSSEL_PB2  
*\*\            - OPAMP3_CS_VPSSEL_PA1  
*\*\            - OPAMP3_CS_VPSSEL_PA5  
*\*\            - OPAMP3_CS_VPSSEL_PC3 
*\*\                    
*\*\            - OPAMP4_CS_VPSSEL_PA4  
*\*\            - OPAMP4_CS_VPSSEL_PC5  
*\*\            - OPAMP4_CS_VPSSEL_PB13 
*\*\            - OPAMP4_CS_VPSSEL_PA7  
*\*\          - OPAMP_Vmssel : 
*\*\            - OPAMP1_CS_VMSSEL_PA3           
*\*\            - OPAMP1_CS_VMSSEL_PC5           
*\*\            - OPAMP1_CS_VMSSEL_PA0   
*\*\            - OPAMP1_CS_VMSSEL_FLOAT
*\*\                                              
*\*\            - OPAMP2_CS_VMSSEL_PA5           
*\*\            - OPAMP2_CS_VMSSEL_PC5           
*\*\            - OPAMP2_CS_VMSSEL_PB0
*\*\            - OPAMP2_CS_VMSSEL_FLOAT
*\*\                                              
*\*\            - OPAMP3_CS_VMSSEL_PC4           
*\*\            - OPAMP3_CS_VMSSEL_PB10 
*\*\            - OPAMP3_CS_VMSSEL_NC
*\*\            - OPAMP3_CS_VMSSEL_FLOAT
*\*\  
*\*\            - OPAMP4_CS_VMSSEL_PB10          
*\*\            - OPAMP4_CS_VMSSEL_PB1           
*\*\            - OPAMP4_CS_VMSSEL_PA5
*\*\            - OPAMP4_CS_VMSSEL_FLOAT
*\*\          - Gain : 
*\*\            - OPAMP_CS_PGA_GAIN_2 
*\*\            - OPAMP_CS_PGA_GAIN_4 
*\*\            - OPAMP_CS_PGA_GAIN_8 
*\*\            - OPAMP_CS_PGA_GAIN_16
*\*\            - OPAMP_CS_PGA_GAIN_32
*\*\          - VREFSEL : 
*\*\            - OPAMP_VREF_SEL_0_1VDD
*\*\            - OPAMP_VREF_SEL_0_9VDD
*\*\return  none
**/
void OPAMP_Init(OPAMPX OPAMPx, const OPAMP_InitType* OPAMP_InitStruct)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;

    tmp &= ~(OPAMP_EN_MASK | OPAMP_CS_MODE_MASK | OPAMP_CS_PGA_GAIN_MASK 
	         | OPAMPx_CS_VPSEL | OPAMPx_CS_VMSEL 
	         | OPAMPx_CS_VPSSEL | OPAMPx_CS_VMSSEL| OPAMP_VREF_SEL_MASK | OPAMP_CS_CALEN_MASK) ;  
    tmp = ((uint32_t)OPAMP_InitStruct->Gain          | (uint32_t)OPAMP_InitStruct->Mode
	      | (uint32_t)OPAMP_InitStruct->OPAMP_Vpsel  | (uint32_t)OPAMP_InitStruct->OPAMP_Vmsel
          | (uint32_t)OPAMP_InitStruct->OPAMP_Vpssel | (uint32_t)OPAMP_InitStruct->OPAMP_Vmssel
	      | OPAMP_InitStruct->VREFSEL | OPAMP_InitStruct->CALEN);

    *pCs = tmp;
}
/**
*\*\name    OPAMP_Enable.
*\*\fun     Enable or disable opampx .
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void OPAMP_Enable(OPAMPX OPAMPx, FunctionalState Cmd)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));
    
    if (Cmd != DISABLE)
    {
        *pCs |= OPAMP_EN_MASK;
    }
    else
    {
        *pCs &= (~OPAMP_EN_MASK);
    }
}

/**
*\*\name    OPAMP_SetWorkMode.
*\*\fun     OPAwork mode select .
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   Mode :
*\*\          - OPAMP_CS_EXT_OPAMP  
*\*\          - OPAMP_CS_FOLLOW  
*\*\return  none
**/
void OPAMP_SetWorkMode(OPAMPX OPAMPx, OPAMP_CS_MOD Mode)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
     tmp &= (~OPAMP_CS_MODE_MASK);
     tmp |= (uint32_t)Mode;  
    *pCs = tmp;    
}
/**
*\*\name    OPAMP_SetPgaGain.
*\*\fun     Set opampx gain value selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   Gain :
*\*\        - OPAMP
*\*\          - OPAMP_CS_PGA_GAIN_2
*\*\          - OPAMP_CS_PGA_GAIN_4
*\*\          - OPAMP_CS_PGA_GAIN_8
*\*\          - OPAMP_CS_PGA_GAIN_16
*\*\          - OPAMP_CS_PGA_GAIN_32
*\*\return  none
**/
void OPAMP_SetPgaGain(OPAMPX OPAMPx, OPAMP_CS_PGA_GAIN Gain)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
    tmp &= (~OPAMP_CS_PGA_GAIN_MASK);
    tmp |= (uint32_t)Gain;

    *pCs = tmp;
}
 
/**
*\*\name    OPAMP_SetVpSel.
*\*\fun     Set opamp VP selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   - VpSel 
*\*\          - OPAMP1_CS_VPSEL_PA1  
*\*\          - OPAMP1_CS_VPSEL_PA5  
*\*\          - OPAMP1_CS_VPSEL_PA4  
*\*\          - OPAMP1_CS_VPSEL_PA7
*\*\                
*\*\          - OPAMP2_CS_VPSEL_PA7  
*\*\          - OPAMP2_CS_VPSEL_PA4  
*\*\          - OPAMP2_CS_VPSEL_PB0  
*\*\          - OPAMP2_CS_VPSEL_PB14 
*\*\                 
*\*\          - OPAMP3_CS_VPSEL_PB2  
*\*\          - OPAMP3_CS_VPSEL_PA1  
*\*\          - OPAMP3_CS_VPSEL_PA5  
*\*\          - OPAMP3_CS_VPSEL_PC3 
*\*\                  
*\*\          - OPAMP4_CS_VPSEL_PA4  
*\*\          - OPAMP4_CS_VPSEL_PC5  
*\*\          - OPAMP4_CS_VPSEL_PB13 
*\*\          - OPAMP4_CS_VPSEL_PA7       
*\*\return  none
**/
void OPAMP_SetVpSel(OPAMPX OPAMPx, OPAMP_CS_VPSEL VpSel)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
     tmp &= (~OPAMP_CS_VPSEL_MASK);
     tmp |= (uint32_t)VpSel;

    *pCs = tmp;
}
/**
*\*\name    OPAMP_SetVmSel.
*\*\fun     Set opamp VM selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   - VmSel
*\*\          - OPAMP1_CS_VMSEL_PA3           
*\*\          - OPAMP1_CS_VMSEL_PC5           
*\*\          - OPAMP1_CS_VMSEL_PA0               
*\*\                                            
*\*\          - OPAMP2_CS_VMSEL_PA5           
*\*\          - OPAMP2_CS_VMSEL_PC5           
*\*\          - OPAMP2_CS_VMSEL_PB0               
*\*\                                            
*\*\          - OPAMP3_CS_VMSEL_PC4           
*\*\          - OPAMP3_CS_VMSEL_PB10               
*\*\
*\*\          - OPAMP4_CS_VMSEL_PB10          
*\*\          - OPAMP4_CS_VMSEL_PB1           
*\*\          - OPAMP4_CS_VMSEL_PA5           
*\*\return  none
**/
void OPAMP_SetVmSel(OPAMPX OPAMPx, OPAMP_CS_VMSEL VmSel)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
     tmp &= (~OPAMP_CS_VMSEL_MASK);
     tmp |= (uint32_t)VmSel;
        
    *pCs = tmp;
}
/**
*\*\name    OPAMP_SetVpSecondSel.
*\*\fun     Set opamp VP secondary selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   - VpsSel
*\*\          - OPAMP1_CS_VPSSEL_PA1        
*\*\          - OPAMP1_CS_VPSSEL_PA5        
*\*\          - OPAMP1_CS_VPSSEL_PA4        
*\*\          - OPAMP1_CS_VPSSEL_PA7        
*\*\                    
*\*\          - OPAMP2_CS_VPSSEL_PA7         
*\*\          - OPAMP2_CS_VPSSEL_PA4         
*\*\          - OPAMP2_CS_VPSSEL_PB0         
*\*\          - OPAMP2_CS_VPSSEL_PB14        
*\*\                    
*\*\          - OPAMP3_CS_VPSSEL_PB2        
*\*\          - OPAMP3_CS_VPSSEL_PA1        
*\*\          - OPAMP3_CS_VPSSEL_PA5        
*\*\          - OPAMP3_CS_VPSSEL_PC3        
*\*\                    
*\*\          - OPAMP4_CS_VPSSEL_PA4         
*\*\          - OPAMP4_CS_VPSSEL_PC5         
*\*\          - OPAMP4_CS_VPSSEL_PB13       
*\*\          - OPAMP4_CS_VPSSEL_PA7
*\*\return  none   
**/
void OPAMP_SetVpSecondSel(OPAMPX OPAMPx, OPAMP_CS_VPSSEL VpsSel)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
    
    tmp &= (~OPAMP_CS_VPSSEL_MASK);
    tmp |= (uint32_t)VpsSel;
    
    *pCs = tmp;
}
/**
*\*\name    OPAMP_SetVmSecondSel.
*\*\fun     Set opamp VM secondary selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   - VmsSel
*\*\          - OPAMP1_CS_VMSSEL_PA3           
*\*\          - OPAMP1_CS_VMSSEL_PC5           
*\*\          - OPAMP1_CS_VMSSEL_PA0           
*\*\    
*\*\          - OPAMP2_CS_VMSSEL_PA5           
*\*\          - OPAMP2_CS_VMSSEL_PC5           
*\*\          - OPAMP2_CS_VMSSEL_PB0           
*\*\     
*\*\          - OPAMP3_CS_VMSSEL_PC4           
*\*\          - OPAMP3_CS_VMSSEL_PB10          
*\*\    
*\*\          - OPAMP4_CS_VMSSEL_PB10          
*\*\          - OPAMP4_CS_VMSSEL_PB1           
*\*\          - OPAMP4_CS_VMSSEL_PA5        
*\*\return  none
**/
void OPAMP_SetVmSecondSel(OPAMPX OPAMPx, OPAMP_CS_VMSSEL VmsSel)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));

    __IO uint32_t tmp  = *pCs;
    
    tmp &= (~OPAMP_CS_VMSSEL_MASK);
    tmp |= (uint32_t)VmsSel;
    *pCs = tmp;
}


/**
*\*\name    OPAMP_VREFSel.
*\*\fun     Set opampx vref_opt selection
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   VrefSel :
*\*\          - OPAMP_VREF_SEL_0_1VDD
*\*\          - OPAMP_VREF_SEL_0_9VDD
*\*\return  none
**/
void OPAMP_VREFSel(OPAMPX OPAMPx, uint32_t VrefSel)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));
    __IO uint32_t tmp  = *pCs;
    
    tmp &= (~OPAMP_VREF_SEL_MASK);
    tmp |= VrefSel;
    
    *pCs = tmp;
}
/**
*\*\name    OPAMP_CalEn.
*\*\fun     Set OPAMPx offset calibration EN
*\*\param   OPAMPX :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void OPAMP_CalEn(OPAMPX OPAMPx, FunctionalState Cmd)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));
    
    if(Cmd != DISABLE)
    {
        *pCs |= OPAMP_CS_CALEN_ENABLE;
    }
    else
    {
        *pCs &= (~OPAMP_CS_CALEN_MASK);
    }
}
/**
*\*\name    OPAMP_IsCalOutHigh.
*\*\fun     Check whether the specified OPAMP calibration output is high.
*\*\param   OPAMPx :
*\*\          - OPAMP1
*\*\          - OPAMP2
*\*\          - OPAMP3
*\*\          - OPAMP4
*\*\return  true or false
**/
bool OPAMP_IsCalOutHigh(OPAMPX OPAMPx)
{
    __IO uint32_t* pCs = (__IO uint32_t*)(uintptr_t)((uintptr_t)&OPAMP->OPAMP1_CS +
                                                     (uintptr_t)((uint32_t)OPAMPx * sizeof(uint32_t)));
    return ((*pCs & OPAMP_CS_CALOUT_MASK) == OPAMP_CS_CALOUT_MASK) ? true : false;
}

/**
*\*\name    OPAMP_SetLock.
*\*\fun     Set opamp lock
*\*\param   Lock :
*\*\          - OPAMP1_LOCK
*\*\          - OPAMP2_LOCK
*\*\          - OPAMP3_LOCK
*\*\          - OPAMP4_LOCK
*\*\return  none
**/
void OPAMP_SetLock(uint32_t Lock)
{
    OPAMP->OPAMP_LOCK = Lock;
}


