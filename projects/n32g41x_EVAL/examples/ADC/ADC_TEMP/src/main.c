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
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "log.h"
#include "delay.h"

uint32_t T_value= 0;
uint32_t VTS_value= 0;

/* xx mV per degree Celsius by datasheet define */
#define     AVG_SLOPE           (0.0041f)

#define  TS_VALUE_ADDR   (30)

//#define VDDA_5V    1

#ifdef  VDDA_5V
#define  VREF_VALUE      (4.7)    //this value need be configured by the actual voltage reference. 
#define  VTS_ADDR        (0x1FFFF128U)
#else
#define  VREF_VALUE      (3.3)
#define  VTS_ADDR        (0x1FFFF120U)

#endif


ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADCConvertedValue;

__IO float TempValue;

void RCC_Configuration(void);
void DMA_Config(void);


/**
*\*\name    TempratureCalculate.
*\*\fun     Calculate temperature use float result.
*\*\param   TempAdVal :
*\*\          - Temperate sensor code value measured by ADC.
*\*\return  the internal temperate value of the chip.
**/
float TempratureCalculate(uint16_t TempAdVal)
{
    float Temperate,tempValue,VTS;
    uint32_t TSValue;

    /* Voltage value of temperature sensor */
    tempValue=TempAdVal*(VREF_VALUE/4095);

    TSValue= (((*(uint32_t*)(VTS_ADDR)) & 0x0000FFFF));
    
    VTS =  TSValue /1000.0f;  
    
    /* Get the temperature inside the chip */
    Temperate= ((VTS - tempValue)/AVG_SLOPE) + 25;

    return Temperate;
}


/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    ADC_InitStruct(&ADC_InitStructure);
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIG_REG_CONV_SOFTWARE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* ADC1 regular channel16 configuration (internal temperature sensor) */
    ADC_ConfigRegularChannel(ADC1, ADC1_Channel_17_Temperture_Sensor, 1, ADC_SAMP_TIME_CYCLES_600);
    /* Enable Temperature Sensor */
    ADC_EnableTempSensorVrefint(ENABLE);
    /* Enable ADC1 DMA */
    ADC_EnableDMA(ADC1, ENABLE);
    /* Enable ADC1 */
    ADC_Enable(ADC1, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY) == RESET)
        ;
}

/**
*\*\name    main.
*\*\fun     Main program. ADC1 internal temperature sensor demo.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ----------------------------------------------*/
    RCC_Configuration();

    /* Log configuration -------------------------------------------------------*/
    log_init();

    /* DMA channel1 configuration -----------------------------------------------*/
    DMA_Config();

    /* ADC1 configuration -------------------------------------------------------*/
    ADC_Initial();

    /* Start ADC1 Software Conversion */
    ADC_EnableSoftwareStartConv(ADC1, ENABLE);

    /* Check ADC1 Conversion Done */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ENDC) == RESET);

    while (1)
    {
        TempValue = TempratureCalculate(ADCConvertedValue);

        log_debug("\r\n Temperature = %.1f C\r\n", TempValue);

        SysTick_Delay_Ms(1);
    }
}


/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* Enable GPIO clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Enable ADC1 clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);

    /* RCC_ADCSYSCLK_DIV16 */
    ADC_ClockModeConfig(RCC_ADCSYSCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16);  /* select HSI as RCC ADC1M CLK Source */
}


/**
*\*\name    DMA_Config.
*\*\fun     DMA_Initial program.
*\*\return  none
**/
void DMA_Config(void)
{
    DMA_DeInit(DMA_CH1);
    DMA_StructInit(&DMA_InitStructure);

    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC1->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)&ADCConvertedValue;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 1;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_DISABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);

    DMA_RequestRemap(DMA_REMAP_ADC1, DMA, DMA_CH1, ENABLE);

    /* Enable DMA channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);
}


