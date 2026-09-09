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
*\*\file n32g41x_adc.h
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/


#ifndef __N32G41X_ADC_H__
#define __N32G41X_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include <stdbool.h>


/** ADC_Exported_Types **/
#define ADC_SR_CLR(X) (X=0XFFFFFFFF)
#define ADC_SR_CLR1(X,CLR_Value) (X=CLR_Value)

/** ADC Init structure definition **/
typedef struct
{
    uint32_t WorkMode;  /* Configures the ADC to operate in independent or dual mode.*/
                           
    FunctionalState MultiChEn; /* Specifies whether the conversion is performed in
                                  Scan (multichannels) or Single (one channel) mode.  */

    FunctionalState ContinueConvEn; /* Specifies whether the conversion is performed in
                                       Continuous or Single mode. */
    uint32_t ExtTrigSelect;  /*Set ADC group regular conversion trigger source: internal (SW start) or from external peripheral */

    uint32_t DatAlign;   /* Set ADC conversion data alignment.*/

    uint8_t  ChsNumber;  /* Set ADC group regular sequencer length*/

} ADC_InitType;

/** ADC offset structure definition **/
typedef struct
{
    FunctionalState OffsetEn;       /* Set Offset enable or disable*/
    FunctionalState OffsetSatenEn;  /* Set Offset satera*/
    FunctionalState OffsetDirPositiveEn;
    uint8_t  OffsetChannel;
    uint16_t OffsetData;
} ADC_OffsetType;


 /**  Multimode - Delay between two sampling phases **/
#define ADC_ADC_MULTI_TWOSMP_DELAY_MASK           (ADC_CTRL1_DELAY)
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_1        ((uint32_t)0x00000000U << 20) /**1 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_2        ((uint32_t)0x00000001U << 20) /**2 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_3        ((uint32_t)0x00000002U << 20) /**3 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_4        ((uint32_t)0x00000003U << 20) /**4 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_5        ((uint32_t)0x00000004U << 20) /**5 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_6        ((uint32_t)0x00000005U << 20) /**6 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_7        ((uint32_t)0x00000006U << 20) /**7 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_8        ((uint32_t)0x00000007U << 20) /**8 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_9        ((uint32_t)0x00000008U << 20) /**9 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_10       ((uint32_t)0x00000009U << 20) /**10 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_11       ((uint32_t)0x0000000AU << 20) /**11 ADC clock cycle */
#define ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_12       ((uint32_t)0x0000000BU << 20) /**12 ADC clock cycle */

/**  ADC_muli_mode ,including dual-ADC mode and tripple-ADC mode **/
#define ADC_WORKMODE_MULT_MASK                    (ADC_CTRL1_MULTMODE)
#define ADC_WORKMODE_INDEPENDENT                  ((uint32_t)0x00000000U)
/**  Dual-ADC mode **/
#define ADC_WORKMODE_DUAL_REG_SIMULT              ((uint32_t)0x00000001U << 7)
#define ADC_WORKMODE_DUAL_ALTER_TRIG              ((uint32_t)0x00000002U << 7)
#define ADC_WORKMODE_DUAL_INTERL                  ((uint32_t)0x00000003U << 7)
#define ADC_WORKMODE_DUAL_INJ_SIMULT              ((uint32_t)0x00000004U << 7)
#define ADC_WORKMODE_DUAL_REG_INJECT_SIMULT       ((uint32_t)0x00000005U << 7)

/** ADC CTRL1 MASK **/
#define ADC_SCANMD_EN_MASK                        (ADC_CTRL1_SCANMD) /* Muti-channels enable mask */
#define ADC_JAUTO_EN_MASK                         (ADC_CTRL1_AUTOJC) /* Automatic injected group conversion enable mask */

#define ADC_DISC_REG_EN_MASK                      (ADC_CTRL1_DREGCH) /* ADC Discontinous mode enable on regluar channels mask */
#define ADC_DISC_INJ_EN_MASK                      (ADC_CTRL1_DJCH) /* ADC Discontinous mode enable on injected channels mask */

#define ADC_DISC_NUM_MASK                         (ADC_CTRL1_DCTU) /* ADC Discontinuous mode channel count */
/** ADC channels count of discontinuous mode define **/
#define ADC_CHANNEL_COUNT_MASK               ((uint32_t)(~ADC_CTRL1_DCTU)) /* ADC_CTRL1 DCTU[2:0] bit Mask */
#define ADC_CHANNEL_COUNT_1                    ((uint32_t)0x00000000)
#define ADC_CHANNEL_COUNT_2                    ((uint32_t)0x00000004)
#define ADC_CHANNEL_COUNT_3                    ((uint32_t)0x00000008)
#define ADC_CHANNEL_COUNT_4                    ((uint32_t)0x0000000C)
#define ADC_CHANNEL_COUNT_5                    ((uint32_t)0x00000010)
#define ADC_CHANNEL_COUNT_6                    ((uint32_t)0x00000014)
#define ADC_CHANNEL_COUNT_7                    ((uint32_t)0x00000018)
#define ADC_CHANNEL_COUNT_8                    ((uint32_t)0x0000001C)
/**  ADC_channels_definition **/
#define ADC_CH_MASK                               (ADC_CTRL1_AWDGCH)
#define ADC_CH_0                                  ((uint8_t)0x00U)
#define ADC_CH_1                                  ((uint8_t)0x01U)
#define ADC_CH_2                                  ((uint8_t)0x02U)
#define ADC_CH_3                                  ((uint8_t)0x03U)
#define ADC_CH_4                                  ((uint8_t)0x04U)
#define ADC_CH_5                                  ((uint8_t)0x05U)
#define ADC_CH_6                                  ((uint8_t)0x06U)
#define ADC_CH_7                                  ((uint8_t)0x07U)
#define ADC_CH_8                                  ((uint8_t)0x08U)
#define ADC_CH_9                                  ((uint8_t)0x09U)
#define ADC_CH_10                                 ((uint8_t)0x0AU)
#define ADC_CH_11                                 ((uint8_t)0x0BU)
#define ADC_CH_12                                 ((uint8_t)0x0CU)
#define ADC_CH_13                                 ((uint8_t)0x0DU)
#define ADC_CH_14                                 ((uint8_t)0x0EU)
#define ADC_CH_15                                 ((uint8_t)0x0FU)
#define ADC_CH_16                                 ((uint8_t)0x10U)
#define ADC_CH_17                                 ((uint8_t)0x11U)

/**  ADC_analog_watchdog_selection **/
#define ADC_ANALOG_WTDG_SINGLEREG_ENABLE          (ADC_CTRL1_AWDSGLEN | ADC_CTRL1_AWDERCH)
#define ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE        (ADC_CTRL1_AWDSGLEN | ADC_CTRL1_AWDEJCH)
#define ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE (ADC_CTRL1_AWDSGLEN | ADC_CTRL1_AWDERCH | ADC_CTRL1_AWDEJCH)
#define ADC_ANALOG_WTDG_ALLREG_ENABLE             (ADC_CTRL1_AWDERCH)
#define ADC_ANALOG_WTDG_ALLINJEC_ENABLE           (ADC_CTRL1_AWDEJCH)
#define ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE    (ADC_CTRL1_AWDERCH | ADC_CTRL1_AWDEJCH)
#define ADC_ANALOG_WTDG_NONE                      ((uint32_t)0x00000000U)

/** ADC CTRL2 MASK **/
#define ADC_ON_EN_MASK                            (ADC_CTRL2_ON) /* ADC enable mask */
#define ADC_CONT_EN_MASK                          (ADC_CTRL2_CTU) /* ADC continuous conversion mask */

/** ADC_Regular_Group_Trigger_Edge_Configuration **/
#define ADC_REG_TRIG_EXT_MASK                     (ADC_CTRL2_EXTPRSEL) 
#define ADC_REG_TRIG_EXT_SOFTWARE                 ((uint32_t)0x00000000U) 
#define ADC_REG_TRIG_EXT_RISING                   (ADC_CTRL2_EXTPRSEL_0)                          /* rising edge */
#define ADC_REG_TRIG_EXT_FALLING                  (ADC_CTRL2_EXTPRSEL_1)                          /* falling edge */
#define ADC_REG_TRIG_EXT_RISINGFALLING            (ADC_CTRL2_EXTPRSEL_1 | ADC_CTRL2_EXTPRSEL_0)   /* rising and falling edges */

#define ADC_REG_TRIG_EXT_EDGE_DEFAULT             (ADC_REG_TRIG_EXT_RISING)                       /* default trigger rising edge */ 
/** ADC_Injected_Group_Trigger_Edge_Configuration **/
#define ADC_INJ_TRIG_EXT_MASK                     (ADC_CTRL2_EXTPJSEL)
#define ADC_INJ_TRIG_EXT_SOFTWARE                 ((uint32_t)0x00000000U) 
#define ADC_INJ_TRIG_EXT_RISING                   (ADC_CTRL2_EXTPJSEL_0)                          /* rising edge */
#define ADC_INJ_TRIG_EXT_FALLING                  (ADC_CTRL2_EXTPJSEL_1)                          /* falling edge */
#define ADC_INJ_TRIG_EXT_RISINGFALLING            (ADC_CTRL2_EXTPJSEL_1 | ADC_CTRL2_EXTPJSEL_0)   /* rising and falling edges */

#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT             (ADC_INJ_TRIG_EXT_RISING)                       /* default trigger rising edge */

/**  ADC_external_trigger_sources_for_injected_channels_conversion **/
#define ADC_EXT_TRIG_INJ_CONV_MASK                (ADC_CTRL2_EXTJSEL | ADC_INJ_TRIG_EXT_MASK) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO          (((uint32_t)0x00000000U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO2         (((uint32_t)0x00000001U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC1           (((uint32_t)0x00000002U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC2           (((uint32_t)0x00000003U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC3           (((uint32_t)0x00000004U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM1_CC4           (((uint32_t)0x00000005U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO          (((uint32_t)0x00000006U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_CC1           (((uint32_t)0x00000007U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_ATIM2_CC4           (((uint32_t)0x00000008U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM1_TRGO          (((uint32_t)0x00000009U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM1_CC2           (((uint32_t)0x0000000AU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM1_CC4           (((uint32_t)0x0000000BU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM2_TRGO          (((uint32_t)0x0000000CU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM2_CC1           (((uint32_t)0x0000000DU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM2_CC4           (((uint32_t)0x0000000EU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM3_TRGO          (((uint32_t)0x0000000FU << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM3_CC1           (((uint32_t)0x00000010U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM3_CC2           (((uint32_t)0x00000011U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM3_CC4           (((uint32_t)0x00000012U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM4_TRGO          (((uint32_t)0x00000013U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM4_CC1           (((uint32_t)0x00000014U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM4_CC2           (((uint32_t)0x00000015U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_GTIM4_CC4           (((uint32_t)0x00000016U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_BTIM1_TRGO          (((uint32_t)0x00000017U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_EXT_INT0_15         (((uint32_t)0x00000018U << 12) | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_INJ_CONV_SOFTWARE            ((uint32_t)0x00000019U  << 12) 

/**  ADC_external_trigger_sources_for_regular_channels_conversion **/
#define ADC_EXT_TRIG_REG_CONV_MASK                (ADC_CTRL2_EXTRSEL | ADC_REG_TRIG_EXT_MASK) 
#define ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO          (((uint32_t)0x00000000U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT) 
#define ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2         (((uint32_t)0x00000001U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC1           (((uint32_t)0x00000002U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC2           (((uint32_t)0x00000003U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC3           (((uint32_t)0x00000004U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM1_CC4           (((uint32_t)0x00000005U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO          (((uint32_t)0x00000006U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_CC1           (((uint32_t)0x00000007U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_ATIM2_CC4           (((uint32_t)0x00000008U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM1_TRGO          (((uint32_t)0x00000009U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM1_CC2           (((uint32_t)0x0000000AU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM1_CC4           (((uint32_t)0x0000000BU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM2_TRGO          (((uint32_t)0x0000000CU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM2_CC1           (((uint32_t)0x0000000DU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM2_CC4           (((uint32_t)0x0000000EU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM3_TRGO          (((uint32_t)0x0000000FU << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM3_CC1           (((uint32_t)0x00000010U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM3_CC2           (((uint32_t)0x00000011U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM3_CC4           (((uint32_t)0x00000012U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM4_TRGO          (((uint32_t)0x00000013U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM4_CC1           (((uint32_t)0x00000014U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM4_CC2           (((uint32_t)0x00000015U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_GTIM4_CC4           (((uint32_t)0x00000016U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_BTIM1_TRGO          (((uint32_t)0x00000017U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_EXT_INT0_15         (((uint32_t)0x00000018U << 17) | ADC_REG_TRIG_EXT_EDGE_DEFAULT)
#define ADC_EXT_TRIG_REG_CONV_SOFTWARE            ((uint32_t)0x00000019U << 17 )


/**  ADC DMA Mode **/
#define ADC_DMAEN_MASK                            (ADC_CTRL2_ENDMA)  
/**  ADC_data_align **/
#define ADC_DAT_ALIGN_MASK                        (ADC_CTRL2_ALIG)
#define ADC_DAT_ALIGN_R                           ((uint32_t)0x00000000U)
#define ADC_DAT_ALIGN_L                           (ADC_CTRL2_ALIG)

#define ADC_VREFINT_EN_MASK                       (ADC_CTRL3_VREFEN)  /**  ADC vreint enable  **/
#define ADC_TS_EN_MASK                            (ADC_CTRL2_TEMPEN)  /**  ADC temper sensor enable  **/
#define ADC_INJ_SWSTART_MASK                      (ADC_CTRL2_SWSTRJCH)/**  Start conversion of injected channels  **/
#define ADC_REG_SWSTART_MASK                      (ADC_CTRL2_SWSTRRCH)/**  Start conversion of regular channels  **/
#define ADC_INJ_SWSTOP_MASK                       (ADC_CTRL2_SWJSTOP) /**  Stop conversion of injected channels  **/
#define ADC_REG_SWSTOP_MASK                       (ADC_CTRL2_SWRSTOP) /**  Stop conversion of regular channels  **/

/**  ADC_Vrefp Seletion **/
#define ADC_VREFSEL_MASK                          (ADC_CTRL3_BUFSEL)
#define ADC_VREFSEL_VDDA                          ((uint32_t)0x00000000U)
#define ADC_VREFSEL_VREFP                         ((uint32_t)ADC_CTRL3_BUFSEL_0)
#define ADC_VREFSEL_VREFBUFF_2_4V                 ((uint32_t)ADC_CTRL3_BUFSEL_1)
#define ADC_VREFSEL_OFF                           ((uint32_t)(ADC_CTRL3_BUFSEL_0 | ADC_CTRL3_BUFSEL_1))

#define ADC_OVERSAMPE_RATE_TIMES_MASK             (ADC_CTRL3_OSR)    /**ADC oversampling ratio times bit mask **/
#define ADC_OVERSAMPE_RATE_TIMES_1                ((uint32_t)0x00000000U)   
#define ADC_OVERSAMPE_RATE_TIMES_2                ((uint32_t)0x00000001U)   
#define ADC_OVERSAMPE_RATE_TIMES_4                ((uint32_t)0x00000002U)   
#define ADC_OVERSAMPE_RATE_TIMES_8                ((uint32_t)0x00000003U)   
#define ADC_OVERSAMPE_RATE_TIMES_16               ((uint32_t)0x00000004U) 
#define ADC_OVERSAMPE_RATE_TIMES_32               ((uint32_t)0x00000005U) 
#define ADC_OVERSAMPE_RATE_TIMES_64               ((uint32_t)0x00000006U) 
#define ADC_OVERSAMPE_RATE_TIMES_128              ((uint32_t)0x00000007U) 
#define ADC_OVERSAMPE_RATE_TIMES_256              ((uint32_t)0x00000008U) 

#define ADC_OVERSAMPE_DATA_SHIFT_MASK             (ADC_CTRL3_OSS)    /**ADC oversampling data right shift bit mask **/
#define ADC_OVERSAMPE_DATA_SHIFT_0                (((uint32_t)0x00000000U) << 4)   
#define ADC_OVERSAMPE_DATA_SHIFT_1                (((uint32_t)0x00000001U) << 4)   
#define ADC_OVERSAMPE_DATA_SHIFT_2                (((uint32_t)0x00000002U) << 4)   
#define ADC_OVERSAMPE_DATA_SHIFT_3                (((uint32_t)0x00000003U) << 4)   
#define ADC_OVERSAMPE_DATA_SHIFT_4                (((uint32_t)0x00000004U) << 4) 
#define ADC_OVERSAMPE_DATA_SHIFT_5                (((uint32_t)0x00000005U) << 4) 
#define ADC_OVERSAMPE_DATA_SHIFT_6                (((uint32_t)0x00000006U) << 4) 
#define ADC_OVERSAMPE_DATA_SHIFT_7                (((uint32_t)0x00000007U) << 4) 
#define ADC_OVERSAMPE_DATA_SHIFT_8                (((uint32_t)0x00000008U) << 4) 

#define ADC_OVERSAMPE_REG_EN_MASK                 (ADC_CTRL3_OSRE)    /**ADC oversampling on regular channels **/
#define ADC_OVERSAMPE_INJ_EN_MASK                 (ADC_CTRL3_OSJE)    /**ADC oversampling on injected channels **/
#define ADC_OVERSAMPE_TRIG_REG_MASK               (ADC_CTRL3_OSRTRIG) /**ADC oversampling trigger mode on regular channels **/
#define ADC_OVERSAMPE_MODE_MASK                   (ADC_CTRL3_OSRMD)   /**ADC oversampling mode on regular channels **/
/**Oversample scope **/
#define ADC_OVERSAMPE_DISABLE                     ((uint32_t)0x00000000U)
#define ADC_OVERSAMPE_REGULAR_CONTINUED           (ADC_OVERSAMPE_REG_EN_MASK)
#define ADC_OVERSAMPE_REGULAR_RESUMED             (ADC_OVERSAMPE_MODE_MASK | ADC_OVERSAMPE_REG_EN_MASK)
#define ADC_OVERSAMPE_INJECTED                    (ADC_OVERSAMPE_INJ_EN_MASK)
#define ADC_OVERSAMPE_REGULAR_INJECTED            (ADC_OVERSAMPE_REG_EN_MASK | ADC_OVERSAMPE_INJ_EN_MASK)

/**  ADC_sampling_time **/
#define ADC_SAMP_TIME_CYCLES_MASK                 (ADC_SAMPT1_SAMP0)
#define ADC_SAMP_TIME_CYCLES_4                    ((uint8_t)0x00U)
#define ADC_SAMP_TIME_CYCLES_6                    ((uint8_t)0x01U)
#define ADC_SAMP_TIME_CYCLES_8                    ((uint8_t)0x02U)
#define ADC_SAMP_TIME_CYCLES_14                   ((uint8_t)0x03U)
#define ADC_SAMP_TIME_CYCLES_29                   ((uint8_t)0x04U)
#define ADC_SAMP_TIME_CYCLES_42                   ((uint8_t)0x05U)
#define ADC_SAMP_TIME_CYCLES_56                   ((uint8_t)0x06U)
#define ADC_SAMP_TIME_CYCLES_72                   ((uint8_t)0x07U)
#define ADC_SAMP_TIME_CYCLES_88                   ((uint8_t)0x08U)
#define ADC_SAMP_TIME_CYCLES_120                  ((uint8_t)0x09U)
#define ADC_SAMP_TIME_CYCLES_182                  ((uint8_t)0x0AU)
#define ADC_SAMP_TIME_CYCLES_240                  ((uint8_t)0x0BU)
#define ADC_SAMP_TIME_CYCLES_300                  ((uint8_t)0x0CU)
#define ADC_SAMP_TIME_CYCLES_400                  ((uint8_t)0x0DU)
#define ADC_SAMP_TIME_CYCLES_480                  ((uint8_t)0x0EU)
#define ADC_SAMP_TIME_CYCLES_600                  ((uint8_t)0x0FU)
/**  ADC_offset_channel_offset **/
#define ADC_REGESTER_OFFSET_1                     ((uint8_t)0x20U)
#define ADC_REGESTER_OFFSET_2                     ((uint8_t)0x24U)
#define ADC_REGESTER_OFFSET_3                     ((uint8_t)0x28U)
#define ADC_REGESTER_OFFSET_4                     ((uint8_t)0x2CU)

#define ADC_OFFSET_EN_MASK                        (ADC_OFFSET1_OFFSCH1EN)
#define ADC_OFFSET_CH_MASK                        (ADC_OFFSET1_OFFSCH1CH)
#define ADC_OFFSET_SATEN_EN_MASK                  (ADC_OFFSET1_OFFSCH1SATEN)
#define ADC_OFFSET_DIR_MASK                       (ADC_OFFSET1_OFFSCH1DIR)
#define ADC_OFFSET_DATA_MASK                      (ADC_OFFSET1_OFFSCH1DAT)

/**  ADC regular sequence **/
#define ADC_RESQ_SEQ_MASK                         (ADC_RSEQ1_SEQ1)

/**  ADC inject sequence **/
#define ADC_JESQ_LEN_MASK                         (ADC_JSEQ_JLEN)
#define ADC_JESQ_SEQ_MASK                         (ADC_JSEQ_JSEQ1)

/** ADC regular channel sequence length define **/
#define ADC_REGULAR_LEN_MSAK                 ((uint32_t)(~ADC_RSEQ3_LEN)) /* ADC_RSEQ3 LEN[3:0] bits Mask */
#define ADC_REGULAR_LEN_1                    ((uint32_t)1)
#define ADC_REGULAR_LEN_2                    ((uint32_t)2)
#define ADC_REGULAR_LEN_3                    ((uint32_t)3)
#define ADC_REGULAR_LEN_4                    ((uint32_t)4)
#define ADC_REGULAR_LEN_5                    ((uint32_t)5)
#define ADC_REGULAR_LEN_6                    ((uint32_t)6)
#define ADC_REGULAR_LEN_7                    ((uint32_t)7)
#define ADC_REGULAR_LEN_8                    ((uint32_t)8)
#define ADC_REGULAR_LEN_9                    ((uint32_t)9)
#define ADC_REGULAR_LEN_10                   ((uint32_t)10)
#define ADC_REGULAR_LEN_11                   ((uint32_t)11)
#define ADC_REGULAR_LEN_12                   ((uint32_t)12)
#define ADC_REGULAR_LEN_13                   ((uint32_t)13)
#define ADC_REGULAR_LEN_14                   ((uint32_t)14)
#define ADC_REGULAR_LEN_15                   ((uint32_t)15)
#define ADC_REGULAR_LEN_16                   ((uint32_t)16)

#define ADC_INJECT_DATA_OFFSET_1                  ((uint8_t)0x70U)
#define ADC_INJECT_DATA_OFFSET_2                  ((uint8_t)0x74U)
#define ADC_INJECT_DATA_OFFSET_3                  ((uint8_t)0x78U)
#define ADC_INJECT_DATA_OFFSET_4                  ((uint8_t)0x7CU)

/** ADC injected sequence number define **/
#define ADC_INJECTED_NUM_UNIT                ((uint32_t)0x0000001F) 
#define ADC_INJECTED_NUM_UNIT_NUM            ((uint8_t)0x05) 
#define ADC_INJECTED_NUMBER_MASK(num)        ((uint32_t)(~(ADC_INJECTED_NUM_UNIT << ((num) * ADC_INJECTED_NUM_UNIT_NUM))))
#define ADC_INJECTED_NUMBER_SET(ch, num)     ((uint32_t)((ch) << ((num) * ADC_INJECTED_NUM_UNIT_NUM)))
#define ADC_INJECTED_NUMBER_1                ((uint8_t)0x01)
#define ADC_INJECTED_NUMBER_2                ((uint8_t)0x02)
#define ADC_INJECTED_NUMBER_3                ((uint8_t)0x03)
#define ADC_INJECTED_NUMBER_4                ((uint8_t)0x04)

/** ADC injected channel sequence length define **/
#define ADC_INJECTED_LEN_MSAK                ((uint32_t)(~ADC_JSEQ_JLEN)) /* ADC_JSEQ LEN[1:0] bits Mask */
#define ADC_INJECTED_LEN_1                   ((uint8_t)0x01) /* Start conversion in the order of 4 */
#define ADC_INJECTED_LEN_2                   ((uint8_t)0x02) /* Start conversion in the order of 3, 4 */
#define ADC_INJECTED_LEN_3                   ((uint8_t)0x03) /* Start conversion in the order of 2, 3, 4 */
#define ADC_INJECTED_LEN_4                   ((uint8_t)0x04) /* Start conversion in the order of 1, 2, 3, 4 */



/**  ADC_flags_definition **/
#define ADC_FLAG_ALL_MASK                         (ADC_STS_ALL)
#define ADC_FLAG_ENDC                             ((uint16_t)ADC_STS_ENDC)
#define ADC_FLAG_EOC_ANY                          ((uint16_t)ADC_STS_ENDCA)
#define ADC_FLAG_JENDC                            ((uint16_t)ADC_STS_JENDC)
#define ADC_FLAG_JEOC_ANY                         ((uint16_t)ADC_STS_JENDCA)
#define ADC_FLAG_AWDG                             ((uint16_t)ADC_STS_AWDG)
#define ADC_FLAG_OVERRUN                          ((uint16_t)ADC_STS_OVR)
#define ADC_FLAG_RDY                              ((uint16_t)ADC_STS_RDY)
#define ADC_FLAG_PDRDY                            ((uint16_t)ADC_STS_PDRDY)
#define ADC_FLAG_EOSAMP                           ((uint16_t)ADC_STS_EOSAMP)
#define ADC_FLAG_TCFLAG                           ((uint16_t)ADC_STS_TCFLAG)
#define ADC_FLAG_STR                              ((uint16_t)ADC_STS_STR)
#define ADC_FLAG_JSTR                             ((uint16_t)ADC_STS_JSTR)
#define ADC_FLAG_VREFRDY                          ((uint16_t)ADC_STS_VREFRDY)
/**  ADC_CTRL4_definition **/
#define ADC_CTRL4_EXTRRSEL_MASK                   (ADC_CTRL4_EXTRRSEL)
#define ADC_CTRL4_EXTRISEL_MASK                   (ADC_CTRL4_EXTRISEL)

#define ADC_TRIG_EXTI_0                           ((uint32_t)0x00U)
#define ADC_TRIG_EXTI_1                           ((uint32_t)0x01U)
#define ADC_TRIG_EXTI_2                           ((uint32_t)0x02U)
#define ADC_TRIG_EXTI_3                           ((uint32_t)0x03U)
#define ADC_TRIG_EXTI_4                           ((uint32_t)0x04U)
#define ADC_TRIG_EXTI_5                           ((uint32_t)0x05U)
#define ADC_TRIG_EXTI_6                           ((uint32_t)0x06U)
#define ADC_TRIG_EXTI_7                           ((uint32_t)0x07U)
#define ADC_TRIG_EXTI_8                           ((uint32_t)0x08U)
#define ADC_TRIG_EXTI_9                           ((uint32_t)0x09U)
#define ADC_TRIG_EXTI_10                          ((uint32_t)0x0AU)
#define ADC_TRIG_EXTI_11                          ((uint32_t)0x0BU)
#define ADC_TRIG_EXTI_12                          ((uint32_t)0x0CU)
#define ADC_TRIG_EXTI_13                          ((uint32_t)0x0DU)
#define ADC_TRIG_EXTI_14                          ((uint32_t)0x0EU)
#define ADC_TRIG_EXTI_15                          ((uint32_t)0x0FU)

/**  ADC_interrupts_definition **/
#define ADC_INTFLAG_ALL_MASK                      (0x000003FFU)
#define ADC_INT_ENDC                              ((uint16_t)ADC_INTEN_ENDCIEN)
#define ADC_INT_ENDCA                             ((uint16_t)ADC_INTEN_ENDCAIEN)
#define ADC_INT_JENDC                             ((uint16_t)ADC_INTEN_JENDCIEN)
#define ADC_INT_JENDCA                            ((uint16_t)ADC_INTEN_JENDCAIEN)
#define ADC_INT_AWDG                              ((uint16_t)ADC_INTEN_AWDIEN)
#define ADC_INT_OVERRUN                           ((uint16_t)ADC_INTEN_OVRIEN)
#define ADC_INT_RDY                               ((uint16_t)ADC_INTEN_RDYIEN)
#define ADC_INT_PDRDY                             ((uint16_t)ADC_INTEN_PDRDYIEN)
#define ADC_INT_EOSAMP                            ((uint16_t)ADC_INTEN_EOSAMPIEN)

/**  ADC1_channels_definition **/
#define ADC1_Channel_00_PA0                       (ADC_CH_0)  
#define ADC1_Channel_01_PA1                       (ADC_CH_1)  
#define ADC1_Channel_02_PA2                       (ADC_CH_2)  
#define ADC1_Channel_03_PA3                       (ADC_CH_3)  
#define ADC1_Channel_04_PA4                       (ADC_CH_4)  
#define ADC1_Channel_05_PA5                       (ADC_CH_5)  
#define ADC1_Channel_06_PA6                       (ADC_CH_6)  
#define ADC1_Channel_07_PA7                       (ADC_CH_7)  
#define ADC1_Channel_08_PB0                       (ADC_CH_8)  
#define ADC1_Channel_09_PB1                       (ADC_CH_9)  
#define ADC1_Channel_10_PC0                       (ADC_CH_10) 
#define ADC1_Channel_11_PC1                       (ADC_CH_11) 
#define ADC1_Channel_12_PC2                       (ADC_CH_12) 
#define ADC1_Channel_13_PC3                       (ADC_CH_13) 
#define ADC1_Channel_14_PC4                       (ADC_CH_14) 
#define ADC1_Channel_15_PC5                       (ADC_CH_15) 
#define ADC1_Channel_16_VREFINT                   (ADC_CH_16)
#define ADC1_Channel_17_Temperture_Sensor         (ADC_CH_17)

/**  ADC2_channels_definition **/
#define ADC2_Channel_00_PB2                       (ADC_CH_0)  
#define ADC2_Channel_01_PB10                      (ADC_CH_1)  
#define ADC2_Channel_02_PB11                      (ADC_CH_2)  
#define ADC2_Channel_03_PB12                      (ADC_CH_3)  
#define ADC2_Channel_04_PA4                       (ADC_CH_4)  
#define ADC2_Channel_05_PA5                       (ADC_CH_5)  
#define ADC2_Channel_06_PA6                       (ADC_CH_6)  
#define ADC2_Channel_07_PA7                       (ADC_CH_7)  
#define ADC2_Channel_08_PB0                       (ADC_CH_8)  
#define ADC2_Channel_09_PB1                       (ADC_CH_9)  
#define ADC2_Channel_10_PA13                      (ADC_CH_10) 
#define ADC2_Channel_11_PA14                      (ADC_CH_11) 
#define ADC2_Channel_12_PB13                      (ADC_CH_12)  
#define ADC2_Channel_13_PB14                      (ADC_CH_13)  
#define ADC2_Channel_14_PB15                      (ADC_CH_14)  
#ifdef N32G415
#define ADC2_Channel_15_PA8                       (ADC_CH_15)  
#else
#define ADC2_Channel_15_PC6                       (ADC_CH_15)  
#endif

/*** ADC Driving Functions Declaration ***/

/* Reset and initialization */
void ADC_DeInit(const ADC_Module* ADCx);
void ADC_Init(ADC_Module* ADCx, const ADC_InitType* ADC_InitParam);
void ADC_InitStruct(ADC_InitType* ADC_InitStructure);
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_EnableDMA(ADC_Module* ADCx, FunctionalState Cmd);

/* Regular conversion control */
void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd);
FlagStatus ADC_GetSoftwareStartConvStatus(const ADC_Module* ADCx);
void ADC_StopRegularConv(ADC_Module* ADCx);
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
uint16_t ADC_GetDat(const ADC_Module* ADCx);
uint32_t ADC_GetMutiModeConversionDat(void);
void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number);
void ADC_EnableDiscMode(ADC_Module* ADCx, FunctionalState Cmd);

/* Injected conversion control */
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(const ADC_Module* ADCx);
void ADC_StopInjectedConv(ADC_Module* ADCx);
void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length);
uint16_t ADC_GetInjectedConversionDat(const ADC_Module* ADCx, uint8_t ADC_InjectedChannel);
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd);
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd);

/* Trigger configuration */
void ADC_SetRegularTriggerEdge(ADC_Module* ADCx, uint32_t ExternalRegularTriggerEdge);
void ADC_SetInjectTriggerEdge(ADC_Module* ADCx, uint32_t ExternalInjectTriggerEdge);
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ConfigExternalTrigRegularConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigRegularConv);
void ADC_ConfigRegularExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger);
void ADC_ConfigInjectedExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger);

/* Multi-mode configuration */
void ADC_SetMultiTwoSamplingDelay(ADC_Module* ADCx, uint32_t MultiTwoSamplingDelay);

/* Analog watchdog configuration */
void ADC_ConfigAnalogWatchdogWorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel);

/* Temperature sensor and internal reference */
void ADC_EnableTempSensorVrefint(FunctionalState Cmd);
void Reference_VoltageSelect(uint32_t Ref_Type);

/* Oversampling configuration */
void ADC_ConfigOverSamplingRatioAndShift(ADC_Module *ADCx, uint32_t Ratio, uint32_t Shift);
void ADC_SetOverSamplingScope(ADC_Module *ADCx, uint32_t OversampleScope);
void ADC_EnableOverSamplingDiscont(ADC_Module *ADCx, FunctionalState Cmd);

/* Offset configuration */
void ADC_SetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, const ADC_OffsetType* ADC_OffsetStruct);
void ADC_GetOffsetConfig(const ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct);

/* Interrupt and flag management */
FlagStatus ADC_GetFlagStatus(const ADC_Module* ADCx, uint16_t ADC_FLAG);
void ADC_ClearFlag(ADC_Module* ADCx, uint16_t ADC_FLAG);
void ADC_ConfigInt(ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd);
INTStatus ADC_GetIntStatus(const ADC_Module* ADCx, uint16_t ADC_IT);
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint16_t ADC_IT);

/* Clock configuration */
void ADC_ClockModeConfig(uint32_t RCC_ADCHCLKprescaler);

#ifdef __cplusplus
}
#endif

#endif /*__N32G41X_ADC_H__ */

