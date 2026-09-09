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
*\*\file n32g41x_comp.h
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __N32G41X_COMP_H__
#define __N32G41X_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include <stdbool.h> 

/** @addtogroup N32G41X_StdPeriph_Driver
 * @{
 */

/** @addtogroup COMP
 * @{
 */
typedef enum
{
    COMP1 = 0x0U,
    COMP2 = 0x1U,
    COMP3 = 0x2U,
} COMPX;


/** COMP switch definition **/
#define COMP_ENABLE_MASK                  ((uint32_t)COMPx_CTRL_EN)

/** COMP Out mask definition **/
#define COMP_OUT_MASK                     ((uint32_t)COMPx_CTRL_OUT)

/** COMP clock mask definition **/
#define COMP_CLKSEL_SYSTEMCLK             ((uint32_t)0x00000000U) 
#define COMP_CLKSEL_LSX                   ((uint32_t)COMPx_CTRL_CLKSEL)

/** COMP operation mode definition **/
#define COMP_CTRL_PWRMD_NORMAL            ((uint32_t)0x00000000U) 
#define COMP_CTRL_PWRMD_LOWPWR            ((uint32_t)COMPx_CTRL_PWRMD)

/** COMP output polarity definition **/
#define COMP_OUTPOL_REV                   ((uint32_t)COMPx_CTRL_POL)
#define COMP_OUTPOL_NREV                  ((uint32_t)0x00000000U)

/** COMP non inverting input definition **/
#define COMP_INPSEL_MASK                  (COMPx_CTRL_INPSEL)

/** COMP inverting input definition **/
#define COMP_INMSEL_MASK                  (COMPx_CTRL_INMSEL)

typedef enum {
  COMP_INPSEL_RES           = (0x0U << 1U),
  /*comp1 inp sel*/
  COMP1_INPSEL_PA0          = (0x0U << 1U),
  COMP1_INPSEL_PA1          = (0x1U << 1U),
  COMP1_INPSEL_PA2          = (0x2U << 1U),
  COMP1_INPSEL_PA3          = (0x3U << 1U),
  COMP1_INPSEL_PA6          = (0x4U << 1U),
  COMP1_INPSEL_PA12         = (0x5U << 1U),
  COMP1_INPSEL_PB2          = (0x6U << 1U),
  COMP1_INPSEL_PB3          = (0x7U << 1U),
  COMP1_INPSEL_PB4          = (0x8U << 1U),
  COMP1_INPSEL_PB10         = (0x9U << 1U),
  COMP1_INPSEL_PC5          = (0xAU << 1U),
  COMP1_INPSEL_VREF_VC1     = (0xBU << 1U),
  /*comp2 inp sel*/
  COMP2_INPSEL_PA1          = (0x0U << 1U),
  COMP2_INPSEL_PA3          = (0x1U << 1U),
  COMP2_INPSEL_PA6          = (0x2U << 1U),
  COMP2_INPSEL_PA7          = (0x3U << 1U),
  COMP2_INPSEL_PA11         = (0x4U << 1U),
  COMP2_INPSEL_PA15         = (0x5U << 1U),
  COMP2_INPSEL_PB0          = (0x6U << 1U),
  COMP2_INPSEL_PB4          = (0x7U << 1U),
  COMP2_INPSEL_PB6          = (0x8U << 1U),
  COMP2_INPSEL_PB7          = (0x9U << 1U),
  COMP2_INPSEL_PB11         = (0xAU << 1U),
  COMP2_INPSEL_PB12         = (0xBU << 1U),
  COMP2_INPSEL_VREF_VC2     = (0xCU << 1U),
  /*comp3 inp sel*/
  COMP3_INPSEL_PA5          = (0x0U << 1U),
  COMP3_INPSEL_PA11         = (0x1U << 1U),
  COMP3_INPSEL_PB0          = (0x2U << 1U),
  COMP3_INPSEL_PB1          = (0x3U << 1U),
  COMP3_INPSEL_PB11         = (0x4U << 1U),
  COMP3_INPSEL_PB12         = (0x5U << 1U),
  COMP3_INPSEL_PB14         = (0x6U << 1U),
  COMP3_INPSEL_VREF_VC3     = (0x7U << 1U),
}COMP_CTRL_INPSEL;

typedef enum {
  COMP_INMSEL_RES           = (0x0U << 5U),
  /*comp1 inm sel*/
  COMP1_INMSEL_PA0          = (0x0U << 5U),
  COMP1_INMSEL_PA4          = (0x1U << 5U),
  COMP1_INMSEL_PA5          = (0x2U << 5U),
  COMP1_INMSEL_PB1          = (0x3U << 5U),
  COMP1_INMSEL_PB5          = (0x4U << 5U),
  COMP1_INMSEL_PC4          = (0x5U << 5U),
  COMP1_INMSEL_VREF_VC1     = (0x6U << 5U),
   /*comp2 inm sel*/
  COMP2_INMSEL_PA4          = (0x0U << 5U),
  COMP2_INMSEL_PA2          = (0x1U << 5U),
  COMP2_INMSEL_PA5          = (0x2U << 5U),
  COMP2_INMSEL_PA6          = (0x3U << 5U),
  COMP2_INMSEL_PB3          = (0x4U << 5U),
  COMP2_INMSEL_PB7          = (0x5U << 5U),
  COMP2_INMSEL_VREF_VC2     = (0x6U << 5U),
  /*comp3 inm sel*/
  COMP3_INMSEL_PA5          = (0x0U << 5U),
  COMP3_INMSEL_PA12         = (0x1U << 5U),
  COMP3_INMSEL_PB1          = (0x2U << 5U),
  COMP3_INMSEL_PB11         = (0x3U << 5U),
  COMP3_INMSEL_PB14         = (0x4U << 5U),
  COMP3_INMSEL_VREF_VC3     = (0x5U << 5U),
}COMP_CTRL_INMSEL;

typedef enum
{
  COMP_HYST_NO              = (0x0L << 12U),
  COMP_HYST_LOW             = (0x1L << 12U),
  COMP_HYST_MID             = (0x2L << 12U),
  COMP_HYST_HIGH            = (0x3L << 12U),
} COMP_CTRL_HYST;

typedef enum
{
  COMP_BLKING_NO            = (0x0L << 16U),
  COMP_BLKING_ATIM1_OC5     = (0x1L << 16U),
  COMP_BLKING_ATIM2_OC5     = (0x2L << 16U),
  COMP_BLKING_ATIM1_OC4     = (0x3L << 16U),
  COMP_BLKING_GTIM1_OC3     = (0x4L << 16U),
  COMP_BLKING_GTIM2_OC3     = (0x5L << 16U),
  COMP_BLKING_ATIM2_OC1     = (0x6L << 16U),
} COMP_CTRL_BLKING;

/** COMP filter prescale definition **/
#define COMP_FILTER_CLKPSC_MASK           (COMPx_FILP_CLKPSC) /* Low filter sample clock prescale mask*/

/** COMP blanking definition **/
#define COMP_BLANKING_MASK                (COMPx_CTRL_BLKING)

/** COMP double hysteresis mask definition **/
#define COMP_DPUBLEHYST_MASK              (COMPx_CTRL_DOUHYSIEN)

#define COMP_DPUBLEHYST_EN                (COMPx_CTRL_DOUHYSIEN)
#define COMP_DPUBLEHYST_DIS               (0x00000000U)

#define COMP_POL_MASK                     (COMPx_CTRL_POL)
/** COMP hysteresis mask definition **/
#define COMP_HYST_MASK                    (COMPx_CTRL_HYST)

/** COMP_WINMODE  **/
#define COMP_WINMODE_CMPMD_MSK                      (COMP_WINMODE_COMP12MD|COMP_WINMODE_COMP23MD)
#define COMP_WINMODE_CMP23MD                        (COMP_WINMODE_COMP23MD)/* Comparators 2 and 3 can be used in window mode.*/
#define COMP_WINMODE_CMP12MD                        (COMP_WINMODE_COMP12MD)/* Comparators 1 and 2 can be used in window mode.*/

/** COMP Lock definition **/
#define COMP1_LOCK                        (COMP_LOCK_CMP1LK)
#define COMP2_LOCK                        (COMP_LOCK_CMP2LK)
#define COMP3_LOCK                        (COMP_LOCK_CMP3LK)

/** COMP_VREFSCL   **/
#define COMP_VREFSCL_VVxEN_MSK            (COMP_INVREF_VREFEN)
#define COMP_VREFSCL_VVxTRM_MSK           (COMP_INVREF_VREFSEL)

/** COMP init structure definition **/
typedef struct
{
    uint32_t ClockSelect;        /* Specifies the comp clock select during STOP and lowpower run mode */	
    uint32_t LowPoweMode;        /* Specifies the comp operation mode switch bit */		
	  
	  COMP_CTRL_BLKING Blking;     /* Specifies which timer can control the comp output blanking with its capture event */
    uint32_t DoubleHyst;         /* Specifies the comp double hysteresis selection */
    COMP_CTRL_HYST Hyst;         /* Specifies the comp hysteresis level with low/medium/high level */
    uint32_t PolRev;             /* Specifies the comp output polarity */
    COMP_CTRL_INPSEL InpSel;     /* Specifies the comp inpsel */
    COMP_CTRL_INMSEL InmSel;     /* Specifies the comp inmsel */
    FunctionalState En;          /* enable or disable the comp */

    /* filter define */
    uint8_t SampWindow;          /* Initializes comp sampwindow value ~5bit */
    uint8_t Threshold;           /* ~5bit ,need > SampWindow/2 */
    FunctionalState FilterEn;    /* enable or disable the comp filter */

    /* filter prescale */
    uint16_t ClkPsc;             /* Initializes comp clkpsc value ~5bit */
}COMP_InitType;

/*** COMP Driving Functions Declaration ***/

/* Reset and initialization */
void COMP_DeInit(void);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);
void COMP_Init(COMPX COMPx, const COMP_InitType* COMP_InitStruct);
void COMP_Enable(COMPX COMPx, FunctionalState Cmd);

/* Input and output configuration */
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel);
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel);
void COMP_OutputPolarityConfig(COMPX COMPx, uint32_t POL);

/* Hysteresis and blanking configuration */
void COMP_SetHyst(COMPX COMPx, COMP_CTRL_HYST HYST);
void COMP_EnableDoubleHyst(COMPX COMPx, FunctionalState Cmd);
void COMP_SetBlanking(COMPX COMPx, COMP_CTRL_BLKING BLK);

/* Filter configuration */
void COMP_SetFilterControl(COMPX COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW);
void COMP_SetFilterPrescaler(COMPX COMPx, uint16_t FilPreVal);

/* Low-power and lock configuration */
void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd);
void COMP_SetLock(uint32_t Lock);
void COMP_StopOrLowpower32KClkSel(COMPX COMPx, FunctionalState Cmd);
void COMP_StopOrLowpowerMode(COMPX COMPx, FunctionalState Cmd);

/* Voltage reference configuration */
void COMP_SetRefScl(uint8_t Vv3Trim, bool Vv3En, uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En);

/* Output status, interrupt and flag management */
FlagStatus COMP_GetOutStatus(COMPX COMPx);
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd);
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx);
void COMP_ClearIntStsOneComp(COMPX COMPx);
#ifdef __cplusplus
}
#endif

#endif /*__N32G41X_COMP_H__ */

