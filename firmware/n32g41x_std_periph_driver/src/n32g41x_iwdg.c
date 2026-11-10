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
*\*\file n32g41x_iwdg.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/
#include "n32g41x_iwdg.h"


/**
*\*\name    IWDG_WriteConfig.
*\*\fun     Config write protection of IWDG_PREDIV and IWDG_RELV registers.
*\*\param   IWDG_WriteAccess : key value written to IWDG_KEY.KEYV[15:0]
*\*\        - IWDG_WRITE_ENABLE (0x5555) : disable the write protection, so
*\*\          that IWDG_PREDIV and IWDG_RELV become writable
*\*\        - IWDG_WRITE_DISABLE (0x0000) : re-arm the write protection
*\*\return  none
**/
void IWDG_WriteConfig(IWDG_WRITE_CONFIG IWDG_WriteAccess)
{
    /* Check the parameters */
    IWDG->KEY = (uint32_t)IWDG_WriteAccess;
}

/**
*\*\name    IWDG_SetPrescalerDiv.
*\*\fun     Sets the IWDG prescaler divider ratio (IWDG_PREDIV.PD[2:0]).
*\*\param   IWDG_Prescaler : prescaler divider, one of :
*\*\          - IWDG_PRESCALER_DIV4   (PD[2:0] = 0b000, divisor 4)
*\*\          - IWDG_PRESCALER_DIV8   (PD[2:0] = 0b001, divisor 8)
*\*\          - IWDG_PRESCALER_DIV16  (PD[2:0] = 0b010, divisor 16)
*\*\          - IWDG_PRESCALER_DIV32  (PD[2:0] = 0b011, divisor 32)
*\*\          - IWDG_PRESCALER_DIV64  (PD[2:0] = 0b100, divisor 64)
*\*\          - IWDG_PRESCALER_DIV128 (PD[2:0] = 0b101, divisor 128)
*\*\          - IWDG_PRESCALER_DIV256 (PD[2:0] = 0b111, divisor 256)
*\*\return  none
**/
void IWDG_SetPrescalerDiv(uint8_t IWDG_Prescaler)
{
    IWDG->PREDIV = IWDG_Prescaler;
}

/**
*\*\name    IWDG_CntReload.
*\*\fun     Sets IWDG reload value.
*\*\param   Reload :
*\*\          - 0x000 ~ 0xFFF (REL[11:0]); larger values are truncated by the field mask
*\*\return  none
**/
void IWDG_CntReload(uint16_t Reload)
{
    IWDG->RELV = (uint32_t)Reload & (uint32_t)IWDG_RELV_REL;
}

/**
*\*\name    IWDG_ReloadKey.
*\*\fun     Reload IWDG counter with value defined in IWDG_RELV register.
*\*\param   none
*\*\return  none
**/
void IWDG_ReloadKey(void)
{
    IWDG->KEY = KEY_ReloadKey;
}

/**
*\*\name    IWDG_Enable.
*\*\fun     Start watch dog counter.
*\*\param   none
*\*\return  none
**/
void IWDG_Enable(void)
{
    IWDG->KEY = KEY_EnableKey;
}

/**
*\*\name    IWDG_Freeze_Enable.
*\*\fun     Freeze or unfreeze IWDG while IWDG is running in run mode.
*\*\param   Cmd : freeze control, written to IWDG_KEY.KEYV[15:0]
*\*\          - ENABLE  : 0x4567, stops the IWDG counter in RUN mode
*\*\          - DISABLE : 0x89AB, resumes the counter in RUN mode
*\*\return  none
**/
void IWDG_Freeze_Enable(FunctionalState Cmd)
{
    if (Cmd == ENABLE)
    {
        IWDG->KEY = IWDG_FREEZE;
    }
    else
    {
        IWDG->KEY = IWDG_UNFREEZE;
    }
}

/**
*\*\name    IWDG_GetStatus.
*\*\fun     Checks whether the specified IWDG flag is set or not.
*\*\param   IWDG_FLAG : status flag selected in the IWDG_STS register
*\*\          - IWDG_PVU_FLAG
*\*\          - IWDG_CRVU_FLAG
*\*\          - IWDG_FRZF_FLAG
*\*\return  FlagStatus :
*\*\          - RESET
*\*\          - SET
**/
FlagStatus IWDG_GetStatus(IWDG_STATUS_FLAG IWDG_FLAG)
{
    FlagStatus bitstatus;

    if ((IWDG->STS & (uint32_t)IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}
