/*********************************************************************************************************
;     Copyright (c) 2025, Nsing Technologies Inc.
; 
;     All rights reserved.
;
;     This software is the exclusive property of Nsing Technologies Inc. (Hereinafter 
; referred to as Nsing). This software, and the product of Nsing described herein 
; (Hereinafter referred to as the Product) are owned by Nsing under the laws and treaties
; of the People's Republic of China and other applicable jurisdictions worldwide.
;
;     Nsing does not grant any license under its patents, copyrights, trademarks, or other 
; intellectual property rights. Names and brands of third party may be mentioned or referred 
; thereto (if any) for identification purposes only.
;
;     Nsing reserves the right to make changes, corrections, enhancements, modifications, and 
; improvements to this software at any time without notice. Please contact Nsing and obtain 
; the latest version of this software before placing orders.

;     Although Nsing has attempted to provide accurate and reliable information, Nsing assumes 
; no responsibility for the accuracy and reliability of this software.
; 
;     It is the responsibility of the user of this software to properly design, program, and test 
; the functionality and safety of any application made of this information and any resulting product. 
; In no event shall Nsing be liable for any direct, indirect, incidental, special,exemplary, or 
; consequential damages arising in any way out of the use of this software or the Product.
;
;     Nsing Products are neither intended nor warranted for usage in systems or equipment, any
; malfunction or failure of which may cause loss of human life, bodily injury or severe property 
; damage. Such applications are deemed, "Insecure Usage".
;
;     All Insecure Usage shall be made at user's risk. User shall indemnify Nsing and hold Nsing 
; harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
; to any customer's Insecure Usage.

;     Any express or implied warranty with regard to this software or the Product, including,but not 
; limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
; are disclaimed to the fullest extent permitted by law.

;     Unless otherwise explicitly permitted by Nsing, anyone may not duplicate, modify, transcribe
; or otherwise distribute this software for any purposes, in whole or in part.
;
;     Nsing products and technologies shall not be used for or incorporated into any products or systems
; whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
; User shall comply with any applicable export control laws and regulations promulgated and administered by 
; the governments of any countries asserting jurisdiction over the parties or transactions.
; ************************************************************************************************************/


  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * param  None
 * retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M4.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  /* External Interrupts */
  .word  WWDG_IRQHandler 
  .word  PVD_IRQHandler                   /* EXTI Line16 */
  .word  RTC_STAMP_LSECSS_IRQHandler      /* EXTI Line18 */
  .word  RTC_WKUP_IRQHandler              /* EXTI Line19 */
  .word  FLASH_IRQHandler
  .word  RCC_IRQHandler
  .word  EXTI0_IRQHandler 
  .word  EXTI1_IRQHandler
  .word  EXTI2_IRQHandler
  .word  EXTI3_IRQHandler 
  .word  EXTI4_IRQHandler 
  .word  DMA_CH1_IRQHandler
  .word  DMA_CH2_IRQHandler
  .word  DMA_CH3_IRQHandler 
  .word  DMA_CH4_IRQHandler
  .word  DMA_CH5_IRQHandler
  .word  DMA_CH6_IRQHandler 
  .word  DMA_CH7_IRQHandler 
  .word  ADC2_IRQHandler
  .word  ADC1_IRQHandler
  .word  BTIM1_IRQHandler                /* EXTI Line20 */
  .word  BTIM2_IRQHandler
  .word  COMP123_IRQHandler              /* COMP1->EXTI Line21  COMP2->EXTI Line22  COMP3->EXTI Line23 */
  .word  EXTI5_9_IRQHandler 
  .word  ATIM1_BRK_IRQHandler 
  .word  ATIM1_UP_IRQHandler
  .word  ATIM1_TRG_COM_IRQHandler
  .word  ATIM1_CC_IRQHandler 
  .word  GTIM1_IRQHandler
  .word  GTIM2_IRQHandler
  .word  GTIM3_IRQHandler 
  .word  I2C1_IRQHandler 
  .word  USART4_IRQHandler              /* EXTI Line25 */
  .word  I2C2_IRQHandler 
  .word  CAN_IRQHandler
  .word  SPI1_IRQHandler
  .word  SPI2_IRQHandler           
  .word  USART1_IRQHandler              /* EXTI Line24 */
  .word  USART2_IRQHandler        
  .word  USART3_IRQHandler 
  .word  EXTI10_15_IRQHandler 
  .word  RTC_ALARM_IRQHandler           /* EXTI Line17 */
  .word  GTIM4_IRQHandler
  .word  AGTIM2_BRK_IRQHandler 
  .word  AGTIM2_UP_IRQHandler
  .word  AGTIM2_TRG_COM_IRQHandler
  .word  AGTIM2_CC_IRQHandler 
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler
  
  .weak      MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler
  
  .weak      BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler
  
  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Default_Handler

  .weak      PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler

  .weak      RTC_STAMP_LSECSS_IRQHandler
  .thumb_set RTC_STAMP_LSECSS_IRQHandler,Default_Handler

  .weak      RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler

  .weak      FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler 

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak      EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler

  .weak      EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler

  .weak      EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler 

  .weak      EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak      EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak      DMA_CH1_IRQHandler
  .thumb_set DMA_CH1_IRQHandler,Default_Handler

  .weak      DMA_CH2_IRQHandler
  .thumb_set DMA_CH2_IRQHandler,Default_Handler 

  .weak      DMA_CH3_IRQHandler
  .thumb_set DMA_CH3_IRQHandler,Default_Handler

  .weak      DMA_CH4_IRQHandler
  .thumb_set DMA_CH4_IRQHandler,Default_Handler

  .weak      DMA_CH5_IRQHandler
  .thumb_set DMA_CH5_IRQHandler,Default_Handler 

  .weak      DMA_CH6_IRQHandler
  .thumb_set DMA_CH6_IRQHandler,Default_Handler

  .weak      DMA_CH7_IRQHandler
  .thumb_set DMA_CH7_IRQHandler,Default_Handler

  .weak      ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak      ADC1_IRQHandler
  .thumb_set ADC1_IRQHandler,Default_Handler 

  .weak      BTIM1_IRQHandler
  .thumb_set BTIM1_IRQHandler,Default_Handler

  .weak      BTIM2_IRQHandler
  .thumb_set BTIM2_IRQHandler,Default_Handler

  .weak      COMP123_IRQHandler
  .thumb_set COMP123_IRQHandler,Default_Handler 

  .weak      EXTI5_9_IRQHandler
  .thumb_set EXTI5_9_IRQHandler,Default_Handler

  .weak      ATIM1_BRK_IRQHandler
  .thumb_set ATIM1_BRK_IRQHandler,Default_Handler

  .weak      ATIM1_UP_IRQHandler
  .thumb_set ATIM1_UP_IRQHandler,Default_Handler

  .weak      ATIM1_TRG_COM_IRQHandler
  .thumb_set ATIM1_TRG_COM_IRQHandler,Default_Handler 

  .weak      ATIM1_CC_IRQHandler
  .thumb_set ATIM1_CC_IRQHandler,Default_Handler

  .weak      GTIM1_IRQHandler
  .thumb_set GTIM1_IRQHandler,Default_Handler

  .weak      GTIM2_IRQHandler
  .thumb_set GTIM2_IRQHandler,Default_Handler 

  .weak      GTIM3_IRQHandler
  .thumb_set GTIM3_IRQHandler,Default_Handler

  .weak      I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Default_Handler

  .weak      USART4_IRQHandler
  .thumb_set USART4_IRQHandler,Default_Handler

  .weak      I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,Default_Handler 

  .weak      CAN_IRQHandler
  .thumb_set CAN_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler 

  .weak      USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak      USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak      USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler

  .weak      EXTI10_15_IRQHandler
  .thumb_set EXTI10_15_IRQHandler,Default_Handler 

  .weak      RTC_ALARM_IRQHandler
  .thumb_set RTC_ALARM_IRQHandler,Default_Handler

  .weak      GTIM4_IRQHandler
  .thumb_set GTIM4_IRQHandler,Default_Handler

  .weak      AGTIM2_BRK_IRQHandler
  .thumb_set AGTIM2_BRK_IRQHandler,Default_Handler 

  .weak      AGTIM2_UP_IRQHandler
  .thumb_set AGTIM2_UP_IRQHandler,Default_Handler

  .weak      AGTIM2_TRG_COM_IRQHandler
  .thumb_set AGTIM2_TRG_COM_IRQHandler,Default_Handler

  .weak      AGTIM2_CC_IRQHandler
  .thumb_set AGTIM2_CC_IRQHandler,Default_Handler


