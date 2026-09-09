; *********************************************************************************************************
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
; ************************************************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
  
    MODULE  ?cstartup
        
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

        DATA
       
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler
        DCD     NMI_Handler               ; NMI Handler
        DCD     HardFault_Handler         ; Hard Fault Handler
        DCD     MemManage_Handler         ; MemManage_Handler
        DCD     BusFault_Handler          ; BusFault_Handler
        DCD     UsageFault_Handler        ; UsageFault_Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler               ; SVCall Handler
        DCD     DebugMon_Handler          ; DebugMon_Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler            ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler

        ; External Interrupts
                DCD     WWDG_IRQHandler;           
		DCD     PVD_IRQHandler;                 EXTI Line16       
		DCD     RTC_STAMP_LSECSS_IRQHandler;    EXTI Line18
		DCD     RTC_WKUP_IRQHandler;            EXTI Line19
		DCD     FLASH_IRQHandler;          
		DCD     RCC_IRQHandler;            
		DCD     EXTI0_IRQHandler;          
		DCD     EXTI1_IRQHandler;          
		DCD     EXTI2_IRQHandler;          
		DCD     EXTI3_IRQHandler;          
		DCD     EXTI4_IRQHandler;          
		DCD     DMA_CH1_IRQHandler;        
		DCD     DMA_CH2_IRQHandler;        
		DCD     DMA_CH3_IRQHandler;        
		DCD     DMA_CH4_IRQHandler;        
		DCD     DMA_CH5_IRQHandler;        
		DCD     DMA_CH6_IRQHandler;        
		DCD     DMA_CH7_IRQHandler;        
		DCD     ADC2_IRQHandler;           
		DCD     ADC1_IRQHandler;           
		DCD     BTIM1_IRQHandler;             EXTI Line20      
		DCD     BTIM2_IRQHandler;          
		DCD     COMP123_IRQHandler;           COMP1->EXTI Line21  COMP2->EXTI Line22  COMP3->EXTI Line23       																										
		DCD     EXTI5_9_IRQHandler;        
		DCD     ATIM1_BRK_IRQHandler;				
		DCD     ATIM1_UP_IRQHandler;				
		DCD     ATIM1_TRG_COM_IRQHandler;		
		DCD     ATIM1_CC_IRQHandler;			 
		DCD     GTIM1_IRQHandler;			 
		DCD     GTIM2_IRQHandler;			 
		DCD     GTIM3_IRQHandler;			 
		DCD     I2C1_IRQHandler;           
		DCD     USART4_IRQHandler;            EXTI Line25 
		DCD     I2C2_IRQHandler;           
		DCD     CAN_IRQHandler;            
		DCD     SPI1_IRQHandler;           
		DCD     SPI2_IRQHandler;                     
		DCD     USART1_IRQHandler;            EXTI Line24    
		DCD     USART2_IRQHandler;         
		DCD     USART3_IRQHandler;         
		DCD     EXTI10_15_IRQHandler;      
		DCD     RTC_ALARM_IRQHandler;         EXTI Line17 
		DCD     GTIM4_IRQHandler;          
		DCD     AGTIM2_BRK_IRQHandler;     
		DCD     AGTIM2_UP_IRQHandler;      
		DCD     AGTIM2_TRG_COM_IRQHandler; 
		DCD     AGTIM2_CC_IRQHandler; 			
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
               
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)		
SVC_Handler
        B SVC_Handler
		
		PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)		
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler
		
		PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler
		
		PUBWEAK RTC_STAMP_LSECSS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_STAMP_LSECSS_IRQHandler
        B RTC_STAMP_LSECSS_IRQHandler
		
		PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler
        B FLASH_IRQHandler
		
		PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler
		
		PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler
		
		PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler
		
		PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler
		
		PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler
		
		PUBWEAK DMA_CH1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH1_IRQHandler
        B DMA_CH1_IRQHandler
		
		PUBWEAK DMA_CH2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH2_IRQHandler
        B DMA_CH2_IRQHandler
		
		PUBWEAK DMA_CH3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH3_IRQHandler
        B DMA_CH3_IRQHandler
		
		PUBWEAK DMA_CH4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH4_IRQHandler
        B DMA_CH4_IRQHandler
		
		PUBWEAK DMA_CH5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH5_IRQHandler
        B DMA_CH5_IRQHandler
		
		PUBWEAK DMA_CH6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH6_IRQHandler
        B DMA_CH6_IRQHandler
		
		PUBWEAK DMA_CH7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_CH7_IRQHandler
        B DMA_CH7_IRQHandler
		
		PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC2_IRQHandler
        B ADC2_IRQHandler
		
		PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_IRQHandler
        B ADC1_IRQHandler
		
		PUBWEAK BTIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM1_IRQHandler
        B BTIM1_IRQHandler
		
		PUBWEAK BTIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM2_IRQHandler
        B BTIM2_IRQHandler
		
		PUBWEAK COMP123_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP123_IRQHandler
        B COMP123_IRQHandler
		
		PUBWEAK EXTI5_9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI5_9_IRQHandler
        B EXTI5_9_IRQHandler
		
		PUBWEAK ATIM1_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_BRK_IRQHandler
        B ATIM1_BRK_IRQHandler
		
		PUBWEAK ATIM1_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_UP_IRQHandler
        B ATIM1_UP_IRQHandler
		
		PUBWEAK ATIM1_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_TRG_COM_IRQHandler
        B ATIM1_TRG_COM_IRQHandler
		
		PUBWEAK ATIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_CC_IRQHandler
        B ATIM1_CC_IRQHandler
		
		PUBWEAK GTIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM1_IRQHandler
        B GTIM1_IRQHandler
		
		PUBWEAK GTIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM2_IRQHandler
        B GTIM2_IRQHandler
		
		PUBWEAK GTIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM3_IRQHandler
        B GTIM3_IRQHandler
		
		PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_IRQHandler
        B I2C1_IRQHandler
		
		PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART4_IRQHandler
        B USART4_IRQHandler
		
		PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_IRQHandler
        B I2C2_IRQHandler
		
		PUBWEAK CAN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN_IRQHandler
        B CAN_IRQHandler
		
		PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler
		
		PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
        B SPI2_IRQHandler
		
		PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler
		
		PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler
		
		PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler
		
		PUBWEAK EXTI10_15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI10_15_IRQHandler
        B EXTI10_15_IRQHandler
		
		PUBWEAK RTC_ALARM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_ALARM_IRQHandler
        B RTC_ALARM_IRQHandler
		
		PUBWEAK GTIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIM4_IRQHandler
        B GTIM4_IRQHandler
		
		PUBWEAK AGTIM2_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AGTIM2_BRK_IRQHandler
        B AGTIM2_BRK_IRQHandler
		
		PUBWEAK AGTIM2_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AGTIM2_UP_IRQHandler
        B AGTIM2_UP_IRQHandler
		
		PUBWEAK AGTIM2_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AGTIM2_TRG_COM_IRQHandler
        B AGTIM2_TRG_COM_IRQHandler
		
		PUBWEAK AGTIM2_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AGTIM2_CC_IRQHandler
        B AGTIM2_CC_IRQHandler
		
        END

