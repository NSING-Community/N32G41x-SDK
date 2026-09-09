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
*\*\file n32g41x_opamp.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#ifndef __N32G41X_OPAMPMP_H__
#define __N32G41X_OPAMPMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include <stdbool.h>

/** N32G41X_StdPeriph_Driver    */

/**  OPAMP      */

/** OPAMP_Exported_Constants  */
typedef enum
{
    OPAMP1 = 0x0U,
    OPAMP2 = 0x1U,
    OPAMP3 = 0x2U,
    OPAMP4 = 0x3U
} OPAMPX;




/*OPAMPx_VREFSEL bit:18*/
#define OPAMP_VREF_SEL_MASK              ((uint32_t)OPAMPx_CS_VREFSEL)
#define OPAMP_VREF_SEL_0_1VDD            ((uint32_t)0x00000000U)           //0.1*VDDA
#define OPAMP_VREF_SEL_0_9VDD            ((uint32_t)OPAMPx_CS_VREFSEL)      //0.9*VDDA
 
/*  OPAMP_CS_CALOUT bit:17  */
#define OPAMP_CS_CALOUT_MASK              ((uint32_t)OPAMPx_CS_CALOUT)

/*  OPAMP_CS_CALEN bit:16  */
#define OPAMP_CS_CALEN_MASK              ((uint32_t)OPAMPx_CS_CALEN)
#define OPAMP_CS_CALEN_ENABLE            ((uint32_t)OPAMPx_CS_CALEN)
#define OPAMP_CS_CALEN_DISABLE           ((uint32_t)0x00000000U)

typedef enum
{
    OPAMP1_CS_VMSSEL_PA3        = (0x00L << 14U),
    OPAMP1_CS_VMSSEL_PC5        = (0x01L << 14U),
    OPAMP1_CS_VMSSEL_PA0        = (0x02L << 14U),
    OPAMP1_CS_VMSSEL_FLOAT      = (0x03U << 14U),
    
    OPAMP2_CS_VMSSEL_PA5        = (0x00L << 14U),
    OPAMP2_CS_VMSSEL_PC5        = (0x01L << 14U),
    OPAMP2_CS_VMSSEL_PB0        = (0x02L << 14U),
    OPAMP2_CS_VMSSEL_FLOAT      = (0x03U << 14U),
    
    OPAMP3_CS_VMSSEL_PC4        = (0x00L << 14U),
    OPAMP3_CS_VMSSEL_PB10       = (0x01L << 14U),
    OPAMP3_CS_VMSSEL_NC         = (0x02U << 14U), 
    OPAMP3_CS_VMSSEL_FLOAT      = (0x03U << 14U),
    
    OPAMP4_CS_VMSSEL_PB10       = (0x00L << 14U),
    OPAMP4_CS_VMSSEL_PB1        = (0x01L << 14U),
    OPAMP4_CS_VMSSEL_PA5        = (0x02L << 14U),
    OPAMP4_CS_VMSSEL_FLOAT      = (0x03U << 14U),
}OPAMP_CS_VMSSEL;

typedef enum
{
    OPAMP1_CS_VPSSEL_PA1        = (0x00L << 12U),
    OPAMP1_CS_VPSSEL_PA5        = (0x01L << 12U),
    OPAMP1_CS_VPSSEL_PA4        = (0x02L << 12U),
    OPAMP1_CS_VPSSEL_PA7        = (0x03L << 12U),
    
    OPAMP2_CS_VPSSEL_PA7        = (0x00L << 12U),
    OPAMP2_CS_VPSSEL_PA4        = (0x01L << 12U),
    OPAMP2_CS_VPSSEL_PB0        = (0x02L << 12U),
    OPAMP2_CS_VPSSEL_PB14       = (0x03L << 12U),
    
    OPAMP3_CS_VPSSEL_PB2        = (0x00L << 12U),
    OPAMP3_CS_VPSSEL_PA1        = (0x01L << 12U),
    OPAMP3_CS_VPSSEL_PA5        = (0x02L << 12U),
    OPAMP3_CS_VPSSEL_PC3        = (0x03L << 12U),
    
    OPAMP4_CS_VPSSEL_PA4        = (0x00L << 12U),
    OPAMP4_CS_VPSSEL_PC5        = (0x01L << 12U),
    OPAMP4_CS_VPSSEL_PB13       = (0x02L << 12U),
    OPAMP4_CS_VPSSEL_PA7        = (0x03L << 12U),
}OPAMP_CS_VPSSEL;

typedef enum
{
    OPAMP1_CS_VMSEL_PA3        = (0x00L << 10U),
    OPAMP1_CS_VMSEL_PC5        = (0x01L << 10U),
    OPAMP1_CS_VMSEL_PA0        = (0x02L << 10U),
    OPAMP1_CS_VMSEL_FLOAT      = (0x03U << 10U),
    
    OPAMP2_CS_VMSEL_PA5        = (0x00L << 10U),
    OPAMP2_CS_VMSEL_PC5        = (0x01L << 10U),
    OPAMP2_CS_VMSEL_PB0        = (0x02L << 10U),
    OPAMP2_CS_VMSEL_FLOAT      = (0x03U << 10U),
    
    OPAMP3_CS_VMSEL_PC4        = (0x00L << 10U),
    OPAMP3_CS_VMSEL_PB10       = (0x01L << 10U),
    OPAMP3_CS_VMSEL_NC         = (0x02U << 10U), 
    OPAMP3_CS_VMSEL_FLOAT      = (0x03U << 10U),
    
    OPAMP4_CS_VMSEL_PB10       = (0x00L << 10U),
    OPAMP4_CS_VMSEL_PB1        = (0x01L << 10U),
    OPAMP4_CS_VMSEL_PA5        = (0x02L << 10U),
    OPAMP4_CS_VMSEL_FLOAT      = (0x03U << 10U),
}OPAMP_CS_VMSEL;

typedef enum
{
    OPAMP1_CS_VPSEL_PA1        = (0x00L << 8U),
    OPAMP1_CS_VPSEL_PA5        = (0x01L << 8U),
    OPAMP1_CS_VPSEL_PA4        = (0x02L << 8U),
    OPAMP1_CS_VPSEL_PA7        = (0x03L << 8U),
    
    OPAMP2_CS_VPSEL_PA7        = (0x00L << 8U),
    OPAMP2_CS_VPSEL_PA4        = (0x01L << 8U),
    OPAMP2_CS_VPSEL_PB0        = (0x02L << 8U),
    OPAMP2_CS_VPSEL_PB14       = (0x03L << 8U),
    
    OPAMP3_CS_VPSEL_PB2        = (0x00L << 8U),
    OPAMP3_CS_VPSEL_PA1        = (0x01L << 8U),
    OPAMP3_CS_VPSEL_PA5        = (0x02L << 8U),
    OPAMP3_CS_VPSEL_PC3        = (0x03L << 8U),
    
    OPAMP4_CS_VPSEL_PA4        = (0x00L << 8U),
    OPAMP4_CS_VPSEL_PC5        = (0x01L << 8U),
    OPAMP4_CS_VPSEL_PB13       = (0x02L << 8U),
    OPAMP4_CS_VPSEL_PA7        = (0x03L << 8U),
}OPAMP_CS_VPSEL;

/*  OPAMP_CS_GAIN bit:5:3 for OPAMP */
typedef enum
{
    OPAMP_CS_PGA_GAIN_2  = (0x00U << 3U),
    OPAMP_CS_PGA_GAIN_4  = (0x01U << 3U),
    OPAMP_CS_PGA_GAIN_8  = (0x02U << 3U),
    OPAMP_CS_PGA_GAIN_16 = (0x03U << 3U),
    OPAMP_CS_PGA_GAIN_32 = (0x04U << 3U),
}OPAMP_CS_PGA_GAIN;

/*  OPAMP_CS_MODE bit:2:1  */ 
typedef enum
{
    OPAMP_CS_EXT_OPAMP   = (0x00U << 1U),
    OPAMP_CS_PGA_EN      = (0x02U << 1U),
    OPAMP_CS_FOLLOW      = (0x03U << 1U),
} OPAMP_CS_MOD;


#define OPAMP_CS_MODE_MASK              (OPAMPx_CS_MOD)
#define OPAMP_CS_PGA_GAIN_MASK          (OPAMPx_CS_GAIN)
#define OPAMP_CS_VMSSEL_MASK            (OPAMPx_CS_VMSSEL)
#define OPAMP_CS_VPSSEL_MASK            (OPAMPx_CS_VPSSEL)
#define OPAMP_CS_VMSEL_MASK             (OPAMPx_CS_VMSEL)
#define OPAMP_CS_VPSEL_MASK             (OPAMPx_CS_VPSEL)
/*OPA enable mask */
#define OPAMP_EN_MASK                   ((uint32_t)OPAMPx_CS_EN)

/*OPAMP_LOCK */
#define OPAMP1_LOCK                     ((uint32_t)OPAMP_LOCK_OPAMP1LK)
#define OPAMP2_LOCK                     ((uint32_t)OPAMP_LOCK_OPAMP2LK)
#define OPAMP3_LOCK                     ((uint32_t)OPAMP_LOCK_OPAMP3LK)
#define OPAMP4_LOCK                     ((uint32_t)OPAMP_LOCK_OPAMP4LK)


/**    OPAMP Init structure definition  */
typedef struct
{
    OPAMP_CS_PGA_GAIN Gain;         /*see @OPAMP_CS_PGA_GAIN*/ 
    OPAMP_CS_MOD Mode;              /*see @OPAMP_CS_MOD*/ 
    OPAMP_CS_VPSEL OPAMP_Vpsel;     /*see @OPAMP_CS_VPSEL*/ 
    OPAMP_CS_VMSEL OPAMP_Vmsel;     /*see @OPAMP_CS_VMSEL*/ 
    OPAMP_CS_VPSSEL OPAMP_Vpssel;   /*see @OPAMP_CS_VPSSEL*/ 
    OPAMP_CS_VMSSEL OPAMP_Vmssel;   /*see @OPAMP_CS_VMSSEL*/ 
    uint32_t CALEN;
    uint32_t VREFSEL;
} OPAMP_InitType;



/* Reset and init */
void OPAMP_DeInit(void);
void OPAMP_StructInit(OPAMP_InitType* OPAMP_InitStruct);
void OPAMP_Init(OPAMPX OPAMPx, const OPAMP_InitType* OPAMP_InitStruct);

/* Enable and disable */
void OPAMP_Enable(OPAMPX OPAMPx, FunctionalState Cmd);

/* Configuration */
void OPAMP_SetWorkMode(OPAMPX OPAMPx, OPAMP_CS_MOD Mode);
void OPAMP_SetPgaGain(OPAMPX OPAMPx, OPAMP_CS_PGA_GAIN Gain);
void OPAMP_SetVpSel(OPAMPX OPAMPx, OPAMP_CS_VPSEL VpSel);
void OPAMP_SetVmSel(OPAMPX OPAMPx, OPAMP_CS_VMSEL VmSel);
void OPAMP_SetVmSecondSel(OPAMPX OPAMPx, OPAMP_CS_VMSSEL VmsSel);
void OPAMP_SetVpSecondSel(OPAMPX OPAMPx, OPAMP_CS_VPSSEL VpsSel);
void OPAMP_VREFSel(OPAMPX OPAMPx, uint32_t VrefSel);

/* Lock */
void OPAMP_SetLock(uint32_t Lock);

/* Calibration */
void OPAMP_CalEn(OPAMPX OPAMPx, FunctionalState Cmd);
bool OPAMP_IsCalOutHigh(OPAMPX OPAMPx);


#ifdef __cplusplus
}
#endif

#endif /*__N32G41X_OPAMPMP_H__ */

