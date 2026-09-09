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

/** SPI_9Bit_Slave **/

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize 32

SPI_InitType SPI_InitStructure;

/* 9-bit TX data: slave sends 0x151~0x170 */
uint16_t SPI_Slave_Tx[BufferSize] = {
    0x151, 0x152, 0x153, 0x154, 0x155, 0x156, 0x157, 0x158,
    0x159, 0x15A, 0x15B, 0x15C, 0x15D, 0x15E, 0x15F, 0x160,
    0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167, 0x168,
    0x169, 0x16A, 0x16B, 0x16C, 0x16D, 0x16E, 0x16F, 0x170
};

/* Expected data from master (master sends 0x101~0x120) */
uint16_t SPI_Master_Expected[BufferSize] = {
    0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0x108,
    0x109, 0x10A, 0x10B, 0x10C, 0x10D, 0x10E, 0x10F, 0x110,
    0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118,
    0x119, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E, 0x11F, 0x120
};

uint16_t SPI_Slave_Rx[BufferSize];
uint8_t TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;

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
    /* System clocks configuration */
    RCC_Configuration();

    log_init();
    log_info("\r\nSPI2 9-Bit Slave Demo\r\n");

    /* GPIO configuration */
    GPIO_Configuration();

    /* SPI2 configuration: Slave, 9-bit, soft NSS, no CRC (9-bit does not support CRC) */
    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode      = SPI_MODE_SLAVE;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_9BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_64;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* Enable SPI2 */
    SPI_Enable(SPI2, ENABLE);

    log_info("Slave ready, waiting for master...\r\n");

    /* Pre-load first TX data before enabling SPI */
    SPI_I2S_TransmitData(SPI2, SPI_Slave_Tx[TxIdx++]);

    /* Transfer procedure */
    while (RxIdx < BufferSize)
    {
        /* Wait for Rx buffer not empty (master has sent a byte) */
        while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
            ;

        /* Read received 9-bit data */
        SPI_Slave_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI2);

        /* Load next TX data if available */
        if (TxIdx < BufferSize)
        {
            /* Wait for Tx buffer empty */
            while (SPI_I2S_GetStatus(SPI2, SPI_I2S_TE_FLAG) == RESET)
                ;
            SPI_I2S_TransmitData(SPI2, SPI_Slave_Tx[TxIdx++]);
        }
    }

    /* Verify received data */
    TransferStatus = Buffercmp(SPI_Slave_Rx, SPI_Master_Expected, BufferSize);

    if (TransferStatus == PASSED)
    {
        log_info("9-Bit Transfer PASSED!\r\n");
        /* LED1 ON: test passed */
        GPIO_ResetBits(LED1_PORT, LED1_PIN);
    }
    else
    {
        log_info("9-Bit Transfer FAILED!\r\n");
        log_info("Received data:\r\n");
        for (TxIdx = 0; TxIdx < BufferSize; TxIdx++)
        {
            log_info("  [%d] RX=0x%03X, Expected=0x%03X\r\n",
                     TxIdx, SPI_Slave_Rx[TxIdx], SPI_Master_Expected[TxIdx]);
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
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable SPI2 clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI2, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures GPIO pins for SPI2 slave and LED.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* SPI2 SCK: PB13 - input (slave receives clock) */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.Pin            = SPI2_SCK_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI2_SCK_AF;
    GPIO_InitPeripheral(SPI2_SCK_GPIO, &GPIO_InitStructure);

    /* SPI2 MOSI: PB15 - input (slave receives on MOSI) */
    GPIO_InitStructure.Pin            = SPI2_MOSI_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI2_MOSI_AF;
    GPIO_InitPeripheral(SPI2_MOSI_GPIO, &GPIO_InitStructure);

    /* SPI2 MISO: PB14 - AF push-pull (slave drives MISO) */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pin            = SPI2_MISO_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI2_MISO_AF;
    GPIO_InitPeripheral(SPI2_MISO_GPIO, &GPIO_InitStructure);

    /* LED1: PA8 - push-pull output */
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin       = LED1_PIN;
    GPIO_InitPeripheral(LED1_PORT, &GPIO_InitStructure);
    /* LED1 OFF initially */
    GPIO_SetBits(LED1_PORT, LED1_PIN);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two 16-bit buffers (only lower 9 bits are compared).
*\*\param   pBuffer1 - pointer to first buffer
*\*\param   pBuffer2 - pointer to second buffer
*\*\param   BufferLength - buffer length
*\*\return  FAILED or PASSED
**/
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if ((*pBuffer1 & 0x01FF) != (*pBuffer2 & 0x01FF))
        {
            return FAILED;
        }
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
