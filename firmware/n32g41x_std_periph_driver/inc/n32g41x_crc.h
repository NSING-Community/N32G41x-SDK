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
*\*\file n32g41x_crc.h
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/

#ifndef __N32G41X_CRC_H__
#define __N32G41X_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"

/*** CRC clear the CRC16 check value definition ***/
#define CRC_CRC16_VALUE_CLEAR    ((uint32_t)CRC16_CTRL_RESET)
#define CRC_CRC16_VALUE_NO_CLEAR_MASK ((uint32_t)CRC16_CTRL_NO_RESET)

/*** CRC16D check value definition ***/
#define CRC_CRC16D_CLEAR_VALUE   ((uint16_t)0x0000U)           /* Clear CRC16D to 0x0000 */

/*** CRC little-endian and big-endian definition ***/
#define CRC_LITTLE_ENDIAN_ENABLE ((uint32_t)CRC16_CTRL_LITTLE) /* Set little-endian */
#define CRC_BIG_ENDIAN_MASK    ((uint32_t)CRC16_CTRL_BIG)    /* Set big-endian */

/* CRC32 calculation */
void CRC32_ResetCrc(void);
uint32_t CRC32_CalcCrc(uint32_t Data);
uint32_t CRC32_CalcBufCrc(const uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC32_GetCrc(void);
void CRC32_SetIDat(uint8_t IDValue);
uint8_t CRC32_GetIDat(void);

/* CRC16 low-level configuration */
void __CRC16_SetLittleEndianFmt(void);
void __CRC16_SetBigEndianFmt(void);
void __CRC16_SetCleanEnable(void);
void __CRC16_SetCleanDisable(void);

/* CRC16 calculation */
uint16_t __CRC16_CalcCrc(uint8_t Data);
void __CRC16_SetCrc(uint8_t Data);
uint16_t __CRC16_GetCrc(void);
uint16_t CRC16_CalcBufCrc(const uint8_t pBuffer[], uint32_t BufferLength);
uint16_t CRC16_CalcCRC(uint8_t Data);

/* CRC16 LRC */
void __CRC16_SetLRC(uint8_t Data);
uint8_t __CRC16_GetLRC(void);

#ifdef __cplusplus
}
#endif
#endif /* __N32G41X_CRC_H__ */

