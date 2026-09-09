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
*\*\file      spi_flash.c
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "spi_flash.h"

/**
*\*\name    sFLASH_LowLevel_DeInit.
*\*\fun     DeInit SPI Flash GPIO and peripheral.
*\*\param   none
*\*\return  none
**/
static void sFLASH_LowLevel_DeInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /*!< Disable the sFLASH_SPI  */
    SPI_Enable(sFLASH_SPI, DISABLE);

    /*!< DeInitializes the sFLASH_SPI */
    SPI_I2S_DeInit(sFLASH_SPI);

    /*!< sFLASH_SPI Periph clock disable */
    RCC_EnableAPB2PeriphClk(sFLASH_SPI_CLK, DISABLE);

    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;

    GPIO_InitStructure.Pin            = sFLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_SCK_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = sFLASH_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MISO_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = sFLASH_SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MOSI_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = sFLASH_CS_PIN;
    GPIO_InitPeripheral(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
*\*\name    sFLASH_LowLevel_Init.
*\*\fun     Init SPI Flash GPIO and enable clocks.
*\*\param   none
*\*\return  none
**/
static void sFLASH_LowLevel_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Enable GPIO and SPI clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);
    RCC_EnableAPB2PeriphClk(sFLASH_SPI_CLK, ENABLE);

    /* SCK */
    GPIO_InitStructure.Pin            = sFLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_SCK_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /* MOSI */
    GPIO_InitStructure.Pin            = sFLASH_SPI_MOSI_PIN;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MOSI_GPIO_AF;
    GPIO_InitPeripheral(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /* MISO */
    GPIO_InitStructure.Pin            = sFLASH_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Alternate = sFLASH_SPI_MISO_GPIO_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /* CS as GPIO output */
    GPIO_InitStructure.Pin       = sFLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
*\*\name    sFLASH_DeInit.
*\*\fun     DeInitializes the peripherals used by the SPI FLASH driver.
*\*\param   none
*\*\return  none
**/
void sFLASH_DeInit(void)
{
    sFLASH_LowLevel_DeInit();
}

/**
*\*\name    sFLASH_Init.
*\*\fun     Initializes the peripherals used by the SPI FLASH driver.
*\*\param   none
*\*\return  none
**/
void sFLASH_Init(void)
{
    SPI_InitType SPI_InitStructure;

    sFLASH_LowLevel_Init();
    sFLASH_CS_HIGH();

    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_16;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly      = 7;
    SPI_Init(sFLASH_SPI, &SPI_InitStructure);
    SPI_Enable(sFLASH_SPI, ENABLE);
}

/**
*\*\name    sFLASH_EraseSector.
*\*\fun     Erases the specified FLASH sector.
*\*\param   SectorAddr - address of the sector to erase
*\*\return  none
**/
void sFLASH_EraseSector(uint32_t SectorAddr)
{
    sFLASH_WriteEnable();
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_SE);
    sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
    sFLASH_SendByte(SectorAddr & 0xFF);
    sFLASH_CS_HIGH();
    sFLASH_WaitForWriteEnd();
}

/**
*\*\name    sFLASH_EraseBulk.
*\*\fun     Erases the entire FLASH.
*\*\param   none
*\*\return  none
**/
void sFLASH_EraseBulk(void)
{
    sFLASH_WriteEnable();
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_BE);
    sFLASH_CS_HIGH();
    sFLASH_WaitForWriteEnd();
}

/**
*\*\name    sFLASH_WritePage.
*\*\fun     Writes more than one byte to the FLASH with a single WRITE cycle (Page WRITE sequence).
*\*\param   pBuffer - pointer to the buffer containing the data to be written to the FLASH
*\*\param   WriteAddr - FLASH's internal address to write to
*\*\param   NumByteToWrite - number of bytes to write to the FLASH, must be equal or less than page size
*\*\return  none
**/
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    sFLASH_WriteEnable();
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_WRITE);
    sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
    sFLASH_SendByte(WriteAddr & 0xFF);
    while (NumByteToWrite--)
    {
        sFLASH_SendByte(*pBuffer);
        pBuffer++;
    }
    sFLASH_CS_HIGH();
    sFLASH_WaitForWriteEnd();
}

/**
*\*\name    sFLASH_WriteBuffer.
*\*\fun     Writes block of data to the FLASH. Uses Page WRITE sequence to reduce WRITE cycles.
*\*\param   pBuffer - pointer to the buffer containing the data to be written to the FLASH
*\*\param   WriteAddr - FLASH's internal address to write to
*\*\param   NumByteToWrite - number of bytes to write to the FLASH
*\*\return  none
**/
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr        = WriteAddr % sFLASH_SPI_PAGESIZE;
    count       = sFLASH_SPI_PAGESIZE - Addr;
    NumOfPage   = NumByteToWrite / sFLASH_SPI_PAGESIZE;
    NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

    if (Addr == 0)
    {
        if (NumOfPage == 0)
        {
            sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else
        {
            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }
            sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else
    {
        if (NumOfPage == 0)
        {
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                sFLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;
                sFLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else
        {
            NumByteToWrite -= count;
            NumOfPage   = NumByteToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;
            sFLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;
            while (NumOfPage--)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }
            if (NumOfSingle != 0)
            {
                sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
*\*\name    sFLASH_ReadBuffer.
*\*\fun     Reads a block of data from the FLASH.
*\*\param   pBuffer - pointer to the buffer that receives the data read from the FLASH
*\*\param   ReadAddr - FLASH's internal address to read from
*\*\param   NumByteToRead - number of bytes to read from the FLASH
*\*\return  none
**/
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_READ);
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);
    while (NumByteToRead--)
    {
        *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
        pBuffer++;
    }
    sFLASH_CS_HIGH();
}

/**
*\*\name    sFLASH_ReadID.
*\*\fun     Reads FLASH identification.
*\*\param   none
*\*\return  FLASH identification (32-bit ID value)
**/
uint32_t sFLASH_ReadID(void)
{
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

    sFLASH_CS_LOW();
    sFLASH_SendByte(0x9F);
    Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    sFLASH_CS_HIGH();
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}

/**
*\*\name    sFLASH_StartReadSequence.
*\*\fun     Initiates a read data byte (READ) sequence from the Flash.
*\*\param   ReadAddr - FLASH's internal address to read from
*\*\return  none
**/
void sFLASH_StartReadSequence(uint32_t ReadAddr)
{
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_READ);
    sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
    sFLASH_SendByte((ReadAddr & 0xFF00) >> 8);
    sFLASH_SendByte(ReadAddr & 0xFF);
}

/**
*\*\name    sFLASH_ReadByte.
*\*\fun     Reads a byte from the SPI Flash.
*\*\param   none
*\*\return  Byte read from the SPI Flash
*\*\note    This function must be used only if sFLASH_StartReadSequence has been previously called.
**/
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/**
*\*\name    sFLASH_SendByte.
*\*\fun     Sends a byte through the SPI interface and returns the byte received from the SPI bus.
*\*\param   byte - byte to send
*\*\return  The value of the received byte
**/
uint8_t sFLASH_SendByte(uint8_t byte)
{
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;
    SPI_I2S_TransmitData(sFLASH_SPI, byte);
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_BUSY_FLAG) != RESET)
        ;
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;
    return (uint8_t)SPI_I2S_ReceiveData(sFLASH_SPI);
}

/**
*\*\name    sFLASH_SendHalfWord.
*\*\fun     Sends a half word through the SPI interface and returns the half word received from the SPI bus.
*\*\param   HalfWord - half word to send
*\*\return  The value of the received half word
**/
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;
    SPI_I2S_TransmitData(sFLASH_SPI, HalfWord);
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_TE_FLAG) == RESET)
        ;
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_BUSY_FLAG) != RESET)
        ;
    while (SPI_I2S_GetStatus(sFLASH_SPI, SPI_I2S_RNE_FLAG) == RESET)
        ;
    return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/**
*\*\name    sFLASH_WriteEnable.
*\*\fun     Enables the write access to the FLASH.
*\*\param   none
*\*\return  none
**/
void sFLASH_WriteEnable(void)
{
    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_WREN);
    sFLASH_CS_HIGH();
}

/**
*\*\name    sFLASH_WaitForWriteEnd.
*\*\fun     Polls the status of the Write In Progress (WIP) flag in the FLASH's status register until write operation completes.
*\*\param   none
*\*\return  none
**/
void sFLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;

    sFLASH_CS_LOW();
    sFLASH_SendByte(sFLASH_CMD_RDSR);
    do
    {
        flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    } while ((flashstatus & sFLASH_WIP_FLAG) == SET);
    sFLASH_CS_HIGH();
}
