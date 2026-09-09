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
*\*\file      n32g41x_spi.c
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved. 
**/

#include "n32g41x_spi.h"
#include "n32g41x_rcc.h"

/* SPI Driving Functions Declaration */

/* SPI_Private_Defines  */

/* SPI SPIEN mask */
#define CTRL2_SPIEN_ENABLE          ((uint16_t)SPI_CTRL2_SPIEN)
#define CTRL2_SPIEN_DISABLE         ((uint16_t)~SPI_CTRL2_SPIEN)

/* I2S I2SEN mask */
#define I2SCFG_I2SEN_ENABLE         ((uint16_t)SPI_I2SCFG_I2SEN)
#define I2SCFG_I2SEN_DISABLE        ((uint16_t)~SPI_I2SCFG_I2SEN)

/* SPI SSOE mask */
#define CTRL1_SSOEN_ENABLE          ((uint16_t)SPI_CTRL1_SSOEN)
#define CTRL1_SSOEN_DISABLE         ((uint16_t)~SPI_CTRL1_SSOEN)

/* SPI CRCEN  */
#define CTRL2_CRCEN_ENABLE          ((uint16_t)SPI_CTRL2_CRCEN)
#define CTRL2_CRCEN_DISABLE         ((uint16_t)~SPI_CTRL2_CRCEN)

/* SPI CRCSTP */
#define CTRL2_CRC_STOP_CACULATE     ((uint16_t)SPI_CTRL2_CRCSTOP)
#define CTRL2_CRC_CONTINUE_CACULATE ((uint16_t)~SPI_CTRL2_CRCSTOP)

/* SPI_I2S_CFGR */
#define SPI_I2S_CFGR_PCM_BYPASS     ((uint16_t)SPI_I2SCFG_PCMBYPASS)
#define SPI_I2S_CFGR_PCM_NOBYPASS   ((uint16_t)~SPI_I2SCFG_PCMBYPASS)

/* SPI or I2S mode selection masks */
#define SPI_MODE_ENABLE             ((uint16_t)~SPI_I2SCFG_MODSEL)
#define I2S_MODE_ENABLE             ((uint16_t)SPI_I2SCFG_MODSEL)

/* SPI registers Masks */ 
#define CTRL1_CLR_MASK              ((uint16_t)(~(SPI_CTRL1_BIDIRMODE | SPI_CTRL1_BIDIROEN | SPI_CTRL1_RONLY | SPI_CTRL1_SSMEN | SPI_CTRL1_SSEL | \
                                                 SPI_CTRL1_DATFF | SPI_CTRL1_LSBFF | SPI_CTRL1_MSEL | SPI_CTRL1_CLKPHA | SPI_CTRL1_CLKPOL | SPI_CTRL1_BR)))   
#define I2SCFG_CLR_MASK             ((uint16_t)(~(SPI_I2SCFG_CLKPOL | SPI_I2SCFG_PCMFSYNC | SPI_I2SCFG_CHBITS | SPI_I2SCFG_TDATLEN | \
                                                  SPI_I2SCFG_MODCFG | SPI_I2SCFG_STDSEL | SPI_I2SCFG_MODSEL | SPI_I2SCFG_I2SEN)))



/**
*\*\name    SPI_I2S_DeInit.
*\*\fun     Reset the SPI/I2S registers.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2
*\*\return  none
**/
void SPI_I2S_DeInit(const SPI_Module* SPIx)
{
    if (SPIx == SPI1)
    {
        /* SPI1 Reset */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI1);
    }
    else if (SPIx == SPI2)
    {
        /* SPI2 Reset */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI2);
    }
    else
    {
      /* no process */
    }
}

/**
*\*\name    SPI_Init.
*\*\fun     Initializes the SPIx peripheral according to the specified parameters in the SPI_InitStruct.
*\*\param   SPIx :
*\*\          - SPI1   
*\*\          - SPI2
*\*\param   SPI_InitParam :
*\*\          - DataDirection
*\*\            - SPI_DIR_DOUBLELINE_FULLDUPLEX
*\*\            - SPI_DIR_DOUBLELINE_RONLY     
*\*\            - SPI_DIR_SINGLELINE_RX        
*\*\            - SPI_DIR_SINGLELINE_TX 
*\*\          - SpiMode
*\*\            - SPI_MODE_MASTER
*\*\            - SPI_MODE_SLAVE
*\*\          - DataLen
*\*\            - SPI_DATA_SIZE_16BITS
*\*\            - SPI_DATA_SIZE_8BITS
*\*\            - SPI_DATA_SIZE_9BITS (Only valid for SPI2)
*\*\          - CLKPOL
*\*\            - SPI_CLKPOL_LOW 
*\*\            - SPI_CLKPOL_HIGH
*\*\          - CLKPHA
*\*\            - SPI_CLKPHA_FIRST_EDGE 
*\*\            - SPI_CLKPHA_SECOND_EDGE
*\*\          - NSS
*\*\            - SPI_NSS_SOFT
*\*\            - SPI_NSS_HARD
*\*\          - BaudRatePres
*\*\            - SPI_BR_PRESCALER_2  
*\*\            - SPI_BR_PRESCALER_4  
*\*\            - SPI_BR_PRESCALER_8  
*\*\            - SPI_BR_PRESCALER_16 
*\*\            - SPI_BR_PRESCALER_32 
*\*\            - SPI_BR_PRESCALER_64 
*\*\            - SPI_BR_PRESCALER_128
*\*\            - SPI_BR_PRESCALER_256
*\*\          - FirstBit
*\*\            - SPI_FB_MSB
*\*\            - SPI_FB_LSB
*\*\          - CRCPoly     default 0x0007, max 0xffff 
*\*\return  none
**/
void SPI_Init(SPI_Module* SPIx, const SPI_InitType* SPI_InitParam)
{
    uint16_t tmpregister;
    uint16_t tmpregister1;

    /*---------------------------- SPIx CTRL1 Configuration ------------------------*/
    /* Get the SPIx CTRL1 value */
    tmpregister = SPIx->CTRL1;
    /* Clear: BIDIRMODE | BIDIROEN | RONLY | SSMEN | SSEL |  DATFF | LSBFF | MSEL | CLKPHA | CLKPOL | BR */
    tmpregister &= CTRL1_CLR_MASK;

    /* Get the SPIx CTRL1 value */
    tmpregister1 = SPIx->CTRL2;
    /* Clear: DATFF9 */
    tmpregister1 &= ~SPI_CTRL2_DATFF9;

    /* SPI CTRL2 DATFF9 (Only valid for SPI2) */
    if ((SPIx == SPI2) && (SPI_InitParam->DataLen == SPI_DATA_SIZE_9BITS))
    {
        tmpregister1 |= SPI_DATA_SIZE_9BITS;
    }
    else
    {
        tmpregister |= SPI_InitParam->DataLen;
    }

    /* Write to SPIx CTRL2 */
    SPIx->CTRL2 = tmpregister1;

    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to DataDirection value */
    /* Set SSM, SSI and MSTR bits according to SpiMode and NSS values */
    /* Set LSBFirst bit according to FirstBit value */
    /* Set BR bits according to BaudRatePres value */
    /* Set CPOL bit according to CLKPOL value */
    /* Set CPHA bit according to CLKPHA value */
    tmpregister |= (uint16_t)((uint32_t)SPI_InitParam->DataDirection | SPI_InitParam->SpiMode | SPI_InitParam->CLKPOL | 
                                        SPI_InitParam->CLKPHA | SPI_InitParam->NSS | SPI_InitParam->BaudRatePres | SPI_InitParam->FirstBit);
    /* Write to SPIx CTRL1 */
    SPIx->CTRL1 = tmpregister;

    /* Activate the SPI mode (Reset I2SMOD bit in SPI_I2S_CFGR register) */
    SPIx->SPI_I2S_CFGR &= SPI_MODE_ENABLE;

    /* SPIx CRCPOLY Configuration */
    /* Write to SPIx CRCPOLY */
    SPIx->CRCPOLY = SPI_InitParam->CRCPoly;
}



/**
*\*\name    I2S_Init.
*\*\fun     Initializes the SPIx peripheral according to the specified parameters in the I2S_InitStruct.
*\*\param   SPIx :
*\*\          - SPI1
*\*\param   I2S_InitParam :
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX 
*\*\           - I2S_MODE_SlAVE_RX 
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS      
*\*\           - I2S_STD_MSB_ALIGN     
*\*\           - I2S_STD_LSB_ALIGN     
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME 
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS          
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED 
*\*\           - I2S_DATA_FMT_24BITS          
*\*\           - I2S_DATA_FMT_32BITS          
*\*\          - MCLKEnable
*\*\           - I2S_MCLK_ENABLE 
*\*\           - I2S_MCLK_DISABLE
*\*\          - AudioFrequency
*\*\           - I2S_AUDIO_FREQ_192K   
*\*\           - I2S_AUDIO_FREQ_96K    
*\*\           - I2S_AUDIO_FREQ_48K    
*\*\           - I2S_AUDIO_FREQ_44K    
*\*\           - I2S_AUDIO_FREQ_32K    
*\*\           - I2S_AUDIO_FREQ_22K    
*\*\           - I2S_AUDIO_FREQ_16K    
*\*\           - I2S_AUDIO_FREQ_11K    
*\*\           - I2S_AUDIO_FREQ_8K     
*\*\           - I2S_AUDIO_FREQ_DEFAULT
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW 
*\*\           - I2S_CLKPOL_HIGH
*\*\          - ClkSrcFrequency
*\*\           - RCC_Clocks.SysclkFreq
*\*\           - user defined
**/
void I2S_Init(SPI_Module* SPIx, const I2S_InitType* I2S_InitParam)
{
    uint16_t tmpregister, i2sdiv, i2sodd, packetlength;
    uint32_t tmp;
    uint32_t sourceclock;

    /*----------------------- SPIx SPI_I2S_CFGR & I2SPREDIV Configuration -----------------*/
    /* Clear: PCMBYPASS | CLKPOL | PCMFSYNC | CHBITS | CHBITS | DATLEN | MODCFG | STDSEL| MODSEL | I2SEN */
    SPIx->SPI_I2S_CFGR &= I2SCFG_CLR_MASK;
    SPIx->I2SPREDIV = 0x0002;

    /* Get the SPI_I2S_CFGR register value */
    tmpregister = SPIx->SPI_I2S_CFGR;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
    if (I2S_InitParam->AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    /* If the requested audio frequency is not the default, compute the prescaler */
    else
    {
        /* Check the frame length (For the Prescaler computing) */
        if (I2S_InitParam->DataFormat == I2S_DATA_FMT_16BITS)
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }
        else
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }

        /* Get the source clock value: based on System Clock value */
        sourceclock = I2S_InitParam->ClkSrcFrequency;
                
        /* Compute the Real divider depending on the MCLK output state with a floating point */
        if (I2S_InitParam->MCLKEnable == I2S_MCLK_ENABLE)
        {
            /* When MCLK is enabled, the divider directly targets MCLK instead of CLK */
            /* N32 consistently uses a ratio of 256 between the MCLK and the sampling frequency(Fs) 
               So MCLK = 256 * Fs -----> I2SDIV = sourceclock / (256 × FS) */
            
            /* (sourceclock / 256): is the basic part of the formula */
            /* ((sourceclock / 256) * 10): increase by ten times, which will improve the calculation precision by one decimal place*/
            /* ((((sourceclock / 256) * 10) / I2S_InitParam->AudioFrequency)): Obtain a frequency division factor that is magnified ten times */
            /* (((((sourceclock / 256) * 10) / I2S_InitParam->AudioFrequency)) + 5): Adding 5 before dividing by 10 is equivalent to rounding the final result */
            tmp = (uint16_t)(((((sourceclock / 256U) * 10U) / I2S_InitParam->AudioFrequency)) + 5U);
        }
        else
        {
            /* MCLK output is disabled */
            /* When MCLK output is disabled, the direct target of the divider generates CLK bit-clock */
            /* In one Fs cycle, data for both the left and right channels needs to be transmitted, 
               with each channel transmitting data of a specified bit depth (such as 16-bit, 24-bit, or 32-bit).
               So  CLK = Fs * 2 * packetlength --------> sourceclock / I2SDIV = FS × 2 × packetlength
               Inside the I2S, after calculating the divider, a further 2 * 4 * 2 = 16 times division is performed.
               So  I2SDIV = sourceclock / (16 × 2 × packetlength × FS) = sourceclock / (32 × packetlength × FS) */

            /* (sourceclock / (32 * packetlength)): is the basic part of the formula */
            /* ((sourceclock / (32 * packetlength)) * 10): increase by ten times, which will improve the calculation precision by one decimal place*/
            /* ((((sourceclock / (32 * packetlength)) * 10) / I2S_InitParam->AudioFrequency)): Obtain a frequency division factor that is magnified ten times */
            /* (((((sourceclock / (32 * packetlength)) * 10) / I2S_InitParam->AudioFrequency)) + 5): Adding 5 before dividing by 10 is equivalent to rounding the final result */
            tmp = (uint16_t)(((((sourceclock / (32U * (uint32_t)packetlength)) * 10U) / I2S_InitParam->AudioFrequency)) + 5U);
        }

        /* Remove the floating point. The previous frequency division coefficient was amplified by 10 times, restore it. */
        tmp = tmp / 10U;

        /* Check the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001U);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2U);

        /* Get the Mask for the Odd bit (SPI_I2SPREDIV[10]) register */
        i2sodd = (uint16_t)(i2sodd << 10U);
    }

    /* Test if the divider is 1 or 0 or greater than 0x3FF */
    if ((i2sdiv < 2U) || (i2sdiv > 0x3FFU))
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to SPIx I2SPREDIV register the computed value */
    SPIx->I2SPREDIV = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitParam->MCLKEnable));

    /* Configure the I2S with the I2S_InitParam values */
    tmpregister |= (uint16_t)(
        I2S_MODE_ENABLE
        | (uint16_t)(I2S_InitParam->I2sMode
                     | (uint16_t)(I2S_InitParam->Standard
                                  | (uint16_t)(I2S_InitParam->DataFormat | (uint16_t)I2S_InitParam->CLKPOL))));

    /* Write to SPIx SPI_I2S_CFGR */
    SPIx->SPI_I2S_CFGR = tmpregister;
}



/**
*\*\name    SPI_InitStruct.
*\*\fun     Fills each SPI_InitStruct member with its default value.
*\*\param   SPI_InitStruct (The input parameters must be the following values):
*\*\          - DataDirection
*\*\          - SpiMode
*\*\          - DataLen
*\*\          - CLKPOL
*\*\          - CLKPHA
*\*\          - NSS      
*\*\          - BaudRatePres     
*\*\          - FirstBit      
*\*\return  none
**/
void SPI_InitStruct(SPI_InitType* SPI_StructInit)
{
    /* Initialize the DataDirection member */
    SPI_StructInit->DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    /* initialize the Mode member */
    SPI_StructInit->SpiMode       = SPI_MODE_SLAVE;
    /* initialize the DataLen member */
    SPI_StructInit->DataLen       = SPI_DATA_SIZE_8BITS;
    /* Initialize the CLKPOL member */
    SPI_StructInit->CLKPOL        = SPI_CLKPOL_LOW;
    /* Initialize the CLKPHA member */
    SPI_StructInit->CLKPHA        = SPI_CLKPHA_FIRST_EDGE;
    /* Initialize the NSS member */
    SPI_StructInit->NSS           = SPI_NSS_HARD;
    /* Initialize the BaudRatePres member */
    SPI_StructInit->BaudRatePres  = SPI_BR_PRESCALER_2;
    /* Initialize the FirstBit member */
    SPI_StructInit->FirstBit      = SPI_FB_MSB;
    /* Initialize the CRCPoly member */
    SPI_StructInit->CRCPoly = 7;
}
/**
*\*\name    I2S_InitStruct.
*\*\fun     Fills each I2S_InitStruct member with its default value.
*\*\param   I2S_StructInit :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - MCLKEnable
*\*\          - AudioFrequency
*\*\          - CLKPOL      
*\*\return  none
**/
void I2S_InitStruct(I2S_InitType* I2S_StructInit)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_StructInit->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_StructInit->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_StructInit->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the MCLKEnable member */
    I2S_StructInit->MCLKEnable = I2S_MCLK_DISABLE;

    /* Initialize the AudioFrequency member */
    I2S_StructInit->AudioFrequency = I2S_AUDIO_FREQ_DEFAULT;

    /* Initialize the CLKPOL member */
    I2S_StructInit->CLKPOL = I2S_CLKPOL_LOW;
}


/**
*\*\name    SPI_Enable.
*\*\fun     Enables or disables the specified SPI peripheral.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2    
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void SPI_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral */
        SPIx->CTRL2 |= CTRL2_SPIEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral */
        SPIx->CTRL2 &= CTRL2_SPIEN_DISABLE;
    }
}

/**
*\*\name    I2S_Enable.
*\*\fun     Enables or disables the specified SPI peripheral (in I2S mode).
*\*\param   SPIx :
*\*\          - SPI1
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral (in I2S mode) */
        SPIx->SPI_I2S_CFGR |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral (in I2S mode) */
        SPIx->SPI_I2S_CFGR &= I2SCFG_I2SEN_DISABLE;
    }
}

/**
*\*\name    SPI_I2S_EnableInt.
*\*\fun     Enables or disables the specified SPI/I2S interrupts.
*\*\param   SPIx :
*\*\         - SPI1   
*\*\         - SPI2 
*\*\param   SPI_I2S_IT :
*\*\         - SPI_I2S_INT_TE               
*\*\         - SPI_I2S_INT_RNE               
*\*\      	 - SPI_I2S_INT_ERR       
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void SPI_I2S_EnableInt(SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd)
{
    uint8_t itpos;
    uint16_t itmask;

    /* Get the SPI/I2S IT index */
    itpos = SPI_I2S_IT >> 4U;

    /* Set the IT mask */
    itmask = (uint16_t)1U << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S interrupt */
        SPIx->CTRL2 |= itmask;
    }
    else
    {
        /* Disable the selected SPI/I2S interrupt */
        SPIx->CTRL2 &= (uint16_t)~itmask;
    }
}

/**
*\*\name    SPI_I2S_EnableDma.
*\*\fun     Enables or disables the SPIx/I2Sx DMA interface.
*\*\param   SPIx :
*\*\         - SPI2
*\*\         - SPI1
*\*\param   SPI_I2S_DMAReq :
*\*\         - SPI_I2S_DMA_TX           
*\*\         - SPI_I2S_DMA_RX            
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void SPI_I2S_EnableDma(SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 |= SPI_I2S_DMAReq;
    }
    else
    {
        /* Disable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 &= (uint16_t)~SPI_I2S_DMAReq;
    }
}

/**
*\*\name    SPI_I2S_TransmitData.
*\*\fun     Transmits a Data through the SPIx/I2Sx peripheral.
*\*\param   SPIx :
*\*\         - SPI2
*\*\         - SPI1          
*\*\param   Data: Data to be transmitted 
*\*\return  none
**/
void SPI_I2S_TransmitData(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the DAT register the data to be sent */
    SPIx->DAT = Data;
}

/**
*\*\name    SPI_I2S_ReceiveData.
*\*\fun     Get SPI/I2S data from DAT register.
*\*\param   SPIx (The input parameters must be the following values):
*\*\        - SPI2
*\*\        - SPI1      
*\*\return  The data in the SPI_DAT register
**/
uint16_t SPI_I2S_ReceiveData(const SPI_Module* SPIx)
{
    /* Return the data in the SPI_DAT register */
    return ((uint16_t)SPIx->DAT);
}


/**
*\*\name    SPI_SetNssLevel.
*\*\fun     Configures internally by software the NSS pin for the selected SPI.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2    
*\*\param   SPI_NSSInternalSoft (The input parameters must be the following values):
*\*\          - SPI_NSS_HIGH Set NSS pin internally
*\*\          - SPI_NSS_LOW  Reset NSS pin internally
*\*\return  none
**/
void SPI_SetNssLevel(SPI_Module* SPIx, uint32_t SPI_NSSInternalSoft)
{
    if (SPI_NSSInternalSoft != SPI_NSS_LOW)
    {
        /* Set NSS pin internally by software */
        SPIx->CTRL1 |= SPI_NSS_HIGH;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SPIx->CTRL1 &= SPI_NSS_LOW;
    }
}

/**
*\*\name    SPI_SSOutputEnable.
*\*\fun     Configures internally by software the NSS pin for the selected SPI.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void SPI_SSOutputEnable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI SS output */
        SPIx->CTRL1 |= CTRL1_SSOEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI SS output */
        SPIx->CTRL1 &= CTRL1_SSOEN_DISABLE;
    }
}


/**
*\*\name    SPI_ConfigDataLen.
*\*\fun     Configures the data size for the selected SPI.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   DataLen (The input parameters must be the following values):
*\*\          - SPI_DATA_SIZE_16BITS
*\*\          - SPI_DATA_SIZE_8BITS
*\*\          - SPI_DATA_SIZE_9BITS (Only valid for SPI2)
*\*\return  none
**/
void SPI_ConfigDataLen(SPI_Module* SPIx, uint16_t DataLen)
{
    uint16_t tmpregister1, tmpregister2;

    tmpregister1 = SPIx->CTRL1;
    tmpregister2 = SPIx->CTRL2;
    tmpregister2 &= ~SPI_CTRL2_DATFF9;

    if ((SPIx == SPI2) && (DataLen == SPI_DATA_SIZE_9BITS))
    {
        tmpregister2 |= DataLen;
    }
    else
    {
        tmpregister1 &= ~SPI_CTRL1_DATFF;
        tmpregister1 |= DataLen;
    }

    SPIx->CTRL1 = tmpregister1;
    SPIx->CTRL2 = tmpregister2;
}


/**
*\*\name    SPI_TransmitCrcNext.
*\*\fun     Transmit the SPIx CRC value.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2
*\*\return  none
**/
void SPI_TransmitCrcNext(SPI_Module* SPIx)
{
    /* Set the SPI_CTRL1 CRCNEXT bit */
    SPIx->CTRL1 |= SPI_CTRL1_CRCNEXT;
}

/**
*\*\name    SPI_TransmitCrcNext.
*\*\fun     Transmit the SPIx CRC value.
*\*\          - SPI1   
*\*\          - SPI2
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE 
*\*\return  none
**/
void SPI_TransmitCrcNextCmd(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI CRC transmission */
        SPIx->CTRL1 |= SPI_CTRL1_CRCNEXT;
    }
    else
    {
        /* Disable the selected SPI CRC transmission */
        SPIx->CTRL1 &= (~SPI_CTRL1_CRCNEXT);
    }
}

/**
*\*\name    SPI_EnableCalculateCrc.
*\*\fun     Enables or disables the CRC value calculation of the transferred bytes.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void SPI_EnableCalculateCrc(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI CRC calculation */
        SPIx->CTRL2 |= CTRL2_CRCEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI CRC calculation */
        SPIx->CTRL2 &= CTRL2_CRCEN_DISABLE;
    }
}


/**
*\*\name    SPI_GetCRCDat.
*\*\fun     Get SPI CRC data from SPI_CRCTDAT/SPI_CRCRDAT register.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2     
*\*\param   SPI_CRC (The input parameters must be the following values):
*\*\          - SPI_CRC_TX       
*\*\          - SPI_CRC_RX        
*\*\return  Tx/Rx CRC register value.
**/
uint32_t SPI_GetCRCDat(const SPI_Module* SPIx, uint8_t SPI_CRC)
{
    uint32_t value_temp;
    if (SPI_CRC != SPI_CRC_RX)
    {
        /* return Tx CRC register value */
        value_temp = SPIx->CRCTDAT;
    }
    else
    {
        /* return Rx CRC register value */
        value_temp = SPIx->CRCRDAT;
    }
    return value_temp;
}

/**
*\*\name    SPI_GetCRCPoly.
*\*\fun     Get CRC Polynomial from SPI_CRC_POLY register.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2       
*\*\return  The CRC Polynomial register value.
**/
uint32_t SPI_GetCRCPoly(const SPI_Module* SPIx)
{
    /* Return the CRC polynomial register value */
    return SPIx->CRCPOLY;
}

/**
*\*\name    SPI_ConfigBidirectionalMode.
*\*\fun     Selects the data transfer direction in bi-directional mode for the specified SPI.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   DataDirection (The input parameters must be the following values):
*\*\          - SPI_BIDIRECTION_RX   
*\*\          - SPI_BIDIRECTION_TX
*\*\return  none
**/
void SPI_ConfigBidirectionalMode(SPI_Module* SPIx, uint32_t DataDirection)
{
    if (DataDirection == SPI_BIDIRECTION_TX)
    {
        /* Set the Tx only mode */
        SPIx->CTRL1 |= SPI_BIDIRECTION_TX;
    }
    else
    {
        /* Set the Rx only mode */
        SPIx->CTRL1 &= SPI_BIDIRECTION_RX;
    }
}


/**
*\*\name    SPI_I2S_GetStatus.
*\*\fun     Checks whether the specified SPI/I2S flag is set or not.
*\*\param   SPIx :
*\*\         - SPI1
*\*\         - SPI2
*\*\param   SPI_I2S_FLAG :
*\*\         - SPI_I2S_TE_FLAG  
*\*\         - SPI_I2S_RNE_FLAG 
*\*\         - SPI_I2S_BUSY_FLAG
*\*\         - SPI_CRCERR_FLAG  
*\*\         - SPI_MODERR_FLAG  
*\*\         - SPI_I2S_OVER_FLAG
*\*\         - I2S_UNDER_FLAG   
*\*\         - I2S_CHSIDE_FLAG  

*\*\return  The new state of SPI_I2S_FLAG (SET or RESET).
**/
FlagStatus SPI_I2S_GetStatus(const SPI_Module* SPIx, uint16_t SPI_I2S_FLAG)
{
    FlagStatus bitstatus;

    /* Check the status of the specified SPI/I2S flag */
    if ((SPIx->STS & SPI_I2S_FLAG) != (uint16_t)RESET)
    {
        /* SPI_I2S_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_I2S_FLAG status */
    return bitstatus;
}
/**
*\*\name    SPI_ClrCRCErrFlag.
*\*\fun     Clear SPI flag status.           
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2
*\*\param   SPI_FLAG (The input parameters must be the following values):
*\*\          - SPI_CRCERR_FLAG
*\*\return  none
*\*\note
*\*\        - OVER (OverRun error) flag is cleared by software sequence: a read
*\*\          operation to SPI_DAT register (SPI_I2S_ReceiveData()) followed by a read
*\*\          operation to SPI_STS register (SPI_I2S_GetStatus()).
*\*\        - UNDER (UnderRun error) flag is cleared by a read operation to
*\*\          SPI_STS register (SPI_I2S_GetStatus()).
*\*\        - MODERR (Mode Fault) flag is cleared by software sequence: a read/write
*\*\          operation to SPI_STS register (SPI_I2S_GetStatus()) followed by a
*\*\          write operation to SPI_CTRL1 register (SPI_Enable() to enable the SPI).
**/
void SPI_ClrCRCErrFlag(SPI_Module* SPIx, uint32_t SPI_FLAG)
{
    /* Clear the selected SPI CRC Error (CRCERR) flag */
     SPIx->STS = (uint16_t)~SPI_FLAG;
}

/**
*\*\name    SPI_I2S_GetIntStatus.
*\*\fun     Checks whether the specified SPI/I2S interrupt has occurred or not.
*\*\param   SPIx :
*\*\          - SPI1   
*\*\          - SPI2
*\*\          - I2S1
*\*\param   SPI_I2S_IT :         
*\*\         - SPI_I2S_INT_TE     
*\*\         - SPI_I2S_INT_RNE       
*\*\         - SPI_I2S_INT_OVER 
*\*\         - SPI_INT_MODERR 
*\*\         - SPI_INT_CRCERR
*\*\         - I2S_INT_UNDER  
*\*\return  The new state of SPI_I2S_IT (SET or RESET).
**/

INTStatus SPI_I2S_GetIntStatus(const SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    INTStatus bitstatus = RESET;
    uint8_t it_en_pos = 0;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* Get the SPI/I2S IT index */
    itpos = ((uint16_t)0x0001U) << (SPI_I2S_IT & 0x0FU);

    /* Get the SPI/I2S IT mask */
    it_en_pos = (SPI_I2S_IT >> 4U);

    /* Set the IT mask */
    itmask = ((uint16_t)0x0001U) << it_en_pos;

    /* Get the SPI_I2S_IT enable bit status */
    enablestatus = (SPIx->CTRL2 & (uint16_t)itmask);

    /* Check the status of the specified SPI/I2S interrupt */
    if (((SPIx->STS & itpos) != (uint16_t)RESET) && (enablestatus != 0U))
    {
        /* SPI_I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_IT is reset */
        bitstatus = RESET;
    }
    
    /* Return the SPI_I2S_IT status */
    return bitstatus;
}


/**
*\*\name    SPI_I2S_ClrITPendingBit.
*\*\fun     Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
*\*\param   SPIx :
*\*\          - SPI1   
*\*\          - SPI2
*\*\param   SPI_I2S_IT :
*\*\          - SPI_INT_CRCERR
*\*\return  none.
**/
void SPI_I2S_ClrITPendingBit(SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    uint16_t itpos;

    /* Get the SPI IT index */
    itpos = ((uint16_t)0x0001U) << (SPI_I2S_IT & 0x0FU);

    /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
    SPIx->STS = (uint16_t)~itpos;
}

/**
*\*\name    SPI_DelayTime_Set.
*\*\fun     SPI Master Sampling Delay Time Configuration.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   DelayTime (The input parameters must be the following values):
*\*\          - SPI_MASTER_SAMPLING_DELAY_BYPASS
*\*\          - SPI_MASTER_SAMPLING_DELAY_1_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_2_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_3_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_4_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_5_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_6_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_7_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_8_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_9_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_10_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_11_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_12_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_13_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_14_2_CLK
*\*\          - SPI_MASTER_SAMPLING_DELAY_15_2_CLK
*\*\return  The CRC Polynomial register value.
*\*\
*\*\note only be configured in SPI master full-duplex and SPI master receive mode
**/
void SPI_DelayTime_Set(SPI_Module* SPIx,uint16_t DelayTime)
{
    SPIx->CTRL3 = DelayTime;
}


/**
*\*\name    SPI_DelayTime_Get.
*\*\fun     Get SPI master clock delay time.
*\*\param   SPIx :
*\*\         - SPI1
*\*\         - SPI2
*\*\return  The clock delay time.
**/
uint16_t SPI_DelayTime_Get(const SPI_Module* SPIx)
{
    /* Return clock delay time. */
    return  SPIx->CTRL3;
}


/**
*\*\name    SPI_NSSFailCRCStopEnable.
*\*\fun     NSS failure, CRC calculation stops.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE: stop crc caculate
*\*\          - DISABLE: continue calculate crc
*\*\return  none
**/
void SPI_NSSFailCRCStopEnable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* NSS failure, CRC calculation continues. */
        SPIx->CTRL2 |= CTRL2_CRC_STOP_CACULATE;
    }
    else
    {
        /* NSS failure, CRC calculation stops. */
        SPIx->CTRL2 &= CTRL2_CRC_CONTINUE_CACULATE;
    }
}

/**
*\*\name    SPI_NssPolSet.
*\*\fun     NSS Polarity control.
*\*\param   SPIx (The input parameters must be the following values):
*\*\          - SPI1   
*\*\          - SPI2   
*\*\param   Level (The input parameters must be the following values):
*\*\          - NSS_LOW_LEVEL_VALID
*\*\          - NSS_HIGH_LEVEL_VALID
*\*\return  none
**/

void SPI_NssPolSet(SPI_Module* SPIx, uint16_t Level)
{
    uint16_t tmpregister;

    tmpregister = SPIx->CTRL2;
    tmpregister &= ~SPI_CTRL2_NSSPOL;
    tmpregister |= Level;

    SPIx->CTRL2 = tmpregister;
}

/**
*\*\name    I2S_Enable13BitPCMLongBypass.
*\*\fun     pcm long for 13bit is bypass select.
*\*\param   SPIx (The input parameters must be the following values):  
*\*\          - SPI1   
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_Enable13BitPCMLongBypass(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SPIx->SPI_I2S_CFGR |= SPI_I2S_CFGR_PCM_BYPASS;
    }
    else
    {
        SPIx->SPI_I2S_CFGR &= SPI_I2S_CFGR_PCM_NOBYPASS;
    }
}


