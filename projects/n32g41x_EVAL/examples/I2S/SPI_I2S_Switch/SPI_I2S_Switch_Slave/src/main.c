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
*\*\file      main.c
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"

/** SPI_I2S_Switch_Slave - Board-to-board test with SPI_I2S_Switch_Master **/

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

/* Expected I2S data from Master (must match Master I2S_Buffer_Tx) */
const uint16_t I2S_Expected_Buffer[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                                    0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                                    0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                                    0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};

/* Expected SPI data from Master (must match Master SPI_Buffer_Tx) */
const uint16_t SPI_Expected_Buffer[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                                    0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                                    0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                                    0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};

__IO uint16_t I2S_Buffer_Rx[BufferSize];
__IO uint16_t SPI_Buffer_Rx[BufferSize];
TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED, TransferStatus3 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void I2S_Slave_RX(uint16_t *pBuf);
void SPI_Slave_RX(void);
TestStatus Buffercmp(uint16_t* pBuffer1, const uint16_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     main function.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\n This is SPI I2S Switch Slave demo!!\r\n");

    RCC_Configuration();
    GPIO_Configuration();

    /* Step 1: I2S mode - Slave RX */
    log_info("\r\n Step 1: Waiting for I2S Master TX...\r\n");
    I2S_Slave_RX((uint16_t*)I2S_Buffer_Rx);

    TransferStatus1 = Buffercmp((uint16_t*)I2S_Buffer_Rx, I2S_Expected_Buffer, BufferSize);
    if (TransferStatus1 == PASSED)
        log_info(" Step 1: I2S RX PASS!!\r\n");
    else
        log_info(" Step 1: I2S RX FAIL!!\r\n");

    /* Step 2: Switch to SPI mode - Slave RX */
    log_info("\r\n Step 2: Waiting for SPI Master TX...\r\n");
    SPI_Slave_RX();

    TransferStatus2 = Buffercmp((uint16_t*)SPI_Buffer_Rx, SPI_Expected_Buffer, BufferSize);
    if (TransferStatus2 == PASSED)
        log_info(" Step 2: SPI RX PASS!!\r\n");
    else
        log_info(" Step 2: SPI RX FAIL!!\r\n");

    /* Clear I2S RX buffer for step 3 */
    {
        uint8_t i;
        for (i = 0; i < BufferSize; i++)
            I2S_Buffer_Rx[i] = 0;
    }

    /* Step 3: Switch back to I2S mode - Slave RX */
    log_info("\r\n Step 3: Waiting for I2S Master TX (again)...\r\n");
    I2S_Slave_RX((uint16_t*)I2S_Buffer_Rx);

    TransferStatus3 = Buffercmp((uint16_t*)I2S_Buffer_Rx, I2S_Expected_Buffer, BufferSize);
    if (TransferStatus3 == PASSED)
        log_info(" Step 3: I2S RX PASS!!\r\n");
    else
        log_info(" Step 3: I2S RX FAIL!!\r\n");

    if (TransferStatus1 == PASSED && TransferStatus2 == PASSED && TransferStatus3 == PASSED)
        log_info("\r\n All Tests PASS!!\r\n");
    else
        log_info("\r\n Some Tests FAIL!!\r\n");

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Enable GPIO and SPI clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable SPI1 clock */
    RCC_EnableAPB2PeriphClk(SPI_I2S_SLAVE_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure SPI1/I2S1 slave GPIO pins.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* SPI1/I2S1: NSS/WS(PA4) as AF_PP */
    GPIO_InitStructure.Pin            = SPI_I2S_NSS_WS_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_I2S_NSS_WS_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(SPI_I2S_NSS_WS_GPIO, &GPIO_InitStructure);

    /* SPI1/I2S1: SCK/CK(PA5) as AF_PP */
    GPIO_InitStructure.Pin            = SPI_I2S_SCK_CK_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_I2S_SCK_CK_AF;
    GPIO_InitPeripheral(SPI_I2S_SCK_CK_GPIO, &GPIO_InitStructure);

    /* SPI1/I2S1: MOSI/SD(PA7) as AF_PP */
    GPIO_InitStructure.Pin            = SPI_I2S_MOSI_SD_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_I2S_MOSI_SD_AF;
    GPIO_InitPeripheral(SPI_I2S_MOSI_SD_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    I2S_Slave_RX.
*\*\fun     Configure SPI1 as I2S slave RX and receive data by polling.
*\*\param   pBuf: pointer to receive buffer
*\*\return  none
**/
void I2S_Slave_RX(uint16_t *pBuf)
{
    I2S_InitType I2S_InitStructure;
    RCC_ClocksType RCC_Clocks;
    uint8_t idx;

    SPI_I2S_DeInit(SPI_I2S_SLAVE);

    /* Configure I2S clock source as system clock */
    RCC_ConfigI2SClk(RCC_I2S_CLKSEL_SYS);

    /* I2S configuration - must match Master settings */
    I2S_InitStruct(&I2S_InitStructure);
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS_EXTENDED;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_48K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    RCC_GetClocksFreqValue(&RCC_Clocks);
    I2S_InitStructure.ClkSrcFrequency = RCC_Clocks.SysclkFreq;

    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_RX;
    I2S_Init(SPI_I2S_SLAVE, &I2S_InitStructure);

    /* Enable I2S Slave - must be enabled before Master starts */
    I2S_Enable(SPI_I2S_SLAVE, ENABLE);

    /* Receive data by polling */
    for (idx = 0; idx < BufferSize; idx++)
    {
        while (SPI_I2S_GetStatus(SPI_I2S_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
            ;
        pBuf[idx] = SPI_I2S_ReceiveData(SPI_I2S_SLAVE);
    }

    /* Disable I2S */
    I2S_Enable(SPI_I2S_SLAVE, DISABLE);
}

/**
*\*\name    SPI_Slave_RX.
*\*\fun     Switch to SPI mode, SPI1 slave double-line RX only.
*\*\param   none
*\*\return  none
**/
void SPI_Slave_RX(void)
{
    SPI_InitType SPI_InitStructure;
    uint8_t idx;

    /* Switch to SPI mode */
    SPI_I2S_DeInit(SPI_I2S_SLAVE);

    SPI_InitStruct(&SPI_InitStructure);

    /* SPI1 slave: double-line RX only, 16-bit */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_RONLY;
    SPI_InitStructure.SpiMode      = SPI_MODE_SLAVE;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_32;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly     = 7;
    SPI_Init(SPI_I2S_SLAVE, &SPI_InitStructure);

    /* Enable SPI1 slave */
    SPI_Enable(SPI_I2S_SLAVE, ENABLE);

    /* Receive data by polling */
    for (idx = 0; idx < BufferSize; idx++)
    {
        while (SPI_I2S_GetStatus(SPI_I2S_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
            ;
        SPI_Buffer_Rx[idx] = SPI_I2S_ReceiveData(SPI_I2S_SLAVE);
    }

    /* Disable SPI */
    SPI_Enable(SPI_I2S_SLAVE, DISABLE);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
*\*\return  FAILED or PASSED
**/
TestStatus Buffercmp(uint16_t* pBuffer1, const uint16_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
            return FAILED;
        pBuffer1++;
        pBuffer2++;
    }
    return PASSED;
}

#ifdef USE_FULL_ASSERT
/**
*\*\name    assert_failed.
*\*\fun     Assert failure handler for debug.
*\*\param   expr: failed expression string
*\*\param   file: source file name
*\*\param   line: line number
*\*\return  none
**/
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif
