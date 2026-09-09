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
*\*\file n32g41x_flash.c
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/


#include "n32g41x_flash.h"


/**
*\*\name    FLASH_SetLatency
*\*\fun     Sets the code latency value.
*\*\param   FLASH_Latency :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < HCLK <= 36MHz
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle,  36MHZ < HCLK <= 72MHz
*\*\            - FLASH_LATENCY_2    FLASH two Latency cycle, N32G412: 72Mhz < HCLK <= 80Mhz; N32G415: 72Mhz < HCLK <= 96Mhz;
*\*\return  none
*\*\note    The larger the latency, the longer the flash read operation will take. 
*\*\        If not necessary, it is recommended to use a smaller latency.
**/
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpregister;

    /* Read the AC register */
    tmpregister = FLASH->AC;

    /* Sets the Latency value */
    tmpregister &= (~FLASH_LATENCY_MASK);
    tmpregister |= FLASH_Latency;

    /* Write the AC register */
    FLASH->AC = tmpregister;
}


/**
*\*\name    FLASH_GetLatency
*\*\fun     Get the code latency value.
*\*\param   none
*\*\return  FLASH_LATENCY :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < HCLK <= 36MHz
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle,  36MHZ < HCLK <= 72MHz
*\*\            - FLASH_LATENCY_2    FLASH two Latency cycle, N32G412: 72Mhz < HCLK <= 80Mhz; N32G415: 72Mhz < HCLK <= 96Mhz;
**/
uint8_t FLASH_GetLatency(void)
{
    /* Read the AC register */
    return (uint8_t)(FLASH->AC & FLASH_AC_LATENCY);
}


/**
*\*\name    FLASH_PrefetchBufSet
*\*\fun     Enables or disables the Prefetch Buffer.
*\*\param   FLASH_PrefetchBuf:(The input parameters must be the following values)
*\*\            - FLASH_PrefetchBuf_EN      
*\*\            - FLASH_PrefetchBuf_DIS
*\*\return  none
**/
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf)
{
    /* Enable or disable the Prefetch Buffer */
    FLASH->AC &= FLASH_PrefetchBuf_MSK;
    FLASH->AC |= FLASH_PrefetchBuf;
}

/**
*\*\name   Flash_GetPrefetchBufferStatus
*\*\fun    Get the Prefetch Buffer status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     FLASH is in Prefetch Buffer enabled state
*\*\            - RESET   FLASH is in Prefetch Buffer disabled state
**/
FlagStatus Flash_GetPrefetchBufferStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->AC & FLASH_PRFTBS_MSK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}

/**
*\*\name    FLASH_iCacheRST
*\*\fun     ICache Reset.
*\*\param   none
*\*\return  none
**/
void FLASH_iCacheRST(void)
{
    /* ICache Reset */
    FLASH->AC |= FLASH_AC_ICAHRST;
}

/**
*\*\name    FLASH_iCacheCmd
*\*\fun     Enables or disables the iCache.
*\*\param   FLASH_iCache:(The input parameters must be the following values)
*\*\            - FLASH_iCache_EN FLASH iCache Enable      
*\*\            - FLASH_iCache_DIS FLASH iCache Disable
*\*\return  none
*\*\note    When the N32G412 series runs above 72MHz, can't enable Icache.
**/
void FLASH_iCacheCmd(uint32_t FLASH_iCache)
{
    /* Enable or disable the iCache */
    FLASH->AC &= AC_ICAHEN_MSK;
    FLASH->AC |= FLASH_iCache;
}

/**
*\*\name   FLASH_StartCacheLock
*\*\fun    Start cache lock.
*\*\param  lock_start_way :
*\*\            - FLASH_CAHR_LOCKSTRT_WAY0
*\*\            - FLASH_CAHR_LOCKSTRT_WAY1
*\*\            - FLASH_CAHR_LOCKSTRT_WAY2
*\*\            - FLASH_CAHR_LOCKSTRT_WAY3
*\*\return none
**/
void FLASH_StartCacheLock(uint32_t lock_start_way)
{
    FLASH->CAHR &= (~(lock_start_way << FLASH_CAHR_LOCK_OFFSET));
    FLASH->CAHR |= lock_start_way;
}

/**
*\*\name   FLASH_StopCacheLock
*\*\fun    Stop cache lock.
*\*\param  lock_stop_way :
*\*\            - FLASH_CAHR_LOCKSTOP_WAY0
*\*\            - FLASH_CAHR_LOCKSTOP_WAY1
*\*\            - FLASH_CAHR_LOCKSTOP_WAY2
*\*\            - FLASH_CAHR_LOCKSTOP_WAY3
*\*\return none
**/
void FLASH_StopCacheLock(uint32_t lock_stop_way)
{
    FLASH->CAHR |= lock_stop_way;
}


/**
*\*\name   FLASH_CancelCacheLock
*\*\fun    Cancle cache lock.
*\*\param  lock_stop_way :
*\*\            - FLASH_CAHR_LOCKSTOP_WAY0
*\*\            - FLASH_CAHR_LOCKSTOP_WAY1
*\*\            - FLASH_CAHR_LOCKSTOP_WAY2
*\*\            - FLASH_CAHR_LOCKSTOP_WAY3
*\*\return none
**/
void FLASH_CancelCacheLock(uint32_t lock_stop_way)
{
    FLASH->CAHR |= lock_stop_way;
    FLASH->CAHR &= (~lock_stop_way);
}


/**
*\*\name   FLASH_Unlock
*\*\fun    Unlocks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
*\*\note   Before operating the FLASH_CTRL register, you need to call the FLASH_Unlock function to unlock the LOCK bit.
**/
void FLASH_Unlock(void)
{
    FLASH->KEY = FLASH_KEY1;
    FLASH->KEY = FLASH_KEY2;
}


/**
*\*\name   FLASH_Lock
*\*\fun    Locks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
**/
void FLASH_Lock(void)
{
    FLASH->CTRL |= CTRL_Set_LOCK;
}


/**
*\*\name   Flash_GetLockStatus
*\*\fun    Get the Flash lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     FLASH is in Lock state
*\*\            - RESET   FLASH is in Unlock state
**/
FlagStatus Flash_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & CTRL_Set_LOCK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}


/**
*\*\name   Option_Bytes_Unlock
*\*\fun    Unlocks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Unlock(void)
{
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;
}


/**
*\*\name   Option_Bytes_Lock
*\*\fun    Locks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Lock(void)
{
    /* Set the FLASH_CTRL_SET_OPTWE Bit to lock */
    FLASH->CTRL &= (~FLASH_CTRL_SET_OPTWE);
}


/**
*\*\name   OB_GetLockStatus
*\*\fun    Get the Option Bytes lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     Option byte is in Unlock state
*\*\            - RESET   Option byte is in Lock state
**/
FlagStatus OB_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & FLASH_CTRL_SET_OPTWE) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_EraseOnePage
*\*\fun    Erases a specified main FLASH page.
*\*\param  Page_Address :(The input parameters must be the following values)
*\*\            - main flash, it ranges from 0x08000000 to 0x0801FFFF, it must be a multiple of 0x200
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address)
{
    FLASH_STS status;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= CTRL_Set_PER;
        FLASH->ADD = Page_Address;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the PER Bit */
        FLASH->CTRL &= CTRL_Reset_PER;
    }

    /* Return the Erase Status */
    return status;
}


/**
*\*\name   FLASH_MassErase
*\*\fun    Erases all main FLASH pages.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_MassErase(void)
{
    FLASH_STS status;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= CTRL_Set_MER;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the MER Bit */
        FLASH->CTRL &= CTRL_Reset_MER;
    }

    /* Return the Erase Status */
    return status;
}


/**
*\*\name   FLASH_ProgramWord
*\*\fun    Programs one word at a specified address.
*\*\param  address :(The input parameters must be the following values)
*\*\            - it ranges from 0x08000000 to 0x0801FFFF, it must be a multiple of 0x04
*\*\param  data :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_ADD  FLASH address error
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramWord(uint32_t address, uint32_t data)
{
    FLASH_STS status_value = FLASH_EOP;

    if((address & FLASH_WORD_LENGTH) != (uint32_t)0x00)
    {
        /* The programming address is not a multiple of 4 */
        status_value = FLASH_ERR_ADD;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_ADD)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CTRL_Set_PG;

        *((__IO uint32_t*)(uintptr_t)address) = (uint32_t)data;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CTRL_Reset_PG;
    }
    else
    {
        /*No process*/
    }
    
    /* Return the Program status_value */
    return status_value;
}


/**
*\*\name   FLASH_EraseOB
*\*\fun    Erases the FLASH option bytes.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EraseOB(void)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the erase status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_RDP1
*\*\fun    Programs the Option Byte: RDP1.
*\*\param  option_byte_rpd1 :(The input parameters must be the following values)
*\*\        - FLASH_OB_RDP1_ENABLE   Enable read protection L1
*\*\        - FLASH_OB_RDP1_DISABLE  Disable read protection L1
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_RDP1(uint8_t option_byte_rpd1)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->RDP1 = ((uint32_t)option_byte_rpd1);
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}




/**
*\*\name   FLASH_ProgramOptionBytes_USER0
*\*\fun    Programs the Option Byte: WDG_SW.
*\*\param  option_byte_iwdg :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SOFTWARE Software IWDG selected
*\*\            - FLASH_OB_IWDG_HARDWARE Hardware IWDG selected
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER0(uint32_t option_byte_iwdg)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER0 = ((uint32_t)(option_byte_iwdg));     
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER1
*\*\fun    Programs the Option Byte: NRST_PD7.
*\*\param  option_byte_PD7 :(The input parameters must be the following values)
*\*\            - FLASH_OB_PD7_GPIO PD7 set GPIO
*\*\            - FLASH_OB_PD7_NRST PD7 set NRST
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER1(uint32_t option_byte_PD7)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER1 = ((uint32_t)(option_byte_PD7));       
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_USER3_USER2
*\*\fun    Programs the Option Byte: USER3 and USER2.
*\*\param   option_byte_nBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NBOOT0_SET Set nBOOT0
*\*\            - FLASH_OB_NBOOT0_CLR Clear nBOOT0
*\*\param   option_byte_nBOOT1 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NBOOT1_SET Set nBOOT1
*\*\            - FLASH_OB_NBOOT1_CLR Clear nBOOT1
*\*\param   option_byte_nSWBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NSWBOOT0_SET Set nSWBOOT0
*\*\            - FLASH_OB_NSWBOOT0_CLR Clear nSWBOOT0
*\*\param   option_byte_BOOT0_CFG :(The input parameters must be the following values)
*\*\            - FLASH_OB_BOOT0_CFG_HIGH Boot0 high active
*\*\            - FLASH_OB_BOOT0_CFG_LOW  Boot0 low active
*\*\param   option_byte_iwdg_stop :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SLEEP_NOFRZ IWDG not freeze when enrting Sleep mode
*\*\            - FLASH_OB_IWDG_SLEEP_FRZ  IWDG freeze when enrting Sleep mode
*\*\param   option_byte_iwdg_sleep :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_STOP_NOFRZ IWDG not freeze when enrting Stop mode
*\*\            - FLASH_OB_IWDG_STOP_FRZ  IWDG freeze when enrting Stop mode
*\*\param  option_byte_user2:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF  PDR/POR filter control count value,30~8192us
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER3_USER2(uint32_t option_byte_nBOOT0, uint32_t option_byte_nBOOT1, \
                                               uint32_t option_byte_nSWBOOT0, uint32_t option_byte_BOOT0_CFG, \
                                               uint32_t option_byte_iwdg_stop, uint32_t option_byte_iwdg_sleep, \
                                               uint32_t option_byte_user2)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER3_USER2 = (((uint32_t)(option_byte_nBOOT0 | option_byte_nBOOT1 | option_byte_nSWBOOT0 | option_byte_BOOT0_CFG |\
                                        option_byte_iwdg_stop | option_byte_iwdg_sleep)) | ((uint32_t)option_byte_user2));      
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_USER5_USER4
*\*\fun    Programs the Option Byte: USER5 and USER4.
*\*\param   option_byte_user4 :(The input parameters must be the following values)
*\*\            - BOOT_UARTPIN_PA9PA10
*\*\            - BOOT_UARTPIN_PA0PA1 
*\*\            - BOOT_UARTPIN_PA4PA5       
*\*\            - BOOT_UARTPIN_PB4PB5       
*\*\            - BOOT_UARTPIN_PB6PB7       
*\*\            - BOOT_UARTPIN_NUM5       N32G412 serial BOOT uart pins are PB8 and PB9, N32G415 serial BOOT uart pins are PB8 and PC10
*\*\            - BOOT_UARTPIN_PC4PC5       
*\*\            - BOOT_UARTPIN_NUM7       N32G412 serial BOOT uart pins are PC7 and PC6, N32G415 serial BOOT uart pins are PA9 and PA8
*\*\            - BOOT_UARTPIN_NUM8       N32G412 serial BOOT uart pins are PC12 and PD2, N32G415 serial BOOT uart pins are PD0 and PD2
*\*\param   option_byte_user5 :(The input parameters must be the following values)
*\*\            - BOOT_I2C_PIN_PA4PA5   
*\*\            - BOOT_I2C_PIN_PA9PA10  
*\*\            - BOOT_I2C_PIN_PA15PA14       
*\*\            - BOOT_I2C_PIN_PB6PB7         
*\*\            - BOOT_I2C_PIN_NUM4       N32G412 serial BOOT i2c pins are PB7 and PB8, N32G415 serial BOOT i2c pins are PB7 and PB9  
*\*\            - BOOT_I2C_PIN_NUM5       N32G412 serial BOOT i2c pins are PB8 and PB9, N32G415 serial BOOT i2c pins are PB9 and PC10
*\*\            - BOOT_I2C_PIN_PC0PC1
*\*\            - BOOT_I2C_PIN_PC4PC5         
*\*\            - BOOT_I2C_PIN_PD15PD14 
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER5_USER4(uint32_t option_byte_user4, uint32_t option_byte_user5)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER5_USER4 = ((uint32_t)(option_byte_user4 | option_byte_user5));      
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_USER6
*\*\fun    Programs the Option Byte: USER6.
*\*\param   option_byte_user6 :(The input parameters must be the following values)
*\*\            - BOOT_CAN_PIN_PA12PA11 CAN pins are PA12 and PA11
*\*\            - BOOT_CAN_PIN_NUM1   N32G412 serial CAN pins are PB9 and PB8, N32G415 serial CAN pins are PC10 and PB9 
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER6(uint32_t option_byte_user6)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER6 = ((uint32_t)(option_byte_user6));      
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_USER7
*\*\fun    Programs the Option Byte: BOOT write protection Enable or disable.
*\*\param  option_byte_user7:
*\*\            - BOOT_WRP_ENABLE 
*\*\            - BOOT_WRP_DISABLE 
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER7(uint32_t option_byte_user7)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }
    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER7 = ((uint32_t)(option_byte_user7));     
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_DATA1_DATA0
*\*\fun    Programs 2 half words at a specified Option Byte Data1 and Data0.
*\*\param  option_byte_data1:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF
*\*\param  option_byte_data0:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF
*\*\return FLASH_STS: The returned value can be: 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_DATA1_DATA0(uint8_t option_byte_data1, uint8_t option_byte_data0)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->Data1_Data0 = ((((uint32_t)option_byte_data1) << REG_BIT16_OFFSET) | ((uint32_t)option_byte_data0));        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_EnWriteProtection
*\*\fun    Write protects the desired pages
*\*\param  FLASH_Pages :(The input parameters must be the following values)
*\*\        - FLASH_WRP_Pages0to7      Enable Write protection of page 0 to 7
*\*\        - FLASH_WRP_Pages8to15     Enable Write protection of page 8 to 15
*\*\        - FLASH_WRP_Pages16to23    Enable Write protection of page 16 to 23
*\*\        - FLASH_WRP_Pages24to31    Enable Write protection of page 24 to 31
*\*\        - FLASH_WRP_Pages32to39    Enable Write protection of page 32 to 39
*\*\        - FLASH_WRP_Pages40to47    Enable Write protection of page 40 to 47
*\*\        - FLASH_WRP_Pages48to55    Enable Write protection of page 48 to 55
*\*\        - FLASH_WRP_Pages56to63    Enable Write protection of page 56 to 63
*\*\        - FLASH_WRP_Pages64to71    Enable Write protection of page 64 to 71
*\*\        - FLASH_WRP_Pages72to79    Enable Write protection of page 72 to 79
*\*\        - FLASH_WRP_Pages80to87    Enable Write protection of page 80 to 87
*\*\        - FLASH_WRP_Pages88to95    Enable Write protection of page 88 to 95
*\*\        - FLASH_WRP_Pages96to103   Enable Write protection of page 96 to 103
*\*\        - FLASH_WRP_Pages104to111  Enable Write protection of page 104 to 111
*\*\        - FLASH_WRP_Pages112to119  Enable Write protection of page 112 to 119
*\*\        - FLASH_WRP_Pages120to127  Enable Write protection of page 120 to 127
*\*\        - FLASH_WRP_Pages128to135  Enable Write protection of page 128 to 135
*\*\        - FLASH_WRP_Pages136to143  Enable Write protection of page 136 to 143
*\*\        - FLASH_WRP_Pages144to151  Enable Write protection of page 144 to 151
*\*\        - FLASH_WRP_Pages152to159  Enable Write protection of page 152 to 159
*\*\        - FLASH_WRP_Pages160to167  Enable Write protection of page 160 to 167
*\*\        - FLASH_WRP_Pages168to175  Enable Write protection of page 168 to 175
*\*\        - FLASH_WRP_Pages176to183  Enable Write protection of page 176 to 183
*\*\        - FLASH_WRP_Pages184to191  Enable Write protection of page 184 to 191
*\*\        - FLASH_WRP_Pages192to199  Enable Write protection of page 192 to 199
*\*\        - FLASH_WRP_Pages200to207  Enable Write protection of page 200 to 207
*\*\        - FLASH_WRP_Pages208to215  Enable Write protection of page 208 to 215
*\*\        - FLASH_WRP_Pages216to223  Enable Write protection of page 216 to 223
*\*\        - FLASH_WRP_Pages224to231  Enable Write protection of page 224 to 231
*\*\        - FLASH_WRP_Pages232to239  Enable Write protection of page 232 to 239
*\*\        - FLASH_WRP_Pages240to247  Enable Write protection of page 240 to 247
*\*\        - FLASH_WRP_Pages248to255  Enable Write protection of page 248 to 255
*\*\        - FLASH_WRP_AllPages       Enable Write protection of all Pages
*\*\        - ~FLASH_WRP_AllPages      Disable Write protection of all Pages
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages)
{
    uint32_t WRP0_Data, WRP1_Data,WRP2_Data, WRP3_Data;

    FLASH_STS status_value = FLASH_EOP;
    
    uint32_t FLASH_Pages_temp;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    
    FLASH_Pages_temp = (uint32_t)(~FLASH_Pages);
    WRP0_Data   = (uint16_t)( FLASH_Pages_temp & FLASH_WRP0_MSK);
    WRP1_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP1_MSK) >> FLASH_WRP_WRP1_OFFSET);
    WRP2_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP2_MSK) >> FLASH_WRP_WRP2_OFFSET);
    WRP3_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP3_MSK) >> FLASH_WRP_WRP3_OFFSET);
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= CTRL_Set_OPTPG;

        if ((WRP0_Data != 0xFFU) || (WRP1_Data != 0xFFU))
        {
            OBT->WRP1_WRP0 = ((WRP1_Data << REG_BIT16_OFFSET) | WRP0_Data);

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }
        
        
        if (((WRP2_Data != 0xFFU) || (WRP3_Data != 0xFFU)) &&(status_value == FLASH_EOP))
        {
            OBT->WRP3_WRP2 = ((WRP3_Data << REG_BIT16_OFFSET) | WRP2_Data);

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }
                
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the write protection operation Status */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_RDP2
*\*\fun    Programs the Option Byte: RDP2.
*\*\param  option_byte_rpd2 :(The input parameters must be the following values)
*\*\            - FLASH_OB_RDP2_ENABLE   Enable read protection L2
*\*\            - FLASH_OB_RDP2_DISABLE  Disable read protection L2
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_RDP2(uint8_t option_byte_rpd2)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->RDP2 = (uint32_t)option_byte_rpd2;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ReadOutProtectionL1
*\*\fun    Enables the read out protection.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE   Enable read protection L1
*\*\            - DISABLE  Disable read protection L1
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd)
{ 
    uint32_t user0_temp = 0xFFU, user1_temp = 0xFFU, user2_user3_temp = 0xFFU;    
    uint32_t user4_user5_temp = 0xFFU,user6_temp = 0xFFU,user7_temp = 0xFFU;
    uint32_t data0_data1_temp = 0xFFU,rpd1_tmp = 0xFFU;
    uint32_t wrp0_wrp1_tmp = 0xFFU,wrp2_wrp3_tmp = 0xFFU;
    FLASH_STS status_value;
    uint32_t timeout_value;
    timeout_value = EraseTimeout;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        if(Cmd == ENABLE)
        {
            
        }
        else
        {
            rpd1_tmp = FLASH_OB_RDP1_DISABLE;
        }
        
        user0_temp = OBT->USER0;
        user1_temp = OBT->USER1;
        user2_user3_temp = OBT->USER3_USER2;
        user4_user5_temp = OBT->USER5_USER4;
        user6_temp = OBT->USER6; 
        user7_temp = OBT->USER7;
        data0_data1_temp = OBT->Data1_Data0;
        wrp0_wrp1_tmp = OBT->WRP1_WRP0;
        wrp2_wrp3_tmp = OBT->WRP3_WRP2;
        
        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }
    
    if(status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }
    else
    {
        /*No process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER0 = user0_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER1 = user1_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER3_USER2 = user2_user3_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER5_USER4 = user4_user5_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER6 = user6_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER7 = user7_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->Data1_Data0 = data0_data1_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP1_WRP0 = wrp0_wrp1_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP3_WRP2 = wrp2_wrp3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->RDP1 = rpd1_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
  
    /* Return the protection operation status_value */
    return status_value;
}


/**
*\*\name   FLASH_ReadOutProtectionL2_ENABLE
*\*\fun    Enables the read out protection L2.
*\*\param  none
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void)
{ 
    uint32_t user0_temp = 0xFFU, user1_temp = 0xFFU, user2_user3_temp = 0xFFU;    
    uint32_t user4_user5_temp = 0xFFU,user6_temp = 0xFFU,user7_temp = 0xFFU;
    uint32_t data0_data1_temp = 0xFFU;
    uint32_t wrp0_wrp1_tmp = 0xFFU,wrp2_wrp3_tmp = 0xFFU;
    FLASH_STS status_value;
    uint32_t timeout_value;
    timeout_value = EraseTimeout;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        user0_temp = OBT->USER0;
        user1_temp = OBT->USER1;
        user2_user3_temp = OBT->USER3_USER2;
        user4_user5_temp = OBT->USER5_USER4;
        user6_temp = OBT->USER6; 
        user7_temp = OBT->USER7;
        data0_data1_temp = OBT->Data1_Data0;
        wrp0_wrp1_tmp = OBT->WRP1_WRP0;
        wrp2_wrp3_tmp = OBT->WRP3_WRP2;
        
        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }
    
    if(status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }
    else
    {
        /*No process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER0 = user0_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER1 = user1_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER3_USER2 = user2_user3_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER5_USER4 = user4_user5_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER6 = user6_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER7 = user7_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->Data1_Data0 = data0_data1_temp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP1_WRP0 = wrp0_wrp1_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP3_WRP2 = wrp2_wrp3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
    
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->RDP2 = FLASH_OB_RDP2_ENABLE;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(timeout_value);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
    {
        /* no process*/
    }
  
    /* Return the protection operation status_value */
    return status_value;
}


/**
*\*\name   FLASH_GetOptionBytes_User0
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET      Software watchdog
*\*\            - RESET    Hardware watchdog
**/
FlagStatus FLASH_GetOptionBytes_User0(void)
{
    FlagStatus bit_status;
    if(((FLASH->OB >> REG_BIT2_OFFSET) & FLASH_OB_IWDG_SOFTWARE) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetOptionBytes_User1
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET      PF3 used as NRST
*\*\            - RESET    PF3 used as GPIO
**/
FlagStatus FLASH_GetOptionBytes_User1(void)
{
    FlagStatus bit_status;
    if(((FLASH->OB >> REG_BIT2_OFFSET) & FLASH_OB_PD7_NRST) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetOptionBytes_User2
*\*\fun    Returns the FLASH Option Bytes PORCNT values.
*\*\param  none
*\*\return PORCNT:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_User2(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_USER_POR_DELAY_MSK) >> REG_BIT4_OFFSET);
}


/**
*\*\name   FLASH_GetOptionBytes_User3
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  option_byte_bit: (The input parameters must be the following values)
*\*\            - FLASH_OB_NBOOT0_SET          nBOOT0 configuration bit
*\*\            - FLASH_OB_NBOOT1_SET          nBOOT1 configuration bit
*\*\            - FLASH_OB_NSWBOOT0_SET        nSWBOOT0 configuration bit
*\*\            - FLASH_OB_BOOT0_CFG_HIGH      BOOT0_CFG configuration bit
*\*\            - FLASH_OB_IWDG_SLEEP_NOFRZ    IWDG_SLEEP_NOFRZ configuration bit
*\*\            - FLASH_OB_IWDG_STOP_NOFRZ     IWDG_STOP_NOFRZ configuration bit
*\*\return FlagStatus :
*\*\            - SET      Enter this mode without resetting
*\*\            - RESET    Enter this mode reset
**/
FlagStatus FLASH_GetOptionBytes_User3(uint32_t option_byte_bit)
{
    FlagStatus bit_status;
    if(((FLASH->OB ) & (option_byte_bit >> REG_BIT4_OFFSET)) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}

/**
*\*\name   FLASH_GetBOOTUartPIN
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return option_byte_user4 0x0~0x8:
*\*\            - BOOT_UARTPIN_PA9PA10    BOOT uart pins are PA9 and PA10
*\*\            - BOOT_UARTPIN_PA0PA1     BOOT uart pins are PA0 and PA1 
*\*\            - BOOT_UARTPIN_PA4PA5     BOOT uart pins are PA4 and PA5 
*\*\            - BOOT_UARTPIN_PB4PB5     BOOT uart pins are PB4 and PB5 
*\*\            - BOOT_UARTPIN_PB6PB7     BOOT uart pins are PB6 and PB7 
*\*\            - BOOT_UARTPIN_NUM5       N32G412 serial BOOT uart pins are PB8 and PB9, N32G415 serial BOOT uart pins are PB8 and PC10
*\*\            - BOOT_UARTPIN_PC4PC5     BOOT uart pins are PC4 and PC5 
*\*\            - BOOT_UARTPIN_NUM7       N32G412 serial BOOT uart pins are PC7 and PC6, N32G415 serial BOOT uart pins are PA9 and PA8
*\*\            - BOOT_UARTPIN_NUM8       N32G412 serial BOOT uart pins are PC12 and PD2, N32G415 serial BOOT uart pins are PD0 and PD2
**/
uint32_t FLASH_GetBOOTUartPIN(void)
{
    return (uint32_t)(((FLASH->OB & FLASH_OB_BOOT_SEL_UART) >> REG_BIT20_OFFSET));   
}

/**
*\*\name   FLASH_GetBOOTI2cPIN
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return option_byte_user5 0x0~0x8:
*\*\            - BOOT_I2C_PIN_PA4PA5      I2C SCL SDA pins are PA4 and PA5 
*\*\            - BOOT_I2C_PIN_PA9PA10     I2C SCL SDA pins are PA9 and PA10 
*\*\            - BOOT_I2C_PIN_PA15PA14    I2C SCL SDA pins are PA15 and PA14
*\*\            - BOOT_I2C_PIN_PB6PB7      I2C SCL SDA pins are PB6 and PB7 
*\*\            - BOOT_I2C_PIN_NUM4        N32G412 serial I2C SCL SDA pins are PB7 and PB8 , N32G415 serial I2C SCL SDA pins are PB7 and PB9
*\*\            - BOOT_I2C_PIN_NUM5        N32G412 serial I2C SCL SDA pins are PB8 and PB9 , N32G415 serial I2C SCL SDA pins are PB9 and PC10
*\*\            - BOOT_I2C_PIN_PC0PC1      I2C SCL SDA pins are PC0 and PC1 
*\*\            - BOOT_I2C_PIN_PC4PC5      I2C SCL SDA pins are PC4 and PC5 
*\*\            - BOOT_I2C_PIN_PD15PD14    I2C SCL SDA pins are PD15 and PD14
**/
uint32_t FLASH_GetBOOTI2cPIN(void)
{
    return (uint32_t)(((FLASH->OB2 & FLASH_OB2_BOOT_SEL_I2C) << REG_BIT16_OFFSET));   
}

/**
*\*\name   FLASH_GetBOOTCanPIN
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return option_byte_user6 0x0~0x1:
*\*\            - BOOT_CAN_PIN_PA12PA11    N32G412 serial CAN TX pins are PA12 and PA11
*\*\            - BOOT_CAN_PIN_NUM1        N32G412 serial CAN TX pins are PB9 and PB8, N32G415 serial CAN TX pins are PC10 and PB9
**/
uint32_t FLASH_GetBOOTCanPIN(void)
{
    return (uint32_t)(((FLASH->OB2 & FLASH_OB2_BOOT_SEL_CAN) >> REG_BIT8_OFFSET));   
}

/**
*\*\name   FLASH_GetOptionBytes_Data0
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data0:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data0(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB2 & FLASH_DATA0_MASK) >> REG_BIT16_OFFSET);
}


/**
*\*\name   FLASH_GetOptionBytes_Data1
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data1:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data1(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB2 & FLASH_DATA1_MASK) >> REG_BIT24_OFFSET);
}


/**
*\*\name   FLASH_GetReadOutProtectionSTS
*\*\fun    Checks whether the FLASH Read Out Protection L1 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L1 enable
*\*\        - RESET  Read protection L1 disable
**/
FlagStatus FLASH_GetReadOutProtectionSTS(void)
{
    FlagStatus bit_status;
    if ((FLASH->OB & FLASH_RDPRTL1_MSK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_Read_Out_Protection_L2_Status_Get
*\*\fun    Checks whether the FLASH Read Out Protection L2 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L2 enable
*\*\        - RESET  Read protection L2 disable
**/
FlagStatus FLASH_GetReadOutProtectionL2STS(void)
{
    FlagStatus readoutstatus;
    if ((FLASH->OB & FLASH_RDPRTL2_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}


/**
*\*\name   FLASH_GetWriteProtectionSTS
*\*\fun    Returns the FLASH Write Protection Option Bytes Register value.
*\*\param  none
*\*\return The FLASH Write Protection  Option Bytes Register value :
*\*\            - Bit31 - Bit0 write-protects pages (255~248) - page (0~7) 
**/
uint32_t FLASH_GetWriteProtectionSTS(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}

/**
*\*\name   FLASH_GetBOOTWriteProtectionSTS
*\*\fun    Checks whether the BOOT Protection status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    BOOT write protection enable
*\*\        - RESET  BOOT write protection disable
**/
FlagStatus FLASH_GetBOOTWriteProtectionSTS(void)
{
    FlagStatus readoutstatus;
    if ((FLASH->OB & FLASH_OB_BOOTWRP_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

/**
*\*\name   FLASH_INTConfig
*\*\fun    Enables the specified FLASH interrupts.
*\*\param  FLASH_INT :
*\*\            - FLASH_INT_ERR      FLASH Error Interrupt
*\*\            - FLASH_INT_EOP      FLASH end of operation Interrupt
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return none
**/
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CTRL |= FLASH_INT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
}


/**
*\*\name   FLASH_GetFlagSTS
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_BUSY      FLASH Busy flag
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\        - FLASH_FLAG_FKEYF     FKEYR write KEY1 flag
*\*\        - FLASH_FLAG_OPTKEYF   OPTKEYR write KEY1 flag
*\*\return FlagStatus :
*\*\        - SET      Flag status is set
*\*\        - RESET    Flag status is reset
**/
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bit_status;
    if ((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetOBFlagSTS
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_OBERR FLASH Option Byte error flag
*\*\return FlagStatus :
*\*\        - SET      Flag status is set
*\*\        - RESET    Flag status is reset
**/
FlagStatus FLASH_GetOBFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bit_status;
    if ((FLASH->OB & FLASH_FLAG) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_ClearFlag
*\*\fun    Clears the FLASH's status flags.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\return none
**/
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Clear the flags */
    FLASH->STS = FLASH_FLAG;
}


/**
*\*\name   FLASH_GetSTS
*\*\fun    Returns the FLASH_STS.
*\*\param  none
*\*\return FLASH_STS :
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
**/
FLASH_STS FLASH_GetSTS(void)
{
    FLASH_STS flashstatus;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != 0U)
        {
            flashstatus = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_WRPERR) != 0U)
            {
                flashstatus = FLASH_ERR_WRP;
            }
            else
            {
                flashstatus = FLASH_EOP;
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}


/**
*\*\name   FLASH_WaitForLastOpt
*\*\fun    Waits for a Flash operation to complete or a timeout to occur.
*\*\param  timeout :(The input parameters must be the following values)
*\*\            - EraseTimeout
*\*\            - ProgramTimeout
*\*\return FLASH_STS: The returned value can be: 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout)
{
    FLASH_STS status;
    uint32_t Timeout_temp;
    Timeout_temp = Timeout;
 
    /* Check for the Flash Status */
    status = FLASH_GetSTS();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout_temp != 0x00U))
    {
        status = FLASH_GetSTS();
        Timeout_temp--;
    }
    if (Timeout_temp == 0x00U)
    {
        status = FLASH_TIMEOUT;
    }
    /* Return the operation status */
    return status;
}


