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
*\*\file n32g41x_flash.h
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/


#ifndef __N32G41X_FLASH_H__
#define __N32G41X_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"

/** FLASH Status **/
typedef enum
{ 
    FLASH_BUSY = 1,
    FLASH_ERR_PG,
    FLASH_ERR_WRP,
    FLASH_EOP,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
}FLASH_STS;

/** Flash_Latency **/
#define FLASH_LATENCY_0     ((uint32_t)FLASH_AC_LATENCY_0) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1     ((uint32_t)FLASH_AC_LATENCY_1) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2     ((uint32_t)FLASH_AC_LATENCY_2) /* FLASH two Latency cycles */
#define FLASH_LATENCY_MASK  ((uint32_t)FLASH_AC_LATENCY)

/** Flash Access Control Register bits **/
#define FLASH_PRFTBS_MSK                  ((uint32_t)FLASH_AC_PRFTBFSTS)
/** Prefetch_Buffer_Enable_Disable **/
#define FLASH_PrefetchBuf_EN              ((uint32_t)FLASH_AC_PRFTBFEN)            /* FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuf_DIS             ((uint32_t)0x00000000U)                   /* FLASH Prefetch Buffer Disable */
#define FLASH_PrefetchBuf_MSK             (~((uint32_t)FLASH_AC_PRFTBFEN))         /* FLASH Prefetch Buffer mask    */

/** iCache_Enable_Disable **/
#define AC_ICAHEN_MSK                ((uint32_t)(~FLASH_AC_ICAHEN))
#define FLASH_iCache_EN              ((uint32_t)FLASH_AC_ICAHEN) /* FLASH iCache Enable */
#define FLASH_iCache_DIS             ((uint32_t)0x00000000U) /* FLASH iCache Disable */

/** Bit definition for FLASH_CAHR register **/
#define FLASH_CAHR_LOCKSTRT_WAY0    (FLASH_CAHR_LOCKSTRT_0)
#define FLASH_CAHR_LOCKSTRT_WAY1    (FLASH_CAHR_LOCKSTRT_1)
#define FLASH_CAHR_LOCKSTRT_WAY2    (FLASH_CAHR_LOCKSTRT_2)
#define FLASH_CAHR_LOCKSTRT_WAY3    (FLASH_CAHR_LOCKSTRT_3)
#define FLASH_CAHR_LOCK_OFFSET      (REG_BIT4_OFFSET)
#define FLASH_CAHR_LOCKSTOP_WAY0    (FLASH_CAHR_LOCKSTOP_0)
#define FLASH_CAHR_LOCKSTOP_WAY1    (FLASH_CAHR_LOCKSTOP_1)
#define FLASH_CAHR_LOCKSTOP_WAY2    (FLASH_CAHR_LOCKSTOP_2)
#define FLASH_CAHR_LOCKSTOP_WAY3    (FLASH_CAHR_LOCKSTOP_3)

/** FLASH Keys **/
#define FLASH_KEY1   ((uint32_t)0x45670123U)
#define FLASH_KEY2   ((uint32_t)0xCDEF89ABU)

/** Flash Control Register bits **/
#define CTRL_Set_PG             ((uint32_t)FLASH_CTRL_PG)
#define CTRL_Reset_PG           (~((uint32_t)FLASH_CTRL_PG))
#define CTRL_Set_PER            ((uint32_t)FLASH_CTRL_PER)
#define CTRL_Reset_PER          (~((uint32_t)FLASH_CTRL_PER))
#define CTRL_Set_MER            ((uint32_t)FLASH_CTRL_MER)
#define CTRL_Reset_MER          (~((uint32_t)FLASH_CTRL_MER))
#define CTRL_Set_OPTPG          ((uint32_t)FLASH_CTRL_OPTPG)
#define CTRL_Reset_OPTPG        (~((uint32_t)FLASH_CTRL_OPTPG))
#define CTRL_Set_OPTER          ((uint32_t)FLASH_CTRL_OPTER)
#define CTRL_Reset_OPTER        (~((uint32_t)FLASH_CTRL_OPTER))
#define CTRL_Set_START          ((uint32_t)FLASH_CTRL_START)
#define CTRL_Set_LOCK           ((uint32_t)FLASH_CTRL_LOCK)
#define FLASH_CTRL_SET_OPTWE    ((uint32_t)FLASH_CTRL_OPTWE)

/** Option byte **/
#define L1_RDP_Key                  ((uint32_t)0xFFFF00A5U)  
#define FLASH_L2_RDP_KEY            ((uint32_t)0xFFFF33CCU)
#define FLASH_OB2_DATA0_MASK        (FLASH_OB2_Data0)
#define FLASH_OB2_DATA1_MASK        (FLASH_OB2_Data1)
#define FLASH_OB_BOOTSEL_UART_MASK  (FLASH_OB_BOOT_SEL_UART)
#define FLASH_OB_BOOTSEL_I2C_MASK   (FLASH_OB2_BOOT_SEL_I2C)
#define FLASH_OB_BOOTSEL_CAN_MASK   (FLASH_OB2_BOOT_SEL_CAN)

/** FLASH Mask **/
#define FLASH_RDPRTL1_MSK           ((uint32_t)FLASH_OB_RDPRT1)
#define FLASH_RDPRTL2_MSK           ((uint32_t)FLASH_OB_RDPRT2)
#define FLASH_OB_BOOTWRP_MSK        ((uint32_t)FLASH_OB_BOOT_WRP)

/** user7 Boot wrap **/
#define BOOT_WRP_DISABLE             ((uint32_t)0xA55A5AA5U)
#define BOOT_WRP_ENABLE              ((uint32_t)0x00000000U)

/** user6 CAN REMAP **/
#define BOOT_CAN_PIN_PA12PA11               ((uint32_t)0x00000000U) /* BOOT CAN TX&RX pins are PA12 and PA11 */
#define BOOT_CAN_PIN_NUM1                   ((uint32_t)0x00000001U) /* N32G412 serial CAN pins are PB9 and PB8, N32G415 serial CAN pins are PC10 and PB9 */

/** user5 Option_Bytes_I2C REMAP **/
#define BOOT_I2C_PIN_PA4PA5                 ((uint32_t)0x00000000U) /* BOOT I2C SCL SDA pins are PA4 and PA5 */
#define BOOT_I2C_PIN_PA9PA10                ((uint32_t)0x00010000U) /* BOOT I2C SCL SDA pins are PA9 and PA10 */
#define BOOT_I2C_PIN_PA15PA14               ((uint32_t)0x00020000U) /* BOOT I2C SCL SDA pins are PA15 and PA14 */
#define BOOT_I2C_PIN_PB6PB7                 ((uint32_t)0x00030000U) /* BOOT I2C SCL SDA pins are PB6 and PB7 */
#define BOOT_I2C_PIN_NUM4                   ((uint32_t)0x00040000U) /* N32G412 serial I2C SCL SDA pins are PB7 and PB8 , N32G415 serial I2C SCL SDA pins are PB7 and PB9 */
#define BOOT_I2C_PIN_NUM5                   ((uint32_t)0x00050000U) /* N32G412 serial I2C SCL SDA pins are PB8 and PB9 , N32G415 serial I2C SCL SDA pins are PB9 and PC10 */
#define BOOT_I2C_PIN_PC0PC1                 ((uint32_t)0x00060000U) /* BOOT I2C SCL SDA pins are PC0 and PC1 */
#define BOOT_I2C_PIN_PC4PC5                 ((uint32_t)0x00070000U) /* BOOT I2C SCL SDA pins are PC4 and PC5 */
#define BOOT_I2C_PIN_PD15PD14               ((uint32_t)0x00080000U) /* BOOT I2C SCL SDA pins are PD15 and PD14 */


/** user4 Option_Bytes_BOOTSEL **/   
#define BOOT_UARTPIN_PA9PA10            ((uint32_t)0x00000000U) /* BOOT uart pins are PA9 and PA10 */
#define BOOT_UARTPIN_PA0PA1             ((uint32_t)0x00000001U) /* BOOT uart pins are PA0 and PA1 */
#define BOOT_UARTPIN_PA4PA5             ((uint32_t)0x00000002U) /* BOOT uart pins are PA4 and PA5 */
#define BOOT_UARTPIN_PB4PB5             ((uint32_t)0x00000003U) /* BOOT uart pins are PB4 and PB5 */
#define BOOT_UARTPIN_PB6PB7             ((uint32_t)0x00000004U) /* BOOT uart pins are PB6 and PB7 */
#define BOOT_UARTPIN_NUM5               ((uint32_t)0x00000005U) /* N32G412 serial BOOT uart pins are PB8 and PB9, N32G415 serial BOOT uart pins are PB8 and PC10 */
#define BOOT_UARTPIN_PC4PC5             ((uint32_t)0x00000006U) /* BOOT uart pins are PC4 and PC5 */
#define BOOT_UARTPIN_NUM7               ((uint32_t)0x00000007U) /* N32G412 serial BOOT uart pins are PC7 and PC6, N32G415 serial BOOT uart pins are PA9 and PA8 */
#define BOOT_UARTPIN_NUM8               ((uint32_t)0x00000008U) /* N32G412 serial BOOT uart pins are PC12 and PD2, N32G415 serial BOOT uart pins are PD0 and PD2 */

/** Option_Bytes_RDPx **/
#define FLASH_OB_RDP1_ENABLE            ((uint8_t)0x00U) /* Enable RDP1 */
#define FLASH_OB_RDP1_DISABLE           ((uint8_t)0xA5U) /* DISABLE RDP1 */

#define FLASH_OB_RDP2_ENABLE            ((uint8_t)0xCCU) /* Enable RDP2 */
#define FLASH_OB_RDP2_DISABLE           ((uint8_t)0x00U) /* Disable RDP2 */

/** Option_Bytes_IWatchdog **/
#define FLASH_OB_IWDG_SOFTWARE          ((uint32_t)0x00000001U) /* Software IWDG selected */
#define FLASH_OB_IWDG_HARDWARE          ((uint32_t)0xA55A5AA5U) /* Hardware IWDG selected */

/** Option_Bytes_PD7 **/
#define FLASH_OB_PD7_GPIO               ((uint32_t)0xA55A5AA5U) /* PD7 set GPIO */
#define FLASH_OB_PD7_NRST               ((uint32_t)0x00000002U) /* PD7 set NRST */

#define FLASH_OB_NBOOT0_SET             ((uint32_t)0x00010000U) /* Set nBOOT0 */
#define FLASH_OB_NBOOT0_CLR             ((uint32_t)0x00000000U) /* Clear nBOOT0 */

#define FLASH_OB_NBOOT1_SET             ((uint32_t)0x00020000U) /* Set nBOOT1 */
#define FLASH_OB_NBOOT1_CLR             ((uint32_t)0x00000000U) /* Clear nBOOT1 */

#define FLASH_OB_NSWBOOT0_SET           ((uint32_t)0x00040000U) /* Set nSWBOOT0 */
#define FLASH_OB_NSWBOOT0_CLR           ((uint32_t)0x00000000U) /* Clear nSWBOOT0 */

#define FLASH_OB_BOOT0_CFG_HIGH         ((uint32_t)0x00080000U) /* Boot0 high active */
#define FLASH_OB_BOOT0_CFG_LOW          ((uint32_t)0x00000000U) /* Boot0 low active */

#define FLASH_OB_IWDG_SLEEP_NOFRZ       ((uint32_t)0x00100000U) /* IWDG not freeze when enrting Sleep mode */
#define FLASH_OB_IWDG_SLEEP_FRZ         ((uint32_t)0x00000000U) /* IWDG freeze when enrting Sleep mode */

#define FLASH_OB_IWDG_STOP_NOFRZ        ((uint32_t)0x00200000U) /* IWDG not freeze when enrting Stop mode */
#define FLASH_OB_IWDG_STOP_FRZ          ((uint32_t)0x00000000U) /* IWDG freeze when enrting Stop mode */

/** Option Bytes MASK **/
#define FLASH_OB_MASK                   ((uint32_t)0xFFFFFFFFU)
#define FLASH_OB_RDP1_MASK              ((uint32_t)0x0000FFFFU)

/** FLASH USER Mask **/
#define FLASH_USER_POR_DELAY_MSK        ((uint32_t)FLASH_OB_POR_DELAY)
#define FLASH_DATA0_MASK                ((uint32_t)FLASH_OB2_Data0)
#define FLASH_DATA1_MASK                ((uint32_t)FLASH_OB2_Data1)

#define FLASH_OB_USER2_MASK             ((uint32_t)0x000000FFU)
#define FLASH_OB_USER5_MASK             ((uint32_t)0x00FF0000U)
#define FLASH_OB_USER4_MASK             ((uint32_t)0x000000FFU)

/** Delay definition **/
#define EraseTimeout                    ((uint32_t)0x000B0000U)
#define ProgramTimeout                  ((uint32_t)0x00002000U)
#define FLASH_WORD_LENGTH               ((uint32_t)0x00000003U)


/**  FLASH_Interrupts **/
#define FLASH_INT_ERR      ((uint32_t)FLASH_CTRL_ERRITE) /* PGERR WRPERR ERROR error interrupt source */
#define FLASH_INT_EOP      ((uint32_t)FLASH_CTRL_EOPITE) /* End of FLASH Operation Interrupt source */

/** FLASH_Flags **/
#define FLASH_FLAG_BUSY     ((uint32_t)FLASH_STS_BSY) /* FLASH Busy flag */
#define FLASH_FLAG_PGERR    ((uint32_t)FLASH_STS_PGERR) /* FLASH Program error flag */
#define FLASH_FLAG_WRPERR   ((uint32_t)FLASH_STS_WRPRTERR) /* FLASH Write protected error flag */
#define FLASH_FLAG_EOP      ((uint32_t)FLASH_STS_EOP) /* FLASH End of Operation flag */
#define FLASH_FLAG_OBERR    ((uint32_t)FLASH_OB_OBERR) /* Option Byte Error flag */
#define FLASH_FLAG_FKEYF      ((uint32_t)FLASH_STS_FKEYF) /* FKEYR write KEY1 flag */
#define FLASH_FLAG_OPTKEYF    ((uint32_t)FLASH_STS_OPTKEYF) /* OPTKEYR write KEY1 flag */

/** FLASH_STS_CLRFLAG **/
#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP)


/** FLASH Mask **/
#define FLASH_WRP_WRP1_OFFSET       (REG_BIT8_OFFSET)
#define FLASH_WRP_WRP2_OFFSET       (REG_BIT16_OFFSET)
#define FLASH_WRP_WRP3_OFFSET       (REG_BIT24_OFFSET)
#define FLASH_WRP0_MSK           (FLASH_OB_BYTE1)
#define FLASH_WRP1_MSK           (FLASH_OB_BYTE3 >> REG_BIT8_OFFSET)
#define FLASH_WRP2_MSK           (FLASH_OB_BYTE1 << REG_BIT16_OFFSET)
#define FLASH_WRP3_MSK           (FLASH_OB_BYTE3 << REG_BIT8_OFFSET)


#define FLASH_WRP_Pages0to7      ((uint32_t)FLASH_WRP_WRPT_0)  /* Write protection of page 0 to 7 */
#define FLASH_WRP_Pages8to15     ((uint32_t)FLASH_WRP_WRPT_1)  /* Write protection of page 8 to 15 */
#define FLASH_WRP_Pages16to23    ((uint32_t)FLASH_WRP_WRPT_2)  /* Write protection of page 16 to 23 */
#define FLASH_WRP_Pages24to31    ((uint32_t)FLASH_WRP_WRPT_3)  /* Write protection of page 24 to 31 */
#define FLASH_WRP_Pages32to39    ((uint32_t)FLASH_WRP_WRPT_4)  /* Write protection of page 32 to 39 */
#define FLASH_WRP_Pages40to47    ((uint32_t)FLASH_WRP_WRPT_5)  /* Write protection of page 40 to 47 */
#define FLASH_WRP_Pages48to55    ((uint32_t)FLASH_WRP_WRPT_6)  /* Write protection of page 48 to 55 */
#define FLASH_WRP_Pages56to63    ((uint32_t)FLASH_WRP_WRPT_7)  /* Write protection of page 56 to 63 */
#define FLASH_WRP_Pages64to71    ((uint32_t)FLASH_WRP_WRPT_8)  /* Write protection of page 64 to 71 */
#define FLASH_WRP_Pages72to79    ((uint32_t)FLASH_WRP_WRPT_9)  /* Write protection of page 72 to 79 */
#define FLASH_WRP_Pages80to87    ((uint32_t)FLASH_WRP_WRPT_10) /* Write protection of page 80 to 87 */
#define FLASH_WRP_Pages88to95    ((uint32_t)FLASH_WRP_WRPT_11) /* Write protection of page 88 to 95 */
#define FLASH_WRP_Pages96to103   ((uint32_t)FLASH_WRP_WRPT_12) /* Write protection of page 96 to 103 */
#define FLASH_WRP_Pages104to111  ((uint32_t)FLASH_WRP_WRPT_13) /* Write protection of page 104 to 111 */
#define FLASH_WRP_Pages112to119  ((uint32_t)FLASH_WRP_WRPT_14) /* Write protection of page 112 to 119 */
#define FLASH_WRP_Pages120to127  ((uint32_t)FLASH_WRP_WRPT_15) /* Write protection of page 120 to 127 */
#define FLASH_WRP_Pages128to135  ((uint32_t)FLASH_WRP_WRPT_16) /* Write protection of page 128 to 135 */
#define FLASH_WRP_Pages136to143  ((uint32_t)FLASH_WRP_WRPT_17) /* Write protection of page 136 to 143 */
#define FLASH_WRP_Pages144to151  ((uint32_t)FLASH_WRP_WRPT_18) /* Write protection of page 144 to 151 */
#define FLASH_WRP_Pages152to159  ((uint32_t)FLASH_WRP_WRPT_19) /* Write protection of page 152 to 159 */
#define FLASH_WRP_Pages160to167  ((uint32_t)FLASH_WRP_WRPT_20) /* Write protection of page 160 to 167 */
#define FLASH_WRP_Pages168to175  ((uint32_t)FLASH_WRP_WRPT_21) /* Write protection of page 168 to 175 */
#define FLASH_WRP_Pages176to183  ((uint32_t)FLASH_WRP_WRPT_22) /* Write protection of page 176 to 183 */
#define FLASH_WRP_Pages184to191  ((uint32_t)FLASH_WRP_WRPT_23) /* Write protection of page 184 to 191 */
#define FLASH_WRP_Pages192to199  ((uint32_t)FLASH_WRP_WRPT_24) /* Write protection of page 192 to 199 */
#define FLASH_WRP_Pages200to207  ((uint32_t)FLASH_WRP_WRPT_25) /* Write protection of page 200 to 207 */
#define FLASH_WRP_Pages208to215  ((uint32_t)FLASH_WRP_WRPT_26) /* Write protection of page 208 to 215 */
#define FLASH_WRP_Pages216to223  ((uint32_t)FLASH_WRP_WRPT_27) /* Write protection of page 216 to 223 */
#define FLASH_WRP_Pages224to231  ((uint32_t)FLASH_WRP_WRPT_28) /* Write protection of page 224 to 231 */
#define FLASH_WRP_Pages232to239  ((uint32_t)FLASH_WRP_WRPT_29) /* Write protection of page 232 to 239 */
#define FLASH_WRP_Pages240to247  ((uint32_t)FLASH_WRP_WRPT_30) /* Write protection of page 240 to 247 */
#define FLASH_WRP_Pages248to255  ((uint32_t)FLASH_WRP_WRPT_31) /* Write protection of page 248 to 255 */
#define FLASH_WRP_AllPages       ((uint32_t)0xFFFFFFFFU)       /* Write protection of all Pages */


/* Functions used for N32G41X devices  */

/* Configuration */
void FLASH_SetLatency(uint32_t FLASH_Latency);
uint8_t FLASH_GetLatency(void);
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf);
FlagStatus Flash_GetPrefetchBufferStatus(void);

/* Cache management */
void FLASH_iCacheRST(void);
void FLASH_iCacheCmd(uint32_t FLASH_iCache);
void FLASH_StartCacheLock(uint32_t lock_start_way);
void FLASH_StopCacheLock(uint32_t lock_stop_way);
void FLASH_CancelCacheLock(uint32_t lock_stop_way);

/* Lock/Unlock */
void FLASH_Unlock(void);
void FLASH_Lock(void);
FlagStatus Flash_GetLockStatus(void);
void Option_Bytes_Unlock(void);
void Option_Bytes_Lock(void);
FlagStatus OB_GetLockStatus(void);

/* Erase */
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address);
FLASH_STS FLASH_MassErase(void);
FLASH_STS FLASH_EraseOB(void);

/* Program */
FLASH_STS FLASH_ProgramWord(uint32_t address, uint32_t data);

/* Option bytes programming */
FLASH_STS FLASH_ProgramOptionBytes_RDP1(uint8_t option_byte_rpd1);
FLASH_STS FLASH_ProgramOptionBytes_USER0(uint32_t option_byte_iwdg);
FLASH_STS FLASH_ProgramOptionBytes_USER1(uint32_t option_byte_PD7);
FLASH_STS FLASH_ProgramOptionBytes_USER3_USER2(uint32_t option_byte_nBOOT0, uint32_t option_byte_nBOOT1, \
                                               uint32_t option_byte_nSWBOOT0, uint32_t option_byte_BOOT0_CFG, \
                                               uint32_t option_byte_iwdg_stop, uint32_t option_byte_iwdg_sleep, \
                                               uint32_t option_byte_user2);
FLASH_STS FLASH_ProgramOptionBytes_USER5_USER4(uint32_t option_byte_user4, uint32_t option_byte_user5);
FLASH_STS FLASH_ProgramOptionBytes_USER6(uint32_t option_byte_user6);
FLASH_STS FLASH_ProgramOptionBytes_USER7(uint32_t option_byte_user7);
FLASH_STS FLASH_ProgramOptionBytes_DATA1_DATA0(uint8_t option_byte_data1, uint8_t option_byte_data0);

/* Write protection */
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages);

/* Read protection */
FLASH_STS FLASH_ProgramOptionBytes_RDP2(uint8_t option_byte_rpd2);
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd);
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void);

/* Option bytes read */
FlagStatus FLASH_GetOptionBytes_User0(void);
FlagStatus FLASH_GetOptionBytes_User1(void);
uint32_t FLASH_GetOptionBytes_User2(void);
FlagStatus FLASH_GetOptionBytes_User3(uint32_t option_byte_bit);
uint32_t FLASH_GetBOOTUartPIN(void);
uint32_t FLASH_GetBOOTI2cPIN(void);
uint32_t FLASH_GetBOOTCanPIN(void);
uint32_t FLASH_GetOptionBytes_Data0(void);
uint32_t FLASH_GetOptionBytes_Data1(void);

/* Status and protection status */
FlagStatus FLASH_GetReadOutProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionL2STS(void);
uint32_t FLASH_GetWriteProtectionSTS(void);
FlagStatus FLASH_GetBOOTWriteProtectionSTS(void);

/* Interrupt and flag management */
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd);
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG);
FlagStatus FLASH_GetOBFlagSTS(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_STS FLASH_GetSTS(void);
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout);







#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_FLASH_H__ */
