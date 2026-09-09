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
*\*\file n32g41x_pwr.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#ifndef __N32G41X_PWR_H__
#define __N32G41X_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"

#define PWR_REG_BIT_MASK         ((uint32_t)0x00000000)

/** PWR CTRL register bit mask definition **/
#define PWR_CTRL_NRSTCNT_MASK    (~(PWR_CTRL_NRSTCNT))
#define PWR_CTRL_PLS_MASK        (~(PWR_CTRL_PLS))
#define PWR_CTRL_PVDCNT_MASK     (~(PWR_CTRL_PVDCNT))

/** PWR IWDR reset enable definition **/
#define PWR_IWDGRST_ENABLE       (PWR_CTRL_IWDGRSTEN)

/** PWR PVD threshold level definition **/
#define PWR_PVD_LEVEL_2V0 ((uint32_t)(PWR_CTRL_PLS_0))    /* 2.0v PWR_CTRL bit[8:5]:0001 */
#define PWR_PVD_LEVEL_2V2 ((uint32_t)(PWR_CTRL_PLS_1))    /* 2.2v PWR_CTRL bit[8:5]:0010 */
#define PWR_PVD_LEVEL_2V4 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1))    /* 2.4v PWR_CTRL bit[8:5]:0011 */
#define PWR_PVD_LEVEL_2V6 ((uint32_t)(PWR_CTRL_PLS_2))    /* 2.6v PWR_CTRL bit[8:5]:0100 */
#define PWR_PVD_LEVEL_2V8 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_2))    /* 2.8v PWR_CTRL bit[8:5]:0101 */
#define PWR_PVD_LEVEL_3V0 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))    /* 3.0v PWR_CTRL bit[8:5]:0110 */
#define PWR_PVD_LEVEL_3V2 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))    /* 3.2v PWR_CTRL bit[8:5]:0111 */
#define PWR_PVD_LEVEL_3V4 ((uint32_t)(PWR_CTRL_PLS_3))    /* 3.4v PWR_CTRL bit[8:5]:1000 */
#define PWR_PVD_LEVEL_3V6 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_3))    /* 3.6v PWR_CTRL bit[8:5]:1001 */
#define PWR_PVD_LEVEL_3V8 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_3))    /* 3.8v PWR_CTRL bit[8:5]:1010 */
#define PWR_PVD_LEVEL_4V0 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_3))    /* 4.0v PWR_CTRL bit[8:5]:1011 */
#define PWR_PVD_LEVEL_4V2 ((uint32_t)(PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.2v PWR_CTRL bit[8:5]:1100 */
#define PWR_PVD_LEVEL_4V4 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.4v PWR_CTRL bit[8:5]:1101 */
#define PWR_PVD_LEVEL_4V6 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.6v PWR_CTRL bit[8:5]:1110 */
#define PWR_PVD_LEVEL_4V8 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.8v PWR_CTRL bit[8:5]:1111 */	 

/** PWR registers write protection keys definition **/
#define PWR_CTRL2_KEYS             ((uint32_t)0x57103616U)
#define PWR_CTRL2_KEY              ((uint32_t)0xFFFFFFFFU) 
#define PWR_CTRL2_KEYS_MASK        (~PWR_CTRL2_KEY)

#define PWR_MRLPMODE_FIXED         (PWR_REG_BIT_MASK)
#define PWR_MRLPMODE_AUTO          (PWR_CTRL2_MRLPEN)

/** PWR sleep status definition **/
#define PWR_SLEEP_NOW              ((uint8_t)0x00)
#define PWR_SLEEP_ON_EXIT          ((uint8_t)0x01)

/** PWR SLEEP mode entry definition **/
#define PWR_SLEEPENTRY_WFI         ((uint8_t)0x01) /* enter SLEEP mode with WFI instruction */
#define PWR_SLEEPENTRY_WFE         ((uint8_t)0x02) /* enter SLEEP mode with WFE instruction */

/** PWR STOP mode entry definition **/
#define PWR_STOPENTRY_WFI          ((uint8_t)0x01) /* enter STOP mode with WFI instruction */
#define PWR_STOPENTRY_WFE          ((uint8_t)0x02) /* enter STOP mode with WFE instruction */


/** PWR PVD output Flag definition **/
#define PWR_PVDO_FLAG              (PWR_STS_PVDO)

/*** PWR Macro Definition End ***/

/*** PWR Driving Functions Declaration ***/
/* PVD configuration */
void PWR_PvdEnable(FunctionalState Cmd);
void PWR_PVDFilterWidthSet(uint8_t filter_value);
void PWR_PVDLevelConfig(uint32_t level);

/* Reset configuration */
void PWR_NRSTFilterWidthSet(uint16_t filter_value);
void PWR_EnableIWDGReset(FunctionalState Cmd);

/* Low-power mode */
void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint8_t enter_mode);
void PWR_ConfigMRLPMode(uint32_t Mode);
void PWR_ConfigMRLPDelay(uint16_t delay_value);

/* Write protection */
void PWR_CTRL2WriteProtectionEnable(void);

/* Flag management */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_PWR_H__ */
