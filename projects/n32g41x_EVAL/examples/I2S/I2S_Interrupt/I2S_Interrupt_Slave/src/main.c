/**
*     Copyright (c) 2026, NSING Technologies Inc.
*
*     All rights reserved.
*
*     This software is the exclusive property of NSING Technologies Inc. (Hereinafter
* referred to as NSING). This software, and the product of NSING described herein
* (Hereinafter referred to as the Product) are owned by NSING under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NSING does not grant any license under its patents, copyrights, trademarks, or other
* intellectual property rights. Names and brands of third party may be mentioned or referred
* thereto (if any) for identification purposes only.
*
*     NSING reserves the right to make changes, corrections, enhancements, modifications, and
* improvements to this software at any time without notice. Please contact NSING and obtain
* the latest version of this software before placing orders.

*     Although NSING has attempted to provide accurate and reliable information, NSING assumes
* no responsibility for the accuracy and reliability of this software.
*
*     It is the responsibility of the user of this software to properly design, program, and test
* the functionality and safety of any application made of this information and any resulting product.
* In no event shall NSING be liable for any direct, indirect, incidental, special,exemplary, or
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NSING Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NSING and hold NSING
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NSING, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NSING products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations.
* User shall comply with any applicable export control laws and regulations promulgated and administered by
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "misc.h"
#include "log.h"

/*** I2S_Interrupt_Slave - Board-to-board test with I2S_Interrupt (Master) ***/

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

/* Expected data from Master (must match I2S_Interrupt Master demo) */
const uint16_t I2S_Expected_Buffer[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                                  0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                                  0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                                  0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};

uint16_t I2S_Buffer_Rx[BufferSize];
__IO uint32_t RxIdx       = 0;
TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void I2S_Configuration(void);
TestStatus Buffercmp(uint16_t *pBuffer1, const uint16_t *pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     Main function. Initialize I2S Slave RX, enable RxNE interrupt, wait for 32 words
*\*\        from Master, compare with expected data and output test result via USART.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("\r\n I2S Interrupt Slave RX demo - Board-to-board test\r\n");
    log_info(" Connect this board (Slave) to Master board: WS-WS, CK-CK, SD-SD\r\n");
    log_info(" Run Master first, then reset Slave (or power Slave after Master running)\r\n");

    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();
    I2S_Configuration();

    /* Enable the I2S1 RxNE interrupt */
    SPI_I2S_EnableInt(I2S_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable I2S Slave before Master starts */
    I2S_Enable(I2S_SLAVE, ENABLE);

    /* Wait for all data to be received */
    while (RxIdx < BufferSize)
    {
    }

    TransferStatus = Buffercmp(I2S_Buffer_Rx, I2S_Expected_Buffer, BufferSize);

    if (TransferStatus == PASSED)
    {
        log_info("\r\n I2S Slave RX transfer completed, data match! Test PASS!!\r\n");
    }
    else
    {
        log_info("\r\n I2S Slave RX completed but data mismatch! Test FAIL!!\r\n");
    }

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Enable GPIO and SPI1(I2S1) peripheral clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable SPI1/I2S1 clock */
    RCC_EnableAPB2PeriphClk(I2S_SLAVE_CLK, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configure I2S Slave GPIO pins: PA4(WS), PA5(CK), PA7(SD) in AF_PP mode.
*\*\        These pins receive clock, word select and data from Master.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* I2S_SLAVE: WS(PA4), CK(PA5), SD(PA7) - AF mode, peripheral uses as input from Master */
    GPIO_InitStructure.Pin            = I2S_SLAVE_WS_PIN;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = I2S_SLAVE_WS_AF;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitPeripheral(I2S_SLAVE_WS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = I2S_SLAVE_CK_PIN;
    GPIO_InitStructure.GPIO_Alternate = I2S_SLAVE_CK_AF;
    GPIO_InitPeripheral(I2S_SLAVE_CK_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = I2S_SLAVE_SD_PIN;
    GPIO_InitStructure.GPIO_Alternate = I2S_SLAVE_SD_AF;
    GPIO_InitPeripheral(I2S_SLAVE_SD_GPIO, &GPIO_InitStructure);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configure SPI1(I2S1) RxNE interrupt priority and enable NVIC channel.
*\*\param   none
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* SPI1/I2S1 IRQ channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel                   = I2S_SLAVE_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    I2S_Configuration.
*\*\fun     Configure I2S1 as Slave RX. Standard/format must match Master: Phillips,
*\*\        16-bit extended, 48KHz sample rate, CLKPOL low.
*\*\param   none
*\*\return  none
**/
void I2S_Configuration(void)
{
    I2S_InitType I2S_InitStructure;
    RCC_ClocksType RCC_Clocks;

    SPI_I2S_DeInit(I2S_SLAVE);

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

    /* Configure I2S1 as Slave RX */
    I2S_InitStructure.I2sMode = I2S_MODE_SlAVE_RX;
    I2S_Init(I2S_SLAVE, &I2S_InitStructure);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compare two 16-bit buffers byte by byte.
*\*\param   pBuffer1    Pointer to first buffer (received data)
*\*\param   pBuffer2    Pointer to second buffer (expected data)
*\*\param   BufferLength Number of half-words to compare
*\*\return  PASSED if all match, FAILED otherwise
**/
TestStatus Buffercmp(uint16_t *pBuffer1, const uint16_t *pBuffer2, uint16_t BufferLength)
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

#ifdef USE_FULL_ASSERT
/**
*\*\name    assert_failed.
*\*\fun     Called when assert_param macro fails. Report file/line and enter infinite loop.
*\*\param   expr    The expression that failed
*\*\param   file    Source file name
*\*\param   line    Line number in source file
*\*\return  none
**/
void assert_failed(const uint8_t *expr, const uint8_t *file, uint32_t line)
{
    while (1)
    {
    }
}
#endif
