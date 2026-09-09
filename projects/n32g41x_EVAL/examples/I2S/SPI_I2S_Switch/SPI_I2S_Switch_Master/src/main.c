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
#include "delay.h"

/** SPI_I2S_Switch_Master - Board-to-board test with SPI_I2S_Switch_Slave **/

uint16_t I2S_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                       0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                       0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                       0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};

uint16_t SPI_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                       0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                       0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                       0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};

void RCC_Configuration(void);
void GPIO_Configuration(void);
void I2S_Master_TX(void);
void SPI_Master_TX(void);

/**
*\*\name    main.
*\*\fun     main function.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\n This is SPI I2S Switch Master demo!!\r\n");

    RCC_Configuration();

    /* Delay 1s for Slave to be ready when doing board-to-board test */
    SysTick_Delay_Ms(1000);

    GPIO_Configuration();

    /* Step 1: I2S mode - Master TX */
    log_info("\r\n Step 1: I2S Master TX...\r\n");
    I2S_Master_TX();
    log_info(" Step 1: I2S TX completed!\r\n");

    /* Delay for slave to switch mode */
    SysTick_Delay_Ms(100);

    /* Step 2: Switch to SPI mode - Master TX */
    log_info("\r\n Step 2: SPI Master TX...\r\n");
    SPI_Master_TX();
    log_info(" Step 2: SPI TX completed!\r\n");

    /* Delay for slave to switch mode */
    SysTick_Delay_Ms(100);

    /* Step 3: Switch back to I2S mode - Master TX */
    log_info("\r\n Step 3: I2S Master TX (again)...\r\n");
    I2S_Master_TX();
    log_info(" Step 3: I2S TX completed!\r\n");

    log_info("\r\n All steps done! Master finished.\r\n");

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
    RCC_EnableAPB2PeriphClk(SPI_I2S_MASTER_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure SPI1/I2S1 master GPIO pins.
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
*\*\name    I2S_Master_TX.
*\*\fun     Configure SPI1 as I2S master TX and send data by polling.
*\*\param   none
*\*\return  none
**/
void I2S_Master_TX(void)
{
    I2S_InitType I2S_InitStructure;
    RCC_ClocksType RCC_Clocks;
    uint8_t idx;

    SPI_I2S_DeInit(SPI_I2S_MASTER);

    /* Configure I2S clock source as system clock */
    RCC_ConfigI2SClk(RCC_I2S_CLKSEL_SYS);

    /* I2S configuration */
    I2S_InitStruct(&I2S_InitStructure);
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS_EXTENDED;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_48K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    RCC_GetClocksFreqValue(&RCC_Clocks);
    I2S_InitStructure.ClkSrcFrequency = RCC_Clocks.SysclkFreq;

    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(SPI_I2S_MASTER, &I2S_InitStructure);

    /* Enable I2S */
    I2S_Enable(SPI_I2S_MASTER, ENABLE);

    /* Send data by polling */
    for (idx = 0; idx < BufferSize; idx++)
    {
        while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_TE_FLAG) == RESET)
            ;
        SPI_I2S_TransmitData(SPI_I2S_MASTER, I2S_Buffer_Tx[idx]);
    }

    /* Wait until I2S is not busy */
    while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_TE_FLAG) == RESET)
        ;
    while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_BUSY_FLAG) != RESET)
        ;

    /* Disable I2S */
    I2S_Enable(SPI_I2S_MASTER, DISABLE);
}

/**
*\*\name    SPI_Master_TX.
*\*\fun     Switch to SPI mode, SPI1 master single-line TX.
*\*\param   none
*\*\return  none
**/
void SPI_Master_TX(void)
{
    SPI_InitType SPI_InitStructure;
    uint8_t idx;

    /* Switch to SPI mode */
    SPI_I2S_DeInit(SPI_I2S_MASTER);

    SPI_InitStruct(&SPI_InitStructure);

    /* SPI1 master: single-line TX, 16-bit */
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen      = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA       = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS          = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_32;
    SPI_InitStructure.FirstBit     = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly     = 7;
    SPI_Init(SPI_I2S_MASTER, &SPI_InitStructure);

    /* Enable SPI1 master */
    SPI_Enable(SPI_I2S_MASTER, ENABLE);

    /* Send data by polling */
    for (idx = 0; idx < BufferSize; idx++)
    {
        while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_TE_FLAG) == RESET)
            ;
        SPI_I2S_TransmitData(SPI_I2S_MASTER, SPI_Buffer_Tx[idx]);
    }

    /* Wait until SPI is not busy */
    while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_TE_FLAG) == RESET)
        ;
    while (SPI_I2S_GetStatus(SPI_I2S_MASTER, SPI_I2S_BUSY_FLAG) != RESET)
        ;

    /* Disable SPI */
    SPI_Enable(SPI_I2S_MASTER, DISABLE);
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
