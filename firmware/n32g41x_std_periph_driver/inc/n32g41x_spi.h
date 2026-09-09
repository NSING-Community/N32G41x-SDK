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
*\*\file      n32g41x_spi.h
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved. 
**/
#ifndef __N32G41X_SPI_H__
#define __N32G41X_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"

/**  SPI Init structure definition */
typedef struct
{
    uint16_t DataDirection; /* Specifies the SPI unidirectional or bidirectional data mode  */

    uint16_t SpiMode;       /* Specifies the SPI operating mode */

    uint16_t DataLen;      /* Specifies the SPI data size */

    uint16_t CLKPOL;       /* Specifies the serial clock steady state */

    uint16_t CLKPHA;       /* Specifies the clock active edge for the bit capture */

    uint16_t NSS;          /* Specifies whether the NSS signal is managed by hardware (NSS pin) or by software using the SSI bit */

    uint16_t BaudRatePres; /* Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    uint16_t FirstBit;     /* Specifies whether data transfers start from MSB or LSB bit */

    uint16_t CRCPoly;      /* Specifies the polynomial used for the CRC calculation */
} SPI_InitType;

/** I2S Init structure definition **/
typedef struct
{
    uint16_t I2sMode;           /* Specifies the I2S operating mode */

    uint16_t Standard;          /* Specifies the standard used for the I2S communication */

    uint16_t DataFormat;        /* Specifies the data format for the I2S communication */

    uint16_t MCLKEnable;        /* Specifies whether the I2S MCLK output is enabled or not */

    uint32_t AudioFrequency;    /* Specifies the frequency selected for the I2S communication */

    uint16_t CLKPOL;            /* Specifies the idle state of the I2S clock */

    uint32_t ClkSrcFrequency;   /* Specifies the I2S clock source frequency in Hz */
} I2S_InitType;


/** SPI_Exported_Constants **/
#define IS_SPI_PERIPH(PERIPH) (((PERIPH) == SPI1) || ((PERIPH) == SPI2))


/** SPI_data_direction **/
#define SPI_DIR_DOUBLELINE_FULLDUPLEX ((uint16_t)0x0000U)
#define SPI_DIR_DOUBLELINE_RONLY      ((uint16_t)SPI_CTRL1_RONLY)
#define SPI_DIR_SINGLELINE_RX         ((uint16_t)SPI_CTRL1_BIDIRMODE)
#define SPI_DIR_SINGLELINE_TX         ((uint16_t)SPI_CTRL1_BIDIRMODE | SPI_CTRL1_BIDIROEN)

/** SPI_mode **/
#define SPI_MODE_SLAVE                ((uint16_t)0x0000U)
#define SPI_MODE_MASTER               ((uint16_t)SPI_CTRL1_SSEL | SPI_CTRL1_MSEL)

/** SPI_data_size **/
#define SPI_DATA_SIZE_8BITS           ((uint16_t)0x0000U)
#define SPI_DATA_SIZE_16BITS          ((uint16_t)SPI_CTRL1_DATFF)
#define SPI_DATA_SIZE_9BITS           ((uint16_t)SPI_CTRL2_DATFF9)


/** SPI_Clock_Polarity **/
#define SPI_CLKPOL_LOW                ((uint16_t)0x0000U)
#define SPI_CLKPOL_HIGH               ((uint16_t)SPI_CTRL1_CLKPOL)

/** SPI_Clock_Phase **/
#define SPI_CLKPHA_FIRST_EDGE         ((uint16_t)0x0000U)
#define SPI_CLKPHA_SECOND_EDGE        ((uint16_t)SPI_CTRL1_CLKPHA)


/** SPI_Slave_Select_management **/
#define SPI_NSS_HARD                  ((uint16_t)0x0000U)
#define SPI_NSS_SOFT                  ((uint16_t)SPI_CTRL1_SSMEN)


/** SPI_BaudRate_Prescaler **/
#define SPI_BR_PRESCALER_2            ((uint16_t)0x0000U)
#define SPI_BR_PRESCALER_4            ((uint16_t)SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_8            ((uint16_t)SPI_CTRL1_BR1)
#define SPI_BR_PRESCALER_16           ((uint16_t)SPI_CTRL1_BR1 | SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_32           ((uint16_t)SPI_CTRL1_BR2)
#define SPI_BR_PRESCALER_64           ((uint16_t)SPI_CTRL1_BR2 | SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_128          ((uint16_t)SPI_CTRL1_BR2 | SPI_CTRL1_BR1)
#define SPI_BR_PRESCALER_256          ((uint16_t)SPI_CTRL1_BR2 | SPI_CTRL1_BR1 | SPI_CTRL1_BR0)


/** SPI_MSB_LSB_transmission **/
#define SPI_FB_MSB                    ((uint16_t)0x0000U)
#define SPI_FB_LSB                    ((uint16_t)SPI_CTRL1_LSBFF)


/** I2sMode **/
#define I2S_MODE_SlAVE_TX             ((uint16_t)0x0000U)
#define I2S_MODE_SlAVE_RX             ((uint16_t)SPI_I2SCFG_MODCFG0)
#define I2S_MODE_MASTER_TX            ((uint16_t)SPI_I2SCFG_MODCFG1)
#define I2S_MODE_MASTER_RX            ((uint16_t)SPI_I2SCFG_MODCFG1 | SPI_I2SCFG_MODCFG0)

 
/**  Standard **/
#define I2S_STD_PHILLIPS              ((uint16_t)0x0000U)
#define I2S_STD_MSB_ALIGN             ((uint16_t)SPI_I2SCFG_STDSEL0)
#define I2S_STD_LSB_ALIGN             ((uint16_t)SPI_I2SCFG_STDSEL1)
#define I2S_STD_PCM_SHORTFRAME        ((uint16_t)SPI_I2SCFG_STDSEL1 | SPI_I2SCFG_STDSEL0)
#define I2S_STD_PCM_LONGFRAME         ((uint16_t)SPI_I2SCFG_PCMFSYNC | SPI_I2SCFG_STDSEL1 | SPI_I2SCFG_STDSEL0)


/** I2S_Data_Format **/
#define I2S_DATA_FMT_16BITS           ((uint16_t)0x0000U)
#define I2S_DATA_FMT_16BITS_EXTENDED  ((uint16_t)SPI_I2SCFG_CHBITS)
#define I2S_DATA_FMT_24BITS           ((uint16_t)SPI_I2SCFG_CHBITS | SPI_I2SCFG_TDATLEN0)
#define I2S_DATA_FMT_32BITS           ((uint16_t)SPI_I2SCFG_CHBITS | SPI_I2SCFG_TDATLEN1)


/** I2S_MCLK_Output **/
#define I2S_MCLK_DISABLE              ((uint16_t)0x0000)
#define I2S_MCLK_ENABLE               ((uint16_t)SPI_I2SPREDIV_MCLKOEN)


/** I2S_Audio_Frequency **/
#define I2S_AUDIO_FREQ_192K           ((uint32_t)192000)
#define I2S_AUDIO_FREQ_96K            ((uint32_t)96000)
#define I2S_AUDIO_FREQ_48K            ((uint32_t)48000)
#define I2S_AUDIO_FREQ_44K            ((uint32_t)44100)
#define I2S_AUDIO_FREQ_32K            ((uint32_t)32000)
#define I2S_AUDIO_FREQ_22K            ((uint32_t)22050)
#define I2S_AUDIO_FREQ_16K            ((uint32_t)16000)
#define I2S_AUDIO_FREQ_11K            ((uint32_t)11025)
#define I2S_AUDIO_FREQ_8K             ((uint32_t)8000)
#define I2S_AUDIO_FREQ_DEFAULT        ((uint32_t)2)


/** I2S_Clock_Polarity **/
#define I2S_CLKPOL_LOW                ((uint16_t)0x0000)
#define I2S_CLKPOL_HIGH               ((uint16_t)SPI_I2SCFG_CLKPOL)


/** SPI_I2S_DMA_transfer_requests **/
#define SPI_I2S_DMA_TX                ((uint16_t)SPI_CTRL2_TDMAEN)
#define SPI_I2S_DMA_RX                ((uint16_t)SPI_CTRL2_RDMAEN)
 
 
/** SPI_NSS_internal_software_management **/
#define SPI_NSS_HIGH                  ((uint16_t)SPI_CTRL1_SSEL)
#define SPI_NSS_LOW                   ((uint16_t)~SPI_CTRL1_SSEL)


/** SPI_CRC_Transmit_Receive **/
#define SPI_CRC_TX                    ((uint8_t)0x00)
#define SPI_CRC_RX                    ((uint8_t)0x01)
 

/** SPI_direction_transmit_receive **/
#define SPI_BIDIRECTION_RX            ((uint16_t)~SPI_CTRL1_BIDIROEN)
#define SPI_BIDIRECTION_TX            ((uint16_t)SPI_CTRL1_BIDIROEN)

/* SPI CTRL2 NSSPOL */
#define NSS_LOW_LEVEL_VALID           ((uint16_t)~SPI_CTRL2_NSSPOL) 
#define NSS_HIGH_LEVEL_VALID          ((uint16_t)SPI_CTRL2_NSSPOL) 

/** SPI_I2S_interrupts_definition **/
#define SPI_I2S_INT_TE                ((uint8_t)0x40)
#define SPI_I2S_INT_RNE               ((uint8_t)0x51)
#define SPI_I2S_INT_ERR               ((uint8_t)0x60)

#define I2S_INT_UNDER                 ((uint8_t)0x66)
#define SPI_I2S_INT_OVER              ((uint8_t)0x65)
#define SPI_INT_MODERR                ((uint8_t)0x64)
#define SPI_INT_CRCERR                ((uint8_t)0x63)


/** SPI_I2S_flags_definition **/
#define SPI_I2S_TE_FLAG               ((uint16_t)SPI_STS_TE)
#define SPI_I2S_RNE_FLAG              ((uint16_t)SPI_STS_RNE)
#define SPI_I2S_BUSY_FLAG             ((uint16_t)SPI_STS_BUSY)
#define SPI_CRCERR_FLAG               ((uint16_t)SPI_STS_CRCERR)
#define SPI_MODERR_FLAG               ((uint16_t)SPI_STS_MODERR)
#define SPI_I2S_OVER_FLAG             ((uint16_t)SPI_STS_OVER)
#define I2S_UNDER_FLAG                ((uint16_t)SPI_STS_UNDER)
#define I2S_CHSIDE_FLAG               ((uint16_t)SPI_STS_CHSIDE)

/** Delay Time Definition **/
#define SPI_MASTER_SAMPLING_DELAY_BYPASS    ((uint16_t)0x0000)
#define SPI_MASTER_SAMPLING_DELAY_1_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_2_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME1)
#define SPI_MASTER_SAMPLING_DELAY_3_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME1 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_4_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME2)
#define SPI_MASTER_SAMPLING_DELAY_5_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_6_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME1)
#define SPI_MASTER_SAMPLING_DELAY_7_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME1 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_8_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME3)
#define SPI_MASTER_SAMPLING_DELAY_9_2_CLK   ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_10_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME1)
#define SPI_MASTER_SAMPLING_DELAY_11_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME1 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_12_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME2)
#define SPI_MASTER_SAMPLING_DELAY_13_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME0)
#define SPI_MASTER_SAMPLING_DELAY_14_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME1)
#define SPI_MASTER_SAMPLING_DELAY_15_2_CLK  ((uint16_t)SPI_CTRL3_DELAYTIME3 | SPI_CTRL3_DELAYTIME2 | SPI_CTRL3_DELAYTIME1 | SPI_CTRL3_DELAYTIME0)


/** SPI_Exported_Functions **/

/* Reset and init */
void SPI_I2S_DeInit(const SPI_Module* SPIx);
void SPI_Init(SPI_Module* SPIx, const SPI_InitType* SPI_InitParam);
void SPI_InitStruct(SPI_InitType* SPI_StructInit);
void SPI_Enable(SPI_Module* SPIx, FunctionalState Cmd);

/* I2S init */
void I2S_Init(SPI_Module* SPIx, const I2S_InitType* I2S_InitParam);
void I2S_InitStruct(I2S_InitType* I2S_StructInit);
void I2S_Enable(SPI_Module* SPIx, FunctionalState Cmd);
void I2S_Enable13BitPCMLongBypass(SPI_Module* SPIx, FunctionalState Cmd);

/* Data transfer */
void SPI_I2S_TransmitData(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(const SPI_Module* SPIx);
void SPI_ConfigDataLen(SPI_Module* SPIx, uint16_t DataLen);
void SPI_ConfigBidirectionalMode(SPI_Module* SPIx, uint32_t DataDirection);

/* NSS management */
void SPI_SetNssLevel(SPI_Module* SPIx, uint32_t SPI_NSSInternalSoft);
void SPI_SSOutputEnable(SPI_Module* SPIx, FunctionalState Cmd);
void SPI_NssPolSet(SPI_Module* SPIx, uint16_t Level);
void SPI_NSSFailCRCStopEnable(SPI_Module* SPIx, FunctionalState Cmd);

/* CRC */
void SPI_TransmitCrcNext(SPI_Module* SPIx);
void SPI_TransmitCrcNextCmd(SPI_Module* SPIx, FunctionalState Cmd);
void SPI_EnableCalculateCrc(SPI_Module* SPIx, FunctionalState Cmd);
uint32_t SPI_GetCRCDat(const SPI_Module* SPIx, uint8_t SPI_CRC);
uint32_t SPI_GetCRCPoly(const SPI_Module* SPIx);

/* Sampling delay */
void SPI_DelayTime_Set(SPI_Module* SPIx,uint16_t DelayTime);
uint16_t SPI_DelayTime_Get(const SPI_Module* SPIx);

/* DMA */
void SPI_I2S_EnableDma(SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd);

/* Interrupt and flag management */
void SPI_I2S_EnableInt(SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd);
FlagStatus SPI_I2S_GetStatus(const SPI_Module* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_ClrCRCErrFlag(SPI_Module* SPIx, uint32_t SPI_FLAG);
INTStatus SPI_I2S_GetIntStatus(const SPI_Module* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClrITPendingBit(SPI_Module* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__N32G41X_SPI_H__ */

