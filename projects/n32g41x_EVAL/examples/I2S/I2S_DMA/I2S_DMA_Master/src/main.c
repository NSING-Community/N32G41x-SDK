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

/** I2S_DMA_Master **/

#define BufferSize 32

const uint16_t I2S_MASTER_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
																									 0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
																									 0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
																									 0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};
void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);
void I2S_Configuration(void);

/**
*\*\name    main.
*\*\fun     main function.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\n This is I2S DMA Master TX demo!!\r\n");

    RCC_Configuration();
    /* Delay 1s for Slave to be ready when doing board-to-board test */
    SysTick_Delay_Ms(1000);
    GPIO_Configuration();
    DMA_Configuration();
    I2S_Configuration();

    /* Enable I2S DMA TX request */
    SPI_I2S_EnableDma(I2S_MASTER, SPI_I2S_DMA_TX, ENABLE);

    /* Enable DMA TX channel */
    DMA_EnableChannel(I2S_MASTER_Tx_DMA_Channel, ENABLE);

    /* Enable I2S */
    I2S_Enable(I2S_MASTER, ENABLE);

    /* Wait for DMA TX transfer complete */
    while (!DMA_GetFlagStatus(I2S_MASTER_Tx_DMA_FLAG, DMA))
        ;

    /* Wait until I2S TX buffer is empty and bus is not busy */
    while (SPI_I2S_GetStatus(I2S_MASTER, SPI_I2S_TE_FLAG) == RESET)
        ;
    while (SPI_I2S_GetStatus(I2S_MASTER, SPI_I2S_BUSY_FLAG) != RESET)
        ;

    log_info("\r\n I2S DMA Master TX transfer completed! Test results from the slave print output!!\r\n");

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Enable DMA, GPIO and SPI/I2S clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable DMA clock */
    RCC_EnableAHBPeriphClk(I2S_MASTER_DMA_CLK, ENABLE);

    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable SPI1/I2S1 clock */
    RCC_EnableAPB2PeriphClk(I2S_MASTER_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure I2S master GPIO pins.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* I2S_MASTER: WS(PA4) as AF_PP */
    GPIO_InitStructure.Pin            = I2S_MASTER_WS_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = I2S_MASTER_WS_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(I2S_MASTER_WS_GPIO, &GPIO_InitStructure);

    /* I2S_MASTER: CK(PA5) as AF_PP */
    GPIO_InitStructure.Pin            = I2S_MASTER_CK_PIN;
    GPIO_InitStructure.GPIO_Alternate = I2S_MASTER_CK_AF;
    GPIO_InitPeripheral(I2S_MASTER_CK_GPIO, &GPIO_InitStructure);

    /* I2S_MASTER: SD(PA7) as AF_PP */
    GPIO_InitStructure.Pin            = I2S_MASTER_SD_PIN;
    GPIO_InitStructure.GPIO_Alternate = I2S_MASTER_SD_AF;
    GPIO_InitPeripheral(I2S_MASTER_SD_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    DMA_Configuration.
*\*\fun     Configure DMA for I2S TX.
*\*\param   none
*\*\return  none
**/
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* I2S_MASTER TX DMA channel configuration */
    DMA_DeInit(I2S_MASTER_Tx_DMA_Channel);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&I2S_MASTER->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)I2S_MASTER_Buffer_Tx;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = BufferSize;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(I2S_MASTER_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(I2S_MASTER_Tx_DMA_Remap, DMA, I2S_MASTER_Tx_DMA_Channel, ENABLE);
}

/**
*\*\name    I2S_Configuration.
*\*\fun     Configure I2S master TX.
*\*\param   none
*\*\return  none
**/
void I2S_Configuration(void)
{
    I2S_InitType I2S_InitStructure;
    RCC_ClocksType RCC_Clocks;

    SPI_I2S_DeInit(I2S_MASTER);

    /* Configure I2S clock source as system clock */
    RCC_ConfigI2SClk(RCC_I2S_CLKSEL_SYS);

    /* I2S configuration */
    I2S_InitStruct(&I2S_InitStructure);
    I2S_InitStructure.Standard       = I2S_STD_PHILLIPS;
    I2S_InitStructure.DataFormat     = I2S_DATA_FMT_16BITS_EXTENDED;
    I2S_InitStructure.MCLKEnable     = I2S_MCLK_DISABLE;
    I2S_InitStructure.AudioFrequency = I2S_AUDIO_FREQ_48K;
    I2S_InitStructure.CLKPOL         = I2S_CLKPOL_LOW;

    /* Get system clock frequency for I2S clock calculation */
    RCC_GetClocksFreqValue(&RCC_Clocks);
    I2S_InitStructure.ClkSrcFrequency = RCC_Clocks.SysclkFreq;

    /* Configure I2S1 as Master TX */
    I2S_InitStructure.I2sMode = I2S_MODE_MASTER_TX;
    I2S_Init(I2S_MASTER, &I2S_InitStructure);
}

#ifdef USE_FULL_ASSERT
/**
*\*\name    assert_failed.
*\*\fun     Reports the name of the source file and line number where assert_param error occurred.
*\*\param   expr - pointer to the assertion expression
*\*\param   file - pointer to the source file name
*\*\param   line - assert_param error line source number
*\*\return  none
**/
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif
