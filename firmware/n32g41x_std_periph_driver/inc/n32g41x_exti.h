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

/***
*\*\file n32g41x_exti.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
***/
#ifndef __N32G41X_EXTI_H__
#define __N32G41X_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"

/*** EXTI Structure Definition Start ***/

/** EXTI mode enumeration **/
typedef enum
{
    EXTI_Mode_Event      = 0x00U,
    EXTI_Mode_Interrupt  = 0x04U
} EXTI_ModeType;

/** EXTI Trigger enumeration **/
typedef enum
{   
    EXTI_Trigger_Falling        = 0x08U,
    EXTI_Trigger_Rising         = 0x0CU,    
    EXTI_Trigger_Rising_Falling  = 0x10U
} EXTI_TriggerType;

/** EXTI Init Structure definition **/
typedef struct
{
    uint32_t EXTI_Line;   /* < Specifies the EXTI lines to be enabled or disabled */

    EXTI_ModeType EXTI_Mode;    /* < Specifies the mode for the EXTI lines */

    EXTI_TriggerType EXTI_Trigger; /* < Specifies the trigger signal active edge for the EXTI lines */
    
    FunctionalState EXTI_LineCmd;  /* Specifies the new state of the selected EXTI lines. */
} EXTI_InitType;



/*** EXTI Structure Definition End ***/

/*** EXTI Macro Definition Start ***/


/** EXTI_Lines **/
#define EXTI_LINENONE ((uint32_t)0x000000000)  /** No interrupt selected */
#define EXTI_LINE0    ((uint32_t)0x00000001)   /** External interrupt line 0 */
#define EXTI_LINE1    ((uint32_t)0x00000002)   /** External interrupt line 1 */
#define EXTI_LINE2    ((uint32_t)0x00000004)   /** External interrupt line 2 */
#define EXTI_LINE3    ((uint32_t)0x00000008)   /** External interrupt line 3 */
#define EXTI_LINE4    ((uint32_t)0x00000010)   /** External interrupt line 4 */
#define EXTI_LINE5    ((uint32_t)0x00000020)   /** External interrupt line 5 */
#define EXTI_LINE6    ((uint32_t)0x00000040)   /** External interrupt line 6 */
#define EXTI_LINE7    ((uint32_t)0x00000080)   /** External interrupt line 7 */
#define EXTI_LINE8    ((uint32_t)0x00000100)   /** External interrupt line 8 */
#define EXTI_LINE9    ((uint32_t)0x00000200)   /** External interrupt line 9 */
#define EXTI_LINE10   ((uint32_t)0x00000400)   /** External interrupt line 10 */
#define EXTI_LINE11   ((uint32_t)0x00000800)   /** External interrupt line 11 */
#define EXTI_LINE12   ((uint32_t)0x00001000)   /** External interrupt line 12 */
#define EXTI_LINE13   ((uint32_t)0x00002000)   /** External interrupt line 13 */
#define EXTI_LINE14   ((uint32_t)0x00004000)   /** External interrupt line 14 */
#define EXTI_LINE15   ((uint32_t)0x00008000)   /** External interrupt line 15 */
#define EXTI_LINE16   ((uint32_t)0x00010000)   /** External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE17   ((uint32_t)0x00020000)   /** External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_LINE18   ((uint32_t)0x00040000)   /** External interrupt line 18 Connected to the RTC Timestamp and LSECSS event */
#define EXTI_LINE19   ((uint32_t)0x00080000)   /** External interrupt line 19 Connected to the RTC Wakeup event */
#define EXTI_LINE20   ((uint32_t)0x00100000)   /** External interrupt line 20 Connected to the BTIM1 Global event */
#define EXTI_LINE21   ((uint32_t)0x00200000)   /** External interrupt line 21 Connected to the COMP1 Global interrupt */
#define EXTI_LINE22   ((uint32_t)0x00400000)   /** External interrupt line 22 Connected to the COMP2 Global interrupt */
#define EXTI_LINE23   ((uint32_t)0x00800000)   /** External interrupt line 23 Connected to the COMP3 Global interrupt */
#define EXTI_LINE24   ((uint32_t)0x01000000)   /** External interrupt line 24 Connected to the USART1 Wakeup interrupt */
#define EXTI_LINE25   ((uint32_t)0x02000000)   /** External interrupt line 25 Connected to the USART4 Wakeup interrupt */
#define EXTI_LINEALL  ((uint32_t)0x03FFFFFF)   


#define EXTI_TSSEL_LINE_MASK ((uint32_t)0x00000)
#define EXTI_TSSEL_LINE0     ((uint32_t)0x00000) /** External interrupt line 0 */
#define EXTI_TSSEL_LINE1     ((uint32_t)0x00001) /** External interrupt line 1 */
#define EXTI_TSSEL_LINE2     ((uint32_t)0x00002) /** External interrupt line 2 */
#define EXTI_TSSEL_LINE3     ((uint32_t)0x00003) /** External interrupt line 3 */
#define EXTI_TSSEL_LINE4     ((uint32_t)0x00004) /** External interrupt line 4 */
#define EXTI_TSSEL_LINE5     ((uint32_t)0x00005) /** External interrupt line 5 */
#define EXTI_TSSEL_LINE6     ((uint32_t)0x00006) /** External interrupt line 6 */
#define EXTI_TSSEL_LINE7     ((uint32_t)0x00007) /** External interrupt line 7 */
#define EXTI_TSSEL_LINE8     ((uint32_t)0x00008) /** External interrupt line 8 */
#define EXTI_TSSEL_LINE9     ((uint32_t)0x00009) /** External interrupt line 9 */
#define EXTI_TSSEL_LINE10    ((uint32_t)0x0000A) /** External interrupt line 10 */
#define EXTI_TSSEL_LINE11    ((uint32_t)0x0000B) /** External interrupt line 11 */
#define EXTI_TSSEL_LINE12    ((uint32_t)0x0000C) /** External interrupt line 12 */
#define EXTI_TSSEL_LINE13    ((uint32_t)0x0000D) /** External interrupt line 13 */
#define EXTI_TSSEL_LINE14    ((uint32_t)0x0000E) /** External interrupt line 14 */
#define EXTI_TSSEL_LINE15    ((uint32_t)0x0000F) /** External interrupt line 15 */


/*** EXTI Macro Definition End ***/

/** EXTI Driving Functions Declaration **/

/* Reset/Init */
void EXTI_DeInit(void);
void EXTI_InitPeripheral(const EXTI_InitType* EXTI_InitParam);
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct);

/* Interrupt and flag management */
void EXTI_TriggerSWInt(uint32_t EXTI_Line);
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line);
void EXTI_ClrStatusFlag(uint32_t EXTI_Line);
INTStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClrITPendBit(uint32_t EXTI_Line);

/* Configuration */
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line);

#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_EXTI_H__ */

