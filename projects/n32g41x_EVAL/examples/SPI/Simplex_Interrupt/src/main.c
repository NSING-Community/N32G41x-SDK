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

/** Simplex_Interrupt **/

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
uint8_t SPI_Slave_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\nSPI Simplex Interrupt Demo\r\n");

    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();

    SPI_InitStruct(&SPI_InitStructure);
    /* SPI_Master configuration: single line TX, master mode */
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_HARD;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_Slave configuration: single line RX, slave mode */
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
    SPI_InitStructure.SpiMode      = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_Master NSS output for master mode */
    SPI_SSOutputEnable(SPI_MASTER, ENABLE);

    /* Enable SPI_Master TXE interrupt */
    SPI_I2S_EnableInt(SPI_MASTER, SPI_I2S_INT_TE, ENABLE);
    /* Enable SPI_Slave RXNE interrupt */
    SPI_I2S_EnableInt(SPI_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable SPI_Slave */
    SPI_Enable(SPI_SLAVE, ENABLE);
    /* Enable SPI_Master */
    SPI_Enable(SPI_MASTER, ENABLE);

    /* Wait for transfer to complete */
    while (RxIdx < BufferSize)
    {
    }

    TransferStatus = Buffercmp(SPI_Slave_Buffer_Rx, SPI_Master_Buffer_Tx, BufferSize);

    if (TransferStatus == PASSED)
    {
        log_info("Test PASSED!\r\n");
    }
    else
    {
        log_info("Test FAILED!\r\n");
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
    /* Enable SPI_Master and SPI_Slave clocks */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_CLK | SPI_SLAVE_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports for SPI.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);

    /* SPI_Master: NSS(PA4) SCK(PA5) and MOSI(PA7) as AF push-pull */
    GPIO_InitStructure.Pin            = SPI_MASTER_NSS_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_NSS_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(SPI_MASTER_NSS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = SPI_MASTER_SCK_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_SCK_AF;
    GPIO_InitPeripheral(SPI_MASTER_SCK_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = SPI_MASTER_MOSI_PIN;
    GPIO_InitStructure.GPIO_Alternate = SPI_MASTER_MOSI_AF;
    GPIO_InitPeripheral(SPI_MASTER_MOSI_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: NSS(PB12) as input */
    GPIO_InitStructure.Pin            = SPI_SLAVE_NSS_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_NSS_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(SPI_SLAVE_NSS_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: SCK(PB13) as input */
    GPIO_InitStructure.Pin            = SPI_SLAVE_SCK_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_SCK_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(SPI_SLAVE_SCK_GPIO, &GPIO_InitStructure);

    /* SPI_SLAVE: MISO(PB14) as AF_PP (slave single-line RX) */
    GPIO_InitStructure.Pin            = SPI_SLAVE_MISO_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = SPI_SLAVE_MISO_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(SPI_SLAVE_MISO_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures NVIC for SPI interrupts.
*\*\param   none
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* SPI_Master interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = SPI_MASTER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* SPI_Slave interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = SPI_SLAVE_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
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
