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

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize 32

SPI_InitType SPI_InitStructure;

uint16_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                             0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                             0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                             0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};
uint16_t SPI_SLAVE_Buffer_Tx[BufferSize]  = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                             0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                             0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                             0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};
uint16_t SPI_MASTER_Buffer_Rx[BufferSize], SPI_SLAVE_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0, RxIdx = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\n This is SPI CRC demo!!\r\n");

    /* System clocks configuration */
    RCC_Configuration();

    /* GPIO configuration */
    GPIO_Configuration();

    /* SPI_MASTER configuration: full-duplex, master, 16-bit */
    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_128;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_SLAVE configuration: full-duplex, slave, 16-bit */
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable CRC calculation */
    SPI_EnableCalculateCrc(SPI_MASTER, ENABLE);
    SPI_EnableCalculateCrc(SPI_SLAVE, ENABLE);

    /* Enable SPI peripherals */
    SPI_Enable(SPI_MASTER, ENABLE);
    SPI_Enable(SPI_SLAVE, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize - 1)
    {
        /* Wait for SPI_MASTER Tx buffer empty */
        while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_TE_FLAG) == RESET)
            ;
        /* Send SPI_SLAVE data */
        SPI_I2S_TransmitData(SPI_SLAVE, SPI_SLAVE_Buffer_Tx[TxIdx]);
        /* Send SPI_MASTER data */
        SPI_I2S_TransmitData(SPI_MASTER, SPI_MASTER_Buffer_Tx[TxIdx++]);
        /* Wait for SPI_SLAVE data reception */
        while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_SLAVE received data */
        SPI_SLAVE_Buffer_Rx[RxIdx] = (uint16_t)SPI_I2S_ReceiveData(SPI_SLAVE);
        /* Wait for SPI_MASTER data reception */
        while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_MASTER received data */
        SPI_MASTER_Buffer_Rx[RxIdx++] = (uint16_t)SPI_I2S_ReceiveData(SPI_MASTER);
    }

    /* Wait for SPI_MASTER Tx buffer empty */
    while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_TE_FLAG) == RESET)
        ;
    /* Wait for SPI_SLAVE Tx buffer empty */
    while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_TE_FLAG) == RESET)
        ;

    /* Send last SPI_SLAVE data */
    SPI_I2S_TransmitData(SPI_SLAVE, SPI_SLAVE_Buffer_Tx[TxIdx]);
    /* Enable SPI_SLAVE CRC transmission */
    SPI_TransmitCrcNext(SPI_SLAVE);
    /* Send last SPI_MASTER data */
    SPI_I2S_TransmitData(SPI_MASTER, SPI_MASTER_Buffer_Tx[TxIdx]);
    /* Enable SPI_MASTER CRC transmission */
    SPI_TransmitCrcNext(SPI_MASTER);

    /* Wait for SPI_MASTER last data reception */
    while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Read SPI_MASTER last received data */
    SPI_MASTER_Buffer_Rx[RxIdx] = (uint16_t)SPI_I2S_ReceiveData(SPI_MASTER);

    /* Wait for SPI_SLAVE last data reception */
    while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Read SPI_SLAVE last received data */
    SPI_SLAVE_Buffer_Rx[RxIdx] = (uint16_t)SPI_I2S_ReceiveData(SPI_SLAVE);

    /* Wait for SPI_MASTER data reception: CRC transmitted by SPI_SLAVE */
    while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Wait for SPI_SLAVE data reception: CRC transmitted by SPI_MASTER */
    while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /* Check the received data with the sent ones */
    TransferStatus1 = Buffercmp(SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPI_MASTER_Buffer_Rx, SPI_SLAVE_Buffer_Tx, BufferSize);

    /* Test on the SPI_MASTER CRC Error flag */
    if ((SPI_I2S_GetStatus(SPI_MASTER, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus2 = FAILED;
    }

    /* Test on the SPI_SLAVE CRC Error flag */
    if ((SPI_I2S_GetStatus(SPI_SLAVE, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus1 = FAILED;
    }

    /* Read SPI_MASTER received CRC value */
    CRC1Value = (uint16_t)SPI_I2S_ReceiveData(SPI_MASTER);
    /* Read SPI_SLAVE received CRC value */
    CRC2Value = (uint16_t)SPI_I2S_ReceiveData(SPI_SLAVE);

    {
        TestStatus s1 = TransferStatus1;
        TestStatus s2 = TransferStatus2;
        uint16_t crc1 = CRC1Value;
        uint16_t crc2 = CRC2Value;
        if ((s1 == PASSED) && (s2 == PASSED))
            log_info("\r\n Test PASS!! CRC1=0x%04X, CRC2=0x%04X\r\n", crc1, crc2);
        else
            log_info("\r\n Test fail!! Status1=%d, Status2=%d\r\n", s1, s2);
    }

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

    /* Enable SPI1 and SPI2 clocks (both on APB2) */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_CLK | SPI_SLAVE_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure SPI master and slave GPIO pins.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* SPI_MASTER: SCK(PA5), MOSI(PA7) as AF Push-Pull */
    GPIO_InitStructure.Pin            = SPI_MASTER_SCK_PIN | SPI_MASTER_MOSI_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_SCK_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(SPI_MASTER_SCK_GPIO, &GPIO_InitStructure);

    /* SPI_MASTER: MISO(PA6) as Input */
    GPIO_InitStructure.Pin            = SPI_MASTER_MISO_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_MISO_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(SPI_MASTER_MISO_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: SCK(PB13) as Input with pull-up */
    GPIO_InitStructure.Pin            = SPI_SLAVE_SCK_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_SCK_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(SPI_SLAVE_SCK_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: MOSI(PB15) as Input */
    GPIO_InitStructure.Pin            = SPI_SLAVE_MOSI_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MOSI_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(SPI_SLAVE_MOSI_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: MISO(PB14) as AF Push-Pull */
    GPIO_InitStructure.Pin            = SPI_SLAVE_MISO_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MISO_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(SPI_SLAVE_MISO_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compare two buffers.
*\*\param   pBuffer1: pointer to first buffer
*\*\param   pBuffer2: pointer to second buffer
*\*\param   BufferLength: buffer length to compare
*\*\return  PASSED or FAILED
**/
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
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
