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

/** FullDuplex_SoftNSS **/

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize 32

SPI_InitType SPI_InitStructure;
uint8_t SPI_Master_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                            0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                            0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPI_Slave_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
                                           0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                                           0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70};
uint8_t SPI_Master_Buffer_Rx[BufferSize], SPI_Slave_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(uint16_t SPI_Master_Mode, uint16_t SPI_Slave_Mode);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration */
    RCC_Configuration();

    log_init();
    log_info("\r\nSPI FullDuplex SoftNSS Demo\r\n");

    /* 1st phase: SPI_Master as Master and SPI_Slave as Slave */
    GPIO_Configuration(SPI_MODE_MASTER, SPI_MODE_SLAVE);

    SPI_InitStruct(&SPI_InitStructure);
    /* SPI_Master Config */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit     = SPI_FB_LSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_Slave Config */
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_Master */
    SPI_Enable(SPI_MASTER, ENABLE);
    /* Enable SPI_Slave */
    SPI_Enable(SPI_SLAVE, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPI_Master Tx buffer empty */
        while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_TE_FLAG) == RESET)
            ;

        /* Send SPI_Slave data */
        SPI_I2S_TransmitData(SPI_SLAVE, SPI_Slave_Buffer_Tx[TxIdx]);
        /* Send SPI_Master data */
        SPI_I2S_TransmitData(SPI_MASTER, SPI_Master_Buffer_Tx[TxIdx++]);

        /* Wait for SPI_Slave data reception */
        while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_Slave received data */
        SPI_Slave_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI_SLAVE);

        /* Wait for SPI_Master data reception */
        while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_Master received data */
        SPI_Master_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI_MASTER);
    }

    /* Check the correctness of written data */
    TransferStatus1 = Buffercmp(SPI_Slave_Buffer_Rx, SPI_Master_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPI_Master_Buffer_Rx, SPI_Slave_Buffer_Tx, BufferSize);

    {
        TestStatus s1 = TransferStatus1;
        TestStatus s2 = TransferStatus2;
        if ((s1 == PASSED) && (s2 == PASSED))
        {
            log_info("Phase1: Master->Slave PASSED, Slave->Master PASSED\r\n");
        }
        else
        {
            log_info("Phase1: FAILED (Status1=%d, Status2=%d)\r\n", s1, s2);
        }
    }

    /* 2nd phase: SPI_Master as Slave and SPI_Slave as Master */
    GPIO_Configuration(SPI_MODE_SLAVE, SPI_MODE_MASTER);

    SPI_I2S_DeInit(SPI_MASTER);
    SPI_I2S_DeInit(SPI_SLAVE);

    SPI_InitStruct(&SPI_InitStructure);
    
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode      = SPI_MODE_SLAVE;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit     = SPI_FB_LSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_Slave Re-configuration as Master */
    SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_Slave */
    SPI_Enable(SPI_SLAVE, ENABLE);
    /* Enable SPI_Master */
    SPI_Enable(SPI_MASTER, ENABLE);

    /* Reset TxIdx, RxIdx indexes and receive tables values */
    TxIdx = 0;
    RxIdx = 0;

    for (k = 0; k < BufferSize; k++)
        SPI_Slave_Buffer_Rx[k] = 0;

    for (k = 0; k < BufferSize; k++)
        SPI_Master_Buffer_Rx[k] = 0;

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPI_Slave Tx buffer empty */
        while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_TE_FLAG) == RESET)
            ;

        /* Send SPI_Master data */
        SPI_I2S_TransmitData(SPI_MASTER, SPI_Master_Buffer_Tx[TxIdx]);
        /* Send SPI_Slave data */
        SPI_I2S_TransmitData(SPI_SLAVE, SPI_Slave_Buffer_Tx[TxIdx++]);

        /* Wait for SPI_Master data reception */
        while (SPI_I2S_GetStatus(SPI_MASTER, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_Master received data */
        SPI_Master_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI_MASTER);

        /* Wait for SPI_Slave data reception */
        while (SPI_I2S_GetStatus(SPI_SLAVE, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI_Slave received data */
        SPI_Slave_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI_SLAVE);
    }

    /* Check the correctness of written data */
    TransferStatus3 = Buffercmp(SPI_Slave_Buffer_Rx, SPI_Master_Buffer_Tx, BufferSize);
    TransferStatus4 = Buffercmp(SPI_Master_Buffer_Rx, SPI_Slave_Buffer_Tx, BufferSize);

    {
        TestStatus s3 = TransferStatus3;
        TestStatus s4 = TransferStatus4;
        if ((s3 == PASSED) && (s4 == PASSED))
        {
            log_info("Phase2: Master->Slave PASSED, Slave->Master PASSED\r\n");
        }
        else
        {
            log_info("Phase2: FAILED (Status3=%d, Status4=%d)\r\n", s3, s4);
        }
    }

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(SPI_MASTER_GPIO_CLK | SPI_SLAVE_GPIO_CLK, ENABLE);
    /* Enable SPI_Master and SPI_Slave clocks */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_CLK | SPI_SLAVE_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports for SPI.
*\*\param   SPI_Master_Mode - SPI_MODE_MASTER or SPI_MODE_SLAVE
*\*\param   SPI_Slave_Mode  - SPI_MODE_MASTER or SPI_MODE_SLAVE
*\*\return  none
**/
void GPIO_Configuration(uint16_t SPI_Master_Mode, uint16_t SPI_Slave_Mode)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure SPI_Master pins: SCK and MOSI */
    GPIO_InitStructure.Pin            = SPI_MASTER_SCK_PIN | SPI_MASTER_MOSI_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_SCK_AF;

    if (SPI_Master_Mode == SPI_MODE_MASTER)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    }
    GPIO_InitPeripheral(SPI_MASTER_SCK_GPIO, &GPIO_InitStructure);

    /* Configure SPI_Master pin: MISO */
    GPIO_InitStructure.Pin            = SPI_MASTER_MISO_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_MISO_AF;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;

    if (SPI_Master_Mode == SPI_MODE_MASTER)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    }
    GPIO_InitPeripheral(SPI_MASTER_MISO_GPIO, &GPIO_InitStructure);

    /* Configure SPI_Slave pins: SCK and MOSI */
    GPIO_InitStructure.Pin            = SPI_SLAVE_SCK_PIN | SPI_SLAVE_MOSI_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_SCK_AF;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;

    if (SPI_Slave_Mode == SPI_MODE_SLAVE)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    }
    GPIO_InitPeripheral(SPI_SLAVE_SCK_GPIO, &GPIO_InitStructure);

    /* Configure SPI_Slave pin: MISO */
    GPIO_InitStructure.Pin            = SPI_SLAVE_MISO_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MISO_AF;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;

    if (SPI_Slave_Mode == SPI_MODE_SLAVE)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    }
    else
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    }
    GPIO_InitPeripheral(SPI_SLAVE_MISO_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1 - pointer to first buffer
*\*\param   pBuffer2 - pointer to second buffer
*\*\param   BufferLength - buffer length
*\*\return  FAILED or PASSED
**/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}
