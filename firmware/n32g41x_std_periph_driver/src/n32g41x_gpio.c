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
*\*\file n32g41x_gpio.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "n32g41x_gpio.h"
#include "n32g41x_rcc.h"

/**
 *\*\name   GPIO_DeInit.
 *\*\fun    Reset the GPIOx peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_DeInit(void)
{
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_GPIO);
}

/**
 *\*\name   GPIO_DeInitPin.
 *\*\fun    Deinitializes the GPIOx peripheral registers to their default reset values.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13 
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIO_DeInitPin(GPIO_Module* GPIOx, uint32_t Pin)
{
    uint32_t pos = 0, currentpin;

    while((Pin >> pos) != 0U)
    {
        /* Get the IO position */
        currentpin = (Pin) & ((uint32_t)1U << pos);

        if(currentpin > 0U)
        {
            /*------------------------- GPIO Mode/PULL/AFH/AFL Configuration --------------------*/
            /* Configure GPIO as Analog Mode by default, except for the following pins: 
             * PA13(Alternate mode\Pull-Up\AF0)
             * PA14(Input mode\Pull-Down\AF0) */
            if ((GPIOA == GPIOx) && (currentpin == GPIO_PIN_13))
            {
                GPIOx->PMODE &= ~GPIO_PMODE13_Msk;
                GPIOx->PMODE |=  GPIO_PMODE13_2;

                GPIOx->PUPD  &= ~GPIO_PUPD13_Msk;
                GPIOx->PUPD  |=  GPIO_PUPD13_1;

                GPIOx->AFH   &= ~GPIO_AFH_AFSEL13;
            }
            else if ((GPIOA == GPIOx) && (currentpin == GPIO_PIN_14))
            {
                GPIOx->PMODE &= ~GPIO_PMODE14_Msk;

                GPIOx->PUPD  &= ~GPIO_PUPD14_Msk;
                GPIOx->PUPD  |=  GPIO_PUPD14_2;

                GPIOx->AFH   &= ~GPIO_AFH_AFSEL14;
            }
            else
            {
                GPIOx->PMODE |= (GPIO_PMODE0_Msk << (pos * 2u));

				GPIOx->PUPD &= ~(GPIO_PUPD0_Msk << (pos * 2u));

                if ((pos & (uint8_t)0x08u) != 0U)
                {
                    GPIOx->AFH |= (GPIO_AFL_AFSEL0 << ((pos & 0x07u) * 4u));
                }
                else
                {
                    GPIOx->AFL |= (GPIO_AFL_AFSEL0 << ((pos & 0x07u) * 4u));
                }
            }

            /* Configure the default value IO Output Type */
            GPIOx->POTYPE &= ~(GPIO_POTYPE_POT0 << pos);
            
            /* Configure the default value IO Output */
            GPIOx->POD &= ~(GPIO_POD_POD0 << pos);

            /* Configure the default DS in current IO */
            GPIOx->DS |= (GPIO_DS_DS0 << pos);
        
            if (((GPIOx == GPIOA) && ((currentpin & GPIOA_SLEW_RATE_PIN_MASK) != 0U)) ||
                ((GPIOx == GPIOB) && ((currentpin & GPIOB_SLEW_RATE_PIN_MASK) != 0U)))
            {
                GPIOx->DS |= ((uint32_t)1U << ((uint32_t)pos + (uint32_t)16U));
            }

            
            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */
            AFIO->EXTI_CFG[pos >> 2u] |= (AFIO_EXTI_CFG1_EXTI0_CFG << ((pos % 4u) * 4u));

            /* Clear EXTI line configuration */
            EXTI->IMASK &= ~((uint32_t)currentpin);
            EXTI->EMASK &= ~((uint32_t)currentpin);

            /* Clear Rising Falling edge configuration */
            EXTI->RT_CFG &= ~((uint32_t)currentpin);
            EXTI->FT_CFG &= ~((uint32_t)currentpin);
        } 
        pos++;
    }
}


/**
 *\*\name   GPIO_InitPeripheral.
 *\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  GPIO_InitParam :
 *\*\            - pin
 *\*\               - GPIO_PIN_0
 *\*\               - GPIO_PIN_1
 *\*\               - GPIO_PIN_2
 *\*\               - GPIO_PIN_3
 *\*\               - GPIO_PIN_4
 *\*\               - GPIO_PIN_5
 *\*\               - GPIO_PIN_6
 *\*\               - GPIO_PIN_7
 *\*\               - GPIO_PIN_8
 *\*\               - GPIO_PIN_9
 *\*\               - GPIO_PIN_10
 *\*\               - GPIO_PIN_11
 *\*\               - GPIO_PIN_12
 *\*\               - GPIO_PIN_13
 *\*\               - GPIO_PIN_14
 *\*\               - GPIO_PIN_15
 *\*\               - GPIO_PIN_ALL
 *\*\            - GPIO_Mode
 *\*\               - GPIO_MODE_INPUT
 *\*\               - GPIO_MODE_OUTPUT_PP
 *\*\               - GPIO_MODE_OUTPUT_OD
 *\*\               - GPIO_MODE_AF_PP
 *\*\               - GPIO_MODE_AF_OD
 *\*\               - GPIO_MODE_ANALOG
 *\*\            - GPIO_Pull
 *\*\               - GPIO_NO_PULL
 *\*\               - GPIO_PULL_UP
 *\*\               - GPIO_PULL_DOWN
 *\*\            - GPIO_Slew_Rate
 *\*\               note: only effective for pins PA0, PA1, PA2, PB5, PB6, PB7
 *\*\               - GPIO_SLEW_RATE_FAST
 *\*\               - GPIO_SLEW_RATE_SLOW
 *\*\            - GPIO_Current
 *\*\               - GPIO_DS_HIGH
 *\*\               - GPIO_DS_LOW
 *\*\            - GPIO_Alternate
 *\*\               - GPIO_AF0    
 *\*\               - GPIO_AF1 
 *\*\               - GPIO_AF2
 *\*\               - GPIO_AF3
 *\*\               - GPIO_AF4
 *\*\               - GPIO_AF5
 *\*\               - GPIO_AF6
 *\*\               - GPIO_AF7
 *\*\               - GPIO_AF8
 *\*\               - GPIO_AF9
 *\*\               - GPIO_AF10
 *\*\               - GPIO_AF11
 *\*\               - GPIO_AF12
 *\*\               - GPIO_AF13
 *\*\               - GPIO_AF14
 *\*\               - GPIO_NO_AF            NO alternate Function mapping
 *\*\return none
 */
void GPIO_InitPeripheral(GPIO_Module* GPIOx, const GPIO_InitType * GPIO_InitParam)
{
    uint32_t pos = 0x00U, currentpin;
    uint32_t tmpregister; 

    while(((GPIO_InitParam->Pin) >> pos) != 0U)
    {
        /* Get the IO position */
        currentpin = (GPIO_InitParam->Pin) & ((uint32_t)1U << pos);

        if(currentpin > 0U)
        {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if((GPIO_InitParam->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitParam->GPIO_Mode == GPIO_MODE_AF_OD) || (GPIO_InitParam->GPIO_Mode == GPIO_MODE_ANALOG) || (GPIO_InitParam->GPIO_Mode == GPIO_MODE_INPUT))
            {
                /* Configure Alternate function mapped with the current IO */
                if((pos & (uint8_t)0x08U) > 0U)
                {
                    tmpregister = GPIOx->AFH;
                    tmpregister &= ~((uint32_t)0xFU << ((uint32_t)(pos & (uint32_t)0x07U) * 4U));
                    tmpregister |= ((uint32_t)(GPIO_InitParam->GPIO_Alternate) << ((uint32_t)(pos & (uint32_t)0x07U) * 4U)) ;
                    GPIOx->AFH = tmpregister;
                }
                else
                {
                    tmpregister = GPIOx->AFL;
                    tmpregister &= ~((uint32_t)0xFU << ((uint32_t)(pos & (uint32_t)0x07U) * 4U)) ;
                    tmpregister |= ((uint32_t)(GPIO_InitParam->GPIO_Alternate) << ((uint32_t)(pos & (uint32_t)0x07U) * 4U)) ;
                    GPIOx->AFL = tmpregister;
                }
            }

            /* In case of Output or Alternate function mode selection */
            if ((GPIO_InitParam->GPIO_Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_InitParam->GPIO_Mode == GPIO_MODE_OUTPUT_OD)
                 ||(GPIO_InitParam->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitParam->GPIO_Mode == GPIO_MODE_AF_OD))
            {
                /* Configure the IO Output Type */
                tmpregister = GPIOx->POTYPE;
                tmpregister &= ~(GPIO_POTYPE_POT0 << pos);
                tmpregister |= (((GPIO_InitParam->GPIO_Mode >> 4U) & 0x01U) << pos);
                GPIOx->POTYPE = tmpregister;
            }

            /*---------------------------- GPIO Mode Configuration -----------------------*/
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            tmpregister = GPIOx->PMODE;
            tmpregister &= ~(GPIO_PMODE0 << (pos * 2U));
            tmpregister |= (((GPIO_InitParam->GPIO_Mode & 0x03U) << (pos * 2U)));
            GPIOx->PMODE = tmpregister;

            /* Configure pull-down mode */
            tmpregister = GPIOx->PUPD;
            tmpregister &= ~(GPIO_PUPD0 << (pos * 2U));
            tmpregister |= (GPIO_InitParam->GPIO_Pull << (pos * 2U));
            GPIOx->PUPD = tmpregister;

            /* Configure driver current */
            tmpregister = GPIOx->DS;
            tmpregister &= ~(GPIO_DS_DS0 << pos);
            tmpregister |= (GPIO_InitParam->GPIO_Current << pos);
            GPIOx->DS = tmpregister;

            /* Configure slew rate */
            if (((GPIOx == GPIOA) && ((currentpin & GPIOA_SLEW_RATE_PIN_MASK) != 0U)) ||
                ((GPIOx == GPIOB) && ((currentpin & GPIOB_SLEW_RATE_PIN_MASK) != 0U)))
            {
                tmpregister = GPIOx->DS;
                tmpregister &= ~(GPIO_DS_DS0 << (pos + 16u));
                tmpregister |= (GPIO_InitParam->GPIO_Slew_Rate << (pos + 16u));
                GPIOx->DS = tmpregister;
            }
        }
        pos++;      
    }
}


/**
 *\*\name   GPIO_InitStruct.
 *\*\fun    Assign default values to each GPIO_InitType member.
 *\*\param  GPIO_InitStructure :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStructure)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStructure->Pin            = GPIO_PIN_ALL;
    GPIO_InitStructure->GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStructure->GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure->GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure->GPIO_Current   = GPIO_DS_LOW;
    GPIO_InitStructure->GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
}


/**
 *\*\name   GPIO_ReadInputDataBit.
 *\*\fun    Get the pin status on the specified input port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the input port.
 */
uint8_t GPIO_ReadInputDataBit(const GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus;

    if ((GPIOx->PID & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}


/**
 *\*\name   GPIO_ReadInputData.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_ReadInputData(const GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->PID);
}

/**
 *\*\name   GPIO_ReadOutputDataBit.
 *\*\fun    Get the pin status on the specified output port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the output port.
 */
uint8_t GPIO_ReadOutputDataBit(const GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus;

    if ((GPIOx->POD & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 *\*\name   GPIO_ReadOutputData.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_ReadOutputData(const GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->POD);
}

/**
 *\*\name   GPIO_SetBits.
 *\*\fun    Sets the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}


/**
 *\*\name   GPIO_WritePBSC.
 *\*\fun    Sets the selected data port bits using PBSC.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\param  bitstatus :
 *\*\             - Bit_SET
 *\*\             - Bit_RESET
 *\*\return none
 */
void GPIO_WritePBSC(GPIO_Module* GPIOx, uint16_t Pin,uint8_t bitstatus)
{
    if (bitstatus == (uint8_t)Bit_SET)
    {
       GPIOx->PBSC = (uint32_t)Pin;
    }
    else
    {
       GPIOx->PBSC = (((uint32_t)Pin) << 16U);
    }
}


/**
 *\*\name   GPIO_ResetBits.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 *\*\name   GPIO_WriteBit.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\param  BitCmd :
 *\*\          - Bit_RESET
 *\*\          - Bit_SET
 *\*\return none
 */
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd)
{
    if (BitCmd != Bit_RESET)
    {
        GPIOx->PBSC = Pin;
    }
    else
    {
        GPIOx->PBC = Pin;
    }
}

/**
 *\*\name   GPIO_Write.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\          - 0~0xFFFF
 *\*\return none
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}

/**
 *\*\name   GPIO_TogglePin.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 *\*\name   GPIO_ConfigPinLock.
 *\*\fun    GPIO port lock register configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint32_t tmp = 0x00010000;

    tmp |= Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset LCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read LCKK bit*/
    GPIOx->PLOCK;
    /* Read LCKK bit*/
    GPIOx->PLOCK;
}



/**
 *\*\name   GPIO_ConfigPinRemap.
 *\*\fun    Pin remapping configuration.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\param  AlternateFunction :
 *\*\          - GPIO_AF0    
 *\*\          - GPIO_AF1 
 *\*\          - GPIO_AF2
 *\*\          - GPIO_AF3
 *\*\          - GPIO_AF4
 *\*\          - GPIO_AF5
 *\*\          - GPIO_AF6
 *\*\          - GPIO_AF7
 *\*\          - GPIO_AF8
 *\*\          - GPIO_AF9
 *\*\          - GPIO_AF10
 *\*\          - GPIO_AF11
 *\*\          - GPIO_AF12
 *\*\          - GPIO_AF13
 *\*\          - GPIO_AF14 
 *\*\          - GPIO_NO_AF            NO alternate Function mapping
 *\*\return none
 */
void GPIO_ConfigPinRemap(uint8_t PortSource, uint32_t PinSource, uint32_t AlternateFunction)
{
    uint8_t temp_value, pin_source; 
    uint32_t tmpregister;
    GPIO_Module *GPIOx;

    pin_source = (uint8_t)(PinSource & 0x0000000FU);

    /*Get Peripheral point*/
    GPIOx = GPIO_GET_PERIPH(PortSource);

    if((pin_source & (uint8_t)0x08) != 0U)
    {
        temp_value = (pin_source & (uint8_t)0x07);
        /*Read GPIO_AFH register*/
        tmpregister  = GPIOx->AFH;
        /*Reset corresponding bits*/
        tmpregister &= ~((uint32_t)0x0F <<(temp_value * 4U));
        /*Set corresponding bits*/
        tmpregister |= ((uint32_t)(AlternateFunction) << (temp_value * 4U));
        /*Write to the GPIO_AFH register*/
        GPIOx->AFH = tmpregister;
    }
    else
    {
        temp_value = (pin_source & (uint8_t)0x07);
        /*Read GPIO_AFL register*/
        tmpregister  = GPIOx->AFL;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(temp_value * 4U));
        /*Set corresponding bits*/
        tmpregister |= ((uint32_t)(AlternateFunction) << (temp_value * 4U));
        /*Write to the GPIO_AFL register*/
        GPIOx->AFL = tmpregister;
    }
}


/**
 *\*\name   AFIO_ConfigSPINSSMode.
 *\*\fun    Selects the alternate function SPIx NSS mode.
 *\*\param  AFIO_SPIx_NSS : 
 *\*\          choose which SPI configuration.
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\param  SpiNssMode : 
 *\*\          specifies the SPI_NSS mode to be configured.
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_High_LEVEL
 *\*\return none
 */
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t SpiNssMode)
{
    uint32_t tmpregister;

    tmpregister = AFIO->CFG;

    if(SpiNssMode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        tmpregister |= AFIO_SPIx_NSS;
    }
    else 
    {
        tmpregister &= ~AFIO_SPIx_NSS;
    }

    AFIO->CFG = tmpregister;
}


/**
 *\*\name   ConfigEXTIFlitEN.
 *\*\fun    Configure EXTI filter enable.
  *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void AFIO_ConfigEXTIFlitEN(FunctionalState Cmd)
{
    uint32_t tmpregister;

    tmpregister = AFIO->CFG;

    if (Cmd != DISABLE)
    {
        tmpregister |= AFIO_CFG_EXTIFLITEN;
    }
    else
    {
        tmpregister &= ~AFIO_CFG_EXTIFLITEN;
    }

    AFIO->CFG = tmpregister;
}


/**
 *\*\name   AFIO_ConfigIOFlitNum.
 *\*\fun    Configure IO filter number in APB clock.
 *\*\param  Cmd
 *\*\          - GPIO_FILTER_BYPASS
 *\*\          - GPIO_FILTER_1_CLK
 *\*\          - GPIO_FILTER_2_CLK
 *\*\          - GPIO_FILTER_3_CLK
 *\*\return none
 */
void AFIO_ConfigIOFlitNum(uint32_t filter_clk)
{
    uint32_t tmpregister;

    tmpregister = AFIO->CFG;
    tmpregister &= ~AFIO_CFG_IOFILTCFG;
    tmpregister |= filter_clk;

    AFIO->CFG = tmpregister;
}


/**
 *\*\name   AFIO_DIGEFTEnable.
 *\*\fun    Enables or disable digital EFT of port pins.
 *\*\param  GPIO_Module :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD 
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void AFIO_DIGEFTEnable(const GPIO_Module* GPIOx, uint32_t Pin, FunctionalState Cmd)
{
	
    uint32_t tmpregister;
    uint32_t GPIO_Index;
#ifdef N32G415
	uint32_t i;
	uint32_t pos = 0x00U, currentpin;
	const uint16_t DigMask[14U] = { 0x0826, 0x0927, 0x1830, 0x1918, 0x2628, 0x2729, 0x282A, 0x292B, 0x2A19, 0x2B3B, 0x2C3C, 0x302C, 0x3808, 0x3909 };
#endif /* N32G415 */
    
    GPIO_Index = GPIO_GET_INDEX(GPIOx);

    if (GPIO_Index < 4U)
    {
#ifdef N32G415
		while((Pin >> pos) != 0U)
		{
			/* Get the IO position */
			currentpin = (Pin) & ((uint32_t)1U << pos);
		    /* Clear i */
			i = 0;

			if(currentpin > 0U)
			{
				for (i = 0; i < 14U; i++)
				{
					if (((DigMask[i] >> 12U) == GPIO_Index) && (((DigMask[i] & 0x0F00) >> 8U) == pos))
					{
						tmpregister = AFIO->DIGEFT_CFG[((DigMask[i] & 0x0030) >> 4U)];

						if(Cmd != DISABLE)
						{
							tmpregister |= ((uint32_t)1U << (DigMask[i] & 0x000F));

						}
						else
						{
							tmpregister &= ~((uint32_t)1U << (DigMask[i] & 0x000F));
						}

						AFIO->DIGEFT_CFG[((DigMask[i] & 0x0030) >> 4U)] = tmpregister;
						break;
					}
				}
				
				if (i >= 14U)
				{
					tmpregister = AFIO->DIGEFT_CFG[GPIO_Index];

					if(Cmd != DISABLE)
					{
						tmpregister |= currentpin;

					}
					else
					{
						tmpregister &= ~(currentpin);
					}

					AFIO->DIGEFT_CFG[GPIO_Index] = tmpregister;
				}
			}
			pos++;      
		}
#else
		tmpregister = AFIO->DIGEFT_CFG[GPIO_Index];

        if(Cmd != DISABLE)
        {
            tmpregister |= Pin;

        }
        else
        {
            tmpregister &= ~(Pin);
        }

        AFIO->DIGEFT_CFG[GPIO_Index] = tmpregister;
#endif /* N32G415 */
    }
    else
    {
        /* No process */
    }
}

/**
 *\*\name   GPIO_ConfigEXTILine.
 *\*\fun    Selects the GPIO pin used as EXTI Line. A single EXTI line can only be configured with a single pin.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE  
 *\*\          - GPIOB_PORT_SOURCE  
 *\*\          - GPIOC_PORT_SOURCE  
 *\*\          - GPIOD_PORT_SOURCE  
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\return none
 */
void GPIO_ConfigEXTILine(uint8_t PortSource, uint32_t PinSource)
{
    uint8_t line_index, reg_index, line_position;
    uint32_t tmpregister;
    uint32_t port;

    port          = PortSource;
    line_index    = (uint8_t)(PinSource & 0x0000000FU);
    reg_index     = line_index >> 0x02;
    line_position = (line_index & (uint8_t)0x03) * 4u;

    tmpregister = AFIO->EXTI_CFG[reg_index];
    tmpregister &= ~(((uint32_t)0x07) << line_position);
    
#ifdef N32G415
    if ((PinSource & 0xF0000000) & (0x10000000 << PortSource))
    {
        tmpregister |= (((PinSource & (0x0000F000 << PortSource * 4u)) >> (12u + PortSource * 4u)) << line_position);
    }
    else
    {
        tmpregister |= (port << line_position);
    }

    AFIO->EXTI_CFG[reg_index] = tmpregister;
#else
    tmpregister |= (port << line_position);
    AFIO->EXTI_CFG[reg_index] = tmpregister;
#endif /* N32G415 */
}


/**
 *\*\name   GPIO_ClearEXTILine.
 *\*\fun    Clear the GPIO pin used as EXTI Line.
 *\*\param  LineSource :
 *\*\          - GPIO_EXTILINE_SOURCE0
 *\*\          - GPIO_EXTILINE_SOURCE1
 *\*\          - GPIO_EXTILINE_SOURCE2
 *\*\          - GPIO_EXTILINE_SOURCE3
 *\*\          - GPIO_EXTILINE_SOURCE4
 *\*\          - GPIO_EXTILINE_SOURCE5
 *\*\          - GPIO_EXTILINE_SOURCE6
 *\*\          - GPIO_EXTILINE_SOURCE7
 *\*\          - GPIO_EXTILINE_SOURCE8
 *\*\          - GPIO_EXTILINE_SOURCE9
 *\*\          - GPIO_EXTILINE_SOURCE10
 *\*\          - GPIO_EXTILINE_SOURCE11
 *\*\          - GPIO_EXTILINE_SOURCE12
 *\*\          - GPIO_EXTILINE_SOURCE13
 *\*\          - GPIO_EXTILINE_SOURCE14
 *\*\          - GPIO_EXTILINE_SOURCE15
 *\*\return none
 */
void GPIO_ClearEXTILine( uint8_t LineSource)
{
    uint8_t reg_index, line_position;
    uint32_t tmpregister;

    reg_index = (LineSource >> 0x02U);
    line_position = ((LineSource & 0x03U) * 4U);

    tmpregister = AFIO->EXTI_CFG[reg_index];
    tmpregister |= (AFIO_EXTI_CFGMASK << line_position);
    AFIO->EXTI_CFG[reg_index] = tmpregister;
}
