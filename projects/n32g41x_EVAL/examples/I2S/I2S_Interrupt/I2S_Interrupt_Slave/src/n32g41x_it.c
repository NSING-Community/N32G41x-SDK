/**
*     Copyright (c) 2025, Nsing Technologies Inc.
*
*     All rights reserved.
**/

/**
*\*\file n32g41x_it.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "n32g41x_it.h"
#include "main.h"

extern uint16_t I2S_Buffer_Rx[BufferSize];
extern __IO uint32_t RxIdx;

/**
*\*\name    NMI_Handler.
*\*\fun     This function handles NMI exception.
*\*\param   none
*\*\return  none
**/

/** Cortex-M Processor Exceptions Handlers **/
/**
 *\*\name   NMI_Handler.
 *\*\fun    This function handles NMI exception.
 *\*\param  none
 *\*\return none
 */
void NMI_Handler(void)
{
}

/**
 *\*\name   HardFault_Handler.
 *\*\fun    This function handles Hard Fault exception.
 *\*\param  none
 *\*\return none
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 *\*\name   MemManage_Handler.
 *\*\fun    This function handles Memory Manage exception.
 *\*\param  none
 *\*\return none
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 *\*\name   BusFault_Handler.
 *\*\fun    This function handles Bus Fault exception.
 *\*\param  none
 *\*\return none
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 *\*\name   UsageFault_Handler.
 *\*\fun    This function handles Usage Fault exception.
 *\*\param  none
 *\*\return none
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 *\*\name   SVC_Handler.
 *\*\fun    This function handles SVCall exception.
 *\*\param  none
 *\*\return none
 */
void SVC_Handler(void)
{
}

/**
 *\*\name   DebugMon_Handler.
 *\*\fun    This function handles Debug Monitor exception.
 *\*\param  none
 *\*\return none
 */
void DebugMon_Handler(void)
{
}

/**
*\*\name    PendSV_Handler.
*\*\fun     This function handles PendSV_Handler exception.
*\*\param   none
*\*\return  none
**/
void PendSV_Handler(void)
{
}

/**
*\*\name    SysTick_Handler.
*\*\fun     This function handles SysTick Handler.
*\*\param   none
*\*\return  none 
**/
void SysTick_Handler(void)
{
}


/* n32g41x Peripherals Interrupt Handlers, interrupt handler's name please refer to the startup file (startup_n32g41x.s). */

/**
*\*\name    SPI1_IRQHandler.
*\*\fun     SPI1/I2S1 Slave RX interrupt handler. When RxNE flag is set, read received
*\*\        data from I2S data register and store in I2S_Buffer_Rx.
*\*\param   none
*\*\return  none
**/
void SPI1_IRQHandler(void)
{
    if (SPI_I2S_GetIntStatus(I2S_SLAVE, SPI_I2S_INT_RNE) != RESET)
    {
        I2S_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(I2S_SLAVE);
    }
}
