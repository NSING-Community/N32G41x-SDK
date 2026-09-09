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

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
                                                  
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MemManage_Handler
                DCD     BusFault_Handler           ; BusFault_Handler
                DCD     UsageFault_Handler         ; UsageFault_Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; DebugMon_Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler
					
					

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
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY
                
; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP							
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT     WWDG_IRQHandler     			    [WEAK]           
				EXPORT     PVD_IRQHandler     				[WEAK]            
				EXPORT     RTC_STAMP_LSECSS_IRQHandler      [WEAK]    
				EXPORT     RTC_WKUP_IRQHandler     		    [WEAK]
				EXPORT     FLASH_IRQHandler     			[WEAK]          
				EXPORT     RCC_IRQHandler     				[WEAK]            
				EXPORT     EXTI0_IRQHandler     			[WEAK]          
				EXPORT     EXTI1_IRQHandler     			[WEAK]          
				EXPORT     EXTI2_IRQHandler     			[WEAK]          
				EXPORT     EXTI3_IRQHandler     			[WEAK]          
				EXPORT     EXTI4_IRQHandler     			[WEAK]          
				EXPORT     DMA_CH1_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH2_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH3_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH4_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH5_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH6_IRQHandler     			[WEAK]        
				EXPORT     DMA_CH7_IRQHandler     			[WEAK]        
				EXPORT     ADC2_IRQHandler     			    [WEAK]           
				EXPORT     ADC1_IRQHandler     			    [WEAK]           
				EXPORT     BTIM1_IRQHandler     			[WEAK]          
				EXPORT     BTIM2_IRQHandler     			[WEAK]          
				EXPORT     COMP123_IRQHandler     			[WEAK]        																										
				EXPORT     EXTI5_9_IRQHandler     			[WEAK]        
				EXPORT     ATIM1_BRK_IRQHandler     		[WEAK]				
				EXPORT     ATIM1_UP_IRQHandler     		    [WEAK]				
				EXPORT     ATIM1_TRG_COM_IRQHandler     	[WEAK]		
				EXPORT     ATIM1_CC_IRQHandler     		    [WEAK]			 
				EXPORT     GTIM1_IRQHandler     			[WEAK]			 
				EXPORT     GTIM2_IRQHandler     			[WEAK]			 
				EXPORT     GTIM3_IRQHandler     			[WEAK]			 
				EXPORT     I2C1_IRQHandler     			    [WEAK]           
				EXPORT     USART4_IRQHandler     			[WEAK]         
				EXPORT     I2C2_IRQHandler     			    [WEAK]           
				EXPORT     CAN_IRQHandler     				[WEAK]            
				EXPORT     SPI1_IRQHandler     			    [WEAK]           
				EXPORT     SPI2_IRQHandler     			    [WEAK]           
				EXPORT     USART1_IRQHandler     			[WEAK]         
				EXPORT     USART2_IRQHandler     			[WEAK]         
				EXPORT     USART3_IRQHandler     			[WEAK]         
				EXPORT     EXTI10_15_IRQHandler     		[WEAK]      
				EXPORT     RTC_ALARM_IRQHandler     		[WEAK]      
				EXPORT     GTIM4_IRQHandler     			[WEAK]          
				EXPORT     AGTIM2_BRK_IRQHandler     		[WEAK]     
				EXPORT     AGTIM2_UP_IRQHandler     		[WEAK]      
				EXPORT     AGTIM2_TRG_COM_IRQHandler     	[WEAK] 
				EXPORT     AGTIM2_CC_IRQHandler     		[WEAK]   
				
WWDG_IRQHandler     			        
PVD_IRQHandler     				         
RTC_STAMP_LSECSS_IRQHandler      
RTC_WKUP_IRQHandler     		
FLASH_IRQHandler     			       
RCC_IRQHandler     				         
EXTI0_IRQHandler     			       
EXTI1_IRQHandler     			       
EXTI2_IRQHandler     			       
EXTI3_IRQHandler     			       
EXTI4_IRQHandler     			       
DMA_CH1_IRQHandler     			     
DMA_CH2_IRQHandler     			     
DMA_CH3_IRQHandler     			     
DMA_CH4_IRQHandler     			     
DMA_CH5_IRQHandler     			     
DMA_CH6_IRQHandler     			     
DMA_CH7_IRQHandler     			     
ADC2_IRQHandler     			        
ADC1_IRQHandler     			        
BTIM1_IRQHandler     			       
BTIM2_IRQHandler     			       
COMP123_IRQHandler     			     																										
EXTI5_9_IRQHandler     			     
ATIM1_BRK_IRQHandler     						
ATIM1_UP_IRQHandler     						
ATIM1_TRG_COM_IRQHandler     			
ATIM1_CC_IRQHandler     					 
GTIM1_IRQHandler     					 
GTIM2_IRQHandler     					 
GTIM3_IRQHandler     					 
I2C1_IRQHandler     			        
USART4_IRQHandler     			      
I2C2_IRQHandler     			        
CAN_IRQHandler     				         
SPI1_IRQHandler     			        
SPI2_IRQHandler     			        
USART1_IRQHandler     			      
USART2_IRQHandler     			      
USART3_IRQHandler     			      
EXTI10_15_IRQHandler     		   
RTC_ALARM_IRQHandler     		   
GTIM4_IRQHandler     			       
AGTIM2_BRK_IRQHandler     		  
AGTIM2_UP_IRQHandler     		   
AGTIM2_TRG_COM_IRQHandler     	 
AGTIM2_CC_IRQHandler     		
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END


