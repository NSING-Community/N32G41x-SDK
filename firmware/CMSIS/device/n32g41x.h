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
*\*\file n32g41x.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#ifndef __N32G41X_H__
#define __N32G41X_H__

#ifdef __cplusplus
extern "C" {
#endif

/**  N32G41X_Library_Basic **/

#if !defined USE_STDPERIPH_DRIVER
/*
 * Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
#define USE_STDPERIPH_DRIVER
#endif

/*
 * In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined HSE_VALUE
#define HSE_VALUE (8000000U) /* Value of the External oscillator in Hz */
#endif                      /* HSE_VALUE */

/** In the following line adjust the HSE\HSI\LSI\LSE Startup
   Timeout value **/
#define HSE_STARTUP_TIMEOUT ((uint16_t)0x4000U)     /* SYSCLK= 80M Time out for HSE start up */    
#define HSI_STARTUP_TIMEOUT ((uint16_t)0x0500U)     /* Time out for HSI start up */
#define LSI_STARTUP_TIMEOUT ((uint16_t)0x1000U)     /* Time out for LSI start up */
#define LSE_STARTUP_TIMEOUT ((uint32_t)0x00400000)  /* SYSCLK= 80M Time out for LSE start up */

#define HSI_VALUE (16000000U) /* Value of the Internal oscillator in Hz*/
#define LSI_VALUE (32000U) /* Value of the Internal Low Speed oscillator in Hz*/  
#define LSE_VALUE (32768U) /* Value of the External Low Speed oscillator in Hz*/

#define __N32G41X_STDPERIPH_VERSION_MAIN (0x01) /* [31:24] main version */
#define __N32G41X_STDPERIPH_VERSION_SUB1 (0x00) /* [23:16] sub1 version */
#define __N32G41X_STDPERIPH_VERSION_SUB2 (0x00) /* [15:8]  sub2 version */
#define __N32G41X_STDPERIPH_VERSION_RC   (0x00) /* [7:0]  release candidate */

/**
 * @brief N32G41X Standard Peripheral Library version number
 */
#define __N32G41X_STDPERIPH_VERSION                                                                                    \
    ((__N32G41X_STDPERIPH_VERSION_MAIN << 24) | (__N32G41X_STDPERIPH_VERSION_SUB1 << 16)                               \
     | (__N32G41X_STDPERIPH_VERSION_SUB2 << 8) | (__N32G41X_STDPERIPH_VERSION_RC))

/*
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#define __MPU_PRESENT 0          /* MPU present*/
#define __FPU_PRESENT 0          /* FPU present                            */
                                 /* N32G41X */
#define __NVIC_PRIO_BITS       4 /* N32G41X uses 4 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig 0 /* Set to 1 if different SysTick Config is used */

/** N32G41X Interrupt Number Definition **/
typedef enum IRQn
{
    /******  Cortex-M4 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,  /* 2 Non Maskable Interrupt                                          */
    HardFault_IRQn              = -13,  /* 3 Hard Fault Interrupt                                            */
    MemoryManagement_IRQn       = -12,  /* 4 Cortex-M4 Memory Management Interrupt                           */
    BusFault_IRQn               = -11,  /* 5 Cortex-M4 Bus Fault Interrupt                                   */
    UsageFault_IRQn             = -10,  /* 6 Cortex-M4 Usage Fault Interrupt                                 */
    SVCall_IRQn                 = -5,   /* 11 Cortex-M4 SV Call Interrupt                                    */
    DebugMonitor_IRQn           = -4,   /* 12 Cortex-M4 Debug Monitor Interrupt                              */
    PendSV_IRQn                 = -2,   /* 14 Cortex-M4 Pend SV Interrupt                                    */
    SysTick_IRQn                = -1,   /* 15 Cortex-M4 System Tick Interrupt                                */

    /******  N32G41X specific Interrupt Numbers **/
    WWDG_IRQn                   = 0,    /* Window Watchdog Interrupt                                         */
    PVD_IRQn                    = 1,    /* PVD through EXTI Line 16 detection Interrupt                      */
    RTC_STAMP_LSECSS_IRQn       = 2,    /* RTC STAMP and LSECSS through EXTI Line 18 detection Interrupt     */
    RTC_WKUP_IRQn               = 3,    /* RTC WKUP through EXTI Line 19 detection Interrupt                 */
    FLASH_IRQn                  = 4,    /* FLASH global Interrupt                                            */
    RCC_IRQn                    = 5,    /* RCC global Interrupt                                              */
    EXTI0_IRQn                  = 6,    /* EXTI Line0 Interrupt                                              */
    EXTI1_IRQn                  = 7,    /* EXTI Line1 Interrupt                                              */
    EXTI2_IRQn                  = 8,    /* EXTI Line2 Interrupt                                              */
    EXTI3_IRQn                  = 9,    /* EXTI Line3 Interrupt                                              */
    EXTI4_IRQn                  = 10,   /* EXTI Line4 Interrupt                                              */
    DMA_CH1_IRQn                = 11,   /* DMA Channel 1 global Interrupt                                    */
    DMA_CH2_IRQn                = 12,   /* DMA Channel 2 global Interrupt                                    */
    DMA_CH3_IRQn                = 13,   /* DMA Channel 3 global Interrupt                                    */
    DMA_CH4_IRQn                = 14,   /* DMA Channel 4 global Interrupt                                    */
    DMA_CH5_IRQn                = 15,   /* DMA Channel 5 global Interrupt                                    */
    DMA_CH6_IRQn                = 16,   /* DMA Channel 6 global Interrupt                                    */
    DMA_CH7_IRQn                = 17,   /* DMA Channel 7 global Interrupt                                    */
    ADC2_IRQn                   = 18,   /* ADC2 global Interrupts                                            */
    ADC1_IRQn                   = 19,   /* ADC1 global Interrupts                                            */
    BTIM1_IRQn                  = 20,   /* BTIM1 through EXTI Line 20 detection Interrupt                    */
    BTIM2_IRQn                  = 21,   /* BTIM2 global Interrupts                                           */
    COMP123_IRQn                = 22,   /* COMP1(through EXTI line 21) Interrupt                             */
                                        /* COMP2(through EXTI line 22) Interrupt                             */
                                        /* COMP3(through EXTI line 23) Interrupt                             */
    EXTI5_9_IRQn                = 23,   /* EXTI Line[9:5] Interrupt                                          */
    ATIM1_BRK_IRQn              = 24,   /* ATIM1 BRK Interrupt                                               */
    ATIM1_UP_IRQn               = 25,   /* ATIM1 UP Interrupt                                                */
    ATIM1_TRG_COM_IRQn          = 26,   /* ATIM1 TRG COM Interrupt                                           */
    ATIM1_CC_IRQn               = 27,   /* ATIM1 CC Interrupt                                                */
    GTIM1_IRQn                  = 28,   /* GTIM1 global Interrupt                                            */
    GTIM2_IRQn                  = 29,   /* GTIM2 global Interrupt                                            */
    GTIM3_IRQn                  = 30,   /* GTIM3 global Interrupt                                            */
    I2C1_IRQn                   = 31,   /* I2C1 global Interrupts                                            */
    USART4_IRQn                 = 32,   /* USART4 through EXTI Line 25 detection Interrupt                   */
    I2C2_IRQn                   = 33,   /* I2C2 global Interrupt                                             */
    CAN_IRQn                    = 34,   /* CAN global Interrupt                                              */
    SPI1_IRQn                   = 35,   /* SPI1 global Interrupt                                             */
    SPI2_IRQn                   = 36,   /* SPI2 global Interrupt                                             */
    USART1_IRQn                 = 37,   /* USART1 through EXTI Line 24 detection Interrupt                   */
    USART2_IRQn                 = 38,   /* USART2 global Interrupt                                           */
    USART3_IRQn                 = 39,   /* USART3 global Interrupt                                           */
    EXTI10_15_IRQn              = 40,   /* EXTI Line[15:10] Interrupts                                       */
    RTC_ALARM_IRQn              = 41,   /* RTC ALARM through EXTI Line 17 detection Interrupt                */
    GTIM4_IRQn                  = 42,   /* GTIM4 global Interrupt                                            */
    AGTIM2_BRK_IRQn             = 43,   /* ATIM2 BRK Interrupt                                               */
    AGTIM2_UP_IRQn              = 44,   /* ATIM2 UP Interrupt                                                */
    AGTIM2_TRG_COM_IRQn         = 45,   /* ATIM2 TRG COM Interrupt                                           */
    AGTIM2_CC_IRQn              = 46,   /* ATIM2 CC Interrupt                                                */
} IRQn_Type;

#include "core_cm4.h"
#include "system_n32g41x.h"
#include <stdint.h>
#include <stdbool.h>

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef const int32_t sc32; /* Read Only */
typedef const int16_t sc16; /* Read Only */
typedef const int8_t sc8;   /* Read Only */

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t vs8;

typedef __I int32_t vsc32; /* Read Only */
typedef __I int16_t vsc16; /* Read Only */
typedef __I int8_t vsc8;   /* Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef const uint32_t uc32; /* Read Only */
typedef const uint16_t uc16; /* Read Only */
typedef const uint8_t uc8;   /* Read Only */

typedef __IO uint32_t vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t vu8;

typedef __I uint32_t vuc32; /* Read Only */
typedef __I uint16_t vuc16; /* Read Only */
typedef __I uint8_t vuc8;   /* Read Only */

typedef enum {RESET = 0, SET = 1} FlagStatus, INTStatus;

typedef enum {DISABLE = 0, ENABLE = 1} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = 1} ErrorStatus;


/* N32G41X Standard Peripheral Library old definitions (maintained for legacy purpose) */
#define HSEStartUp_TimeOut HSE_STARTUP_TIMEOUT
#define HSE_Value          HSE_VALUE
#define HSI_Value          HSI_VALUE

/** Analog to Digital Converter **/
typedef struct
{
    __IO uint32_t STS;            //0x00
    __IO uint32_t CTRL1;          //0x04
    __IO uint32_t CTRL2;          //0x08
    __IO uint32_t CTRL3;          //0x0C
    __IO uint32_t SAMPT1;         //0x10
    __IO uint32_t SAMPT2;         //0x14
    __IO uint32_t SAMPT3;         //0x18
    __IO uint32_t INTEN;          //0x1C
    __IO uint32_t OFFSET1;        //0x20
    __IO uint32_t OFFSET2;        //0x24
    __IO uint32_t OFFSET3;        //0x28
    __IO uint32_t OFFSET4;        //0x2C
    __IO uint32_t AWDHIGH;        //0x30
    __IO uint32_t AWDLOW;         //0x34
    __IO uint32_t RESERVED0[10];  //0x38 - 0x5C
    __IO uint32_t RSEQ1;          //0x60
    __IO uint32_t RSEQ2;          //0x64
    __IO uint32_t RSEQ3;          //0x68
    __IO uint32_t JSEQ;           //0x6C
    __IO uint32_t JDAT1;          //0x70
    __IO uint32_t JDAT2;          //0x74
    __IO uint32_t JDAT3;          //0x78
    __IO uint32_t JDAT4;          //0x7C
    __IO uint32_t DAT;            //0x80
    __IO uint32_t RESERVED1[4];   //0x84 - 0x90
    __IO uint32_t CTRL4;          //0x94
}ADC_Module;

/** OPAMP **/
typedef struct
{
    __IO uint32_t OPAMP1_CS;          //0x00
    __IO uint32_t OPAMP2_CS;          //0x04
    __IO uint32_t OPAMP3_CS;          //0x08
    __IO uint32_t OPAMP4_CS;          //0x0C
    __IO uint32_t OPAMP_LOCK;         //0x10

} OPAMP_Module;


/** COMP_Single **/
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t FILC;
    __IO uint32_t FILP;
} COMP_SingleType;
/** COMP **/
typedef struct
{
    __IO uint32_t INTEN;         //0x00
    __IO uint32_t INTSTS;        //0x04
    __IO uint32_t WINMODE;       //0x08
    __IO uint32_t LOCK;          //0x0C
    COMP_SingleType Cmp[3];      //0x10 ~0x30
    __IO uint32_t INVREF1;       //0x34
    __IO uint32_t INVREF2;       //0x38
    __IO uint32_t INVREF3;       //0x3C
} COMP_Module;

/*** DMA Controller ***/
typedef struct
{
    __IO uint32_t CHCFG;              //0x08+20 * (x-1)
    __IO uint32_t TXNUM;              //0x0c+20 * (x-1)
    __IO uint32_t PADDR;              //0x10+20 * (x-1)
    __IO uint32_t MADDR;              //0x14+20 * (x-1)
    __IO uint32_t CHSEL;              //0x18+20 * (x-1)
} DMA_ChannelType;

typedef struct
{
    __IO uint32_t INTSTS;              //0x00
    __IO uint32_t INTCLR;              //0x04
    __IO DMA_ChannelType DMA_Channel[7];
} DMA_Module;


/*** Debug MCU ***/
typedef struct
{
    __IO uint32_t ID;           //0x00
    __IO uint32_t CTRL;         //0x04
} DBG_Module;




/** External Interrupt/Event Controller **/
typedef struct
{
  __IO uint32_t EMASK;    /*offset 0x00*/
  __IO uint32_t IMASK;    /*offset 0x04*/
  __IO uint32_t FT_CFG;   /*offset 0x08*/
  __IO uint32_t RT_CFG;   /*offset 0x0C*/
  __IO uint32_t PEND;     /*offset 0x10*/
  __IO uint32_t SWIE;     /*offset 0x14*/
  __IO uint32_t TS_SEL;   /*offset 0x18*/
} EXTI_Module;

/** FLASH Registers **/
typedef struct
{
    __IO uint32_t AC;       //0x00
    __IO uint32_t KEY;      //0x04
    __IO uint32_t OPTKEY;   //0x08
    __IO uint32_t STS;      //0x0C
    __IO uint32_t CTRL;     //0x10
    __IO uint32_t ADD;      //0x14
    __IO uint32_t OB2;      //0x18
    __IO uint32_t OB;       //0x1C
    __IO uint32_t WRP;      //0x20
    uint32_t RESERVED[3];   //0x24 - 0x2C
    __IO uint32_t CAHR;     //0x30
} FLASH_Module;

/** Option Bytes Registers **/
typedef struct
{
    __IO uint32_t RDP1;         //0x00
    __IO uint32_t USER0;        //0x04
    __IO uint32_t USER1;        //0x08
    __IO uint32_t USER3_USER2;  //0x0C
    __IO uint32_t USER5_USER4;  //0x10
    __IO uint32_t USER6;        //0x14
    __IO uint32_t USER7;        //0x18
    __IO uint32_t Data1_Data0;  //0x1C
    __IO uint32_t WRP1_WRP0;    //0x20
    __IO uint32_t WRP3_WRP2;    //0x24
    __IO uint32_t RDP2;         //0x28
} OB_Module;

/** CRC calculation unit **/
typedef struct
{
    __IO uint32_t CRC32CTRL;    //0x00
    __IO uint32_t CRC32DAT;     //0x04
    __IO uint8_t  CRC32IDAT;    //0x08
    uint8_t RESERVED0;
    uint16_t RESERVED1;
    __IO uint32_t CRC32D;       //0x0C
    __IO uint32_t CRC16CTRL;    //0x10
    __IO uint8_t  CRC16DAT;     //0x14
    uint8_t RESERVED2;
    uint16_t RESERVED3;
    __IO uint16_t CRC16D;       //0x18
    uint16_t RESERVED4;
    __IO uint8_t LRC;           //0x1C
    uint8_t RESERVED5;
    uint16_t RESERVED6;
} CRC_Module;

/** General Purpose I/O **/
typedef struct
{
    __IO uint32_t PMODE;        //0x00
    __IO uint32_t POTYPE;       //0x04
    uint32_t RESERVED0;         //0x08
    __IO uint32_t PUPD;         //0x0C
    __IO uint32_t PID;          //0x10
    __IO uint32_t POD;          //0x14
    __IO uint32_t PBSC;         //0x18
    __IO uint32_t PLOCK;        //0x1C
    __IO uint32_t AFL;          //0x20
    __IO uint32_t AFH;          //0x24
    __IO uint32_t PBC;          //0x28
    __IO uint32_t DS;           //0x2C
}GPIO_Module;

/** Alternate Function I/O **/
typedef struct
{
  __IO uint32_t CFG;           //0x00
  __IO uint32_t EXTI_CFG[4];   //0x04 ~ 0x10
  __IO uint32_t DIGEFT_CFG[4]; //0x14 ~ 0x20
}AFIO_Module;

/** Inter Integrated Circuit Interface **/
typedef struct
{
    __IO uint32_t CTRL1;          //0x00
    __IO uint32_t CTRL2;          //0x04
    __IO uint16_t OADDR1;         //0x08
    uint16_t  RESERVED1;
    __IO uint16_t OADDR2;         //0x0C
    uint16_t  RESERVED2;
    __IO uint16_t DAT;            //0x10
    uint16_t  RESERVED3; 
    __IO uint32_t STS1;           //0x14
    __IO uint32_t STS2;           //0x18
    __IO uint16_t CLKCTRL;        //0x1C
    uint16_t  RESERVED4;
    __IO uint16_t TMRISE;         //0x20
    uint16_t  RESERVED5; 
    uint32_t RESERVED6;           //0x24
    __IO uint16_t GFLTRCTRL;      //0x28
    uint16_t  RESERVED10; 
} I2C_Module;

/** Controller Area Network TxMailBox **/

typedef struct
{
    __IO uint32_t TMI;
    __IO uint32_t TMDT;
    __IO uint32_t TMDL;
    __IO uint32_t TMDH;
} CAN_TxMailBox_Param;

/** Controller Area Network FIFOMailBox **/

typedef struct
{
    __IO uint32_t RMI;
    __IO uint32_t RMDT;
    __IO uint32_t RMDL;
    __IO uint32_t RMDH;
} CAN_FIFOMailBox_Param;

/** Controller Area Network FilterRegister **/

typedef struct
{
    __IO uint32_t FR1;
    __IO uint32_t FR2;
} CAN_FilterRegister_Param;

/** Controller Area Network **/
typedef struct
{
    __IO uint32_t MCTRL;
    __IO uint32_t MSTS;
    __IO uint32_t TSTS;
    __IO uint32_t RFF0;
    __IO uint32_t RFF1;
    __IO uint32_t INTE;
    __IO uint32_t ESTS;
    __IO uint32_t BTIM;
    uint32_t RESERVED0[88];
    CAN_TxMailBox_Param sTxMailBox[3];
    CAN_FIFOMailBox_Param sFIFOMailBox[2];
    uint32_t RESERVED1[12];
    __IO uint32_t FMC;
    __IO uint32_t FM1;
    uint32_t RESERVED2;
    __IO uint32_t FS1;
    uint32_t RESERVED3;
    __IO uint32_t FFA1;
    uint32_t RESERVED4;
    __IO uint32_t FA1;
    uint32_t RESERVED5[8];
    CAN_FilterRegister_Param sFilterRegister[14];
} CAN_Module;

/** Window WATCHDOG **/
typedef struct
{
    __IO uint32_t CFG;     //0x00
    __IO uint32_t CTRL;    //0x04
    __IO uint32_t STS;     //0x08
} WWDG_Module;

/** Independent WATCHDOG **/
typedef struct
{
  __IO uint32_t KEY;           //0x00
  __IO uint32_t STS;           //0x04
  __IO uint32_t PREDIV;        //0x08
  __IO uint32_t RELV;          //0x0C
}IWDG_Module;

/**  Power Control **/
typedef struct
{
  __IO uint32_t CTRL;       //0x00
  __IO uint32_t CTRLSTS;    //0x04
  __IO uint32_t CTRL2;      //0x08
} PWR_Module;


/** Reset and Clock Control **/
typedef struct
{
    __IO uint32_t CTRL;                //0x0
    __IO uint32_t CFG;                 //0x4
    __IO uint32_t CLKINT;              //0x8
    __IO uint32_t APB2PRST;            //0xC
    __IO uint32_t APB1PRST;            //0x10
    __IO uint32_t AHBPCLKEN;           //0x14
    __IO uint32_t APB2PCLKEN;          //0x18
    __IO uint32_t APB1PCLKEN;          //0x1C
    uint32_t RESERVED0;                //0x20
    __IO uint32_t CTRLSTS;             //0x24
    __IO uint32_t AHBPRST;             //0x28
    __IO uint32_t CFG2;                //0x2C
    __IO uint32_t CFG3;                //0x30
      __IO uint32_t RESERVED1[3];      //0x34
    __IO uint32_t PLLCTRL;             //0x40
    __IO uint32_t PWRCTRL;             //0x44
    __IO uint32_t CFG4;                //0x48
    __IO uint32_t EMCCTRL;             //0x4C
    __IO uint32_t CFG5;                //0x50
} RCC_Module;


/** Real-Time Clock **/
typedef struct
{
    __IO uint32_t INITSTS;     /* RTC initialization and status register,                    Address offset: 0x00 */
    __IO uint32_t CTRL;        /* RTC control register,                                      Address offset: 0x04 */
    __IO uint32_t TSH;         /* RTC time register,                                         Address offset: 0x08 */
    __IO uint32_t DATE;        /* RTC date register,                                         Address offset: 0x0C */
    __IO uint32_t WRP;         /* RTC write protection register,                             Address offset: 0x10 */
    __IO uint32_t SCTRL;       /* RTC shift control register,                                Address offset: 0x14 */
    __IO uint32_t SUBS;        /* RTC sub second register,                                   Address offset: 0x18 */
    __IO uint32_t TST;         /* RTC time stamp time register,                              Address offset: 0x1C */
    __IO uint32_t ALARMA;      /* RTC alarm A register,                                      Address offset: 0x20 */
    __IO uint32_t PRE;         /* RTC prescaler register,                                    Address offset: 0x24 */
    __IO uint32_t ALARMB;      /* RTC alarm B register,                                      Address offset: 0x28 */
    __IO uint32_t WKUPT;       /* RTC wakeup timer register,                                 Address offset: 0x2C */
    __IO uint32_t RESERVED;    /* Reserved,                                                  Address offset: 0x30 */
    __IO uint32_t ALRMASS;     /* RTC alarm A sub second register,                           Address offset: 0x34 */
    __IO uint32_t OPT;         /* RTC option register,                                       Address offset: 0x38 */
    __IO uint32_t ALRMBSS;     /* RTC alarm B sub second register,                           Address offset: 0x3C */
    __IO uint32_t CALIB;       /* RTC calibration register,                                  Address offset: 0x40 */
    __IO uint32_t TSSS;        /* RTC time-stamp sub second register,                        Address offset: 0x44 */
    __IO uint32_t TSD;         /* RTC time stamp date register,                              Address offset: 0x48 */
} RTC_Module;


typedef struct
{
    __IO uint16_t CTRL1;        // 0x00
    uint16_t RESERVED0;
    __IO uint16_t CTRL2;        // 0x04
    uint16_t RESERVED1;
    __IO uint16_t STS;          // 0x08
    uint16_t RESERVED2;
    __IO uint16_t DAT;          // 0x0c
    uint16_t RESERVED3;
	__IO uint16_t CRCTDAT;      // 0x10
    uint16_t RESERVED4;
	__IO uint16_t CRCRDAT;      // 0x14
    uint16_t RESERVED5;
    __IO uint16_t CRCPOLY;      // 0x18
    uint16_t RESERVED6;
    __IO uint16_t SPI_I2S_CFGR; // 0x1c
    uint16_t RESERVED7;
    __IO uint16_t I2SPREDIV;    // 0x20
    uint16_t RESERVED8;
	uint32_t RESERVED9;         // 0x24
	uint32_t RESERVED10;        // 0x28
	uint32_t RESERVED11;        // 0x2c
	uint32_t RESERVED12;        // 0x30
	uint32_t RESERVED13;        // 0x34
	__IO uint16_t CTRL3;        // 0x38
} SPI_Module;


/** TIM **/
typedef struct
{
    __IO uint32_t CTRL1;         //0x00
    __IO uint32_t CTRL2;         //0x04
    __IO uint32_t STS;           //0x08
    __IO uint32_t EVTGEN;        //0x0C
    __IO uint32_t SMCTRL;        //0x10
    __IO uint32_t DINTEN;        //0x14
    __IO uint32_t CCMOD1;        //0x18
    __IO uint32_t CCMOD2;        //0x1C
    __IO uint32_t CCMOD3;        //0x20
    __IO uint32_t CCEN;          //0x24
    __IO uint32_t CCDAT1;        //0x28
    __IO uint32_t CCDAT2;        //0x2C
    __IO uint32_t CCDAT3;        //0x30
    __IO uint32_t CCDAT4;        //0x34
    __IO uint32_t CCDAT5;        //0x38
    __IO uint32_t CCDAT6;        //0x3C
    __IO uint32_t PSC;           //0x40
    __IO uint32_t AR;            //0x44
    __IO uint32_t CNT;           //0x48
    __IO uint32_t REPCNT;        //0x4C
    __IO uint32_t BKDT;          //0x50
    __IO uint32_t CCDAT7;        //0x54
    __IO uint32_t CCDAT8;        //0x58
    __IO uint32_t CCDAT9;        //0x5C
    __IO uint32_t BKFR;          //0x60
    __IO uint32_t C1FILT;        //0x64
    __IO uint32_t C2FILT;        //0x68
    __IO uint32_t C3FILT;        //0x6C
    __IO uint32_t C4FILT;        //0x70
    __IO uint32_t FILTO;         //0x74
    __IO uint32_t INSEL;         //0x78
    __IO uint32_t AF1;           //0x7C
    __IO uint32_t RESERVED3[2];  //0x80//0x84
    __IO uint32_t ENCDAT;        //0x88
    __IO uint32_t ENCMCTRL;      //0x8C
    __IO uint32_t ENCLVR;        //0x90
    __IO uint32_t DCTRL;         //0x94
    __IO uint32_t DADDR;         //0x98
} TIM_Module;


/** Universal Synchronous Asynchronous Receiver Transmitter **/
typedef struct
{
    __IO uint32_t CTRL1;        //0x00
    __IO uint32_t CTRL2;        //0x04
    __IO uint32_t CTRL3;        //0x08
    __IO uint32_t STS;          //0x0C
    __IO uint32_t DAT;          //0x10
    __IO uint32_t BRCF;         //0x14
    __IO uint32_t GTP;          //0x18
    __IO uint32_t RESERVED[2];  //0x1C
    __IO uint32_t RTO;          //0x24
    __IO uint32_t WKUP;         //0x28
} USART_Module;


#define FLASH_BASE           ((uint32_t)0x08000000) /* FLASH base address in the alias region */
#define SRAM_BASE            ((uint32_t)0x20000000) /* SRAM base address in the alias region */
#define PERIPH_BASE          ((uint32_t)0x40000000) /* Peripheral base address in the alias region */

#define UCID_BASE            ((uint32_t)0x1FFFF4D0) /* UCID Address */
#define UCID_LENGTH          ((uint8_t)0x10)        /* UCID Length : 16 Bytes */
#define UID_BASE             ((uint32_t)0x1FFFF500) /* UID Address */
#define UID_LENGTH           ((uint8_t)0x0C)        /* UID Length : 12 Bytes */
#define DBGMCU_ID_BASE       ((uint32_t)0xE0042000U) /* DBGMCU_ID Address */
#define DBGMCU_ID_LENGTH     ((uint8_t)0x04)        /* DBGMCU_ID Length : 4 Bytes */

/* Peripheral memory map */
#define APB1PERIPH_BASE      ((uint32_t)(PERIPH_BASE))
#define APB2PERIPH_BASE      ((uint32_t)(PERIPH_BASE + (uint32_t)0x10000U))
#define AHBPERIPH_BASE       ((uint32_t)(PERIPH_BASE + (uint32_t)0x20000U))

/* APB1 */
#define GTIM1_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x0000U))
#define GTIM2_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x0400U))
#define GTIM3_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x0800U))
#define GTIM4_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x0C00U))
#define BTIM1_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x1000U))
#define BTIM2_BASE           ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x1400U))
#define OPA_BASE             ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x2000U))
#define COMP_BASE            ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x2400U))
#define RTC_BASE             ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x2800U))
#define WWDG_BASE            ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x2C00U))
#define IWDG_BASE            ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x3000U))
#define USART2_BASE          ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x4400U))
#define USART3_BASE          ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x4800U))
#define I2C1_BASE            ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x5400U))
#define I2C2_BASE            ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x5800U))
#define CAN_BASE             ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x6400U))
#define PWR_BASE             ((uint32_t)(APB1PERIPH_BASE + (uint32_t)0x7000U))


/* APB2 */
#define EXTI_BASE            ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x0400U))
#define ATIM1_BASE           ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x2C00U))
#define SPI1_BASE            ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x3000U))
#define ATIM2_BASE           ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x3400U))
#define USART1_BASE          ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x3800U))
#define SPI2_BASE            ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x3C00U))
#define USART4_BASE          ((uint32_t)(APB2PERIPH_BASE + (uint32_t)0x5000U))


/* AHB */
#define DMA_BASE             ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0000))
#define DMA_CH1_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0008))
#define DMA_CH2_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x001C))
#define DMA_CH3_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0030))
#define DMA_CH4_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0044))
#define DMA_CH5_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0058))
#define DMA_CH6_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x006C))
#define DMA_CH7_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0080))
#define ADC1_BASE            ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0800))
#define ADC2_BASE            ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x0900))
#define RCC_BASE             ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1000))
#define GPIOA_BASE           ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1400))
#define GPIOB_BASE           ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1500))
#define GPIOC_BASE           ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1600))
#define GPIOD_BASE           ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1700))
#define AFIO_BASE            ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x1800))
#define FLASH_R_BASE         ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x2000))  /* Flash registers base address */
#define OB_BASE              ((uint32_t)0x1FFFF600U)              /* Flash Option Bytes base address */
#define CRC_BASE             ((uint32_t)(AHBPERIPH_BASE + (uint32_t)0x3000))

#define DBG_BASE             ((uint32_t)0xE0042000U)    /* Debug MCU registers base address */


#define GTIM1                ((TIM_Module*)(uintptr_t)GTIM1_BASE)
#define GTIM2                ((TIM_Module*)(uintptr_t)GTIM2_BASE)
#define GTIM3                ((TIM_Module*)(uintptr_t)GTIM3_BASE)
#define GTIM4                ((TIM_Module*)(uintptr_t)GTIM4_BASE)
#define BTIM1                ((TIM_Module*)(uintptr_t)BTIM1_BASE)
#define BTIM2                ((TIM_Module*)(uintptr_t)BTIM2_BASE)
#define OPAMP                ((OPAMP_Module*)(uintptr_t)OPA_BASE)
#define COMP                 ((COMP_Module*)(uintptr_t)COMP_BASE)
#define RTC                  ((RTC_Module*)(uintptr_t)RTC_BASE)
#define WWDG                 ((WWDG_Module*)(uintptr_t)WWDG_BASE)
#define IWDG                 ((IWDG_Module*)(uintptr_t)IWDG_BASE)
#define USART2               ((USART_Module*)(uintptr_t)USART2_BASE)
#define USART3               ((USART_Module*)(uintptr_t)USART3_BASE)
#define I2C1                 ((I2C_Module*)(uintptr_t)I2C1_BASE)
#define I2C2                 ((I2C_Module*)(uintptr_t)I2C2_BASE)
#define CAN                  ((CAN_Module*)(uintptr_t)CAN_BASE)
#define PWR                  ((PWR_Module*)(uintptr_t)PWR_BASE)

#define EXTI                 ((EXTI_Module*)(uintptr_t)EXTI_BASE)
#define ATIM1                ((TIM_Module*)(uintptr_t)ATIM1_BASE)
#define SPI1                 ((SPI_Module*)(uintptr_t)SPI1_BASE)
#define ATIM2                ((TIM_Module*)(uintptr_t)ATIM2_BASE)
#define USART1               ((USART_Module*)(uintptr_t)USART1_BASE)
#define SPI2                 ((SPI_Module*)(uintptr_t)SPI2_BASE)
#define USART4               ((USART_Module*)(uintptr_t)USART4_BASE)

#define DMA                  ((DMA_Module*)(uintptr_t)DMA_BASE)
#define DMA_CH1              ((DMA_ChannelType*)(uintptr_t)DMA_CH1_BASE)
#define DMA_CH2              ((DMA_ChannelType*)(uintptr_t)DMA_CH2_BASE)
#define DMA_CH3              ((DMA_ChannelType*)(uintptr_t)DMA_CH3_BASE)
#define DMA_CH4              ((DMA_ChannelType*)(uintptr_t)DMA_CH4_BASE)
#define DMA_CH5              ((DMA_ChannelType*)(uintptr_t)DMA_CH5_BASE)
#define DMA_CH6              ((DMA_ChannelType*)(uintptr_t)DMA_CH6_BASE)
#define DMA_CH7              ((DMA_ChannelType*)(uintptr_t)DMA_CH7_BASE)
#define ADC1                 ((ADC_Module*)(uintptr_t)ADC1_BASE)
#define ADC2                 ((ADC_Module*)(uintptr_t)ADC2_BASE)
#define RCC                  ((RCC_Module*)(uintptr_t)RCC_BASE)
#define GPIOA                ((GPIO_Module*)(uintptr_t)GPIOA_BASE)
#define GPIOB                ((GPIO_Module*)(uintptr_t)GPIOB_BASE)
#define GPIOC                ((GPIO_Module*)(uintptr_t)GPIOC_BASE)
#define GPIOD                ((GPIO_Module*)(uintptr_t)GPIOD_BASE)
#define AFIO                 ((AFIO_Module*)(uintptr_t)AFIO_BASE)
#define FLASH                ((FLASH_Module*)(uintptr_t)FLASH_R_BASE)
#define OBT                  ((OB_Module*)(uintptr_t)OB_BASE)
#define CRC                  ((CRC_Module*)(uintptr_t)CRC_BASE)

#define DBG                  ((DBG_Module*)(uintptr_t)DBG_BASE)

/***  Peripheral Registers_Bits_Definition   ***/

/*** Power Control ***/

/** Bit definition for PWR_CTRL register **/
#define PWR_CTRL_NRSTCNT                                 ((uint32_t)0x03F80000U)         /* Bit[25:19] */
#define PWR_CTRL_NRSTCNT_0                               ((uint32_t)0x00080000U)         /* Bit19 */
#define PWR_CTRL_NRSTCNT_1                               ((uint32_t)0x00100000U)         /* Bit20 */
#define PWR_CTRL_NRSTCNT_2                               ((uint32_t)0x00200000U)         /* Bit21 */
#define PWR_CTRL_NRSTCNT_3                               ((uint32_t)0x00400000U)         /* Bit22 */
#define PWR_CTRL_NRSTCNT_4                               ((uint32_t)0x00800000U)         /* Bit23 */
#define PWR_CTRL_NRSTCNT_5                               ((uint32_t)0x01000000U)         /* Bit24 */
#define PWR_CTRL_NRSTCNT_6                               ((uint32_t)0x02000000U)         /* Bit25 */
#define PWR_CTRL_PVDCNT                                  ((uint32_t)0x0007C000U)         /* Bit[18:14] */
#define PWR_CTRL_PVDCNT_0                                ((uint32_t)0x00004000U)         /* Bit14 */
#define PWR_CTRL_PVDCNT_1                                ((uint32_t)0x00008000U)         /* Bit15 */
#define PWR_CTRL_PVDCNT_2                                ((uint32_t)0x00010000U)         /* Bit16 */
#define PWR_CTRL_PVDCNT_3                                ((uint32_t)0x00020000U)         /* Bit17 */
#define PWR_CTRL_PVDCNT_4                                ((uint32_t)0x00040000U)         /* Bit18 */
#define PWR_CTRL_IWDGRSTEN                               ((uint32_t)0x00001000U)         /* Bit[12] */
#define PWR_CTRL_PLS                                     ((uint32_t)0x000001E0U)         /* Bit[8:5] */
#define PWR_CTRL_PLS_0                                   ((uint32_t)0x00000020U)         /* Bit5 */
#define PWR_CTRL_PLS_1                                   ((uint32_t)0x00000040U)         /* Bit6 */
#define PWR_CTRL_PLS_2                                   ((uint32_t)0x00000080U)         /* Bit7 */
#define PWR_CTRL_PLS_3                                   ((uint32_t)0x00000100U)         /* Bit8 */
#define PWR_CTRL_PVDEN                                   ((uint32_t)0x00000010U)         /* Bit[4] */

/** Bit definition for PWR_STS register **/
#define PWR_STS_PVDO                                     ((uint32_t)0x00000004U)         /* Bit[2] */

/** Bit definition for PWR_CTRL2 register **/
#define PWR_CTRL2_MRLPDLY                                ((uint32_t)0x00001FFEU)         /* Bit[12:1] */
#define PWR_CTRL2_MRLPDLY_0                              ((uint32_t)0x00000002U)         /* Bit1 */
#define PWR_CTRL2_MRLPDLY_1                              ((uint32_t)0x00000004U)         /* Bit2 */
#define PWR_CTRL2_MRLPDLY_2                              ((uint32_t)0x00000008U)         /* Bit3 */
#define PWR_CTRL2_MRLPDLY_3                              ((uint32_t)0x00000010U)         /* Bit4 */
#define PWR_CTRL2_MRLPDLY_4                              ((uint32_t)0x00000020U)         /* Bit5 */
#define PWR_CTRL2_MRLPDLY_5                              ((uint32_t)0x00000040U)         /* Bit6 */
#define PWR_CTRL2_MRLPDLY_6                              ((uint32_t)0x00000080U)         /* Bit7 */
#define PWR_CTRL2_MRLPDLY_7                              ((uint32_t)0x00000100U)         /* Bit8 */
#define PWR_CTRL2_MRLPDLY_8                              ((uint32_t)0x00000200U)         /* Bit9 */
#define PWR_CTRL2_MRLPDLY_9                              ((uint32_t)0x00000400U)         /* Bit10 */
#define PWR_CTRL2_MRLPDLY_10                             ((uint32_t)0x00000800U)         /* Bit11 */
#define PWR_CTRL2_MRLPDLY_11                             ((uint32_t)0x00001000U)         /* Bit12 */
#define PWR_CTRL2_MRLPEN                                 ((uint32_t)0x00000001U)         /* Bit[0] */


/*** Reset and Clock Control ***/
/******** Bit definition for RCC_CTRL register  ********/
#define RCC_CTRL_LSIEN                                   ((uint32_t)0x80000000U)         /* Bit31 */
#define RCC_CTRL_LSEEN                                   ((uint32_t)0x40000000U)         /* Bit30 */
#define RCC_CTRL_LSECSSEN                                ((uint32_t)0x20000000U)         /* Bit29 */
#define RCC_CTRL_LSEBP                                   ((uint32_t)0x10000000U)         /* Bit28 */
#define RCC_CTRL_LSERDF                                  ((uint32_t)0x08000000U)         /* Bit27 */
#define RCC_CTRL_LSIRDF                                  ((uint32_t)0x04000000U)         /* Bit26 */
#define RCC_CTRL_PLLRDF                                  ((uint32_t)0x02000000U)         /* Bit25 */
#define RCC_CTRL_PLLEN                                   ((uint32_t)0x01000000U)         /* Bit24 */
#define RCC_CTRL_PLLBP                                   ((uint32_t)0x00800000U)         /* Bit23 */
#define RCC_CTRL_LSECAPEN                                ((uint32_t)0x00400000U)         /* Bit22 */
#define RCC_CTRL_HSECAPEN                                ((uint32_t)0x00200000U)         /* Bit21 */
#define RCC_CTRL_CLKSSEN                                 ((uint32_t)0x00100000U)         /* Bit20 */
#define RCC_CTRL_HSEBP                                   ((uint32_t)0x00080000U)         /* Bit19 */
#define RCC_CTRL_HSERDF                                  ((uint32_t)0x00040000U)         /* Bit18 */
#define RCC_CTRL_HSEEN                                   ((uint32_t)0x00020000U)         /* Bit17 */

#define RCC_CTRL_HSITRIM                                 ((uint32_t)0x0001FF00U)         /* Bit[16:8] */
#define RCC_CTRL_HSITRIM_0                               ((uint32_t)0x00000100U)         /* Bit8 */
#define RCC_CTRL_HSITRIM_1                               ((uint32_t)0x00000200U)         /* Bit9 */
#define RCC_CTRL_HSITRIM_2                               ((uint32_t)0x00000400U)         /* Bit10 */
#define RCC_CTRL_HSITRIM_3                               ((uint32_t)0x00000800U)         /* Bit11 */
#define RCC_CTRL_HSITRIM_4                               ((uint32_t)0x00001000U)         /* Bit12 */
#define RCC_CTRL_HSITRIM_5                               ((uint32_t)0x00002000U)         /* Bit13 */
#define RCC_CTRL_HSITRIM_6                               ((uint32_t)0x00004000U)         /* Bit14 */
#define RCC_CTRL_HSITRIM_7                               ((uint32_t)0x00008000U)         /* Bit15 */
#define RCC_CTRL_HSITRIM_8                               ((uint32_t)0x00010000U)         /* Bit16 */

#define RCC_CTRL_LSITRIM                                 ((uint32_t)0x000000FCU)         /* Bit[7:2] */
#define RCC_CTRL_LSITRIM_0                               ((uint32_t)0x00000004U)         /* Bit2 */
#define RCC_CTRL_LSITRIM_1                               ((uint32_t)0x00000008U)         /* Bit3 */
#define RCC_CTRL_LSITRIM_2                               ((uint32_t)0x00000010U)         /* Bit4 */
#define RCC_CTRL_LSITRIM_3                               ((uint32_t)0x00000020U)         /* Bit5 */
#define RCC_CTRL_LSITRIM_4                               ((uint32_t)0x00000040U)         /* Bit6 */
#define RCC_CTRL_LSITRIM_5                               ((uint32_t)0x00000080U)         /* Bit7 */

#define RCC_CTRL_HSIRDF                                  ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_CTRL_HSIEN                                   ((uint32_t)0x00000001U)         /* Bit[0] */

/******** Bit definition for RCC_CFG register  ********/
#define RCC_CFG_MCOPRES                                  ((uint32_t)0xE0000000U)         /* Bit[31:29] */
#define RCC_CFG_MCOPRES_0                                ((uint32_t)0x20000000U)         /* Bit29 */
#define RCC_CFG_MCOPRES_1                                ((uint32_t)0x40000000U)         /* Bit30 */
#define RCC_CFG_MCOPRES_2                                ((uint32_t)0x80000000U)         /* Bit31 */

#define RCC_CFG_MCO                                      ((uint32_t)0x07000000U)         /* Bit[26:24] */
#define RCC_CFG_MCO_0                                    ((uint32_t)0x01000000U)         /* Bit24 */
#define RCC_CFG_MCO_1                                    ((uint32_t)0x02000000U)         /* Bit25 */
#define RCC_CFG_MCO_2                                    ((uint32_t)0x04000000U)         /* Bit26 */

#define RCC_CFG_PLLSYSDIV                                ((uint32_t)0x00800000U)         /* Bit23 */

#define RCC_CFG_PLLMUL                                   ((uint32_t)0x007F0000U)         /* Bit[22:16] */
#define RCC_CFG_PLLMUL_0                                 ((uint32_t)0x00010000U)         /* Bit16 */
#define RCC_CFG_PLLMUL_1                                 ((uint32_t)0x00020000U)         /* Bit17 */
#define RCC_CFG_PLLMUL_2                                 ((uint32_t)0x00040000U)         /* Bit18 */
#define RCC_CFG_PLLMUL_3                                 ((uint32_t)0x00080000U)         /* Bit19 */
#define RCC_CFG_PLLMUL_4                                 ((uint32_t)0x00100000U)         /* Bit20 */
#define RCC_CFG_PLLMUL_5                                 ((uint32_t)0x00200000U)         /* Bit21 */
#define RCC_CFG_PLLMUL_6                                 ((uint32_t)0x00400000U)         /* Bit22 */

#define RCC_CFG_PLLSRC                                   ((uint32_t)0x00008000U)         /* Bit[15] */
#define RCC_CFG_PLLOD                                    ((uint32_t)0x00004000U)         /* Bit[14] */

#define RCC_CFG_APB2PRES                                 ((uint32_t)0x00003800U)         /* Bit[13:11] */
#define RCC_CFG_APB2PRES_0                               ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_CFG_APB2PRES_1                               ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_CFG_APB2PRES_2                               ((uint32_t)0x00002000U)         /* Bit[13] */

#define RCC_CFG_APB1PRES                                 ((uint32_t)0x00000700U)         /* Bit[10:8] */
#define RCC_CFG_APB1PRES_0                               ((uint32_t)0x00000100U)         /* Bit[8] */
#define RCC_CFG_APB1PRES_1                               ((uint32_t)0x00000200U)         /* Bit[9] */
#define RCC_CFG_APB1PRES_2                               ((uint32_t)0x00000400U)         /* Bit[10] */

#define RCC_CFG_AHBPRES                                  ((uint32_t)0x000000F0U)         /* Bit[7:4] */
#define RCC_CFG_AHBPRES_0                                ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_CFG_AHBPRES_1                                ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_CFG_AHBPRES_2                                ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_CFG_AHBPRES_3                                ((uint32_t)0x00000080U)         /* Bit[7] */

#define RCC_CFG_SCLKSTS                                  ((uint32_t)0x0000000CU)         /* Bit[3:2] */
#define RCC_CFG_SCLKSTS_HSI                              ((uint32_t)0x00000000U)         /* HSI clock used as system clock*/
#define RCC_CFG_SCLKSTS_HSE                              ((uint32_t)0x00000004U)         /* HSE oscillator used as system clock */
#define RCC_CFG_SCLKSTS_PLL                              ((uint32_t)0x00000008U)         /* PLL clock used as system clock*/

#define RCC_CFG_SCLKSW                                   ((uint32_t)0x00000003U)         /* Bit[1:0] */
#define RCC_CFG_SCLKSW_HSI                               ((uint32_t)0x00000000U)         /* HSI clock used as system clock*/
#define RCC_CFG_SCLKSW_HSE                               ((uint32_t)0x00000001U)         /* HSE oscillator used as system clock */
#define RCC_CFG_SCLKSW_PLL                               ((uint32_t)0x00000002U)         /* PLL clock used as system clock*/

/******** Bit definition for RCC_CLKINT register  ********/
#define RCC_CLKINT_LSESSICLR                             ((uint32_t)0x04000000U)         /* Bit[26] */
#define RCC_CLKINT_LSESSIEN                              ((uint32_t)0x02000000U)         /* Bit[25] */
#define RCC_CLKINT_LSESSIF                               ((uint32_t)0x01000000U)         /* Bit[24] */
#define RCC_CLKINT_CLKSSICLR                             ((uint32_t)0x00800000U)         /* Bit[23] */
#define RCC_CLKINT_PLLRDICLR                             ((uint32_t)0x00100000U)         /* Bit[20] */
#define RCC_CLKINT_HSERDICLR                             ((uint32_t)0x00080000U)         /* Bit[19] */
#define RCC_CLKINT_HSIRDICLR                             ((uint32_t)0x00040000U)         /* Bit[18] */
#define RCC_CLKINT_LSERDICLR                             ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_CLKINT_LSIRDICLR                             ((uint32_t)0x00010000U)         /* Bit[16] */
#define RCC_CLKINT_PLLRDIEN                              ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_CLKINT_HSERDIEN                              ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_CLKINT_HSIRDIEN                              ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_CLKINT_LSERDIEN                              ((uint32_t)0x00000200U)         /* Bit[9] */
#define RCC_CLKINT_LSIRDIEN                              ((uint32_t)0x00000100U)         /* Bit[8] */
#define RCC_CLKINT_CLKSSIF                               ((uint32_t)0x00000080U)         /* Bit[7] */
#define RCC_CLKINT_PLLRDIF                               ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_CLKINT_HSERDIF                               ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_CLKINT_HSIRDIF                               ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_CLKINT_LSERDIF                               ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_CLKINT_LSIRDIF                               ((uint32_t)0x00000001U)         /* Bit[0] */


/******** Bit definition for RCC_APB2PRST register  ********/
#define RCC_APB2PRST_SPI2RST                             ((uint32_t)0x00080000U)         /* Bit[19] */
#define RCC_APB2PRST_USART4RST                           ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_APB2PRST_USART1RST                           ((uint32_t)0x00004000U)         /* Bit[14] */
#define RCC_APB2PRST_ATIM2RST                            ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_APB2PRST_SPI1RST                             ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_APB2PRST_ATIM1RST                            ((uint32_t)0x00000800U)         /* Bit[11] */


/******** Bit definition for RCC_APB1PRST register  ********/
#define RCC_APB1PRST_OPAMPRST                            ((uint32_t)0x80000000U)         /* Bit[31] */
#define RCC_APB1PRST_CANRST                              ((uint32_t)0x02000000U)         /* Bit[25] */
#define RCC_APB1PRST_I2C2RST                             ((uint32_t)0x00400000U)         /* Bit[22] */
#define RCC_APB1PRST_I2C1RST                             ((uint32_t)0x00200000U)         /* Bit[21] */
#define RCC_APB1PRST_USART3RST                           ((uint32_t)0x00040000U)         /* Bit[18] */
#define RCC_APB1PRST_USART2RST                           ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_APB1PRST_WWDGRST                             ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_APB1PRST_RTCRST                              ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_APB1PRST_COMPRST                             ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_APB1PRST_BTIM2RST                            ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_APB1PRST_BTIM1RST                            ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_APB1PRST_GTIM4RST                            ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_APB1PRST_GTIM3RST                            ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_APB1PRST_GTIM2RST                            ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_APB1PRST_GTIM1RST                            ((uint32_t)0x00000001U)         /* Bit[0] */


/******** Bit definition for RCC_AHBPCLKEN register  ********/
/* When using ADC2, both the ADC1EN and ADC2EN bits must be enabled. */
#define RCC_AHBPCLKEN_ADC2EN                             ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_AHBPCLKEN_ADC1EN                             ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_AHBPCLKEN_CRCEN                              ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_AHBPCLKEN_GPIOEN                             ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_AHBPCLKEN_DMAEN                              ((uint32_t)0x00000001U)         /* Bit[0] */


/******** Bit definition for RCC_APB2PCLKEN register  ********/
#define RCC_APB2PCLKEN_SPI2EN                            ((uint32_t)0x00080000U)         /* Bit[19] */
#define RCC_APB2PCLKEN_USART4EN                          ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_APB2PCLKEN_USART1EN                          ((uint32_t)0x00004000U)         /* Bit[14] */
#define RCC_APB2PCLKEN_ATIM2EN                           ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_APB2PCLKEN_SPI1EN                            ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_APB2PCLKEN_ATIM1EN                           ((uint32_t)0x00000800U)         /* Bit[11] */


/******** Bit definition for RCC_APB1PCLKEN register  ********/
#define RCC_APB1PCLKEN_OPAMPEN                           ((uint32_t)0x80000000U)         /* Bit[31] */
#define RCC_APB1PCLKEN_CANEN                             ((uint32_t)0x02000000U)         /* Bit[25] */
#define RCC_APB1PCLKEN_I2C2EN                            ((uint32_t)0x00400000U)         /* Bit[22] */
#define RCC_APB1PCLKEN_I2C1EN                            ((uint32_t)0x00200000U)         /* Bit[21] */
#define RCC_APB1PCLKEN_USART3EN                          ((uint32_t)0x00040000U)         /* Bit[18] */
#define RCC_APB1PCLKEN_USART2EN                          ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_APB1PCLKEN_WWDGEN                            ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_APB1PCLKEN_RTCEN                             ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_APB1PCLKEN_COMPFILTEN                        ((uint32_t)0x00000080U)         /* Bit[7] */
#define RCC_APB1PCLKEN_COMPEN                            ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_APB1PCLKEN_BTIM2EN                           ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_APB1PCLKEN_BTIM1EN                           ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_APB1PCLKEN_GTIM4EN                           ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_APB1PCLKEN_GTIM3EN                           ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_APB1PCLKEN_GTIM2EN                           ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_APB1PCLKEN_GTIM1EN                           ((uint32_t)0x00000001U)         /* Bit[0] */


/******** Bit definition for RCC_CTRLSTS register  ********/
#define RCC_CTRLSTS_LKUPRSTF                             ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_CTRLSTS_EMCGBNRSTF                           ((uint32_t)0x00000200U)         /* Bit[9] */
#define RCC_CTRLSTS_EMCGBRSTF                            ((uint32_t)0x00000100U)         /* Bit[8] */
#define RCC_CTRLSTS_GLITCHRSTF                           ((uint32_t)0x00000080U)         /* Bit[7] */
#define RCC_CTRLSTS_IWDGRSTF                             ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_CTRLSTS_SFTRSTF                              ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_CTRLSTS_WWDGRSTF                             ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_CTRLSTS_PINRSTF                              ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_CTRLSTS_RMRSTF                               ((uint32_t)0x00000001U)         /* Bit[0] */

/******** Bit definition for RCC_AHBPRST register  ********/
#define RCC_AHBPRST_ADC2RST                              ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_AHBPRST_ADC1RST                              ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_AHBPRST_GPIORST                              ((uint32_t)0x00000004U)         /* Bit[2] */

/******** Bit definition for RCC_CFG2 register  ********/
#define RCC_CFG2_ATIM1CLKSEL                             ((uint32_t)0xC0000000U)         /* Bit[31:30] */
#define RCC_CFG2_ATIM1CLKSEL_0                           ((uint32_t)0x40000000U)         /* Bit[30] */
#define RCC_CFG2_ATIM1CLKSEL_1                           ((uint32_t)0x80000000U)         /* Bit[31] */

#define RCC_CFG2_GTIM1CLKSEL                             ((uint32_t)0x20000000U)         /* Bit[29] */
#define RCC_CFG2_BTIM1CLKSEL                             ((uint32_t)0x0C000000U)         /* Bit[27:26] */
#define RCC_CFG2_BTIM1CLKSEL_0                           ((uint32_t)0x04000000U)         /* Bit[26] */
#define RCC_CFG2_BTIM1CLKSEL_1                           ((uint32_t)0x08000000U)         /* Bit[27] */

#define RCC_CFG2_RTCCLKSEL                               ((uint32_t)0x03000000U)         /* Bit[25:24] */
#define RCC_CFG2_RTCCLKSEL_0                             ((uint32_t)0x01000000U)         /* Bit[24] */
#define RCC_CFG2_RTCCLKSEL_1                             ((uint32_t)0x02000000U)         /* Bit[25] */

#define RCC_CFG2_USART1CLKSEL                            ((uint32_t)0x00C00000U)         /* Bit[23:22] */
#define RCC_CFG2_USART1CLKSEL_0                          ((uint32_t)0x00400000U)         /* Bit[22] */
#define RCC_CFG2_USART1CLKSEL_1                          ((uint32_t)0x00800000U)         /* Bit[23] */

#define RCC_CFG2_LPCLKSEL                                ((uint32_t)0x00200000U)         /* Bit[21] */
#define RCC_CFG2_USART4CLKSEL                            ((uint32_t)0x00180000U)         /* Bit[20:19] */
#define RCC_CFG2_USART4CLKSEL_0                          ((uint32_t)0x00080000U)         /* Bit[19] */
#define RCC_CFG2_USART4CLKSEL_1                          ((uint32_t)0x00100000U)         /* Bit[20] */
#define RCC_CFG2_ADC1MSEL                                ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_CFG2_I2SCLKSEL                               ((uint32_t)0x00010000U)         /* Bit[16] */

#define RCC_CFG2_ADC1MPRE                                ((uint32_t)0x0000F000U)         /* Bit[15:12] */
#define RCC_CFG2_ADC1MPRE_0                              ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_CFG2_ADC1MPRE_1                              ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_CFG2_ADC1MPRE_2                              ((uint32_t)0x00004000U)         /* Bit[14] */
#define RCC_CFG2_ADC1MPRE_3                              ((uint32_t)0x00008000U)         /* Bit[15] */

#define RCC_CFG2_ATIM2CLKSEL                             ((uint32_t)0x00000C00U)         /* Bit[11:10] */
#define RCC_CFG2_ATIM2CLKSEL_0                           ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_CFG2_ATIM2CLKSEL_1                           ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_CFG2_GTIM2CLKSEL                             ((uint32_t)0x00000200U)         /* Bit[9] */
#define RCC_CFG2_ADCSYSPRES                              ((uint32_t)0x000000F0U)         /* Bit[7:4] */
#define RCC_CFG2_ADCSYSPRES_0                            ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_CFG2_ADCSYSPRES_1                            ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_CFG2_ADCSYSPRES_2                            ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_CFG2_ADCSYSPRES_3                            ((uint32_t)0x00000080U)         /* Bit[7] */

#define RCC_CFG2_GTIM3CLKSEL                             ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_CFG2_GTIM4CLKSEL                             ((uint32_t)0x00000002U)         /* Bit[1] */


/******** Bit definition for RCC_CFG3 register  ********/
#define RCC_CFG3_ATIM1FILTCLK                            ((uint32_t)0x3E000000U)         /* Bit[29:25] */
#define RCC_CFG3_ATIM1FILTCLK_0                          ((uint32_t)0x02000000U)         /* Bit[25] */
#define RCC_CFG3_ATIM1FILTCLK_1                          ((uint32_t)0x04000000U)         /* Bit[26] */
#define RCC_CFG3_ATIM1FILTCLK_2                          ((uint32_t)0x08000000U)         /* Bit[27] */
#define RCC_CFG3_ATIM1FILTCLK_3                          ((uint32_t)0x10000000U)         /* Bit[28] */
#define RCC_CFG3_ATIM1FILTCLK_4                          ((uint32_t)0x20000000U)         /* Bit[29] */

#define RCC_CFG3_ATIM2FILTCLK                            ((uint32_t)0x01F00000U)         /* Bit[24:20] */
#define RCC_CFG3_ATIM2FILTCLK_0                          ((uint32_t)0x00100000U)         /* Bit[20] */
#define RCC_CFG3_ATIM2FILTCLK_1                          ((uint32_t)0x00200000U)         /* Bit[21] */
#define RCC_CFG3_ATIM2FILTCLK_2                          ((uint32_t)0x00400000U)         /* Bit[22] */
#define RCC_CFG3_ATIM2FILTCLK_3                          ((uint32_t)0x00800000U)         /* Bit[23] */
#define RCC_CFG3_ATIM2FILTCLK_4                          ((uint32_t)0x01000000U)         /* Bit[24] */

#define RCC_CFG3_GTIM1FILTCLK                            ((uint32_t)0x000F8000U)         /* Bit[19:15] */
#define RCC_CFG3_GTIM1FILTCLK_0                          ((uint32_t)0x00008000U)         /* Bit[15] */
#define RCC_CFG3_GTIM1FILTCLK_1                          ((uint32_t)0x00010000U)         /* Bit[16] */
#define RCC_CFG3_GTIM1FILTCLK_2                          ((uint32_t)0x00020000U)         /* Bit[17] */
#define RCC_CFG3_GTIM1FILTCLK_3                          ((uint32_t)0x00040000U)         /* Bit[18] */
#define RCC_CFG3_GTIM1FILTCLK_4                          ((uint32_t)0x00080000U)         /* Bit[19] */

#define RCC_CFG3_GTIM2FILTCLK                            ((uint32_t)0x00007C00U)         /* Bit[14:10] */
#define RCC_CFG3_GTIM2FILTCLK_0                          ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_CFG3_GTIM2FILTCLK_1                          ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_CFG3_GTIM2FILTCLK_2                          ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_CFG3_GTIM2FILTCLK_3                          ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_CFG3_GTIM2FILTCLK_4                          ((uint32_t)0x00004000U)         /* Bit[14] */

#define RCC_CFG3_GTIM3FILTCLK                            ((uint32_t)0x000003E0U)         /* Bit[9:5] */
#define RCC_CFG3_GTIM3FILTCLK_0                          ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_CFG3_GTIM3FILTCLK_1                          ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_CFG3_GTIM3FILTCLK_2                          ((uint32_t)0x00000080U)         /* Bit[7] */
#define RCC_CFG3_GTIM3FILTCLK_3                          ((uint32_t)0x00000100U)         /* Bit[8] */
#define RCC_CFG3_GTIM3FILTCLK_4                          ((uint32_t)0x00000200U)         /* Bit[9] */

#define RCC_CFG3_GTIM4FILTCLK                            ((uint32_t)0x0000001FU)         /* Bit[4:0] */
#define RCC_CFG3_GTIM4FILTCLK_0                          ((uint32_t)0x00000001U)         /* Bit[0] */
#define RCC_CFG3_GTIM4FILTCLK_1                          ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_CFG3_GTIM4FILTCLK_2                          ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_CFG3_GTIM4FILTCLK_3                          ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_CFG3_GTIM4FILTCLK_4                          ((uint32_t)0x00000010U)         /* Bit[4] */

/******** Bit definition for RCC_PLLCTRL register  ********/
#define RCC_PLLCTRL_PLLINPRES                           ((uint32_t)0x00003F00U)         /* Bit[13:8] */
#define RCC_PLLCTRL_PLLINPRES_0                         ((uint32_t)0x00000100U)         /* Bit[8] */
#define RCC_PLLCTRL_PLLINPRES_1                         ((uint32_t)0x00000200U)         /* Bit[9] */
#define RCC_PLLCTRL_PLLINPRES_2                         ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_PLLCTRL_PLLINPRES_3                         ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_PLLCTRL_PLLINPRES_4                         ((uint32_t)0x00001000U)         /* Bit[12] */
#define RCC_PLLCTRL_PLLINPRES_5                         ((uint32_t)0x00002000U)         /* Bit[13] */


/******** Bit definition for RCC_PWRCTRL register  ********/
#define RCC_PWRCTRL_UPSTEPWID                           ((uint32_t)0xFFC00000U)         /* Bit[31:22] */
#define RCC_PWRCTRL_UPSTEPWID_0                         ((uint32_t)0x00400000U)         /* Bit22 */
#define RCC_PWRCTRL_UPSTEPWID_1                         ((uint32_t)0x00800000U)         /* Bit23 */
#define RCC_PWRCTRL_UPSTEPWID_2                         ((uint32_t)0x01000000U)         /* Bit24 */
#define RCC_PWRCTRL_UPSTEPWID_3                         ((uint32_t)0x02000000U)         /* Bit25 */
#define RCC_PWRCTRL_UPSTEPWID_4                         ((uint32_t)0x04000000U)         /* Bit26 */
#define RCC_PWRCTRL_UPSTEPWID_5                         ((uint32_t)0x0800000U)          /* Bit27 */
#define RCC_PWRCTRL_UPSTEPWID_6                         ((uint32_t)0x10000000U)         /* Bit28 */
#define RCC_PWRCTRL_UPSTEPWID_7                         ((uint32_t)0x20000000U)         /* Bit29 */
#define RCC_PWRCTRL_UPSTEPWID_8                         ((uint32_t)0x40000000U)         /* Bit30 */
#define RCC_PWRCTRL_UPSTEPWID_9                         ((uint32_t)0x80000000U)         /* Bit31 */

#define RCC_PWRCTRL_DOWNSTEPWID                         ((uint32_t)0x003FF000U)         /* Bit[21:12] */
#define RCC_PWRCTRL_DOWNSTEPWID_0                       ((uint32_t)0x00001000U)         /* Bit12*/
#define RCC_PWRCTRL_DOWNSTEPWID_1                       ((uint32_t)0x00002000U)         /* Bit13*/
#define RCC_PWRCTRL_DOWNSTEPWID_2                       ((uint32_t)0x00004000U)         /* Bit14*/
#define RCC_PWRCTRL_DOWNSTEPWID_3                       ((uint32_t)0x00008000U)         /* Bit15*/
#define RCC_PWRCTRL_DOWNSTEPWID_4                       ((uint32_t)0x00010000U)         /* Bit16*/
#define RCC_PWRCTRL_DOWNSTEPWID_5                       ((uint32_t)0x00020000U)         /* Bit17*/
#define RCC_PWRCTRL_DOWNSTEPWID_6                       ((uint32_t)0x00040000U)         /* Bit18*/
#define RCC_PWRCTRL_DOWNSTEPWID_7                       ((uint32_t)0x00080000U)         /* Bit19*/
#define RCC_PWRCTRL_DOWNSTEPWID_8                       ((uint32_t)0x00100000U)         /* Bit20*/
#define RCC_PWRCTRL_DOWNSTEPWID_9                       ((uint32_t)0x00200000U)         /* Bit21*/

#define RCC_PWRCTRL_UPSTEPEN                           ((uint32_t)0x00000800U)         /* Bit[11] */
#define RCC_PWRCTRL_DOWNSTEPEN                         ((uint32_t)0x00000400U)         /* Bit[10] */
#define RCC_PWRCTRL_PSTEPSFDIV                         ((uint32_t)0x00000380U)         /* Bit[9:7] */
#define RCC_PWRCTRL_PSTEPSFDIV_0                       ((uint32_t)0x00000080U)         /* Bit7 */
#define RCC_PWRCTRL_PSTEPSFDIV_1                       ((uint32_t)0x00000100U)         /* Bit8 */
#define RCC_PWRCTRL_PSTEPSFDIV_2                       ((uint32_t)0x00000200U)         /* Bit9 */

#define RCC_PWRCTRL_PSTEPSFTEN                         ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_PWRCTRL_PSTEPST                            ((uint32_t)0x0000003CU)         /* Bit[5:2] */
#define RCC_PWRCTRL_PSTEPST_0                          ((uint32_t)0x00000004U)         /* Bit2 */
#define RCC_PWRCTRL_PSTEPST_1                          ((uint32_t)0x00000008U)         /* Bit3 */
#define RCC_PWRCTRL_PSTEPST_2                          ((uint32_t)0x00000010U)         /* Bit4 */
#define RCC_PWRCTRL_PSTEPST_3                          ((uint32_t)0x00000020U)         /* Bit5 */
#define RCC_PWRCTRL_PSTEPDNF                           ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_PWRCTRL_RMVF                               ((uint32_t)0x00000001U)         /* Bit[0] */


/******** Bit definition for RCC_CFG4 register  ********/
#define RCC_CFG4_LSEGFSEL                              ((uint32_t)0x00001E00U)         /* Bit[12:9]*/
#define RCC_CFG4_LSEGFSEL_0                            ((uint32_t)0x00000200U)         /* Bit9*/
#define RCC_CFG4_LSEGFSEL_1                            ((uint32_t)0x00000400U)         /* Bit10*/
#define RCC_CFG4_LSEGFSEL_2                            ((uint32_t)0x00000800U)         /* Bit11*/
#define RCC_CFG4_LSEGFSEL_3                            ((uint32_t)0x00001000U)         /* Bit12*/
#define RCC_CFG4_LSENIMEN                              ((uint32_t)0x00000100U)         /* Bit8*/
#define RCC_CFG4_LSEBUFFOPT                            ((uint32_t)0x000000C0U)         /* Bit[7:6]*/
#define RCC_CFG4_LSEBUFFOPT_0                          ((uint32_t)0x00000040U)         /* Bit6*/
#define RCC_CFG4_LSEBUFFOPT_1                          ((uint32_t)0x00000080U)         /* Bit7*/

#define RCC_CFG4_LSEBIASTRIM                           ((uint32_t)0x0000003CU)         /* Bit[5:2]*/
#define RCC_CFG4_LSEBIASTRIM_0                         ((uint32_t)0x00000004U)         /* Bit2*/
#define RCC_CFG4_LSEBIASTRIM_1                         ((uint32_t)0x00000008U)         /* Bit3*/
#define RCC_CFG4_LSEBIASTRIM_2                         ((uint32_t)0x00000010U)         /* Bit4*/
#define RCC_CFG4_LSEBIASTRIM_3                         ((uint32_t)0x00000020U)         /* Bit5*/

#define RCC_CFG4_LSEDRVTRIM                            ((uint32_t)0x00000003U)         /* Bit[1:0]*/
#define RCC_CFG4_LSEDRVTRIM_0                          ((uint32_t)0x00000001U)         /* Bit0*/
#define RCC_CFG4_LSEDRVTRIM_1                          ((uint32_t)0x00000002U)         /* Bit1*/


/******** Bit definition for RCC_EMCCTRL register  ********/
#define RCC_EMCCTRL_LKUPRSTEN                          ((uint32_t)0x80000000U)         /* Bit[31] */
#define RCC_EMCCTRL_GBNIEN                             ((uint32_t)0x04000000U)         /* Bit[26] */
#define RCC_EMCCTRL_GBIEN                              ((uint32_t)0x02000000U)         /* Bit[25] */
#define RCC_EMCCTRL_GLTIEN                             ((uint32_t)0x01000000U)         /* Bit[24] */
#define RCC_EMCCTRL_GBNSW                              ((uint32_t)0x00800000U)         /* Bit[23] */
#define RCC_EMCCTRL_GBNRST                             ((uint32_t)0x00400000U)         /* Bit[22] */
#define RCC_EMCCTRL_GBNDET                             ((uint32_t)0x00200000U)         /* Bit[21] */
#define RCC_EMCCTRL_GBNDETSEL                          ((uint32_t)0x00030000U)         /* Bit[17:16] */
#define RCC_EMCCTRL_GBNDETSEL_0                        ((uint32_t)0x00010000U)         /* Bit16*/
#define RCC_EMCCTRL_GBNDETSEL_1                        ((uint32_t)0x00020000U)         /* Bit17*/
#define RCC_EMCCTRL_GBSW                               ((uint32_t)0x00008000U)         /* Bit[15] */
#define RCC_EMCCTRL_GBRST                              ((uint32_t)0x00004000U)         /* Bit[14] */
#define RCC_EMCCTRL_GBDET                              ((uint32_t)0x00002000U)         /* Bit[13] */
#define RCC_EMCCTRL_GBDETSEL                           ((uint32_t)0x00000300U)         /* Bit[9:8] */
#define RCC_EMCCTRL_GBDETSEL_0                         ((uint32_t)0x00000100U)         /* Bit8*/
#define RCC_EMCCTRL_GBDETSEL_1                         ((uint32_t)0x00000200U)         /* Bit9*/
#define RCC_EMCCTRL_GVSW                               ((uint32_t)0x00000080U)         /* Bit[7] */
#define RCC_EMCCTRL_GVRST                              ((uint32_t)0x00000040U)         /* Bit[6] */
#define RCC_EMCCTRL_GVDET                              ((uint32_t)0x00000020U)         /* Bit[5] */
#define RCC_EMCCTRL_GVDETSEL                           ((uint32_t)0x0000001FU)         /* Bit[4:0] */
#define RCC_EMCCTRL_GVDETSEL_0                         ((uint32_t)0x00000001U)         /* Bit0*/
#define RCC_EMCCTRL_GVDETSEL_1                         ((uint32_t)0x00000002U)         /* Bit1*/
#define RCC_EMCCTRL_GVDETSEL_2                         ((uint32_t)0x00000004U)         /* Bit2*/
#define RCC_EMCCTRL_GVDETSEL_3                         ((uint32_t)0x00000008U)         /* Bit3*/
#define RCC_EMCCTRL_GVDETSEL_4                         ((uint32_t)0x00000010U)         /* Bit4*/

/******** Bit definition for RCC_CFG5 register  ********/
#define RCC_CFG5_HSERDFDIV                             ((uint32_t)0x00000180U)         /* Bit[8:7]*/
#define RCC_CFG5_HSERDFDIV_0                           ((uint32_t)0x00000080U)         /* Bit[7]*/
#define RCC_CFG5_HSERDFDIV_1                           ((uint32_t)0x00000100U)         /* Bit[8]*/
#define RCC_CFG5_HSERDFDLY                             ((uint32_t)0x00000040U)         /* Bit6*/

#define RCC_CFG5_GPIOFCLKDIV                           ((uint32_t)0x0000003FU)         /* Bit[5:0] */
#define RCC_CFG5_GPIOFCLKDIV_0                         ((uint32_t)0x00000001U)         /* Bit[0] */
#define RCC_CFG5_GPIOFCLKDIV_1                         ((uint32_t)0x00000002U)         /* Bit[1] */
#define RCC_CFG5_GPIOFCLKDIV_2                         ((uint32_t)0x00000004U)         /* Bit[2] */
#define RCC_CFG5_GPIOFCLKDIV_3                         ((uint32_t)0x00000008U)         /* Bit[3] */
#define RCC_CFG5_GPIOFCLKDIV_4                         ((uint32_t)0x00000010U)         /* Bit[4] */
#define RCC_CFG5_GPIOFCLKDIV_5                         ((uint32_t)0x00000020U)         /* Bit[5] */




/*** SystemTick ***/

/** Bit definition for SysTick_CTRL register **/
#define SysTick_CTRL_ENABLE    ((uint32_t)0x00000001U) /* Counter enable */
#define SysTick_CTRL_TICKINT   ((uint32_t)0x00000002U) /* Counting down to 0 pends the SysTick handler */
#define SysTick_CTRL_CLKSOURCE ((uint32_t)0x00000004U) /* Clock source */
#define SysTick_CTRL_COUNTFLAG ((uint32_t)0x00010000U) /* Count Flag */

/** Bit definition for SysTick_LOAD register **/
#define SysTick_LOAD_RELOAD    ((uint32_t)0x00FFFFFFU) /* Value to load into the SysTick Current Value Register when the counter reaches 0 */
/** Bit definition for SysTick_VAL register **/
#define SysTick_VAL_CURRENT    ((uint32_t)0x00FFFFFFU) /* Current value at the time the register is accessed */

/** Bit definition for SysTick_CALIB register **/
#define SysTick_CALIB_TENMS    ((uint32_t)0x00FFFFFFU) /* Reload value to use for 10ms timing */
#define SysTick_CALIB_SKEW     ((uint32_t)0x40000000U) /* Calibration value is not exactly 10 ms */
#define SysTick_CALIB_NOREF    ((uint32_t)0x80000000U) /* The reference clock is not provided */

/*** Nested Vectored Interrupt Controller ***/

/** Bit definition for NVIC_ISER register **/
#define NVIC_ISER_SETENA    ((uint32_t)0xFFFFFFFFU) /* Interrupt set enable bits */
#define NVIC_ISER_SETENA_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ISER_SETENA_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ISER_SETENA_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ISER_SETENA_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ISER_SETENA_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ISER_SETENA_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ISER_SETENA_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ISER_SETENA_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ISER_SETENA_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ISER_SETENA_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ISER_SETENA_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ISER_SETENA_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ISER_SETENA_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ISER_SETENA_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ISER_SETENA_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ISER_SETENA_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ISER_SETENA_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ISER_SETENA_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ISER_SETENA_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ISER_SETENA_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ISER_SETENA_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ISER_SETENA_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ISER_SETENA_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ISER_SETENA_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ISER_SETENA_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ISER_SETENA_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ISER_SETENA_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ISER_SETENA_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ISER_SETENA_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ISER_SETENA_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ISER_SETENA_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ISER_SETENA_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ICER register ***/
#define NVIC_ICER_CLRENA    ((uint32_t)0xFFFFFFFFU) /* Interrupt clear-enable bits */
#define NVIC_ICER_CLRENA_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ICER_CLRENA_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ICER_CLRENA_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ICER_CLRENA_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ICER_CLRENA_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ICER_CLRENA_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ICER_CLRENA_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ICER_CLRENA_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ICER_CLRENA_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ICER_CLRENA_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ICER_CLRENA_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ICER_CLRENA_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ICER_CLRENA_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ICER_CLRENA_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ICER_CLRENA_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ICER_CLRENA_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ICER_CLRENA_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ICER_CLRENA_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ICER_CLRENA_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ICER_CLRENA_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ICER_CLRENA_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ICER_CLRENA_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ICER_CLRENA_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ICER_CLRENA_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ICER_CLRENA_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ICER_CLRENA_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ICER_CLRENA_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ICER_CLRENA_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ICER_CLRENA_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ICER_CLRENA_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ICER_CLRENA_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ICER_CLRENA_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ISPR register **/
#define NVIC_ISPR_SETPEND    ((uint32_t)0xFFFFFFFFU) /* Interrupt set-pending bits */
#define NVIC_ISPR_SETPEND_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ISPR_SETPEND_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ISPR_SETPEND_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ISPR_SETPEND_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ISPR_SETPEND_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ISPR_SETPEND_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ISPR_SETPEND_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ISPR_SETPEND_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ISPR_SETPEND_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ISPR_SETPEND_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ISPR_SETPEND_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ISPR_SETPEND_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ISPR_SETPEND_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ISPR_SETPEND_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ISPR_SETPEND_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ISPR_SETPEND_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ISPR_SETPEND_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ISPR_SETPEND_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ISPR_SETPEND_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ISPR_SETPEND_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ISPR_SETPEND_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ISPR_SETPEND_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ISPR_SETPEND_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ISPR_SETPEND_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ISPR_SETPEND_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ISPR_SETPEND_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ISPR_SETPEND_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ISPR_SETPEND_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ISPR_SETPEND_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ISPR_SETPEND_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ISPR_SETPEND_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ISPR_SETPEND_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ICPR register **/
#define NVIC_ICPR_CLRPEND    ((uint32_t)0xFFFFFFFFU) /* Interrupt clear-pending bits */
#define NVIC_ICPR_CLRPEND_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ICPR_CLRPEND_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ICPR_CLRPEND_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ICPR_CLRPEND_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ICPR_CLRPEND_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ICPR_CLRPEND_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ICPR_CLRPEND_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ICPR_CLRPEND_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ICPR_CLRPEND_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ICPR_CLRPEND_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ICPR_CLRPEND_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ICPR_CLRPEND_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ICPR_CLRPEND_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ICPR_CLRPEND_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ICPR_CLRPEND_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ICPR_CLRPEND_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ICPR_CLRPEND_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ICPR_CLRPEND_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ICPR_CLRPEND_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ICPR_CLRPEND_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ICPR_CLRPEND_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ICPR_CLRPEND_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ICPR_CLRPEND_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ICPR_CLRPEND_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ICPR_CLRPEND_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ICPR_CLRPEND_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ICPR_CLRPEND_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ICPR_CLRPEND_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ICPR_CLRPEND_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ICPR_CLRPEND_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ICPR_CLRPEND_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ICPR_CLRPEND_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_IABR register **/
#define NVIC_IABR_ACTIVE    ((uint32_t)0xFFFFFFFFU) /* Interrupt active flags */
#define NVIC_IABR_ACTIVE_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_IABR_ACTIVE_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_IABR_ACTIVE_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_IABR_ACTIVE_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_IABR_ACTIVE_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_IABR_ACTIVE_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_IABR_ACTIVE_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_IABR_ACTIVE_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_IABR_ACTIVE_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_IABR_ACTIVE_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_IABR_ACTIVE_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_IABR_ACTIVE_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_IABR_ACTIVE_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_IABR_ACTIVE_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_IABR_ACTIVE_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_IABR_ACTIVE_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_IABR_ACTIVE_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_IABR_ACTIVE_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_IABR_ACTIVE_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_IABR_ACTIVE_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_IABR_ACTIVE_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_IABR_ACTIVE_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_IABR_ACTIVE_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_IABR_ACTIVE_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_IABR_ACTIVE_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_IABR_ACTIVE_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_IABR_ACTIVE_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_IABR_ACTIVE_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_IABR_ACTIVE_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_IABR_ACTIVE_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_IABR_ACTIVE_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_IABR_ACTIVE_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_PRI0 register **/
#define NVIC_IPR0_PRI_0 ((uint32_t)0x000000FFU) /* Priority of interrupt 0 */
#define NVIC_IPR0_PRI_1 ((uint32_t)0x0000FF00U) /* Priority of interrupt 1 */
#define NVIC_IPR0_PRI_2 ((uint32_t)0x00FF0000U) /* Priority of interrupt 2 */
#define NVIC_IPR0_PRI_3 ((uint32_t)0xFF000000U) /* Priority of interrupt 3 */

/** Bit definition for NVIC_PRI1 register **/
#define NVIC_IPR1_PRI_4 ((uint32_t)0x000000FFU) /* Priority of interrupt 4 */
#define NVIC_IPR1_PRI_5 ((uint32_t)0x0000FF00U) /* Priority of interrupt 5 */
#define NVIC_IPR1_PRI_6 ((uint32_t)0x00FF0000U) /* Priority of interrupt 6 */
#define NVIC_IPR1_PRI_7 ((uint32_t)0xFF000000U) /* Priority of interrupt 7 */

/** Bit definition for NVIC_PRI2 register **/
#define NVIC_IPR2_PRI_8  ((uint32_t)0x000000FFU) /* Priority of interrupt 8 */
#define NVIC_IPR2_PRI_9  ((uint32_t)0x0000FF00U) /* Priority of interrupt 9 */
#define NVIC_IPR2_PRI_10 ((uint32_t)0x00FF0000U) /* Priority of interrupt 10 */
#define NVIC_IPR2_PRI_11 ((uint32_t)0xFF000000U) /* Priority of interrupt 11 */

/** Bit definition for NVIC_PRI3 register **/
#define NVIC_IPR3_PRI_12 ((uint32_t)0x000000FFU) /* Priority of interrupt 12 */
#define NVIC_IPR3_PRI_13 ((uint32_t)0x0000FF00U) /* Priority of interrupt 13 */
#define NVIC_IPR3_PRI_14 ((uint32_t)0x00FF0000U) /* Priority of interrupt 14 */
#define NVIC_IPR3_PRI_15 ((uint32_t)0xFF000000U) /* Priority of interrupt 15 */

/** Bit definition for NVIC_PRI4 register **/
#define NVIC_IPR4_PRI_16 ((uint32_t)0x000000FFU) /* Priority of interrupt 16 */
#define NVIC_IPR4_PRI_17 ((uint32_t)0x0000FF00U) /* Priority of interrupt 17 */
#define NVIC_IPR4_PRI_18 ((uint32_t)0x00FF0000U) /* Priority of interrupt 18 */
#define NVIC_IPR4_PRI_19 ((uint32_t)0xFF000000U) /* Priority of interrupt 19 */

/** Bit definition for NVIC_PRI5 register **/
#define NVIC_IPR5_PRI_20 ((uint32_t)0x000000FFU) /* Priority of interrupt 20 */
#define NVIC_IPR5_PRI_21 ((uint32_t)0x0000FF00U) /* Priority of interrupt 21 */
#define NVIC_IPR5_PRI_22 ((uint32_t)0x00FF0000U) /* Priority of interrupt 22 */
#define NVIC_IPR5_PRI_23 ((uint32_t)0xFF000000U) /* Priority of interrupt 23 */

/** Bit definition for NVIC_PRI6 register **/
#define NVIC_IPR6_PRI_24 ((uint32_t)0x000000FFU) /* Priority of interrupt 24 */
#define NVIC_IPR6_PRI_25 ((uint32_t)0x0000FF00U) /* Priority of interrupt 25 */
#define NVIC_IPR6_PRI_26 ((uint32_t)0x00FF0000U) /* Priority of interrupt 26 */
#define NVIC_IPR6_PRI_27 ((uint32_t)0xFF000000U) /* Priority of interrupt 27 */

/** Bit definition for NVIC_PRI7 register **/
#define NVIC_IPR7_PRI_28 ((uint32_t)0x000000FFU) /* Priority of interrupt 28 */
#define NVIC_IPR7_PRI_29 ((uint32_t)0x0000FF00U) /* Priority of interrupt 29 */
#define NVIC_IPR7_PRI_30 ((uint32_t)0x00FF0000U) /* Priority of interrupt 30 */
#define NVIC_IPR7_PRI_31 ((uint32_t)0xFF000000U) /* Priority of interrupt 31 */

/** Bit definition for SCB_CPUID register **/
#define SCB_CPUID_REVISION    ((uint32_t)0x0000000FU) /* Implementation defined revision number */
#define SCB_CPUID_PARTNO      ((uint32_t)0x0000FFF0U) /* Number of processor within family */
#define SCB_CPUID_Constant    ((uint32_t)0x000F0000U) /* Reads as 0x0F */
#define SCB_CPUID_VARIANT     ((uint32_t)0x00F00000U) /* Implementation defined variant number */
#define SCB_CPUID_IMPLEMENTER ((uint32_t)0xFF000000U) /* Implementer code. ARM is 0x41 */

/** Bit definition for SCB_ICSR register **/
#define SCB_ICSR_VECTACTIVE  ((uint32_t)0x000001FFU) /* Active INTSTS number field */
#define SCB_ICSR_RETTOBASE   ((uint32_t)0x00000800U) /* All active exceptions minus the IPSR_current_exception yields the empty set */
#define SCB_ICSR_VECTPENDING ((uint32_t)0x003FF000U) /* Pending INTSTS number field */
#define SCB_ICSR_ISRPENDING  ((uint32_t)0x00400000U) /* Interrupt pending flag */
#define SCB_ICSR_ISRPREEMPT  ((uint32_t)0x00800000U) /* It indicates that a pending interrupt becomes active in the next running cycle */
#define SCB_ICSR_PENDSTCLR   ((uint32_t)0x02000000U) /* Clear pending SysTick bit */
#define SCB_ICSR_PENDSTSET   ((uint32_t)0x04000000U) /* Set pending SysTick bit */
#define SCB_ICSR_PENDSVCLR   ((uint32_t)0x08000000U) /* Clear pending pendSV bit */
#define SCB_ICSR_PENDSVSET   ((uint32_t)0x10000000U) /* Set pending pendSV bit */
#define SCB_ICSR_NMIPENDSET  ((uint32_t)0x80000000U) /* Set pending NMI bit */

/** Bit definition for SCB_VTOR register **/
#define SCB_VTOR_TBLOFF  ((uint32_t)0x1FFFFF80U) /* Vector table base offset field */
#define SCB_VTOR_TBLBASE ((uint32_t)0x20000000U) /* Table base in code(0) or RAM(1) */

/** Bit definition for SCB_AIRCR register **/
#define SCB_AIRCR_VECTRESET     ((uint32_t)0x00000001U) /* System Reset bit */
#define SCB_AIRCR_VECTCLRACTIVE ((uint32_t)0x00000002U) /* Clear active vector bit */
#define SCB_AIRCR_SYSRESETREQ   ((uint32_t)0x00000004U) /* Requests chip control logic to generate a reset */

#define SCB_AIRCR_PRIGROUP   ((uint32_t)0x00000700U) /* PRIGROUP[2:0] bits (Priority group) */
#define SCB_AIRCR_PRIGROUP_0 ((uint32_t)0x00000100U) /* Bit 0 */
#define SCB_AIRCR_PRIGROUP_1 ((uint32_t)0x00000200U) /* Bit 1 */
#define SCB_AIRCR_PRIGROUP_2 ((uint32_t)0x00000400U) /* Bit 2  */

/** prority group configuration **/
#define SCB_AIRCR_PRIGROUP0   ((uint32_t)0x00000000U) /* Priority group=0 (7 bits of pre-emption priority, 1 bit of subpriority) */
#define SCB_AIRCR_PRIGROUP1   ((uint32_t)0x00000100U) /* Priority group=1 (6 bits of pre-emption priority, 2 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP2   ((uint32_t)0x00000200U) /* Priority group=2 (5 bits of pre-emption priority, 3 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP3   ((uint32_t)0x00000300U) /* Priority group=3 (4 bits of pre-emption priority, 4 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP4   ((uint32_t)0x00000400U) /* Priority group=4 (3 bits of pre-emption priority, 5 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP5   ((uint32_t)0x00000500U) /* Priority group=5 (2 bits of pre-emption priority, 6 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP6   ((uint32_t)0x00000600U) /* Priority group=6 (1 bit of pre-emption priority, 7 bits of subpriority) */
#define SCB_AIRCR_PRIGROUP7   ((uint32_t)0x00000700U) /* Priority group=7 (no pre-emption priority, 8 bits of subpriority) */

#define SCB_AIRCR_ENDIANESS ((uint32_t)0x00008000U) /* Data endianness bit */
#define SCB_AIRCR_VECTKEY   ((uint32_t)0xFFFF0000U) /* Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT) */

/** Bit definition for SCB_SCR register **/
#define SCB_SCR_SLEEPONEXIT ((uint8_t)0x02U) /* Sleep on exit bit */
#define SCB_SCR_SLEEPDEEP   ((uint8_t)0x04U) /* Sleep deep bit */
#define SCB_SCR_SEVONPEND   ((uint8_t)0x10U) /* Wake up from WFE */

/** Bit definition for SCB_CCR register **/
#define SCB_CCR_NONBASETHRDENA   ((uint16_t)0x0001U) /* Thread mode can be entered from any level in Handler mode by controlled return value */
#define SCB_CCR_USERSETMPEND     ((uint16_t)0x0002U) /* Enables user code to write the Software Trigger Interrupt register to trigger (pend) a     \
                          Main exception */
#define SCB_CCR_UNALIGN_TRP ((uint16_t)0x0008U) /* Trap for unaligned access */
#define SCB_CCR_DIV_0_TRP   ((uint16_t)0x0010U) /* Trap on Divide by 0 */
#define SCB_CCR_BFHFNMIGN   ((uint16_t)0x0100U) /* Handlers running at priority -1 and -2 */
#define SCB_CCR_STKALIGN    ((uint16_t)0x0200U) /* On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned */

/** Bit definition for SCB_SHPR register **/
#define SCB_SHPR_PRI_N    ((uint32_t)0x000000FFU) /* Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor */
#define SCB_SHPR_PRI_N1   ((uint32_t)0x0000FF00U) /* Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved */
#define SCB_SHPR_PRI_N2   ((uint32_t)0x00FF0000U) /* Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV */
#define SCB_SHPR_PRI_N3   ((uint32_t)0xFF000000U) /* Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick */

/** Bit definition for SCB_SHCSR register **/
#define SCB_SHCSR_MEMFAULTACT    ((uint32_t)0x00000001U) /* MemManage is active */
#define SCB_SHCSR_BUSFAULTACT    ((uint32_t)0x00000002U) /* BusFault is active */
#define SCB_SHCSR_USGFAULTACT    ((uint32_t)0x00000008U) /* UsageFault is active */
#define SCB_SHCSR_SVCALLACT      ((uint32_t)0x00000080U) /* SVCall is active */
#define SCB_SHCSR_MONITORACT     ((uint32_t)0x00000100U) /* Monitor is active */
#define SCB_SHCSR_PENDSVACT      ((uint32_t)0x00000400U) /* PendSV is active */
#define SCB_SHCSR_SYSTICKACT     ((uint32_t)0x00000800U) /* SysTick is active */
#define SCB_SHCSR_USGFAULTPENDED ((uint32_t)0x00001000U) /* Usage Fault is pended */
#define SCB_SHCSR_MEMFAULTPENDED ((uint32_t)0x00002000U) /* MemManage is pended */
#define SCB_SHCSR_BUSFAULTPENDED ((uint32_t)0x00004000U) /* Bus Fault is pended */
#define SCB_SHCSR_SVCALLPENDED   ((uint32_t)0x00008000U) /* SVCall is pended */
#define SCB_SHCSR_MEMFAULTENA    ((uint32_t)0x00010000U) /* MemManage enable */
#define SCB_SHCSR_BUSFAULTENA    ((uint32_t)0x00020000U) /* Bus Fault enable */
#define SCB_SHCSR_USGFAULTENA    ((uint32_t)0x00040000U) /* UsageFault enable */

/*** Bit definition for SCB_CFSR register ***/
/** MFSR **/
#define SCB_CFSR_IACCVIOL  ((uint32_t)0x00000001U) /* Instruction access violation */
#define SCB_CFSR_DACCVIOL  ((uint32_t)0x00000002U) /* Data access violation */
#define SCB_CFSR_MUNSTKERR ((uint32_t)0x00000008U) /* Unstacking error */
#define SCB_CFSR_MSTKERR   ((uint32_t)0x00000010U) /* Stacking error */
#define SCB_CFSR_MMARVALID ((uint32_t)0x00000080U) /* Memory Manage Address Register address valid flag */
/** BFSR **/
#define SCB_CFSR_IBUSERR     ((uint32_t)0x00000100U) /* Instruction bus error flag */
#define SCB_CFSR_PRECISERR   ((uint32_t)0x00000200U) /* Precise data bus error */
#define SCB_CFSR_IMPRECISERR ((uint32_t)0x00000400U) /* Imprecise data bus error */
#define SCB_CFSR_UNSTKERR    ((uint32_t)0x00000800U) /* Unstacking error */
#define SCB_CFSR_STKERR      ((uint32_t)0x00001000U) /* Stacking error */
#define SCB_CFSR_BFARVALID   ((uint32_t)0x00008000U) /* Bus Fault Address Register address valid flag */
/** UFSR **/
#define SCB_CFSR_UNDEFINSTR ((uint32_t)0x00010000U) /* The processor attempt to execute an undefined instruction */
#define SCB_CFSR_INVSTATE   ((uint32_t)0x00020000U) /* Invalid combination of EPSR and instruction */
#define SCB_CFSR_INVPC      ((uint32_t)0x00040000U) /* Attempt to load EXC_RETURN into pc illegally */
#define SCB_CFSR_NOCP       ((uint32_t)0x00080000U) /* Attempt to use a coprocessor instruction */
#define SCB_CFSR_UNALIGNED  ((uint32_t)0x01000000U) /* Fault occurs when there is an attempt to make an unaligned memory access */
#define SCB_CFSR_DIVBYZERO  ((uint32_t)0x02000000U) /* Fault occurs when SDIV or DIV instruction is used with a divisor of 0 */

/** Bit definition for SCB_HFSR register **/
#define SCB_HFSR_VECTTBL  ((uint32_t)0x00000002U) /* Fault occurs because of vector table read on exception processing */
#define SCB_HFSR_FORCED   ((uint32_t)0x40000000U) /* Hard Fault activated when a configurable Fault was received and cannot activate */
#define SCB_HFSR_DEBUGEVT ((uint32_t)0x80000000U) /* Fault related to debug */

/** Bit definition for SCB_DFSR register **/
#define SCB_DFSR_HALTED   ((uint8_t)0x01U) /* Halt request flag */
#define SCB_DFSR_BKPT     ((uint8_t)0x02U) /* BKPT flag */
#define SCB_DFSR_DWTTRAP  ((uint8_t)0x04U) /* Data Watchpoint and Trace (DWT) flag */
#define SCB_DFSR_VCATCH   ((uint8_t)0x08U) /* Vector catch flag */
#define SCB_DFSR_EXTERNAL ((uint8_t)0x10U) /* External debug request flag */

/** Bit definition for SCB_MMFAR register **/
#define SCB_MMFAR_ADDRESS ((uint32_t)0xFFFFFFFFU) /* Mem Manage fault address field */

/** Bit definition for SCB_BFAR register **/
#define SCB_BFAR_ADDRESS ((uint32_t)0xFFFFFFFFU) /* Bus fault address field */

/** Bit definition for SCB_afsr register **/
#define SCB_AFSR_IMPDEF ((uint32_t)0xFFFFFFFFU) /* Implementation defined */

/*** DMA Controller ***/

/******** Bit definition for DMA_INTSTS register  ********/
#define DMA_INTSTS_ERRF7                                   ((uint32_t)0x08000000U)         /* Channel 7 Transfer Error flag */
#define DMA_INTSTS_HTXF7                                   ((uint32_t)0x04000000U)         /* Channel 7 Half Transfer flag */
#define DMA_INTSTS_TXCF7                                   ((uint32_t)0x02000000U)         /* Channel 7 Transfer Complete flag */
#define DMA_INTSTS_GLBF7                                   ((uint32_t)0x01000000U)         /* Channel 7 Global interrupt flag */
#define DMA_INTSTS_ERRF6                                   ((uint32_t)0x00800000U)         /* Channel 6 Transfer Error flag */
#define DMA_INTSTS_HTXF6                                   ((uint32_t)0x00400000U)         /* Channel 6 Half Transfer flag */
#define DMA_INTSTS_TXCF6                                   ((uint32_t)0x00200000U)         /* Channel 6 Transfer Complete flag */
#define DMA_INTSTS_GLBF6                                   ((uint32_t)0x00100000U)         /* Channel 6 Global interrupt flag */
#define DMA_INTSTS_ERRF5                                   ((uint32_t)0x00080000U)         /* Channel 5 Transfer Error flag */
#define DMA_INTSTS_HTXF5                                   ((uint32_t)0x00040000U)         /* Channel 5 Half Transfer flag */
#define DMA_INTSTS_TXCF5                                   ((uint32_t)0x00020000U)         /* Channel 5 Transfer Complete flag */
#define DMA_INTSTS_GLBF5                                   ((uint32_t)0x00010000U)         /* Channel 5 Global interrupt flag */
#define DMA_INTSTS_ERRF4                                   ((uint32_t)0x00008000U)         /* Channel 4 Transfer Error flag */
#define DMA_INTSTS_HTXF4                                   ((uint32_t)0x00004000U)         /* Channel 4 Half Transfer flag */
#define DMA_INTSTS_TXCF4                                   ((uint32_t)0x00002000U)         /* Channel 4 Transfer Complete flag */
#define DMA_INTSTS_GLBF4                                   ((uint32_t)0x00001000U)         /* Channel 4 Global interrupt flag */
#define DMA_INTSTS_ERRF3                                   ((uint32_t)0x00000800U)         /* Channel 3 Transfer Error flag */
#define DMA_INTSTS_HTXF3                                   ((uint32_t)0x00000400U)         /* Channel 3 Half Transfer flag */
#define DMA_INTSTS_TXCF3                                   ((uint32_t)0x00000200U)         /* Channel 3 Transfer Complete flag */
#define DMA_INTSTS_GLBF3                                   ((uint32_t)0x00000100U)         /* Channel 3 Global interrupt flag */
#define DMA_INTSTS_ERRF2                                   ((uint32_t)0x00000080U)         /* Channel 2 Transfer Error flag */
#define DMA_INTSTS_HTXF2                                   ((uint32_t)0x00000040U)         /* Channel 2 Half Transfer flag */
#define DMA_INTSTS_TXCF2                                   ((uint32_t)0x00000020U)         /* Channel 2 Transfer Complete flag */
#define DMA_INTSTS_GLBF2                                   ((uint32_t)0x00000010U)         /* Channel 2 Global interrupt flag */
#define DMA_INTSTS_ERRF1                                   ((uint32_t)0x00000008U)         /* Channel 1 Transfer Error flag */
#define DMA_INTSTS_HTXF1                                   ((uint32_t)0x00000004U)         /* Channel 1 Half Transfer flag */
#define DMA_INTSTS_TXCF1                                   ((uint32_t)0x00000002U)         /* Channel 1 Transfer Complete flag */
#define DMA_INTSTS_GLBF1                                   ((uint32_t)0x00000001U)         /* Channel 1 Global interrupt flag */

/******** Bit definition for DMA_INTCLR register  ********/
#define DMA_INTCLR_CERRF7                                  ((uint32_t)0x08000000U)         /* Channel 7 Transfer Error clear */
#define DMA_INTCLR_CHTXF7                                  ((uint32_t)0x04000000U)         /* Channel 7 Half Transfer clear */
#define DMA_INTCLR_CTXCF7                                  ((uint32_t)0x02000000U)         /* Channel 7 Transfer Complete clear */
#define DMA_INTCLR_CGLBF7                                  ((uint32_t)0x01000000U)         /* Channel 7 Global interrupt clear */
#define DMA_INTCLR_CERRF6                                  ((uint32_t)0x00800000U)         /* Channel 6 Transfer Error clear */
#define DMA_INTCLR_CHTXF6                                  ((uint32_t)0x00400000U)         /* Channel 6 Half Transfer clear */
#define DMA_INTCLR_CTXCF6                                  ((uint32_t)0x00200000U)         /* Channel 6 Transfer Complete clear */
#define DMA_INTCLR_CGLBF6                                  ((uint32_t)0x00100000U)         /* Channel 6 Global interrupt clear */
#define DMA_INTCLR_CERRF5                                  ((uint32_t)0x00080000U)         /* Channel 5 Transfer Error clear */
#define DMA_INTCLR_CHTXF5                                  ((uint32_t)0x00040000U)         /* Channel 5 Half Transfer clear */
#define DMA_INTCLR_CTXCF5                                  ((uint32_t)0x00020000U)         /* Channel 5 Transfer Complete clear */
#define DMA_INTCLR_CGLBF5                                  ((uint32_t)0x00010000U)         /* Channel 5 Global interrupt clear */
#define DMA_INTCLR_CERRF4                                  ((uint32_t)0x00008000U)         /* Channel 4 Transfer Error clear */
#define DMA_INTCLR_CHTXF4                                  ((uint32_t)0x00004000U)         /* Channel 4 Half Transfer clear */
#define DMA_INTCLR_CTXCF4                                  ((uint32_t)0x00002000U)         /* Channel 4 Transfer Complete clear */
#define DMA_INTCLR_CGLBF4                                  ((uint32_t)0x00001000U)         /* Channel 4 Global interrupt clear */
#define DMA_INTCLR_CERRF3                                  ((uint32_t)0x00000800U)         /* Channel 3 Transfer Error clear */
#define DMA_INTCLR_CHTXF3                                  ((uint32_t)0x00000400U)         /* Channel 3 Half Transfer clear */
#define DMA_INTCLR_CTXCF3                                  ((uint32_t)0x00000200U)         /* Channel 3 Transfer Complete clear */
#define DMA_INTCLR_CGLBF3                                  ((uint32_t)0x00000100U)         /* Channel 3 Global interrupt clear */
#define DMA_INTCLR_CERRF2                                  ((uint32_t)0x00000080U)         /* Channel 2 Transfer Error clear */
#define DMA_INTCLR_CHTXF2                                  ((uint32_t)0x00000040U)         /* Channel 2 Half Transfer clear */
#define DMA_INTCLR_CTXCF2                                  ((uint32_t)0x00000020U)         /* Channel 2 Transfer Complete clear */
#define DMA_INTCLR_CGLBF2                                  ((uint32_t)0x00000010U)         /* Channel 2 Global interrupt clear */
#define DMA_INTCLR_CERRF1                                  ((uint32_t)0x00000008U)         /* Channel 1 Transfer Error clear */
#define DMA_INTCLR_CHTXF1                                  ((uint32_t)0x00000004U)         /* Channel 1 Half Transfer clear */
#define DMA_INTCLR_CTXCF1                                  ((uint32_t)0x00000002U)         /* Channel 1 Transfer Complete clear */
#define DMA_INTCLR_CGLBF1                                  ((uint32_t)0x00000001U)         /* Channel 1 Global interrupt clear */

/******** Bit definition for DMA_CHCFGx(x=1~7) register  ********/
#define DMA_CHCFG_MINC                                    ((uint32_t)0x00000080U)         /* Memory increment mode */
#define DMA_CHCFG_PINC                                    ((uint32_t)0x00000040U)         /* Peripheral increment mode */
#define DMA_CHCFG_CIRC                                    ((uint32_t)0x00000020U)         /* Circular mode */
#define DMA_CHCFG_DIR                                     ((uint32_t)0x00000010U)         /* Data transfer direction */
#define DMA_CHCFG_ERRIE                                   ((uint32_t)0x00000008U)         /* Transfer error interrupt enable */
#define DMA_CHCFG_HTXIE                                   ((uint32_t)0x00000004U)         /* Half Transfer interrupt enable */
#define DMA_CHCFG_TXCIE                                   ((uint32_t)0x00000002U)         /* Transfer complete interrupt enable */
#define DMA_CHCFG_CHEN                                    ((uint32_t)0x00000001U)         /* Channel enable*/

#define DMA_CHCFG_PSIZE                                   ((uint32_t)0x00000300U)         /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG_PSIZE_0                                 ((uint32_t)0x00000100U)         /* Bit 0*/
#define DMA_CHCFG_PSIZE_1                                 ((uint32_t)0x00000200U)         /* Bit 1*/

#define DMA_CHCFG_MSIZE                                   ((uint32_t)0x00000C00U)         /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG_MSIZE_0                                 ((uint32_t)0x00000400U)         /* Bit 0*/
#define DMA_CHCFG_MSIZE_1                                 ((uint32_t)0x00000800U)         /* Bit 1*/

#define DMA_CHCFG_PRIOLVL                                 ((uint32_t)0x00003000U)         /* PRIOLVL[1:0] bits(Channel Priority level) */
#define DMA_CHCFG_PRIOLVL_0                               ((uint32_t)0x00001000U)         /* Bit 0*/
#define DMA_CHCFG_PRIOLVL_1                               ((uint32_t)0x00002000U)         /* Bit 1*/

#define DMA_CHCFG_MEM2MEM                                 ((uint32_t)0x00004000U)         /* Memory to memory mode */

/******** Bit definition for DMA_TXNUM1 register  ********/
#define DMA_TXNUM1_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH1 number of data to transfer */

/******** Bit definition for DMA_TXNUM2 register  ********/
#define DMA_TXNUM2_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH2 number of data to transfer */

/******** Bit definition for DMA_TXNUM3 register  ********/
#define DMA_TXNUM3_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH3 number of data to transfer */

/******** Bit definition for DMA_TXNUM4 register  ********/
#define DMA_TXNUM4_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH4 number of data to transfer */

/******** Bit definition for DMA_TXNUM5 register  ********/
#define DMA_TXNUM5_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH5 number of data to transfer */

/******** Bit definition for DMA_TXNUM6 register  ********/
#define DMA_TXNUM6_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH6 number of data to transfer */

/******** Bit definition for DMA_TXNUM7 register  ********/
#define DMA_TXNUM7_NDTX                                    ((uint32_t)0x0000FFFFU)         /* CH7 number of data to transfer */

/******** Bit definition for DMA_PADDR1 register  ********/
#define DMA_PADDR1_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH1 */

/******** Bit definition for DMA_PADDR2 register  ********/
#define DMA_PADDR2_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH2 */

/******** Bit definition for DMA_PADDR3 register  ********/
#define DMA_PADDR3_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH3 */

/******** Bit definition for DMA_PADDR4 register  ********/
#define DMA_PADDR4_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH4 */

/******** Bit definition for DMA_PADDR5 register  ********/
#define DMA_PADDR5_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH5 */

/******** Bit definition for DMA_PADDR6 register  ********/
#define DMA_PADDR6_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH6 */

/******** Bit definition for DMA_PADDR7 register  ********/
#define DMA_PADDR7_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Peripheral Address of CH7 */

/******** Bit definition for DMA_MADDR1 register  ********/
#define DMA_MADDR1_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH1 */

/******** Bit definition for DMA_MADDR2 register  ********/
#define DMA_MADDR2_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH2 */

/******** Bit definition for DMA_MADDR3 register  ********/
#define DMA_MADDR3_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH3 */

/******** Bit definition for DMA_MADDR4 register  ********/
#define DMA_MADDR4_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH4 */

/******** Bit definition for DMA_MADDR5 register  ********/
#define DMA_MADDR5_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH5 */

/******** Bit definition for DMA_MADDR6 register  ********/
#define DMA_MADDR6_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH6 */

/******** Bit definition for DMA_MADDR7 register  ********/
#define DMA_MADDR7_ADDR                                    ((uint32_t)0xFFFFFFFFU)         /* Memory Address of CH7 */

/******** Bit definition for DMA_CHSELx(x=1~7) register  ********/
#define DMA_CHSEL_CH_SEL                                  ((uint32_t)0x0000003FU)         /* CH_SEL[5:0]: Channel request select */
#define DMA_CHSEL_CH_SEL_0                                ((uint32_t)0x00000001U)         /* Bit0*/
#define DMA_CHSEL_CH_SEL_1                                ((uint32_t)0x00000002U)         /* Bit1*/
#define DMA_CHSEL_CH_SEL_2                                ((uint32_t)0x00000004U)         /* Bit2*/
#define DMA_CHSEL_CH_SEL_3                                ((uint32_t)0x00000008U)         /* Bit3*/
#define DMA_CHSEL_CH_SEL_4                                ((uint32_t)0x00000010U)         /* Bit4*/
#define DMA_CHSEL_CH_SEL_5                                ((uint32_t)0x00000020U)         /* Bit5*/


/***  Analog to Digital Converter ***/

/******** Bit definition for ADC_STS register  ********/
#define ADC_STS_ALL                                       ((uint32_t)0x00001FFFU) 
#define ADC_STS_VREFRDY                                   ((uint32_t)0x00001000U)         /* Bit[12] */
#define ADC_STS_JSTR                                      ((uint32_t)0x00000800U)         /* Bit[11] */
#define ADC_STS_STR                                       ((uint32_t)0x00000400U)         /* Bit[10] */
#define ADC_STS_TCFLAG                                    ((uint32_t)0x00000200U)         /* Bit[9] */
#define ADC_STS_EOSAMP                                    ((uint32_t)0x00000100U)         /* Bit[8] */
#define ADC_STS_PDRDY                                     ((uint32_t)0x00000080U)         /* Bit[7] */
#define ADC_STS_RDY                                       ((uint32_t)0x00000040U)         /* Bit[6] */
#define ADC_STS_OVR                                       ((uint32_t)0x00000020U)         /* Bit[5] */
#define ADC_STS_AWDG                                      ((uint32_t)0x00000010U)         /* Bit[4] */
#define ADC_STS_JENDCA                                    ((uint32_t)0x00000008U)         /* Bit[3] */
#define ADC_STS_JENDC                                     ((uint32_t)0x00000004U)         /* Bit[2] */
#define ADC_STS_ENDCA                                     ((uint32_t)0x00000002U)         /* Bit[1] */
#define ADC_STS_ENDC                                      ((uint32_t)0x00000001U)         /* Bit[0] */

/******** Bit definition for ADC_CTRL1 register  ********/
#define ADC_CTRL1_SCANMD                                  ((uint32_t)0x00000001U)        /* Scan mode */
#define ADC_CTRL1_AUTOJC                                  ((uint32_t)0x00000002U)        /* Automatic injected group conversion */

#define ADC_CTRL1_DCTU                                    ((uint32_t)0x0000001CU)        /* DISC_NUM[2:0] bits (Discontinuous mode channel count) */
#define ADC_CTRL1_DCTU_0                                  ((uint32_t)0x00000004U)        /* Bit 0 */
#define ADC_CTRL1_DCTU_1                                  ((uint32_t)0x00000008U)        /* Bit 1 */
#define ADC_CTRL1_DCTU_2                                  ((uint32_t)0x00000010U)        /* Bit 2 */

#define ADC_CTRL1_DREGCH                                  ((uint32_t)0x00000020U)        /* Discontinuous mode on regular channels */
#define ADC_CTRL1_DJCH                                    ((uint32_t)0x00000040U)        /* Discontinuous mode on injected channels */

#define ADC_CTRL1_MULTMODE                                ((uint32_t)0x00000380U)        /* Mult-ADC mode selection*/
#define ADC_CTRL1_MULTMODE_0                              ((uint32_t)0x00000080U)        /* Bit 0 */
#define ADC_CTRL1_MULTMODE_1                              ((uint32_t)0x00000100U)        /* Bit 1 */
#define ADC_CTRL1_MULTMODE_2                              ((uint32_t)0x00000200U)        /* Bit 1 */

#define ADC_CTRL1_AWDGCH                                  ((uint32_t)0x0001F000U)        /* AWD1CH[4:0] bits (Analog watchdog 1 channel select bits) */
#define ADC_CTRL1_AWDGCH_0                                ((uint32_t)0x00001000U)        /* Bit 0 */
#define ADC_CTRL1_AWDGCH_1                                ((uint32_t)0x00002000U)        /* Bit 1 */
#define ADC_CTRL1_AWDGCH_2                                ((uint32_t)0x00004000U)        /* Bit 2 */
#define ADC_CTRL1_AWDGCH_3                                ((uint32_t)0x00008000U)        /* Bit 3 */
#define ADC_CTRL1_AWDGCH_4                                ((uint32_t)0x00010000U)        /* Bit 4 */

#define ADC_CTRL1_AWDERCH                                 ((uint32_t)0x00020000U)        /* Analog watchdog  enable on regular channels */
#define ADC_CTRL1_AWDEJCH                                 ((uint32_t)0x00040000U)        /* Analog watchdog  enable on injected channels */
#define ADC_CTRL1_AWDSGLEN                                ((uint32_t)0x00080000U)        /* Enable the watchdog  on a single channel in scan mode */

#define ADC_CTRL1_DELAY                                   ((uint32_t)0x00F00000U)        /* The delay time when operating on interleaved mode of dual-ADC or Tripple- ADC  */
#define ADC_CTRL1_DELAY_0                                 ((uint32_t)0x00100000U)        /* Bit 0 */
#define ADC_CTRL1_DELAY_1                                 ((uint32_t)0x00200000U)        /* Bit 1 */
#define ADC_CTRL1_DELAY_2                                 ((uint32_t)0x00400000U)        /* Bit 2 */
#define ADC_CTRL1_DELAY_3                                 ((uint32_t)0x00800000U)        /* Bit 3 */

/******** Bit definition for ADC_CTRL2 register  ********/
#define ADC_CTRL2_ON                                      ((uint32_t)0x00000001U) /* A/D Converter ON / OFF */
#define ADC_CTRL2_CTU                                     ((uint32_t)0x00000002U) /* Continuous Conversion */

#define ADC_CTRL2_EXTPRSEL                                ((uint32_t)0x00000030U) /* EXTPRSEL[1:0] bits (External trigger enable and polarity selection for regular channels) */
#define ADC_CTRL2_EXTPRSEL_0                              ((uint32_t)0x00000010U) /* Bit 0 */
#define ADC_CTRL2_EXTPRSEL_1                              ((uint32_t)0x00000020U) /* Bit 1 */

#define ADC_CTRL2_EXTPJSEL                                ((uint32_t)0x000000C0U) /* EXTPJSEL[1:0] bits (External trigger enable and polarity selection for injected channels) */
#define ADC_CTRL2_EXTPJSEL_0                              ((uint32_t)0x00000040U) /* Bit 0 */
#define ADC_CTRL2_EXTPJSEL_1                              ((uint32_t)0x00000080U) /* Bit 1 */

#define ADC_CTRL2_EXTJSEL                                 ((uint32_t)0x0001F000U) /* EXTJSEL[4:0] bits (External event select for injected group) */
#define ADC_CTRL2_EXTJSEL_0                               ((uint32_t)0x00001000U) /* Bit 0 */
#define ADC_CTRL2_EXTJSEL_1                               ((uint32_t)0x00002000U) /* Bit 1 */
#define ADC_CTRL2_EXTJSEL_2                               ((uint32_t)0x00004000U) /* Bit 2 */
#define ADC_CTRL2_EXTJSEL_3                               ((uint32_t)0x00008000U) /* Bit 3 */
#define ADC_CTRL2_EXTJSEL_4                               ((uint32_t)0x00010000U) /* Bit 4 */


#define ADC_CTRL2_EXTRSEL                                 ((uint32_t)0x003E0000U) /* EXTRSEL[4:0] bits (External event select for regular group) */
#define ADC_CTRL2_EXTRSEL_0                               ((uint32_t)0x00020000U) /* Bit 0 */
#define ADC_CTRL2_EXTRSEL_1                               ((uint32_t)0x00040000U) /* Bit 1 */
#define ADC_CTRL2_EXTRSEL_2                               ((uint32_t)0x00080000U) /* Bit 2 */
#define ADC_CTRL2_EXTRSEL_3                               ((uint32_t)0x00100000U) /* Bit 3 */
#define ADC_CTRL2_EXTRSEL_4                               ((uint32_t)0x00200000U) /* Bit 4 */

#define ADC_CTRL2_ENDMA                                   ((uint32_t)0x00400000U) /* ENDMA bits (DMA mode enable) */
#define ADC_CTRL2_ALIG                                    ((uint32_t)0x01000000U) /* Data Alignment */
#define ADC_CTRL2_TEMPEN                                  ((uint32_t)0x02000000U) /* Temperature Sensor Enable */

#define ADC_CTRL2_SWSTRJCH                                ((uint32_t)0x08000000U) /* Start Conversion of injected channels */
#define ADC_CTRL2_SWSTRRCH                                ((uint32_t)0x10000000U) /* Start Conversion of regular channels */
#define ADC_CTRL2_SWJSTOP                                 ((uint32_t)0x20000000U) /* Stop Conversion of injected channels */
#define ADC_CTRL2_SWRSTOP                                 ((uint32_t)0x40000000U) /* Stop Conversion of regular channels */

/******** Bit definition for ADC_CTRL3 register  ********/
#define ADC_CTRL3_BUFSEL                                  ((uint32_t)0x00006000U)         /* BUFSEL[1:0] bits (VREFP selection) */
#define ADC_CTRL3_BUFSEL_0                                ((uint32_t)0x00002000U)         /* Bit13*/
#define ADC_CTRL3_BUFSEL_1                                ((uint32_t)0x00004000U)         /* Bit14*/

#define ADC_CTRL3_VREFEN                                  ((uint32_t)0x00001000U)         /* Vrefint enable  */
#define ADC_CTRL3_OSRMD                                   ((uint32_t)0x00000800U)         /* Regular channels oversample mode */
#define ADC_CTRL3_OSRTRIG                                 ((uint32_t)0x00000400U)         /* Regular channels oversample triagger mode */
#define ADC_CTRL3_OSJE                                    ((uint32_t)0x00000200U)         /* injected channels oversample enable */
#define ADC_CTRL3_OSRE                                    ((uint32_t)0x00000100U)         /* Regular channels oversample enable */

#define ADC_CTRL3_OSS                                     ((uint32_t)0x000000F0U)         /* OSS[3:0] bits (Oversample data right shift)  */
#define ADC_CTRL3_OSS_0                                   ((uint32_t)0x00000010U)         /* Bit4*/
#define ADC_CTRL3_OSS_1                                   ((uint32_t)0x00000020U)         /* Bit5*/
#define ADC_CTRL3_OSS_2                                   ((uint32_t)0x00000040U)         /* Bit6*/
#define ADC_CTRL3_OSS_3                                   ((uint32_t)0x00000080U)         /* Bit7*/

#define ADC_CTRL3_OSR                                     ((uint32_t)0x0000000FU)         /* OSR[3:0] bits (ADC oversampling ratio times)  */
#define ADC_CTRL3_OSR_0                                   ((uint32_t)0x00000001U)         /* Bit0*/
#define ADC_CTRL3_OSR_1                                   ((uint32_t)0x00000002U)         /* Bit1*/
#define ADC_CTRL3_OSR_2                                   ((uint32_t)0x00000004U)         /* Bit2*/
#define ADC_CTRL3_OSR_3                                   ((uint32_t)0x00000008U)         /* Bit3*/

/******** Bit definition for ADC_SAMPT1 register  ********/
#define ADC_SAMPT1_SAMP0                                  ((uint32_t)0x0000000FU) /* SAMP0[3:0] bits (Channel 0 Sample time selection) */
#define ADC_SAMPT1_SAMP0_0                                ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_SAMPT1_SAMP0_1                                ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_SAMPT1_SAMP0_2                                ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_SAMPT1_SAMP0_3                                ((uint32_t)0x00000008U) /* Bit 3 */

#define ADC_SAMPT1_SAMP1                                  ((uint32_t)0x000000F0U) /* SAMP1[3:0] bits (Channel 1 Sample time selection) */
#define ADC_SAMPT1_SAMP1_0                                ((uint32_t)0x00000010U) /* Bit 0 */
#define ADC_SAMPT1_SAMP1_1                                ((uint32_t)0x00000020U) /* Bit 1 */
#define ADC_SAMPT1_SAMP1_2                                ((uint32_t)0x00000040U) /* Bit 2 */
#define ADC_SAMPT1_SAMP1_3                                ((uint32_t)0x00000080U) /* Bit 3 */

#define ADC_SAMPT1_SAMP2                                  ((uint32_t)0x00000F00U) /* SAMP2[3:0] bits (Channel 2 Sample time selection) */
#define ADC_SAMPT1_SAMP2_0                                ((uint32_t)0x00000100U) /* Bit 0 */
#define ADC_SAMPT1_SAMP2_1                                ((uint32_t)0x00000200U) /* Bit 1 */
#define ADC_SAMPT1_SAMP2_2                                ((uint32_t)0x00000400U) /* Bit 2 */
#define ADC_SAMPT1_SAMP2_3                                ((uint32_t)0x00000800U) /* Bit 3 */

#define ADC_SAMPT1_SAMP3                                  ((uint32_t)0x0000F000U) /* SAMP3[3:0] bits (Channel 3 Sample time selection) */
#define ADC_SAMPT1_SAMP3_0                                ((uint32_t)0x00001000U) /* Bit 0 */
#define ADC_SAMPT1_SAMP3_1                                ((uint32_t)0x00002000U) /* Bit 1 */
#define ADC_SAMPT1_SAMP3_2                                ((uint32_t)0x00004000U) /* Bit 2 */
#define ADC_SAMPT1_SAMP3_3                                ((uint32_t)0x00008000U) /* Bit 3 */

#define ADC_SAMPT1_SAMP4                                  ((uint32_t)0x000F0000U) /* SAMP4[3:0] bits (Channel 4 Sample time selection) */
#define ADC_SAMPT1_SAMP4_0                                ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_SAMPT1_SAMP4_1                                ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_SAMPT1_SAMP4_2                                ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_SAMPT1_SAMP4_3                                ((uint32_t)0x00080000U) /* Bit 3 */

#define ADC_SAMPT1_SAMP5                                  ((uint32_t)0x00F00000U) /* SAMP5[3:0] bits (Channel 5 Sample time selection) */
#define ADC_SAMPT1_SAMP5_0                                ((uint32_t)0x00100000U) /* Bit 0 */
#define ADC_SAMPT1_SAMP5_1                                ((uint32_t)0x00200000U) /* Bit 1 */
#define ADC_SAMPT1_SAMP5_2                                ((uint32_t)0x00400000U) /* Bit 2 */
#define ADC_SAMPT1_SAMP5_3                                ((uint32_t)0x00800000U) /* Bit 3 */

#define ADC_SAMPT1_SAMP6                                  ((uint32_t)0x0F000000U) /* SAMP6[3:0] bits (Channel 6 Sample time selection) */
#define ADC_SAMPT1_SAMP6_0                                ((uint32_t)0x01000000U) /* Bit 0 */
#define ADC_SAMPT1_SAMP6_1                                ((uint32_t)0x02000000U) /* Bit 1 */
#define ADC_SAMPT1_SAMP6_2                                ((uint32_t)0x04000000U) /* Bit 2 */
#define ADC_SAMPT1_SAMP6_3                                ((uint32_t)0x08000000U) /* Bit 3 */

#define ADC_SAMPT1_SAMP7                                  ((uint32_t)0xF0000000U) /* SAMP7[3:0] bits (Channel 7 Sample time selection) */
#define ADC_SAMPT1_SAMP7_0                                ((uint32_t)0x10000000U) /* Bit 0 */
#define ADC_SAMPT1_SAMP7_1                                ((uint32_t)0x20000000U) /* Bit 1 */
#define ADC_SAMPT1_SAMP7_2                                ((uint32_t)0x40000000U) /* Bit 2 */
#define ADC_SAMPT1_SAMP7_3                                ((uint32_t)0x80000000U) /* Bit 3 */

/******** Bit definition for ADC_SAMPT2 register  ********/
#define ADC_SAMPT2_SAMP8                                  ((uint32_t)0x0000000FU) /* SAMP8[3:0] bits (Channel 8 Sample time selection) */
#define ADC_SAMPT2_SAMP8_0                                ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_SAMPT2_SAMP8_1                                ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_SAMPT2_SAMP8_2                                ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_SAMPT2_SAMP8_3                                ((uint32_t)0x00000008U) /* Bit 3 */

#define ADC_SAMPT2_SAMP9                                  ((uint32_t)0x000000F0U) /* SAMP9[3:0] bits (Channel 9 Sample time selection) */
#define ADC_SAMPT2_SAMP9_0                                ((uint32_t)0x00000010U) /* Bit 0 */
#define ADC_SAMPT2_SAMP9_1                                ((uint32_t)0x00000020U) /* Bit 1 */
#define ADC_SAMPT2_SAMP9_2                                ((uint32_t)0x00000040U) /* Bit 2 */
#define ADC_SAMPT2_SAMP9_3                                ((uint32_t)0x00000080U) /* Bit 3 */

#define ADC_SAMPT2_SAMP10                                 ((uint32_t)0x00000F00U) /* SAMP10[3:0] bits (Channel 10 Sample time selection) */
#define ADC_SAMPT2_SAMP10_0                               ((uint32_t)0x00000100U) /* Bit 0 */
#define ADC_SAMPT2_SAMP10_1                               ((uint32_t)0x00000200U) /* Bit 1 */
#define ADC_SAMPT2_SAMP10_2                               ((uint32_t)0x00000400U) /* Bit 2 */
#define ADC_SAMPT2_SAMP10_3                               ((uint32_t)0x00000800U) /* Bit 3 */

#define ADC_SAMPT2_SAMP11                                 ((uint32_t)0x0000F000U) /* SAMP11[3:0] bits (Channel 11 Sample time selection) */
#define ADC_SAMPT2_SAMP11_0                               ((uint32_t)0x00001000U) /* Bit 0 */
#define ADC_SAMPT2_SAMP11_1                               ((uint32_t)0x00002000U) /* Bit 1 */
#define ADC_SAMPT2_SAMP11_2                               ((uint32_t)0x00004000U) /* Bit 2 */
#define ADC_SAMPT2_SAMP11_3                               ((uint32_t)0x00008000U) /* Bit 3 */

#define ADC_SAMPT2_SAMP12                                 ((uint32_t)0x000F0000U) /* SAMP12[3:0] bits (Channel 12 Sample time selection) */
#define ADC_SAMPT2_SAMP12_0                               ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_SAMPT2_SAMP12_1                               ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_SAMPT2_SAMP12_2                               ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_SAMPT2_SAMP12_3                               ((uint32_t)0x00080000U) /* Bit 3 */

#define ADC_SAMPT2_SAMP13                                 ((uint32_t)0x00F00000U) /* SAMP13[3:0] bits (Channel 13 Sample time selection) */
#define ADC_SAMPT2_SAMP13_0                               ((uint32_t)0x00100000U) /* Bit 0 */
#define ADC_SAMPT2_SAMP13_1                               ((uint32_t)0x00200000U) /* Bit 1 */
#define ADC_SAMPT2_SAMP13_2                               ((uint32_t)0x00400000U) /* Bit 2 */
#define ADC_SAMPT2_SAMP13_3                               ((uint32_t)0x00800000U) /* Bit 3 */

#define ADC_SAMPT2_SAMP14                                 ((uint32_t)0x0F000000U) /* SAMP14[3:0] bits (Channel 14 Sample time selection) */
#define ADC_SAMPT2_SAMP14_0                               ((uint32_t)0x01000000U) /* Bit 0 */
#define ADC_SAMPT2_SAMP14_1                               ((uint32_t)0x02000000U) /* Bit 1 */
#define ADC_SAMPT2_SAMP14_2                               ((uint32_t)0x04000000U) /* Bit 2 */
#define ADC_SAMPT2_SAMP14_3                               ((uint32_t)0x08000000U) /* Bit 3 */

#define ADC_SAMPT2_SAMP15                                 ((uint32_t)0xF0000000U) /* SAMP15[3:0] bits (Channel 15 Sample time selection) */
#define ADC_SAMPT2_SAMP15_0                               ((uint32_t)0x10000000U) /* Bit 0 */
#define ADC_SAMPT2_SAMP15_1                               ((uint32_t)0x20000000U) /* Bit 1 */
#define ADC_SAMPT2_SAMP15_2                               ((uint32_t)0x40000000U) /* Bit 2 */
#define ADC_SAMPT2_SAMP15_3                               ((uint32_t)0x80000000U) /* Bit 3 */

/******************  Bit definition for ADC_SAMPT3 register  *******************/
#define ADC_SAMPT3_SAMP16                                 ((uint32_t)0x0000000FU) /* SAMP16[3:0] bits (Channel 16 Sample time selection) */
#define ADC_SAMPT3_SAMP16_0                               ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_SAMPT3_SAMP16_1                               ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_SAMPT3_SAMP16_2                               ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_SAMPT3_SAMP16_3                               ((uint32_t)0x00000008U) /* Bit 3 */

#define ADC_SAMPT3_SAMP17                                 ((uint32_t)0x000000F0U) /* SAMP17[3:0] bits (Channel 17 Sample time selection) */
#define ADC_SAMPT3_SAMP17_0                               ((uint32_t)0x00000010U) /* Bit 0 */
#define ADC_SAMPT3_SAMP17_1                               ((uint32_t)0x00000020U) /* Bit 1 */
#define ADC_SAMPT3_SAMP17_2                               ((uint32_t)0x00000040U) /* Bit 2 */
#define ADC_SAMPT3_SAMP17_3                               ((uint32_t)0x00000080U) /* Bit 3 */

#define ADC_SAMPT3_SAMP18                                 ((uint32_t)0x00000F00U) /* SAMP18[3:0] bits (Channel 18 Sample time selection) */
#define ADC_SAMPT3_SAMP18_0                               ((uint32_t)0x00000100U) /* Bit 0 */
#define ADC_SAMPT3_SAMP18_1                               ((uint32_t)0x00000200U) /* Bit 1 */
#define ADC_SAMPT3_SAMP18_2                               ((uint32_t)0x00000400U) /* Bit 2 */
#define ADC_SAMPT3_SAMP18_3                               ((uint32_t)0x00000800U) /* Bit 3 */

/******** Bit definition for ADC_INTEN register  ********/
#define ADC_INTEN_EOSAMPIEN                               ((uint32_t)0x00000100U)         /* End of Sampling interrupt enable  */
#define ADC_INTEN_PDRDYIEN                                ((uint32_t)0x00000080U)         /* ADC power down ready interrupt enable  */
#define ADC_INTEN_RDYIEN                                  ((uint32_t)0x00000040U)         /* ADC power up ready interrupt enable */
#define ADC_INTEN_OVRIEN                                  ((uint32_t)0x00000020U)         /* Overrun interrupt enable  */
#define ADC_INTEN_AWDIEN                                  ((uint32_t)0x00000010U)         /* Analog watchdog interrupt enable */
#define ADC_INTEN_JENDCAIEN                               ((uint32_t)0x00000008U)         /* Any injected channel end of conversion interrupt enable */
#define ADC_INTEN_JENDCIEN                                ((uint32_t)0x00000004U)         /* Injected channel end of conversion interrupt enable */
#define ADC_INTEN_ENDCAIEN                                ((uint32_t)0x00000002U)         /* Any end of conversion interrupt enable */
#define ADC_INTEN_ENDCIEN                                 ((uint32_t)0x00000001U)         /* End of conversion interrupt enable */

/******************  Bit definition for ADC_OFFSET1 register  *******************/
#define ADC_OFFSET1_OFFSCH1DAT                            ((uint32_t)0x00000FFFU) /* ADC offset number 1 offset date */
#define ADC_OFFSET1_OFFSCH1DIR                            ((uint32_t)0x01000000U) /* ADC offset number 1 positive */
#define ADC_OFFSET1_OFFSCH1SATEN                          ((uint32_t)0x02000000U) /* ADC offset number 1 saturation enable */

#define ADC_OFFSET1_OFFSCH1CH                             ((uint32_t)0x7C000000U) /* OFFSCH1CH[4:0] bits (ADC offset number 1 channel selection) */
#define ADC_OFFSET1_OFFSCH1CH_0                           ((uint32_t)0x04000000U) /* Bit 0 */
#define ADC_OFFSET1_OFFSCH1CH_1                           ((uint32_t)0x08000000U) /* Bit 1 */
#define ADC_OFFSET1_OFFSCH1CH_2                           ((uint32_t)0x10000000U) /* Bit 2 */
#define ADC_OFFSET1_OFFSCH1CH_3                           ((uint32_t)0x20000000U) /* Bit 3 */
#define ADC_OFFSET1_OFFSCH1CH_4                           ((uint32_t)0x40000000U) /* Bit 4 */

#define ADC_OFFSET1_OFFSCH1EN                             ((uint32_t)0x80000000U) /* ADC offset number 1 offset enable */
/******************  Bit definition for ADC_OFFSET2 register  *******************/
#define ADC_OFFSET2_OFFSCH2DAT                            ((uint32_t)0x00000FFFU) /* ADC offset number 2 offset date */
#define ADC_OFFSET2_OFFSCH2DIR                            ((uint32_t)0x01000000U) /* ADC offset number 2 positive */
#define ADC_OFFSET2_OFFSCH2SATEN                          ((uint32_t)0x02000000U) /* ADC offset number 2 saturation enable */

#define ADC_OFFSET2_OFFSCH2CH                             ((uint32_t)0x7C000000U) /* OFFSCH2CH[4:0] bits (ADC offset number 2 channel selection) */
#define ADC_OFFSET2_OFFSCH2CH_0                           ((uint32_t)0x04000000U) /* Bit 0 */
#define ADC_OFFSET2_OFFSCH2CH_1                           ((uint32_t)0x08000000U) /* Bit 1 */
#define ADC_OFFSET2_OFFSCH2CH_2                           ((uint32_t)0x10000000U) /* Bit 2 */
#define ADC_OFFSET2_OFFSCH2CH_3                           ((uint32_t)0x20000000U) /* Bit 3 */
#define ADC_OFFSET2_OFFSCH2CH_4                           ((uint32_t)0x40000000U) /* Bit 4 */

#define ADC_OFFSET2_OFFSCH2EN                             ((uint32_t)0x80000000U) /* ADC offset number 2 offset enable */
/******************  Bit definition for ADC_OFFSET3 register  *******************/
#define ADC_OFFSET3_OFFSCH3DAT                            ((uint32_t)0x00000FFFU) /* ADC offset number 3 offset date */
#define ADC_OFFSET3_OFFSCH3DIR                            ((uint32_t)0x01000000U) /* ADC offset number 3 positive */
#define ADC_OFFSET3_OFFSCH3SATEN                          ((uint32_t)0x02000000U) /* ADC offset number 3 saturation enable */

#define ADC_OFFSET3_OFFSCH3CH                             ((uint32_t)0x7C000000U) /* OFFSCH3CH[4:0] bits (ADC offset number 3 channel selection) */
#define ADC_OFFSET3_OFFSCH3CH_0                           ((uint32_t)0x04000000U) /* Bit 0 */
#define ADC_OFFSET3_OFFSCH3CH_1                           ((uint32_t)0x08000000U) /* Bit 1 */
#define ADC_OFFSET3_OFFSCH3CH_2                           ((uint32_t)0x10000000U) /* Bit 2 */
#define ADC_OFFSET3_OFFSCH3CH_3                           ((uint32_t)0x20000000U) /* Bit 3 */
#define ADC_OFFSET3_OFFSCH3CH_4                           ((uint32_t)0x40000000U) /* Bit 4 */

#define ADC_OFFSET3_OFFSCH3EN                             ((uint32_t)0x80000000U) /* ADC offset number 3 offset enable */

/******************  Bit definition for ADC_OFFSET4 register  *******************/
#define ADC_OFFSET4_OFFSCH4DAT                            ((uint32_t)0x00000FFFU) /* ADC offset number 4 offset date */
#define ADC_OFFSET4_OFFSCH4DIR                            ((uint32_t)0x01000000U) /* ADC offset number 4 positive */
#define ADC_OFFSET4_OFFSCH4SATEN                          ((uint32_t)0x02000000U) /* ADC offset number 4 saturation enable */

#define ADC_OFFSET4_OFFSCH4CH                             ((uint32_t)0x7C000000U) /* OFFSCH4CH[4:0] bits (ADC offset number 4 channel selection) */
#define ADC_OFFSET4_OFFSCH4CH_0                           ((uint32_t)0x04000000U) /* Bit 0 */
#define ADC_OFFSET4_OFFSCH4CH_1                           ((uint32_t)0x08000000U) /* Bit 1 */
#define ADC_OFFSET4_OFFSCH4CH_2                           ((uint32_t)0x10000000U) /* Bit 2 */
#define ADC_OFFSET4_OFFSCH4CH_3                           ((uint32_t)0x20000000U) /* Bit 3 */
#define ADC_OFFSET4_OFFSCH4CH_4                           ((uint32_t)0x40000000U) /* Bit 4 */

#define ADC_OFFSET4_OFFSCH4EN                             ((uint32_t)0x80000000U) /* ADC offset number 4 offset enable */

/******** Bit definition for ADC_AWDHIGH register  ********/
#define ADC_AWDHIGH_HTH                                   ((uint32_t)0x00000FFFU) /* Analog watchdog high threshold */

/******** Bit definition for ADC_AWDLOW register  ********/
#define ADC_AWDLOW_LTH                                    ((uint32_t)0x00000FFFU) /* Analog watchdog low threshold */

/******** Bit definition for ADC_RSEQ1 register  ********/
#define ADC_RSEQ1_SEQ1                                    ((uint32_t)0x0000001FU) /* SEQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_RSEQ1_SEQ1_0                                  ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_RSEQ1_SEQ1_1                                  ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_RSEQ1_SEQ1_2                                  ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_RSEQ1_SEQ1_3                                  ((uint32_t)0x00000008U) /* Bit 3 */
#define ADC_RSEQ1_SEQ1_4                                  ((uint32_t)0x00000010U) /* Bit 4 */

#define ADC_RSEQ1_SEQ2                                    ((uint32_t)0x000003E0U) /* SEQ2[4:0] bits (2nd conversion in regular sequence) */
#define ADC_RSEQ1_SEQ2_0                                  ((uint32_t)0x00000020U) /* Bit 0 */
#define ADC_RSEQ1_SEQ2_1                                  ((uint32_t)0x00000040U) /* Bit 1 */
#define ADC_RSEQ1_SEQ2_2                                  ((uint32_t)0x00000080U) /* Bit 2 */
#define ADC_RSEQ1_SEQ2_3                                  ((uint32_t)0x00000100U) /* Bit 3 */
#define ADC_RSEQ1_SEQ2_4                                  ((uint32_t)0x00000200U) /* Bit 4 */

#define ADC_RSEQ1_SEQ3                                    ((uint32_t)0x00007C00U) /* SEQ3[4:0] bits (3rd conversion in regular sequence) */
#define ADC_RSEQ1_SEQ3_0                                  ((uint32_t)0x00000400U) /* Bit 0 */
#define ADC_RSEQ1_SEQ3_1                                  ((uint32_t)0x00000800U) /* Bit 1 */
#define ADC_RSEQ1_SEQ3_2                                  ((uint32_t)0x00001000U) /* Bit 2 */
#define ADC_RSEQ1_SEQ3_3                                  ((uint32_t)0x00002000U) /* Bit 3 */
#define ADC_RSEQ1_SEQ3_4                                  ((uint32_t)0x00004000U) /* Bit 4 */

#define ADC_RSEQ1_SEQ4                                    ((uint32_t)0x000F8000U) /* SEQ4[4:0] bits (4th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ4_0                                  ((uint32_t)0x00008000U) /* Bit 0 */
#define ADC_RSEQ1_SEQ4_1                                  ((uint32_t)0x00010000U) /* Bit 1 */
#define ADC_RSEQ1_SEQ4_2                                  ((uint32_t)0x00020000U) /* Bit 2 */
#define ADC_RSEQ1_SEQ4_3                                  ((uint32_t)0x00040000U) /* Bit 3 */
#define ADC_RSEQ1_SEQ4_4                                  ((uint32_t)0x00080000U) /* Bit 4 */

#define ADC_RSEQ1_SEQ5                                    ((uint32_t)0x01F00000U) /* SEQ5[4:0] bits (5th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ5_0                                  ((uint32_t)0x00100000U) /* Bit 0 */
#define ADC_RSEQ1_SEQ5_1                                  ((uint32_t)0x00200000U) /* Bit 1 */
#define ADC_RSEQ1_SEQ5_2                                  ((uint32_t)0x00400000U) /* Bit 2 */
#define ADC_RSEQ1_SEQ5_3                                  ((uint32_t)0x00800000U) /* Bit 3 */
#define ADC_RSEQ1_SEQ5_4                                  ((uint32_t)0x01000000U) /* Bit 4 */

#define ADC_RSEQ1_SEQ6                                    ((uint32_t)0x3E000000U) /* SEQ6[4:0] bits (6th conversion in regular sequence) */
#define ADC_RSEQ1_SEQ6_0                                  ((uint32_t)0x02000000U) /* Bit 0 */
#define ADC_RSEQ1_SEQ6_1                                  ((uint32_t)0x04000000U) /* Bit 1 */
#define ADC_RSEQ1_SEQ6_2                                  ((uint32_t)0x08000000U) /* Bit 2 */
#define ADC_RSEQ1_SEQ6_3                                  ((uint32_t)0x10000000U) /* Bit 3 */
#define ADC_RSEQ1_SEQ6_4                                  ((uint32_t)0x20000000U) /* Bit 4 */

/*******************  Bit definition for ADC_RSEQ2 register  *******************/
#define ADC_RSEQ2_SEQ7                                    ((uint32_t)0x0000001FU) /* SEQ7[4:0] bits (7th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ7_0                                  ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_RSEQ2_SEQ7_1                                  ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_RSEQ2_SEQ7_2                                  ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_RSEQ2_SEQ7_3                                  ((uint32_t)0x00000008U) /* Bit 3 */
#define ADC_RSEQ2_SEQ7_4                                  ((uint32_t)0x00000010U) /* Bit 4 */

#define ADC_RSEQ2_SEQ8                                    ((uint32_t)0x000003E0U) /* SEQ8[4:0] bits (8th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ8_0                                  ((uint32_t)0x00000020U) /* Bit 0 */
#define ADC_RSEQ2_SEQ8_1                                  ((uint32_t)0x00000040U) /* Bit 1 */
#define ADC_RSEQ2_SEQ8_2                                  ((uint32_t)0x00000080U) /* Bit 2 */
#define ADC_RSEQ2_SEQ8_3                                  ((uint32_t)0x00000100U) /* Bit 3 */
#define ADC_RSEQ2_SEQ8_4                                  ((uint32_t)0x00000200U) /* Bit 4 */

#define ADC_RSEQ2_SEQ9                                    ((uint32_t)0x00007C00U) /* SEQ9[4:0] bits (9th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ9_0                                  ((uint32_t)0x00000400U) /* Bit 0 */
#define ADC_RSEQ2_SEQ9_1                                  ((uint32_t)0x00000800U) /* Bit 1 */
#define ADC_RSEQ2_SEQ9_2                                  ((uint32_t)0x00001000U) /* Bit 2 */
#define ADC_RSEQ2_SEQ9_3                                  ((uint32_t)0x00002000U) /* Bit 3 */
#define ADC_RSEQ2_SEQ9_4                                  ((uint32_t)0x00004000U) /* Bit 4 */

#define ADC_RSEQ2_SEQ10                                   ((uint32_t)0x000F8000U) /* SEQ10[4:0] bits (10th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ10_0                                 ((uint32_t)0x00008000U) /* Bit 0 */
#define ADC_RSEQ2_SEQ10_1                                 ((uint32_t)0x00010000U) /* Bit 1 */
#define ADC_RSEQ2_SEQ10_2                                 ((uint32_t)0x00020000U) /* Bit 2 */
#define ADC_RSEQ2_SEQ10_3                                 ((uint32_t)0x00040000U) /* Bit 3 */
#define ADC_RSEQ2_SEQ10_4                                 ((uint32_t)0x00080000U) /* Bit 4 */

#define ADC_RSEQ2_SEQ11                                   ((uint32_t)0x01F00000U) /* SEQ11[4:0] bits (11th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ11_0                                 ((uint32_t)0x00100000U) /* Bit 0 */
#define ADC_RSEQ2_SEQ11_1                                 ((uint32_t)0x00200000U) /* Bit 1 */
#define ADC_RSEQ2_SEQ11_2                                 ((uint32_t)0x00400000U) /* Bit 2 */
#define ADC_RSEQ2_SEQ11_3                                 ((uint32_t)0x00800000U) /* Bit 3 */
#define ADC_RSEQ2_SEQ11_4                                 ((uint32_t)0x01000000U) /* Bit 4 */

#define ADC_RSEQ2_SEQ12                                   ((uint32_t)0x3E000000U) /* SEQ12[4:0] bits (12th conversion in regular sequence) */
#define ADC_RSEQ2_SEQ12_0                                 ((uint32_t)0x02000000U) /* Bit 0 */
#define ADC_RSEQ2_SEQ12_1                                 ((uint32_t)0x04000000U) /* Bit 1 */
#define ADC_RSEQ2_SEQ12_2                                 ((uint32_t)0x08000000U) /* Bit 2 */
#define ADC_RSEQ2_SEQ12_3                                 ((uint32_t)0x10000000U) /* Bit 3 */
#define ADC_RSEQ2_SEQ12_4                                 ((uint32_t)0x20000000U) /* Bit 4 */

/*******************  Bit definition for ADC_RSEQ3 register  *******************/
#define ADC_RSEQ3_SEQ13                                   ((uint32_t)0x0000001FU) /* SEQ13[4:0] bits (13th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ13_0                                 ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_RSEQ3_SEQ13_1                                 ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_RSEQ3_SEQ13_2                                 ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_RSEQ3_SEQ13_3                                 ((uint32_t)0x00000008U) /* Bit 3 */
#define ADC_RSEQ3_SEQ13_4                                 ((uint32_t)0x00000010U) /* Bit 4 */

#define ADC_RSEQ3_SEQ14                                   ((uint32_t)0x000003E0U) /* SEQ14[4:0] bits (14th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ14_0                                 ((uint32_t)0x00000020U) /* Bit 0 */
#define ADC_RSEQ3_SEQ14_1                                 ((uint32_t)0x00000040U) /* Bit 1 */
#define ADC_RSEQ3_SEQ14_2                                 ((uint32_t)0x00000080U) /* Bit 2 */
#define ADC_RSEQ3_SEQ14_3                                 ((uint32_t)0x00000100U) /* Bit 3 */
#define ADC_RSEQ3_SEQ14_4                                 ((uint32_t)0x00000200U) /* Bit 4 */

#define ADC_RSEQ3_SEQ15                                   ((uint32_t)0x00007C00U) /* SEQ15[4:0] bits (15th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ15_0                                 ((uint32_t)0x00000400U) /* Bit 0 */
#define ADC_RSEQ3_SEQ15_1                                 ((uint32_t)0x00000800U) /* Bit 1 */
#define ADC_RSEQ3_SEQ15_2                                 ((uint32_t)0x00001000U) /* Bit 2 */
#define ADC_RSEQ3_SEQ15_3                                 ((uint32_t)0x00002000U) /* Bit 3 */
#define ADC_RSEQ3_SEQ15_4                                 ((uint32_t)0x00004000U) /* Bit 4 */

#define ADC_RSEQ3_SEQ16                                   ((uint32_t)0x000F8000U) /* SEQ16[4:0] bits (16th conversion in regular sequence) */
#define ADC_RSEQ3_SEQ16_0                                 ((uint32_t)0x00008000U) /* Bit 0 */
#define ADC_RSEQ3_SEQ16_1                                 ((uint32_t)0x00010000U) /* Bit 1 */
#define ADC_RSEQ3_SEQ16_2                                 ((uint32_t)0x00020000U) /* Bit 2 */
#define ADC_RSEQ3_SEQ16_3                                 ((uint32_t)0x00040000U) /* Bit 3 */
#define ADC_RSEQ3_SEQ16_4                                 ((uint32_t)0x00080000U) /* Bit 4 */

#define ADC_RSEQ3_LEN                                     ((uint32_t)0x1E000000U) /* LEN[3:0] bits (Regular channel sequence length) */
#define ADC_RSEQ3_LEN_0                                   ((uint32_t)0x02000000U) /* Bit 0 */
#define ADC_RSEQ3_LEN_1                                   ((uint32_t)0x04000000U) /* Bit 1 */
#define ADC_RSEQ3_LEN_2                                   ((uint32_t)0x08000000U) /* Bit 2 */
#define ADC_RSEQ3_LEN_3                                   ((uint32_t)0x10000000U) /* Bit 3 */
/******** Bit definition for ADC_JSEQ register  ********/
#define ADC_JSEQ_JSEQ1                                    ((uint32_t)0x0000001FU) /* JSEQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSEQ_JSEQ1_0                                  ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_JSEQ_JSEQ1_1                                  ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_JSEQ_JSEQ1_2                                  ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_JSEQ_JSEQ1_3                                  ((uint32_t)0x00000008U) /* Bit 3 */
#define ADC_JSEQ_JSEQ1_4                                  ((uint32_t)0x00000010U) /* Bit 4 */

#define ADC_JSEQ_JSEQ2                                    ((uint32_t)0x000003E0U) /* JSEQ2[4:0] bits (2nd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ2_0                                  ((uint32_t)0x00000020U) /* Bit 0 */
#define ADC_JSEQ_JSEQ2_1                                  ((uint32_t)0x00000040U) /* Bit 1 */
#define ADC_JSEQ_JSEQ2_2                                  ((uint32_t)0x00000080U) /* Bit 2 */
#define ADC_JSEQ_JSEQ2_3                                  ((uint32_t)0x00000100U) /* Bit 3 */
#define ADC_JSEQ_JSEQ2_4                                  ((uint32_t)0x00000200U) /* Bit 4 */

#define ADC_JSEQ_JSEQ3                                    ((uint32_t)0x00007C00U) /* JSEQ3[4:0] bits (3rd conversion in injected sequence) */
#define ADC_JSEQ_JSEQ3_0                                  ((uint32_t)0x00000400U) /* Bit 0 */
#define ADC_JSEQ_JSEQ3_1                                  ((uint32_t)0x00000800U) /* Bit 1 */
#define ADC_JSEQ_JSEQ3_2                                  ((uint32_t)0x00001000U) /* Bit 2 */
#define ADC_JSEQ_JSEQ3_3                                  ((uint32_t)0x00002000U) /* Bit 3 */
#define ADC_JSEQ_JSEQ3_4                                  ((uint32_t)0x00004000U) /* Bit 4 */

#define ADC_JSEQ_JSEQ4                                    ((uint32_t)0x000F8000U) /* JSEQ4[4:0] bits (4th conversion in injected sequence) */
#define ADC_JSEQ_JSEQ4_0                                  ((uint32_t)0x00008000U) /* Bit 0 */
#define ADC_JSEQ_JSEQ4_1                                  ((uint32_t)0x00010000U) /* Bit 1 */
#define ADC_JSEQ_JSEQ4_2                                  ((uint32_t)0x00020000U) /* Bit 2 */
#define ADC_JSEQ_JSEQ4_3                                  ((uint32_t)0x00040000U) /* Bit 3 */
#define ADC_JSEQ_JSEQ4_4                                  ((uint32_t)0x00080000U) /* Bit 4 */

#define ADC_JSEQ_JLEN                                     ((uint32_t)0x06000000U) /* JLEN[1:0] bits (Injected Sequence length) */
#define ADC_JSEQ_JLEN_0                                   ((uint32_t)0x02000000U) /* Bit 0 */
#define ADC_JSEQ_JLEN_1                                   ((uint32_t)0x04000000U) /* Bit 1 */

/*******************  Bit definition for ADC_JDAT1 register  *******************/
#define ADC_JDAT1_JDAT                                    ((uint16_t)0xFFFFU) /* Injected data */

/*******************  Bit definition for ADC_JDAT2 register  *******************/
#define ADC_JDAT2_JDAT                                    ((uint16_t)0xFFFFU) /* Injected data */

/*******************  Bit definition for ADC_JDAT3 register  *******************/
#define ADC_JDAT3_JDAT                                    ((uint16_t)0xFFFFU) /* Injected data */

/*******************  Bit definition for ADC_JDAT4 register  *******************/
#define ADC_JDAT4_JDAT                                    ((uint16_t)0xFFFFU) /* Injected data */

/******** Bit definition for ADC_DAT register  ********/
#define ADC_DAT_DAT                                       ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT_ADC2DAT                                   ((uint32_t)0xFFFF0000U) /* Slave ADC data when operating on Muti-ADC */

/******** Bit definition for ADC_CTRL4 register  ********/

#define ADC_CTRL4_EXTRRSEL                                ((uint32_t)0x000F0000U) /* EXTRRSEL[3:0] bits (regular channel exti line source select) */
#define ADC_CTRL4_EXTRISEL                                ((uint32_t)0x00F00000U) /* EXTRISEL[3:0] bits (injected channel exti line source select)  */


/***  Optical Preamplifier Amplifier Peripheral Interface ***/

/*** Bit definition for OPAMP_CS register  ***/
#define OPAMPx_CS_VREFSEL                               ((uint32_t)0x00040000U) /* OPA OFFSET VREFSEL */

#define OPAMPx_CS_CALOUT                                ((uint32_t)0x00020000U) /* OPA CALOUT STS */

#define OPAMPx_CS_CALEN                                 ((uint32_t)0x00010000U) /* OPA CALEN */

#define OPAMPx_CS_VMSSEL                                ((uint32_t)0x0000C000U) /* OPA VMSSEL */
#define OPAMPx_CS_VMSSEL_0                              ((uint32_t)0x00004000U) /* Bit0 */
#define OPAMPx_CS_VMSSEL_1                              ((uint32_t)0x00008000U) /* Bit1 */
                                                                         
#define OPAMPx_CS_VPSSEL                                ((uint32_t)0x00003000U) /* OPA VPSSEL */
#define OPAMPx_CS_VPSSEL_0                              ((uint32_t)0x00001000U) /* Bit0 */
#define OPAMPx_CS_VPSSEL_1                              ((uint32_t)0x00002000U) /* Bit1 */
                                                       
#define OPAMPx_CS_VMSEL                                 ((uint32_t)0x00000C00U) /* OPA VMSEL */
#define OPAMPx_CS_VMSEL_0                               ((uint32_t)0x00000400U) /* Bit0 */
#define OPAMPx_CS_VMSEL_1                               ((uint32_t)0x00000800U) /* Bit1 */
                                                       
#define OPAMPx_CS_VPSEL                                 ((uint32_t)0x00000300U) /* OPA VPSEL */
#define OPAMPx_CS_VPSEL_0                               ((uint32_t)0x00000100U) /* Bit0 */
#define OPAMPx_CS_VPSEL_1                               ((uint32_t)0x00000200U) /* Bit1 */

#define OPAMPx_CS_GAIN                                  ((uint32_t)0x00000038U) /* OPA GAIN */
#define OPAMPx_CS_GAIN_0                                ((uint32_t)0x00000008U) /* Bit0 */
#define OPAMPx_CS_GAIN_1                                ((uint32_t)0x00000010U) /* Bit1 */
#define OPAMPx_CS_GAIN_2                                ((uint32_t)0x00000020U) /* Bit2 */
                                                       
#define OPAMPx_CS_MOD                                   ((uint32_t)0x00000006U) /* OPA Mode */
#define OPAMPx_CS_MOD_0                                 ((uint32_t)0x00000002U) /* Bit0 */
#define OPAMPx_CS_MOD_1                                 ((uint32_t)0x00000004U) /* Bit1 */

#define OPAMPx_CS_EN                                    ((uint32_t)0x00000001U) /* OPA Enable */

/***  Bit definition for OPAMP_LOCK register ***/

#define OPAMP_LOCK_OPAMP4LK                           ((uint32_t)0x00000008U)         /* Bit[3] */
#define OPAMP_LOCK_OPAMP3LK                           ((uint32_t)0x00000004U)         /* Bit[2] */
#define OPAMP_LOCK_OPAMP2LK                           ((uint32_t)0x00000002U)         /* Bit[1] */
#define OPAMP_LOCK_OPAMP1LK                           ((uint32_t)0x00000001U)         /* Bit[0] */


/***   TIM  ***/

/** Bit definition for TIM_CTRL1 register  **/
#define TIM_CTRL1_CNTEN                         ((uint32_t)0x00000001U) /* Counter enable */
#define TIM_CTRL1_DIR                           ((uint32_t)0x00000002U) /* Direction */

#define TIM_CTRL1_CAMSEL                        ((uint32_t)0x0000000CU) /* CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CTRL1_CAMSEL_0                      ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CTRL1_CAMSEL_1                      ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CTRL1_UPRS                          ((uint32_t)0x00000010U) /* Update request source */
#define TIM_CTRL1_UPDIS                         ((uint32_t)0x00000020U) /* Update disable */

#define TIM_CTRL1_CLKD                          ((uint32_t)0x000000C0U) /* CKD[1:0] bits (clock division) */
#define TIM_CTRL1_CLKD_0                        ((uint32_t)0x00000040U) /* Bit 0 */
#define TIM_CTRL1_CLKD_1                        ((uint32_t)0x00000080U) /* Bit 1 */

#define TIM_CTRL1_ONEPM                         ((uint32_t)0x00000100U) /* One pulse mode */
#define TIM_CTRL1_ARPEN                         ((uint32_t)0x00000200U) /* Auto-reload preload enable */
#define TIM_CTRL1_LBKPEN                        ((uint32_t)0x00000400U) /* LOCKUP as bkp Enable*/
#define TIM_CTRL1_PBKPEN                        ((uint32_t)0x00000800U) /* PVD as bkp Enable */

#define TIM_CTRL1_CLRSEL                        ((uint32_t)0x00002000U) /* OCxRef clear selection */

#define TIM_CTRL1_CMODE                         ((uint32_t)0x00300000U)  /* In center-aligned mode, channel 4/7/8/9 trigger mode */
#define TIM_CTRL1_CMODE_0                       ((uint32_t)0x00100000U)  /* Bit0 */
#define TIM_CTRL1_CMODE_1                       ((uint32_t)0x00200000U)  /* Bit1 */

#define TIM_CTRL1_ASMMETRIC                     ((uint32_t)0x00800000U)  /* Asynmmetric mode enable in center-aligned */
#define TIM_CTRL1_TRGLDCNTEN                    ((uint32_t)0x80000000U)  /* Trgi reset CNT enable */

/** Bit definition for TIM_CTRL2 register **/
#define TIM_CTRL2_OI1                           ((uint32_t)0x00000001U) /* Output Idle state 1 (OC1 output) */
#define TIM_CTRL2_OI1N                          ((uint32_t)0x00000002U) /* Output Idle state 1 (OC1N output) */
#define TIM_CTRL2_OI2                           ((uint32_t)0x00000004U) /* Output Idle state 2 (OC2 output) */
#define TIM_CTRL2_OI2N                          ((uint32_t)0x00000008U) /* Output Idle state 2 (OC2N output) */
#define TIM_CTRL2_OI3                           ((uint32_t)0x00000010U) /* Output Idle state 3 (OC3 output) */
#define TIM_CTRL2_OI3N                          ((uint32_t)0x00000020U) /* Output Idle state 3 (OC3N output) */
#define TIM_CTRL2_OI4                           ((uint32_t)0x00000040U) /* Output Idle state 4 (OC4 output) */
#define TIM_CTRL2_OI4N                          ((uint32_t)0x00000080U) /* Output Idle state 4 (OC4N output) */

#define TIM_CTRL2_MMSEL                         ((uint32_t)0x0000F000U) /* MMSEL[3:0] bits (Master Mode Selection) */
#define TIM_CTRL2_MMSEL_0                       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CTRL2_MMSEL_1                       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CTRL2_MMSEL_2                       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CTRL2_MMSEL_3                       ((uint32_t)0x00008000U) /* Bit 3 */

#define TIM_CTRL2_CCUSEL                        ((uint32_t)0x00010000U) /* Capture/Compare Control Update Selection */
#define TIM_CTRL2_CCDSEL                        ((uint32_t)0x00020000U) /* Capture/Compare DMA Selection */
#define TIM_CTRL2_CCPCTL                        ((uint32_t)0x00040000U) /* Capture/Compare Preloaded Control */
#define TIM_CTRL2_TI1SEL                        ((uint32_t)0x00080000U) /* TI1 Selection */

#define TIM_CTRL2_TRIG4                         ((uint32_t)0x00100000U) /* OC4REF trigger to ADC enable */
#define TIM_CTRL2_TRIG7                         ((uint32_t)0x00200000U) /* OC7REF trigger to ADC enable */
#define TIM_CTRL2_TRIG8                         ((uint32_t)0x00400000U) /* OC7REF trigger to ADC enable */
#define TIM_CTRL2_TRIG9                         ((uint32_t)0x00800000U) /* OC7REF trigger to ADC enable */

#define TIM_CTRL2_MMSEL2                        ((uint32_t)0x0F000000U) /* MMSEL2[3:0] bits (Master Mode Selection) */
#define TIM_CTRL2_MMSEL2_0                      ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_CTRL2_MMSEL2_1                      ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_CTRL2_MMSEL2_2                      ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_CTRL2_MMSEL2_3                      ((uint32_t)0x08000000U) /* Bit 3 */

/** Bit definition for TIM_STS register **/
#define TIM_STS_CC1ITF                          ((uint32_t)0x00000001U) /* Capture/Compare 1 interrupt Flag */
#define TIM_STS_CC2ITF                          ((uint32_t)0x00000002U) /* Capture/Compare 2 interrupt Flag */
#define TIM_STS_CC3ITF                          ((uint32_t)0x00000004U) /* Capture/Compare 3 interrupt Flag */
#define TIM_STS_CC4ITF                          ((uint32_t)0x00000008U) /* Capture/Compare 4 interrupt Flag */
#define TIM_STS_CC5ITF                          ((uint32_t)0x00000010U) /* Capture/Compare 5 interrupt Flag */
#define TIM_STS_CC6ITF                          ((uint32_t)0x00000020U) /* Capture/Compare 6 interrupt Flag */
#define TIM_STS_CC7ITF                          ((uint32_t)0x01000000U) /* Capture/Compare 7 interrupt Flag */
#define TIM_STS_CC8ITF                          ((uint32_t)0x02000000U) /* Capture/Compare 8 interrupt Flag */
#define TIM_STS_CC9ITF                          ((uint32_t)0x04000000U) /* Capture/Compare 9 interrupt Flag */
#define TIM_STS_C3LDCNTITF                      ((uint32_t)0x00000080U) /* Channel 3 load LVR to CNT interrupt Flag */
#define TIM_STS_CC1OCF                          ((uint32_t)0x00000100U) /* Capture/Compare 1 Overcapture Flag */
#define TIM_STS_CC2OCF                          ((uint32_t)0x00000200U) /* Capture/Compare 2 Overcapture Flag */
#define TIM_STS_CC3OCF                          ((uint32_t)0x00000400U) /* Capture/Compare 3 Overcapture Flag */
#define TIM_STS_CC4OCF                          ((uint32_t)0x00000800U) /* Capture/Compare 4 Overcapture Flag */
#define TIM_STS_UDITF                           ((uint32_t)0x00010000U) /* Update interrupt Flag */
#define TIM_STS_COMITF                          ((uint32_t)0x00020000U) /* COM interrupt Flag */
#define TIM_STS_TITF                            ((uint32_t)0x00040000U) /* Trigger interrupt Flag */
#define TIM_STS_BITF                            ((uint32_t)0x00080000U) /* Break interrupt Flag */
#define TIM_STS_SBITF                           ((uint32_t)0x00200000U) /* System break interrupt Flag */
#define TIM_STS_PBKPITF                         ((uint32_t)0x00400000U) /* PVD break interrupt Flag */
#define TIM_STS_COMPBITF                        ((uint32_t)0x00800000U) /* COMP break interrupt Flag */
#define TIM_STS_IOMBITF                         ((uint32_t)0x08000000U) /* IOM break interrupt Flag */
#define TIM_STS_LBKPITF                         ((uint32_t)0x10000000U) /* Lockup break interrupt Flag */
#define TIM_STS_CSSFBITF                        ((uint32_t)0x20000000U) /* CSS failure break interrupt Flag */

/** Bit definition for TIM_EVTGEN register **/
#define TIM_EVTGEN_CC1GN                        ((uint32_t)0x00000001U) /* Capture/Compare 1 Generation */
#define TIM_EVTGEN_CC2GN                        ((uint32_t)0x00000002U) /* Capture/Compare 2 Generation */
#define TIM_EVTGEN_CC3GN                        ((uint32_t)0x00000004U) /* Capture/Compare 3 Generation */
#define TIM_EVTGEN_CC4GN                        ((uint32_t)0x00000008U) /* Capture/Compare 4 Generation */
#define TIM_EVTGEN_UDGN                         ((uint32_t)0x00000100U) /* Update Generation */
#define TIM_EVTGEN_CCUDGN                       ((uint32_t)0x00000200U) /* Capture/Compare Control Update Generation */
#define TIM_EVTGEN_TGN                          ((uint32_t)0x00000400U) /* Trigger Generation */
#define TIM_EVTGEN_BGN                          ((uint32_t)0x00000800U) /* Break Generation */

/** Bit definition for TIM_SMCTRL register **/
#define TIM_SMCTRL_TSEL                         ((uint32_t)0x00000007U) /* TS[2:0] bits (Trigger selection) */
#define TIM_SMCTRL_TSEL_0                       ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_SMCTRL_TSEL_1                       ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_SMCTRL_TSEL_2                       ((uint32_t)0x00000004U) /* Bit 2 */

#define TIM_SMCTRL_SMSEL                        ((uint32_t)0x000000F0U) /* SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCTRL_SMSEL_0                      ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_SMCTRL_SMSEL_1                      ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_SMCTRL_SMSEL_2                      ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_SMCTRL_SMSEL_3                      ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_SMCTRL_EXTPS                        ((uint32_t)0x00000300U) /* ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCTRL_EXTPS_0                      ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_SMCTRL_EXTPS_1                      ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_SMCTRL_EXCEN                        ((uint32_t)0x00000400U) /* External clock enable */
#define TIM_SMCTRL_EXTP                         ((uint32_t)0x00000800U) /* External trigger polarity */

#define TIM_SMCTRL_EXTF                         ((uint32_t)0x0000F000U) /* ETF[3:0] bits (External trigger filter) */
#define TIM_SMCTRL_EXTF_0                       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_SMCTRL_EXTF_1                       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_SMCTRL_EXTF_2                       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_SMCTRL_EXTF_3                       ((uint32_t)0x00008000U) /* Bit 3 */

#define TIM_SMCTRL_MSMD                         ((uint32_t)0x00010000U) /* Master/slave mode */


/** Bit definition for TIM_DINTEN register **/
#define TIM_DINTEN_CC1IEN                       ((uint32_t)0x00000001U) /* Capture/Compare 1 interrupt enable */
#define TIM_DINTEN_CC2IEN                       ((uint32_t)0x00000002U) /* Capture/Compare 2 interrupt enable */
#define TIM_DINTEN_CC3IEN                       ((uint32_t)0x00000004U) /* Capture/Compare 3 interrupt enable */
#define TIM_DINTEN_CC4IEN                       ((uint32_t)0x00000008U) /* Capture/Compare 4 interrupt enable */
#define TIM_DINTEN_CC5IEN                       ((uint32_t)0x00000010U) /* Capture/Compare 5 interrupt enable */
#define TIM_DINTEN_CC6IEN                       ((uint32_t)0x00000020U) /* Capture/Compare 6 interrupt enable */
#define TIM_DINTEN_CC7IEN                       ((uint32_t)0x00000040U) /* Capture/Compare 7 interrupt enable */
#define TIM_DINTEN_CC8IEN                       ((uint32_t)0x00000080U) /* Capture/Compare 8 interrupt enable */
#define TIM_DINTEN_C3LDCNTIEN                   ((uint32_t)0x00000080U) /* Channel 3 reset CNT interrupt enable */
#define TIM_DINTEN_CC1DEN                       ((uint32_t)0x00000100U) /* Capture/Compare 1 DMA request enable */
#define TIM_DINTEN_CC2DEN                       ((uint32_t)0x00000200U) /* Capture/Compare 2 DMA request enable */
#define TIM_DINTEN_CC3DEN                       ((uint32_t)0x00000400U) /* Capture/Compare 3 DMA request enable */
#define TIM_DINTEN_CC4DEN                       ((uint32_t)0x00000800U) /* Capture/Compare 4 DMA request enable */
#define TIM_DINTEN_UIEN                         ((uint32_t)0x00010000U) /* Update interrupt enable */
#define TIM_DINTEN_TIEN                         ((uint32_t)0x00020000U) /* Trigger interrupt enable */
#define TIM_DINTEN_BIEN                         ((uint32_t)0x00040000U) /* Break interrupt enable */
#define TIM_DINTEN_UDEN                         ((uint32_t)0x00080000U) /* Update DMA request enable */
#define TIM_DINTEN_COMDEN                       ((uint32_t)0x00100000U) /* COM DMA request enable */
#define TIM_DINTEN_TDEN                         ((uint32_t)0x00200000U) /* Trigger DMA request enable */
#define TIM_DINTEN_COMIEN                       ((uint32_t)0x00400000U) /* COM interrupt enable */
#define TIM_DINTEN_CC9IEN                       ((uint32_t)0x00800000U) /* Capture/Compare 9 interrupt enable */

/** Bit definition for TIM_CCMOD1 register **/
#define TIM_CCMOD1_CC1SEL                       ((uint32_t)0x00000003U) /* CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMOD1_CC1SEL_0                     ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_CCMOD1_CC1SEL_1                     ((uint32_t)0x00000002U) /* Bit 1 */

#define TIM_CCMOD1_OC1PEN                       ((uint32_t)0x00000004U) /* Output Compare 1 Preload enable */
#define TIM_CCMOD1_OC1FEN                       ((uint32_t)0x00000008U) /* Output Compare 1 Fast enable */
#define TIM_CCMOD1_OC1CEN                       ((uint32_t)0x00000010U) /* Output Compare 1 Clear Enable */

#define TIM_CCMOD1_OC1MD                        ((uint32_t)0x000000E0U) /* OC1MD[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMOD1_OC1MD_0                      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD1_OC1MD_1                      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD1_OC1MD_2                      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD1_CC2SEL                       ((uint32_t)0x00000300U) /* CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMOD1_CC2SEL_0                     ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_CCMOD1_CC2SEL_1                     ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_CCMOD1_OC2PEN                       ((uint32_t)0x00000400U) /* Output Compare 2 Preload enable */
#define TIM_CCMOD1_OC2FEN                       ((uint32_t)0x00000800U) /* Output Compare 2 Fast enable */
#define TIM_CCMOD1_OC2CEN                       ((uint32_t)0x00001000U) /* Output Compare 2 Clear Enable */

#define TIM_CCMOD1_OC2MD                        ((uint32_t)0x0000E000U) /* OC2MD[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMOD1_OC2MD_0                      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD1_OC2MD_1                      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD1_OC2MD_2                      ((uint32_t)0x00008000U) /* Bit 2 */

#define TIM_CCMOD1_OC1MD_3                      ((uint32_t)0x00020000U) /* OC1MD3 bit (Output Compare 1 Mode) */
#define TIM_CCMOD1_OC2MD_3                      ((uint32_t)0x00040000U) /* OC2MD3 bit (Output Compare 2 Mode) */

#define TIM_CCMOD1_IC1PSC                       ((uint32_t)0x0000000CU) /* IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMOD1_IC1PSC_0                     ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CCMOD1_IC1PSC_1                     ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CCMOD1_IC1F                         ((uint32_t)0x000000F0U) /* IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMOD1_IC1F_0                       ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_CCMOD1_IC1F_1                       ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_CCMOD1_IC1F_2                       ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_CCMOD1_IC1F_3                       ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_CCMOD1_IC2PSC                       ((uint32_t)0x00000C00U) /* IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMOD1_IC2PSC_0                     ((uint32_t)0x00000400U) /* Bit 0 */
#define TIM_CCMOD1_IC2PSC_1                     ((uint32_t)0x00000800U) /* Bit 1 */

#define TIM_CCMOD1_IC2F                         ((uint32_t)0x0000F000U) /* IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMOD1_IC2F_0                       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CCMOD1_IC2F_1                       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CCMOD1_IC2F_2                       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CCMOD1_IC2F_3                       ((uint32_t)0x00008000U) /* Bit 3 */

/** Bit definition for TIM_CCMOD2 register **/
#define TIM_CCMOD2_CC3SEL                       ((uint32_t)0x00000003U) /* CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMOD2_CC3SEL_0                     ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_CCMOD2_CC3SEL_1                     ((uint32_t)0x00000002U) /* Bit 1 */

#define TIM_CCMOD2_OC3PEN                       ((uint32_t)0x00000004U) /* Output Compare 3 Preload enable */
#define TIM_CCMOD2_OC3FEN                       ((uint32_t)0x00000008U) /* Output Compare 3 Fast enable */
#define TIM_CCMOD2_OC3CEN                       ((uint32_t)0x00000010U) /* Output Compare 3 Clear Enable */

#define TIM_CCMOD2_OC3MD                        ((uint32_t)0x000000E0U) /* OC3MD[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMOD2_OC3MD_0                      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD2_OC3MD_1                      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD2_OC3MD_2                      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD2_CC4SEL                       ((uint32_t)0x00000300U) /* CC3S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMOD2_CC4SEL_0                     ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_CCMOD2_CC4SEL_1                     ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_CCMOD2_OC4PEN                       ((uint32_t)0x00000400U) /* Output Compare 4 Preload enable */
#define TIM_CCMOD2_OC4FEN                       ((uint32_t)0x00000800U) /* Output Compare 4 Fast enable */
#define TIM_CCMOD2_OC4CEN                       ((uint32_t)0x00001000U) /* Output Compare 4 Clear Enable */

#define TIM_CCMOD2_OC4MD                        ((uint32_t)0x0000E000U) /* OC4MD[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMOD2_OC4MD_0                      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD2_OC4MD_1                      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD2_OC4MD_2                      ((uint32_t)0x00008000U) /* Bit 2 */

#define TIM_CCMOD2_OC3MD_3                      ((uint32_t)0x00020000U) /* OC3MD3 bit (Output Compare 3 Mode) */
#define TIM_CCMOD2_OC4MD_3                      ((uint32_t)0x00040000U) /* OC4MD3 bit (Output Compare 4 Mode) */

#define TIM_CCMOD2_IC3PSC                       ((uint32_t)0x0000000CU) /* IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMOD2_IC3PSC_0                     ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CCMOD2_IC3PSC_1                     ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CCMOD2_IC3F                         ((uint32_t)0x000000F0U) /* IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMOD2_IC3F_0                       ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_CCMOD2_IC3F_1                       ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_CCMOD2_IC3F_2                       ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_CCMOD2_IC3F_3                       ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_CCMOD2_IC4PSC                       ((uint32_t)0x00000C00U) /* IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMOD2_IC4PSC_0                     ((uint32_t)0x00000400U) /* Bit 0 */
#define TIM_CCMOD2_IC4PSC_1                     ((uint32_t)0x00000800U) /* Bit 1 */


#define TIM_CCMOD2_IC4F                         ((uint32_t)0x0000F000U) /* IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMOD2_IC4F_0                       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CCMOD2_IC4F_1                       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CCMOD2_IC4F_2                       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CCMOD2_IC4F_3                       ((uint32_t)0x00008000U) /* Bit 3 */

/** Bit definition for TIM_CCMOD3 register **/
#define TIM_CCMOD3_OC5PEN                       ((uint32_t)0x00000004U) /* Output Compare 5 Preload enable */
#define TIM_CCMOD3_OC5FEN                       ((uint32_t)0x00000008U) /* Output Compare 5 Fast enable */
#define TIM_CCMOD3_OC5CEN                       ((uint32_t)0x00000010U) /* Output Compare 5 Clear Enable */

#define TIM_CCMOD3_OC5MD                        ((uint32_t)0x000000E0U) /* OC5M[2:0] bits (Output Compare 5 Mode) */
#define TIM_CCMOD3_OC5MD_0                      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD3_OC5MD_1                      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD3_OC5MD_2                      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD3_OC6PEN                       ((uint32_t)0x00000400U) /* Output Compare 6 Preload enable */
#define TIM_CCMOD3_OC6FEN                       ((uint32_t)0x00000800U) /* Output Compare 6 Fast enable */
#define TIM_CCMOD3_OC6CEN                       ((uint32_t)0x00001000U) /* Output Compare 6 Clear Enable */

#define TIM_CCMOD3_OC6MD                        ((uint32_t)0x0000E000U) /* OC6M[2:0] bits (Output Compare 6 Mode) */
#define TIM_CCMOD3_OC6MD_0                      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD3_OC6MD_1                      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD3_OC6MD_2                      ((uint32_t)0x00008000U) /* Bit 2 */

#define TIM_CCMOD3_OC7PEN                       ((uint32_t)0x00010000U) /* Output Compare 7 Preload enable */
#define TIM_CCMOD3_OC8PEN                       ((uint32_t)0x00100000U) /* Output Compare 8 Preload enable */
#define TIM_CCMOD3_OC9PEN                       ((uint32_t)0x01000000U) /* Output Compare 9 Preload enable */

/** Bit definition for TIM_CCEN register **/
#define TIM_CCEN_CC1NEN                         ((uint32_t)0x00000001U) /* Capture/Compare 1 Complementary output enable */
#define TIM_CCEN_CC1NP                          ((uint32_t)0x00000002U) /* Capture/Compare 1 Complementary output Polarity */
#define TIM_CCEN_CC1EN                          ((uint32_t)0x00000004U) /* Capture/Compare 1 output enable */
#define TIM_CCEN_CC1P                           ((uint32_t)0x00000008U) /* Capture/Compare 1 output Polarity */
#define TIM_CCEN_CC2NEN                         ((uint32_t)0x00000010U) /* Capture/Compare 2 Complementary output enable */
#define TIM_CCEN_CC2NP                          ((uint32_t)0x00000020U) /* Capture/Compare 2 Complementary output Polarity */
#define TIM_CCEN_CC2EN                          ((uint32_t)0x00000040U) /* Capture/Compare 2 output enable */
#define TIM_CCEN_CC2P                           ((uint32_t)0x00000080U) /* Capture/Compare 2 output Polarity */
#define TIM_CCEN_CC3NEN                         ((uint32_t)0x00000100U) /* Capture/Compare 3 Complementary output enable */
#define TIM_CCEN_CC3NP                          ((uint32_t)0x00000200U) /* Capture/Compare 3 Complementary output Polarity */
#define TIM_CCEN_CC3EN                          ((uint32_t)0x00000400U) /* Capture/Compare 3 output enable */
#define TIM_CCEN_CC3P                           ((uint32_t)0x00000800U) /* Capture/Compare 3 output Polarity */
#define TIM_CCEN_CC4NEN                         ((uint32_t)0x00001000U) /* Capture/Compare 4 Complementary output enable */
#define TIM_CCEN_CC4NP                          ((uint32_t)0x00002000U) /* Capture/Compare 4 Complementary output Polarity */
#define TIM_CCEN_CC4EN                          ((uint32_t)0x00004000U) /* Capture/Compare 4 output enable */
#define TIM_CCEN_CC4P                           ((uint32_t)0x00008000U) /* Capture/Compare 4 output Polarity */
#define TIM_CCEN_CC5EN                          ((uint32_t)0x00040000U) /* Capture/Compare 5 output enable */
#define TIM_CCEN_CC5P                           ((uint32_t)0x00080000U) /* Capture/Compare 5 output Polarity */
#define TIM_CCEN_CC6EN                          ((uint32_t)0x00400000U) /* Capture/Compare 6 output enable */
#define TIM_CCEN_CC6P                           ((uint32_t)0x00800000U) /* Capture/Compare 6 output Polarity */

/** Bit definition for TIM_CCDAT1 register **/
#define TIM_CCDAT1_CCDAT1                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 1 Value */
#define TIM_CCDAT1_CCDDAT1                      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 1 down-counting Value */
#define TIM_CCDAT1                              ((uint32_t)0xFFFFFFFFU)  /* Capture/Compare 1 Value */

/** Bit definition for TIM_CCDAT2 register **/
#define TIM_CCDAT2_CCDAT2                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 2 Value */
#define TIM_CCDAT2_CCDDAT2                      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 2 down-counting Value */
#define TIM_CCDAT2                              ((uint32_t)0xFFFFFFFFU)  /* Capture/Compare 2 Value */

/** Bit definition for TIM_CCDAT3 register **/
#define TIM_CCDAT3_CCDAT3                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 3 Value */
#define TIM_CCDAT3_CCDDAT3                      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 3 down-counting Value */
#define TIM_CCDAT3                              ((uint32_t)0xFFFFFFFFU)  /* Capture/Compare 3 Value */

/** Bit definition for TIM_CCDAT4 register **/
#define TIM_CCDAT4_CCDAT4                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 4 Value */
#define TIM_CCDAT4_CCDDAT4                      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 4 down-counting Value */
#define TIM_CCDAT4                              ((uint32_t)0xFFFFFFFFU)  /* Capture/Compare 4 Value */

/** Bit definition for TIM_CCDAT5 register **/
#define TIM_CCDAT5_CCDAT5                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 5 Value */

/** Bit definition for TIM_CCDAT6 register **/
#define TIM_CCDAT6_CCDAT6                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 6 Value */

/** Bit definition for TIM_PSC register **/
#define TIM_PSC_PSC                             ((uint32_t)0x0000FFFFU)  /* Prescaler Value */

/** Bit definition for TIM_AR register **/
#define TIM_AR_AR                               ((uint32_t)0xFFFFFFFFU)  /* actual auto-reload Value */

/** Bit definition for TIM_CNT register **/
#define TIM_CNT_CNT                             ((uint32_t)0xFFFFFFFFU)  /* Counter Value */

/** Bit definition for TIM_REPCNT register **/
#define TIM_REPCNT_REPCNT                       ((uint32_t)0x000000FFU) /* Repetition Counter Value */

/** Bit definition for TIM_BKDT register **/
#define TIM_BKDT_DTGN                           ((uint32_t)0x000000FFU) /* DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BKDT_DTGN_0                         ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_BKDT_DTGN_1                         ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_BKDT_DTGN_2                         ((uint32_t)0x00000004U) /* Bit 2 */
#define TIM_BKDT_DTGN_3                         ((uint32_t)0x00000008U) /* Bit 3 */
#define TIM_BKDT_DTGN_4                         ((uint32_t)0x00000010U) /* Bit 4 */
#define TIM_BKDT_DTGN_5                         ((uint32_t)0x00000020U) /* Bit 5 */
#define TIM_BKDT_DTGN_6                         ((uint32_t)0x00000040U) /* Bit 6 */
#define TIM_BKDT_DTGN_7                         ((uint32_t)0x00000080U) /* Bit 7 */

#define TIM_BKDT_MOEN                           ((uint32_t)0x00000100U) /* Main Output enable */
#define TIM_BKDT_AOEN                           ((uint32_t)0x00000200U) /* Automatic Output enable */
#define TIM_BKDT_BKP                            ((uint32_t)0x00000400U) /* Break Polarity */
#define TIM_BKDT_BKEN                           ((uint32_t)0x00000800U) /* Break enable */
#define TIM_BKDT_OSSI                           ((uint32_t)0x00001000U) /* Off-State Selection for Idle mode */
#define TIM_BKDT_OSSR                           ((uint32_t)0x00002000U) /* Off-State Selection for Run mode */

#define TIM_BKDT_LCKCFG                         ((uint32_t)0x0000C000U) /* LOCK[1:0] bits (Lock Configuration) */
#define TIM_BKDT_LCKCFG_0                       ((uint32_t)0x00004000U) /* Bit 0 */
#define TIM_BKDT_LCKCFG_1                       ((uint32_t)0x00008000U) /* Bit 1 */

#define TIM_BKDT_BRKDSRM                        ((uint32_t)0x00040000U) /* Break disarm */
#define TIM_BKDT_BRKBID                         ((uint32_t)0x00100000U) /* Break bidirectional enable */

/** Bit definition for TIM_CCDAT7 register **/
#define TIM_CCDAT7_CCDAT7                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 7 Value */

/** Bit definition for TIM_CCDAT8 register **/
#define TIM_CCDAT8_CCDAT8                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 8 Value */

/** Bit definition for TIM_CCDAT9 register **/
#define TIM_CCDAT9_CCDAT9                       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 9 Value */

/** Bit definition for TIM_BKFR register **/     
#define TIM_BKFR_THRESH                         ((uint32_t)0x3F000000U) /* Break1 filter threshold */
#define TIM_BKFR_THRESH_0                       ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_BKFR_THRESH_1                       ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_BKFR_THRESH_2                       ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_BKFR_THRESH_3                       ((uint32_t)0x08000000U) /* Bit 3 */
#define TIM_BKFR_THRESH_4                       ((uint32_t)0x10000000U) /* Bit 4 */
#define TIM_BKFR_THRESH_5                       ((uint32_t)0x20000000U) /* Bit 5 */

#define TIM_BKFR_WSIZE                          ((uint32_t)0x007E0000U) /* Break1 filter window size */
#define TIM_BKFR_WSIZE_0                        ((uint32_t)0x00020000U) /* Bit 0 */
#define TIM_BKFR_WSIZE_1                        ((uint32_t)0x00040000U) /* Bit 1 */
#define TIM_BKFR_WSIZE_2                        ((uint32_t)0x00080000U) /* Bit 2 */
#define TIM_BKFR_WSIZE_3                        ((uint32_t)0x00100000U) /* Bit 3 */
#define TIM_BKFR_WSIZE_4                        ((uint32_t)0x00200000U) /* Bit 4 */
#define TIM_BKFR_WSIZE_5                        ((uint32_t)0x00400000U) /* Bit 5 */

#define TIM_BKFR_FILTEN                         ((uint32_t)0x00010000U) /* Break1 filter enable */

/** Bit definition for TIM_C1FILT register **/
#define TIM_C1FILT_THRESH                       ((uint32_t)0x3F000000U) /* CH1 filter threshold */
#define TIM_C1FILT_THRESH_0                     ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_C1FILT_THRESH_1                     ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_C1FILT_THRESH_2                     ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_C1FILT_THRESH_3                     ((uint32_t)0x08000000U) /* Bit 3 */
#define TIM_C1FILT_THRESH_4                     ((uint32_t)0x10000000U) /* Bit 4 */
#define TIM_C1FILT_THRESH_5                     ((uint32_t)0x20000000U) /* Bit 5 */

#define TIM_C1FILT_WSIZE                        ((uint32_t)0x007E0000U) /* CH1 filter window size */
#define TIM_C1FILT_WSIZE_0                      ((uint32_t)0x00020000U) /* Bit 0 */
#define TIM_C1FILT_WSIZE_1                      ((uint32_t)0x00040000U) /* Bit 1 */
#define TIM_C1FILT_WSIZE_2                      ((uint32_t)0x00080000U) /* Bit 2 */
#define TIM_C1FILT_WSIZE_3                      ((uint32_t)0x00100000U) /* Bit 3 */
#define TIM_C1FILT_WSIZE_4                      ((uint32_t)0x00200000U) /* Bit 4 */
#define TIM_C1FILT_WSIZE_5                      ((uint32_t)0x00400000U) /* Bit 5 */

#define TIM_C1FILT_FILTEN                       ((uint32_t)0x00010000U)

/** Bit definition for TIM_C2FILT register **/
#define TIM_C2FILT_THRESH                       ((uint32_t)0x3F000000U) /* CH2 filter threshold */
#define TIM_C2FILT_THRESH_0                     ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_C2FILT_THRESH_1                     ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_C2FILT_THRESH_2                     ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_C2FILT_THRESH_3                     ((uint32_t)0x08000000U) /* Bit 3 */
#define TIM_C2FILT_THRESH_4                     ((uint32_t)0x10000000U) /* Bit 4 */
#define TIM_C2FILT_THRESH_5                     ((uint32_t)0x20000000U) /* Bit 5 */

#define TIM_C2FILT_WSIZE                        ((uint32_t)0x007E0000U) /* CH2 filter window size */
#define TIM_C2FILT_WSIZE_0                      ((uint32_t)0x00020000U) /* Bit 0 */
#define TIM_C2FILT_WSIZE_1                      ((uint32_t)0x00040000U) /* Bit 1 */
#define TIM_C2FILT_WSIZE_2                      ((uint32_t)0x00080000U) /* Bit 2 */
#define TIM_C2FILT_WSIZE_3                      ((uint32_t)0x00100000U) /* Bit 3 */
#define TIM_C2FILT_WSIZE_4                      ((uint32_t)0x00200000U) /* Bit 4 */
#define TIM_C2FILT_WSIZE_5                      ((uint32_t)0x00400000U) /* Bit 5 */

#define TIM_C2FILT_FILTEN                       ((uint32_t)0x00010000U)

/** Bit definition for TIM_C3FILT register **/
#define TIM_C3FILT_THRESH                       ((uint32_t)0x3F000000U) /* CH3 filter threshold */
#define TIM_C3FILT_THRESH_0                     ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_C3FILT_THRESH_1                     ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_C3FILT_THRESH_2                     ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_C3FILT_THRESH_3                     ((uint32_t)0x08000000U) /* Bit 3 */
#define TIM_C3FILT_THRESH_4                     ((uint32_t)0x10000000U) /* Bit 4 */
#define TIM_C3FILT_THRESH_5                     ((uint32_t)0x20000000U) /* Bit 5 */

#define TIM_C3FILT_WSIZE                        ((uint32_t)0x007E0000U) /* CH3 filter window size */
#define TIM_C3FILT_WSIZE_0                      ((uint32_t)0x00020000U) /* Bit 0 */
#define TIM_C3FILT_WSIZE_1                      ((uint32_t)0x00040000U) /* Bit 1 */
#define TIM_C3FILT_WSIZE_2                      ((uint32_t)0x00080000U) /* Bit 2 */
#define TIM_C3FILT_WSIZE_3                      ((uint32_t)0x00100000U) /* Bit 3 */
#define TIM_C3FILT_WSIZE_4                      ((uint32_t)0x00200000U) /* Bit 4 */
#define TIM_C3FILT_WSIZE_5                      ((uint32_t)0x00400000U) /* Bit 5 */

#define TIM_C3FILT_FILTEN                       ((uint32_t)0x00010000U)

/** Bit definition for TIM_C4FILT register **/
#define TIM_C4FILT_THRESH                       ((uint32_t)0x3F000000U) /* CH4 filter threshold */
#define TIM_C4FILT_THRESH_0                     ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_C4FILT_THRESH_1                     ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_C4FILT_THRESH_2                     ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_C4FILT_THRESH_3                     ((uint32_t)0x08000000U) /* Bit 3 */
#define TIM_C4FILT_THRESH_4                     ((uint32_t)0x10000000U) /* Bit 4 */
#define TIM_C4FILT_THRESH_5                     ((uint32_t)0x20000000U) /* Bit 5 */

#define TIM_C4FILT_WSIZE                        ((uint32_t)0x007E0000U) /* CH4 filter window size */
#define TIM_C4FILT_WSIZE_0                      ((uint32_t)0x00020000U) /* Bit 0 */
#define TIM_C4FILT_WSIZE_1                      ((uint32_t)0x00040000U) /* Bit 1 */
#define TIM_C4FILT_WSIZE_2                      ((uint32_t)0x00080000U) /* Bit 2 */
#define TIM_C4FILT_WSIZE_3                      ((uint32_t)0x00100000U) /* Bit 3 */
#define TIM_C4FILT_WSIZE_4                      ((uint32_t)0x00200000U) /* Bit 4 */
#define TIM_C4FILT_WSIZE_5                      ((uint32_t)0x00400000U) /* Bit 5 */

#define TIM_C4FILT_FILTEN                       ((uint32_t)0x00010000U)

/** Bit definition for TIM_FILTO register **/
#define TIM_FILTO_C1FILTO                       ((uint32_t)0x00000001U) /* CH1 filter output state */
#define TIM_FILTO_C2FILTO                       ((uint32_t)0x00000002U) /* CH2 filter output state */
#define TIM_FILTO_C3FILTO                       ((uint32_t)0x00000004U) /* CH3 filter output state */
#define TIM_FILTO_C4FILTO                       ((uint32_t)0x00000008U) /* CH4 filter output state */

/** Bit definition for TIM_INSEL register **/
#define TIM_INSEL_TI1S                          ((uint32_t)0x0000000FU) /* TI1 signal selection */
#define TIM_INSEL_TI1S_0                        ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_INSEL_TI1S_1                        ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_INSEL_TI1S_2                        ((uint32_t)0x00000004U) /* Bit 2 */
#define TIM_INSEL_TI1S_3                        ((uint32_t)0x00000008U) /* Bit 3 */

#define TIM_INSEL_TI2S                          ((uint32_t)0x000000F0U) /* TI2 signal selection */
#define TIM_INSEL_TI2S_0                        ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_INSEL_TI2S_1                        ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_INSEL_TI2S_2                        ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_INSEL_TI2S_3                        ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_INSEL_TI3S                          ((uint32_t)0x00000F00U) /* TI3 signal selection */
#define TIM_INSEL_TI3S_0                        ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_INSEL_TI3S_1                        ((uint32_t)0x00000200U) /* Bit 1 */
#define TIM_INSEL_TI3S_2                        ((uint32_t)0x00000400U) /* Bit 2 */
#define TIM_INSEL_TI3S_3                        ((uint32_t)0x00000800U) /* Bit 3 */

#define TIM_INSEL_TI4S                          ((uint32_t)0x0000F000U) /* TI4 signal selection */
#define TIM_INSEL_TI4S_0                        ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_INSEL_TI4S_1                        ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_INSEL_TI4S_2                        ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_INSEL_TI4S_3                        ((uint32_t)0x00008000U) /* Bit 3 */

#define TIM_INSEL_ETRS                          ((uint32_t)0x000F0000U) /* etr signal selection */
#define TIM_INSEL_ETRS_0                        ((uint32_t)0x00010000U) /* Bit 0 */
#define TIM_INSEL_ETRS_1                        ((uint32_t)0x00020000U) /* Bit 1 */
#define TIM_INSEL_ETRS_2                        ((uint32_t)0x00040000U) /* Bit 2 */
#define TIM_INSEL_ETRS_3                        ((uint32_t)0x00080000U) /* Bit 3 */

#define TIM_INSEL_ITRS                          ((uint32_t)0x00F00000U) /* itr signal selection */
#define TIM_INSEL_ITRS_0                        ((uint32_t)0x00100000U) /* Bit 0 */
#define TIM_INSEL_ITRS_1                        ((uint32_t)0x00200000U) /* Bit 1 */
#define TIM_INSEL_ITRS_2                        ((uint32_t)0x00400000U) /* Bit 2 */
#define TIM_INSEL_ITRS_3                        ((uint32_t)0x00800000U) /* Bit 3 */

#define TIM_INSEL_CLRS                          ((uint32_t)0x0F000000U) /* Ocrefclear signal selection */
#define TIM_INSEL_CLRS_0                        ((uint32_t)0x01000000U) /* Bit 0 */
#define TIM_INSEL_CLRS_1                        ((uint32_t)0x02000000U) /* Bit 1 */
#define TIM_INSEL_CLRS_2                        ((uint32_t)0x04000000U) /* Bit 2 */
#define TIM_INSEL_CLRS_3                        ((uint32_t)0x08000000U) /* Bit 3 */

/** Bit definition for TIM_AF1 register **/
#define TIM_AF1_IOM1BRKEN                        ((uint32_t)0x00000001U) /* Enable IOM 1 as break1 input */
#define TIM_AF1_COMP1BRKEN                      ((uint32_t)0x00000002U) /* Enable COMP1 as break1 input */
#define TIM_AF1_COMP2BRKEN                      ((uint32_t)0x00000004U) /* Enable COMP2 as break1 input */
#define TIM_AF1_COMP3BRKEN                      ((uint32_t)0x00000008U) /* Enable COMP3 as break1 input */
#define TIM_AF1_IOM1BRKP                         ((uint32_t)0x00000200U) /* Select polarity of break1 input from IOM 1 */
#define TIM_AF1_COMP1BRKP                       ((uint32_t)0x00000400U) /* Select polarity of break1 input from COMP1 */
#define TIM_AF1_COMP2BRKP                       ((uint32_t)0x00000800U) /* Select polarity of break1 input from COMP2 */
#define TIM_AF1_COMP3BRKP                       ((uint32_t)0x00001000U) /* Select polarity of break1 input from COMP3 */
#define TIM_AF1_IOM2BRKEN                       ((uint32_t)0x00010000U) /* Enable IOM 2 as break1 input */
#define TIM_AF1_IOM3BRKEN                       ((uint32_t)0x00020000U) /* Enable IOM 3 as break1 input */
#define TIM_AF1_IOM4BRKEN                       ((uint32_t)0x00040000U) /* Enable IOM 4 as break1 input */
#define TIM_AF1_IOM2BRKP                        ((uint32_t)0x00080000U) /* Select polarity of break1 input from IOM 2 */
#define TIM_AF1_IOM3BRKP                        ((uint32_t)0x00100000U) /* Select polarity of break1 input from IOM 3 */
#define TIM_AF1_IOM4BRKP                        ((uint32_t)0x00200000U) /* Select polarity of break1 input from IOM 4 */
#define TIM_AF1_IOM5BRKEN                       ((uint32_t)0x00400000U) /* Enable IOM 5 as break1 input */
#define TIM_AF1_IOM5BRKP                        ((uint32_t)0x00800000U) /* Select polarity of break1 input from IOM 5 */
#define TIM_AF1_IOM6BRKEN                       ((uint32_t)0x01000000U) /* Enable IOM 6 as break1 input */
#define TIM_AF1_IOM6BRKP                        ((uint32_t)0x02000000U) /* Select polarity of break1 input from IOM 6 */
#define TIM_AF1_IOM7BRKEN                       ((uint32_t)0x04000000U) /* Enable IOM 7 as break1 input */
#define TIM_AF1_IOM7BRKP                        ((uint32_t)0x08000000U) /* Select polarity of break1 input from IOM 7 */

/** Bit definition for TIM_ENCDAT register **/
#define TIM_ENCDAT_ENCDAT                       ((uint32_t)0xFFFFFFFFU) /* Encoder capture data register */

/** Bit definition for TIM_ENCMCTRL register **/
#define TIM_ENCMCTRL_C3LDCNTEN                  ((uint32_t)0x00000001U) /* CH3 load LVR to counter enable */

#define TIM_ENCMCTRL_C3LDCNTSEL                 ((uint32_t)0x00000006U) /* CH3 senstive select for load LVR to counter in encoder mode */
#define TIM_ENCMCTRL_C3LDCNTSEL_0               ((uint32_t)0x00000002U) /* Bit 0 */
#define TIM_ENCMCTRL_C3LDCNTSEL_1               ((uint32_t)0x00000004U) /* Bit 1 */

#define TIM_ENCMCTRL_ENCMD                      ((uint32_t)0x00000078U) /* Encoder mode select */
#define TIM_ENCMCTRL_ENCMD_0                    ((uint32_t)0x00000008U) /* Bit 0 */
#define TIM_ENCMCTRL_ENCMD_1                    ((uint32_t)0x00000010U) /* Bit 1 */
#define TIM_ENCMCTRL_ENCMD_2                    ((uint32_t)0x00000020U) /* Bit 2 */
#define TIM_ENCMCTRL_ENCMD_3                    ((uint32_t)0x00000040U) /* Bit 3 */

#define TIM_ENCMCTRL_ENCDATS                    ((uint32_t)0x80000000U) /* Sign of encoder capture data */

/** Bit definition for TIM_ENCLVR register **/
#define TIM_ENCLVR_LVR                          ((uint32_t)0xFFFFFFFFU) /* LVR register */

/** Bit definition for TIM_DCTRL register **/
#define TIM_DCTRL_DBADDR                        ((uint32_t)0x00003F00U) /* DBA[5:0] bits (DMA Base Address) */
#define TIM_DCTRL_DBADDR_0                      ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_DCTRL_DBADDR_1                      ((uint32_t)0x00000200U) /* Bit 1 */
#define TIM_DCTRL_DBADDR_2                      ((uint32_t)0x00000400U) /* Bit 2 */
#define TIM_DCTRL_DBADDR_3                      ((uint32_t)0x00000800U) /* Bit 3 */
#define TIM_DCTRL_DBADDR_4                      ((uint32_t)0x00001000U) /* Bit 4 */
#define TIM_DCTRL_DBADDR_5                      ((uint32_t)0x00002000U) /* Bit 5 */

#define TIM_DCTRL_DBLEN                         ((uint32_t)0x0000003FU) /* DBL[5:0] bits (DMA Burst Length) */
#define TIM_DCTRL_DBLEN_0                       ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_DCTRL_DBLEN_1                       ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_DCTRL_DBLEN_2                       ((uint32_t)0x00000004U) /* Bit 2 */
#define TIM_DCTRL_DBLEN_3                       ((uint32_t)0x00000008U) /* Bit 3 */
#define TIM_DCTRL_DBLEN_4                       ((uint32_t)0x00000010U) /* Bit 4 */
#define TIM_DCTRL_DBLEN_5                       ((uint32_t)0x00000020U) /* Bit 5 */

/** Bit definition for TIM_DADDR register **/
#define TIM_DADDR_BURST                         ((uint32_t)0xFFFFFFFFU) /* DMA register for burst accesses */


/*** Real-Time Clock (RTC) ***/
/** Bits definition for RTC_INITSTS register **/
#define RTC_INITSTS_RECPF  ((uint32_t)0x00010000U)
#define RTC_INITSTS_TISOVF ((uint32_t)0x00001000U)
#define RTC_INITSTS_TISF   ((uint32_t)0x00000800U)
#define RTC_INITSTS_WTF    ((uint32_t)0x00000400U)
#define RTC_INITSTS_ALBF   ((uint32_t)0x00000200U)
#define RTC_INITSTS_ALAF   ((uint32_t)0x00000100U)
#define RTC_INITSTS_INITM  ((uint32_t)0x00000080U)
#define RTC_INITSTS_INITF  ((uint32_t)0x00000040U)
#define RTC_INITSTS_RSYF   ((uint32_t)0x00000020U)
#define RTC_INITSTS_INITSF ((uint32_t)0x00000010U)
#define RTC_INITSTS_SHOPF  ((uint32_t)0x00000008U)
#define RTC_INITSTS_WTWF   ((uint32_t)0x00000004U)
#define RTC_INITSTS_ALBWF  ((uint32_t)0x00000002U)
#define RTC_INITSTS_ALAWF  ((uint32_t)0x00000001U)

/** Bits definition for RTC_CTRL register **/
#define RTC_CTRL_COEN     ((uint32_t)0x00800000U)
#define RTC_CTRL_OUTSEL   ((uint32_t)0x00600000U)
#define RTC_CTRL_OUTSEL_0 ((uint32_t)0x00200000U)
#define RTC_CTRL_OUTSEL_1 ((uint32_t)0x00400000U)
#define RTC_CTRL_OPOL     ((uint32_t)0x00100000U)
#define RTC_CTRL_CALOSEL  ((uint32_t)0x00080000U)
#define RTC_CTRL_BAKP     ((uint32_t)0x00040000U)
#define RTC_CTRL_SU1H     ((uint32_t)0x00020000U)
#define RTC_CTRL_AD1H     ((uint32_t)0x00010000U)
#define RTC_CTRL_TSIEN    ((uint32_t)0x00008000U)
#define RTC_CTRL_WTIEN    ((uint32_t)0x00004000U)
#define RTC_CTRL_ALBIEN   ((uint32_t)0x00002000U)
#define RTC_CTRL_ALAIEN   ((uint32_t)0x00001000U)
#define RTC_CTRL_TSEN     ((uint32_t)0x00000800U)
#define RTC_CTRL_WTEN     ((uint32_t)0x00000400U)
#define RTC_CTRL_ALBEN    ((uint32_t)0x00000200U)
#define RTC_CTRL_ALAEN    ((uint32_t)0x00000100U)

#define RTC_CTRL_HFMT      ((uint32_t)0x00000040U)
#define RTC_CTRL_BYPS      ((uint32_t)0x00000020U)
#define RTC_CTRL_REFCLKEN  ((uint32_t)0x00000010U)
#define RTC_CTRL_TEDGE     ((uint32_t)0x00000008U)
#define RTC_CTRL_WKUPSEL   ((uint32_t)0x00000007U)
#define RTC_CTRL_WKUPSEL_0 ((uint32_t)0x00000001U)
#define RTC_CTRL_WKUPSEL_1 ((uint32_t)0x00000002U)
#define RTC_CTRL_WKUPSEL_2 ((uint32_t)0x00000004U)

/** Bits definition for RTC_TSH register **/
#define RTC_TSH_APM        ((uint32_t)0x00400000U)
#define RTC_TSH_HOT        ((uint32_t)0x00300000U)
#define RTC_TSH_HOT_0      ((uint32_t)0x00100000U)
#define RTC_TSH_HOT_1      ((uint32_t)0x00200000U)
#define RTC_TSH_HOU        ((uint32_t)0x000F0000U)
#define RTC_TSH_HOU_0      ((uint32_t)0x00010000U)
#define RTC_TSH_HOU_1      ((uint32_t)0x00020000U)
#define RTC_TSH_HOU_2      ((uint32_t)0x00040000U)
#define RTC_TSH_HOU_3      ((uint32_t)0x00080000U)
#define RTC_TSH_MIT        ((uint32_t)0x00007000U)
#define RTC_TSH_MIT_0      ((uint32_t)0x00001000U)
#define RTC_TSH_MIT_1      ((uint32_t)0x00002000U)
#define RTC_TSH_MIT_2      ((uint32_t)0x00004000U)
#define RTC_TSH_MIU        ((uint32_t)0x00000F00U)
#define RTC_TSH_MIU_0      ((uint32_t)0x00000100U)
#define RTC_TSH_MIU_1      ((uint32_t)0x00000200U)
#define RTC_TSH_MIU_2      ((uint32_t)0x00000400U)
#define RTC_TSH_MIU_3      ((uint32_t)0x00000800U)
#define RTC_TSH_SCT        ((uint32_t)0x00000070U)
#define RTC_TSH_SCT_0      ((uint32_t)0x00000010U)
#define RTC_TSH_SCT_1      ((uint32_t)0x00000020U)
#define RTC_TSH_SCT_2      ((uint32_t)0x00000040U)
#define RTC_TSH_SCU        ((uint32_t)0x0000000FU)
#define RTC_TSH_SCU_0      ((uint32_t)0x00000001U)
#define RTC_TSH_SCU_1      ((uint32_t)0x00000002U)
#define RTC_TSH_SCU_2      ((uint32_t)0x00000004U)
#define RTC_TSH_SCU_3      ((uint32_t)0x00000008U)

/** Bits definition for RTC_DATE register **/
#define RTC_DATE_YRT       ((uint32_t)0x00F00000U)
#define RTC_DATE_YRT_0     ((uint32_t)0x00100000U)
#define RTC_DATE_YRT_1     ((uint32_t)0x00200000U)
#define RTC_DATE_YRT_2     ((uint32_t)0x00400000U)
#define RTC_DATE_YRT_3     ((uint32_t)0x00800000U)
#define RTC_DATE_YRU       ((uint32_t)0x000F0000U)
#define RTC_DATE_YRU_0     ((uint32_t)0x00010000U)
#define RTC_DATE_YRU_1     ((uint32_t)0x00020000U)
#define RTC_DATE_YRU_2     ((uint32_t)0x00040000U)
#define RTC_DATE_YRU_3     ((uint32_t)0x00080000U)
#define RTC_DATE_WDU       ((uint32_t)0x0000E000U)
#define RTC_DATE_WDU_0     ((uint32_t)0x00002000U)
#define RTC_DATE_WDU_1     ((uint32_t)0x00004000U)
#define RTC_DATE_WDU_2     ((uint32_t)0x00008000U)
#define RTC_DATE_MOT       ((uint32_t)0x00001000U)
#define RTC_DATE_MOU       ((uint32_t)0x00000F00U)
#define RTC_DATE_MOU_0     ((uint32_t)0x00000100U)
#define RTC_DATE_MOU_1     ((uint32_t)0x00000200U)
#define RTC_DATE_MOU_2     ((uint32_t)0x00000400U)
#define RTC_DATE_MOU_3     ((uint32_t)0x00000800U)
#define RTC_DATE_DAT       ((uint32_t)0x00000030U)
#define RTC_DATE_DAT_0     ((uint32_t)0x00000010U)
#define RTC_DATE_DAT_1     ((uint32_t)0x00000020U)
#define RTC_DATE_DAU       ((uint32_t)0x0000000FU)
#define RTC_DATE_DAU_0     ((uint32_t)0x00000001U)
#define RTC_DATE_DAU_1     ((uint32_t)0x00000002U)
#define RTC_DATE_DAU_2     ((uint32_t)0x00000004U)
#define RTC_DATE_DAU_3     ((uint32_t)0x00000008U)

/** Bits definition for RTC_WRP register **/
#define RTC_WRP_PKEY      ((uint32_t)0x000000FFU)

/** Bits definition for RTC_SCTRL register **/
#define RTC_SCTRL_AD1S    ((uint32_t)0x80000000U)
#define RTC_SCTRL_SUBF    ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_SUBS register **/
#define RTC_SUBS_SS       ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_TST register **/
#define RTC_TST_APM       ((uint32_t)0x00400000U)
#define RTC_TST_HOT       ((uint32_t)0x00300000U)
#define RTC_TST_HOT_0     ((uint32_t)0x00100000U)
#define RTC_TST_HOT_1     ((uint32_t)0x00200000U)
#define RTC_TST_HOU       ((uint32_t)0x000F0000U)
#define RTC_TST_HOU_0     ((uint32_t)0x00010000U)
#define RTC_TST_HOU_1     ((uint32_t)0x00020000U)
#define RTC_TST_HOU_2     ((uint32_t)0x00040000U)
#define RTC_TST_HOU_3     ((uint32_t)0x00080000U)
#define RTC_TST_MIT       ((uint32_t)0x00007000U)
#define RTC_TST_MIT_0     ((uint32_t)0x00001000U)
#define RTC_TST_MIT_1     ((uint32_t)0x00002000U)
#define RTC_TST_MIT_2     ((uint32_t)0x00004000U)
#define RTC_TST_MIU       ((uint32_t)0x00000F00U)
#define RTC_TST_MIU_0     ((uint32_t)0x00000100U)
#define RTC_TST_MIU_1     ((uint32_t)0x00000200U)
#define RTC_TST_MIU_2     ((uint32_t)0x00000400U)
#define RTC_TST_MIU_3     ((uint32_t)0x00000800U)
#define RTC_TST_SET       ((uint32_t)0x00000070U)
#define RTC_TST_SET_0     ((uint32_t)0x00000010U)
#define RTC_TST_SET_1     ((uint32_t)0x00000020U)
#define RTC_TST_SET_2     ((uint32_t)0x00000040U)
#define RTC_TST_SEU       ((uint32_t)0x0000000FU)
#define RTC_TST_SEU_0     ((uint32_t)0x00000001U)
#define RTC_TST_SEU_1     ((uint32_t)0x00000002U)
#define RTC_TST_SEU_2     ((uint32_t)0x00000004U)
#define RTC_TST_SEU_3     ((uint32_t)0x00000008U)

/** Bits definition for RTC_ALARMA register **/
#define RTC_ALARMA_MASK4  ((uint32_t)0x80000000U)
#define RTC_ALARMA_WKDSEL ((uint32_t)0x40000000U)
#define RTC_ALARMA_DTT    ((uint32_t)0x30000000U)
#define RTC_ALARMA_DTT_0  ((uint32_t)0x10000000U)
#define RTC_ALARMA_DTT_1  ((uint32_t)0x20000000U)
#define RTC_ALARMA_DTU    ((uint32_t)0x0F000000U)
#define RTC_ALARMA_DTU_0  ((uint32_t)0x01000000U)
#define RTC_ALARMA_DTU_1  ((uint32_t)0x02000000U)
#define RTC_ALARMA_DTU_2  ((uint32_t)0x04000000U)
#define RTC_ALARMA_DTU_3  ((uint32_t)0x08000000U)
#define RTC_ALARMA_MASK3  ((uint32_t)0x00800000U)
#define RTC_ALARMA_APM    ((uint32_t)0x00400000U)
#define RTC_ALARMA_HOT    ((uint32_t)0x00300000U)
#define RTC_ALARMA_HOT_0  ((uint32_t)0x00100000U)
#define RTC_ALARMA_HOT_1  ((uint32_t)0x00200000U)
#define RTC_ALARMA_HOU    ((uint32_t)0x000F0000U)
#define RTC_ALARMA_HOU_0  ((uint32_t)0x00010000U)
#define RTC_ALARMA_HOU_1  ((uint32_t)0x00020000U)
#define RTC_ALARMA_HOU_2  ((uint32_t)0x00040000U)
#define RTC_ALARMA_HOU_3  ((uint32_t)0x00080000U)
#define RTC_ALARMA_MASK2  ((uint32_t)0x00008000U)
#define RTC_ALARMA_MIT    ((uint32_t)0x00007000U)
#define RTC_ALARMA_MIT_0  ((uint32_t)0x00001000U)
#define RTC_ALARMA_MIT_1  ((uint32_t)0x00002000U)
#define RTC_ALARMA_MIT_2  ((uint32_t)0x00004000U)
#define RTC_ALARMA_MIU    ((uint32_t)0x00000F00U)
#define RTC_ALARMA_MIU_0  ((uint32_t)0x00000100U)
#define RTC_ALARMA_MIU_1  ((uint32_t)0x00000200U)
#define RTC_ALARMA_MIU_2  ((uint32_t)0x00000400U)
#define RTC_ALARMA_MIU_3  ((uint32_t)0x00000800U)
#define RTC_ALARMA_MASK1  ((uint32_t)0x00000080U)
#define RTC_ALARMA_SET    ((uint32_t)0x00000070U)
#define RTC_ALARMA_SET_0  ((uint32_t)0x00000010U)
#define RTC_ALARMA_SET_1  ((uint32_t)0x00000020U)
#define RTC_ALARMA_SET_2  ((uint32_t)0x00000040U)
#define RTC_ALARMA_SEU    ((uint32_t)0x0000000FU)
#define RTC_ALARMA_SEU_0  ((uint32_t)0x00000001U)
#define RTC_ALARMA_SEU_1  ((uint32_t)0x00000002U)
#define RTC_ALARMA_SEU_2  ((uint32_t)0x00000004U)
#define RTC_ALARMA_SEU_3  ((uint32_t)0x00000008U)

/** Bits definition for RTC_PRE register **/
#define RTC_PRE_DIVA      ((uint32_t)0x007F0000U)
#define RTC_PRE_DIVS      ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_ALARMB register **/
#define RTC_ALARMB_MASK4  ((uint32_t)0x80000000U)
#define RTC_ALARMB_WKDSEL ((uint32_t)0x40000000U)
#define RTC_ALARMB_DTT    ((uint32_t)0x30000000U)
#define RTC_ALARMB_DTT_0  ((uint32_t)0x10000000U)
#define RTC_ALARMB_DTT_1  ((uint32_t)0x20000000U)
#define RTC_ALARMB_DTU    ((uint32_t)0x0F000000U)
#define RTC_ALARMB_DTU_0  ((uint32_t)0x01000000U)
#define RTC_ALARMB_DTU_1  ((uint32_t)0x02000000U)
#define RTC_ALARMB_DTU_2  ((uint32_t)0x04000000U)
#define RTC_ALARMB_DTU_3  ((uint32_t)0x08000000U)
#define RTC_ALARMB_MASK3  ((uint32_t)0x00800000U)
#define RTC_ALARMB_APM    ((uint32_t)0x00400000U)
#define RTC_ALARMB_HOT    ((uint32_t)0x00300000U)
#define RTC_ALARMB_HOT_0  ((uint32_t)0x00100000U)
#define RTC_ALARMB_HOT_1  ((uint32_t)0x00200000U)
#define RTC_ALARMB_HOU    ((uint32_t)0x000F0000U)
#define RTC_ALARMB_HOU_0  ((uint32_t)0x00010000U)
#define RTC_ALARMB_HOU_1  ((uint32_t)0x00020000U)
#define RTC_ALARMB_HOU_2  ((uint32_t)0x00040000U)
#define RTC_ALARMB_HOU_3  ((uint32_t)0x00080000U)
#define RTC_ALARMB_MASK2  ((uint32_t)0x00008000U)
#define RTC_ALARMB_MIT    ((uint32_t)0x00007000U)
#define RTC_ALARMB_MIT_0  ((uint32_t)0x00001000U)
#define RTC_ALARMB_MIT_1  ((uint32_t)0x00002000U)
#define RTC_ALARMB_MIT_2  ((uint32_t)0x00004000U)
#define RTC_ALARMB_MIU    ((uint32_t)0x00000F00U)
#define RTC_ALARMB_MIU_0  ((uint32_t)0x00000100U)
#define RTC_ALARMB_MIU_1  ((uint32_t)0x00000200U)
#define RTC_ALARMB_MIU_2  ((uint32_t)0x00000400U)
#define RTC_ALARMB_MIU_3  ((uint32_t)0x00000800U)
#define RTC_ALARMB_MASK1  ((uint32_t)0x00000080U)
#define RTC_ALARMB_SET    ((uint32_t)0x00000070U)
#define RTC_ALARMB_SET_0  ((uint32_t)0x00000010U)
#define RTC_ALARMB_SET_1  ((uint32_t)0x00000020U)
#define RTC_ALARMB_SET_2  ((uint32_t)0x00000040U)
#define RTC_ALARMB_SEU    ((uint32_t)0x0000000FU)
#define RTC_ALARMB_SEU_0  ((uint32_t)0x00000001U)
#define RTC_ALARMB_SEU_1  ((uint32_t)0x00000002U)
#define RTC_ALARMB_SEU_2  ((uint32_t)0x00000004U)
#define RTC_ALARMB_SEU_3  ((uint32_t)0x00000008U)

/** Bits definition for RTC_WKUPT register **/
#define RTC_WKUPT_WKUPT   ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_ALRMASS register **/
#define RTC_ALRMASS_MASKSSB     ((uint32_t)0x000F0000U)
#define RTC_ALRMASS_MASKSSB_0   ((uint32_t)0x00010000U)
#define RTC_ALRMASS_MASKSSB_1   ((uint32_t)0x00020000U)
#define RTC_ALRMASS_MASKSSB_2   ((uint32_t)0x00040000U)
#define RTC_ALRMASS_MASKSSB_3   ((uint32_t)0x00080000U)
#define RTC_ALRMASS_SSV         ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_OPT register **/
#define RTC_OPT_TYPE  ((uint32_t)0x00000001U)

/** Bits definition for RTC_ALRMBSS register **/
#define RTC_ALRMBSS_MASKSSB     ((uint32_t)0x000F0000U)
#define RTC_ALRMBSS_MASKSSB_0   ((uint32_t)0x00010000U)
#define RTC_ALRMBSS_MASKSSB_1   ((uint32_t)0x00020000U)
#define RTC_ALRMBSS_MASKSSB_2   ((uint32_t)0x00040000U)
#define RTC_ALRMBSS_MASKSSB_3   ((uint32_t)0x00080000U)
#define RTC_ALRMBSS_SSV         ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_CALIB register **/
#define RTC_CALIB_CP    ((uint32_t)0x00000800U)
#define RTC_CALIB_CW8   ((uint32_t)0x00000400U)
#define RTC_CALIB_CW16  ((uint32_t)0x00000200U)
#define RTC_CALIB_CM    ((uint32_t)0x000001FFU)
#define RTC_CALIB_CM_0  ((uint32_t)0x00000001U)
#define RTC_CALIB_CM_1  ((uint32_t)0x00000002U)
#define RTC_CALIB_CM_2  ((uint32_t)0x00000004U)
#define RTC_CALIB_CM_3  ((uint32_t)0x00000008U)
#define RTC_CALIB_CM_4  ((uint32_t)0x00000010U)
#define RTC_CALIB_CM_5  ((uint32_t)0x00000020U)
#define RTC_CALIB_CM_6  ((uint32_t)0x00000040U)
#define RTC_CALIB_CM_7  ((uint32_t)0x00000080U)
#define RTC_CALIB_CM_8  ((uint32_t)0x00000100U)

/** Bits definition for RTC_TSSS register **/
#define RTC_TSSS_SSE ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_TSD register **/
#define RTC_TSD_MOT   ((uint32_t)0x00008000U)
#define RTC_TSD_WDU   ((uint32_t)0x00007000U)
#define RTC_TSD_WDU_0 ((uint32_t)0x00001000U)
#define RTC_TSD_WDU_1 ((uint32_t)0x00002000U)
#define RTC_TSD_WDU_2 ((uint32_t)0x00004000U)
#define RTC_TSD_MOU   ((uint32_t)0x00000F00U)
#define RTC_TSD_MOU_0 ((uint32_t)0x00000100U)
#define RTC_TSD_MOU_1 ((uint32_t)0x00000200U)
#define RTC_TSD_MOU_2 ((uint32_t)0x00000400U)
#define RTC_TSD_MOU_3 ((uint32_t)0x00000800U)
#define RTC_TSD_DAT   ((uint32_t)0x00000030U)
#define RTC_TSD_DAT_0 ((uint32_t)0x00000010U)
#define RTC_TSD_DAT_1 ((uint32_t)0x00000020U)
#define RTC_TSD_DAU   ((uint32_t)0x0000000FU)
#define RTC_TSD_DAU_0 ((uint32_t)0x00000001U)
#define RTC_TSD_DAU_1 ((uint32_t)0x00000002U)
#define RTC_TSD_DAU_2 ((uint32_t)0x00000004U)
#define RTC_TSD_DAU_3 ((uint32_t)0x00000008U)


/*** Window WATCHDOG ***/
/**  Bit definition for WWDG_CFG register **/
#define WWDG_CFG_W       ((uint32_t)0x00003FFF) /* W[13:0] bits (14-bit window value) */
#define WWDG_CFG_W0      ((uint32_t)0x00000001) /* Bit 0 */
#define WWDG_CFG_W1      ((uint32_t)0x00000002) /* Bit 1 */
#define WWDG_CFG_W2      ((uint32_t)0x00000004) /* Bit 2 */
#define WWDG_CFG_W3      ((uint32_t)0x00000008) /* Bit 3 */
#define WWDG_CFG_W4      ((uint32_t)0x00000010) /* Bit 4 */
#define WWDG_CFG_W5      ((uint32_t)0x00000020) /* Bit 5 */
#define WWDG_CFG_W6      ((uint32_t)0x00000040) /* Bit 6 */
#define WWDG_CFG_W7      ((uint32_t)0x00000080) /* Bit 7  */
#define WWDG_CFG_W8      ((uint32_t)0x00000100) /* Bit 8  */
#define WWDG_CFG_W9      ((uint32_t)0x00000200) /* Bit 9  */
#define WWDG_CFG_W10     ((uint32_t)0x00000400) /* Bit 10 */
#define WWDG_CFG_W11     ((uint32_t)0x00000800) /* Bit 11 */
#define WWDG_CFG_W12     ((uint32_t)0x00001000) /* Bit 12 */
#define WWDG_CFG_W13     ((uint32_t)0x00002000) /* Bit 13 */

#define WWDG_CFG_TIMERB  ((uint32_t)0x0000C000) /* WDGTB[1:0] bits (Timer Base) */
#define WWDG_CFG_TIMERB0 ((uint32_t)0x00004000) /* Bit 0 */
#define WWDG_CFG_TIMERB1 ((uint32_t)0x00008000) /* Bit 1 */

#define WWDG_CFG_EWINT   ((uint32_t)0x00010000) /* Early Wakeup Interrupt */

/** Bit definition for WWDG_CTRL register **/
#define WWDG_CTRL_T      ((uint16_t)0x3FFF)     /*T[13:0] bits(14-bit counter (MSB to LSB)) */
#define WWDG_CTRL_T0     ((uint16_t)0x0001)     /* Bit 0  */
#define WWDG_CTRL_T1     ((uint16_t)0x0002)     /* Bit 1  */
#define WWDG_CTRL_T2     ((uint16_t)0x0004)     /* Bit 2  */
#define WWDG_CTRL_T3     ((uint16_t)0x0008)     /* Bit 3  */
#define WWDG_CTRL_T4     ((uint16_t)0x0010)     /* Bit 4  */
#define WWDG_CTRL_T5     ((uint16_t)0x0020)     /* Bit 5  */
#define WWDG_CTRL_T6     ((uint16_t)0x0040)     /* Bit 6  */
#define WWDG_CTRL_T7     ((uint16_t)0x0080)     /* Bit 7  */
#define WWDG_CTRL_T8     ((uint16_t)0x0100)     /* Bit 8  */
#define WWDG_CTRL_T9     ((uint16_t)0x0200)     /* Bit 9  */
#define WWDG_CTRL_T10    ((uint16_t)0x0400)     /* Bit 10 */
#define WWDG_CTRL_T11    ((uint16_t)0x0800)     /* Bit 11 */
#define WWDG_CTRL_T12    ((uint16_t)0x1000)     /* Bit 12 */
#define WWDG_CTRL_T13    ((uint16_t)0x2000)     /* Bit 13 */

#define WWDG_CTRL_ACTB   ((uint16_t)0x4000) /* Activation bit */

/** Bit definition for WWDG_STS register **/
#define WWDG_STS_EWINTF  ((uint8_t)0x01)        /* Early Wakeup Interrupt Flag */


/******************************************************************************/
/*                                                                            */
/*                           Independent WATCHDOG                             */
/*                                                                            */
/******************************************************************************/

/** Bit definition for IWDG_KEY register **/
#define IWDG_KEY_KEYV     ((uint16_t)0xFFFFU) /* Key value (write only, read 0000h) */

/** Bit definition for IWDG_STS register **/
#define IWDG_STS_PVU      ((uint8_t)0x01U)    /* Watchdog prescaler value update */
#define IWDG_STS_CRVU     ((uint8_t)0x02U)    /* Watchdog counter reload value update */
#define IWDG_STS_FRZF     ((uint8_t)0x04U)    /* Watchdog Freeze funcion state */

/** Bit definition for IWDG_PREDIV register **/
#define IWDG_PREDIV_PD    ((uint8_t)0x07U)    /* PD[2:0] (Prescaler divider) */
#define IWDG_PREDIV_PD0   ((uint8_t)0x01U)    /* Bit 0 */
#define IWDG_PREDIV_PD1   ((uint8_t)0x02U)    /* Bit 1 */
#define IWDG_PREDIV_PD2   ((uint8_t)0x04U)    /* Bit 2 */

/** Bit definition for IWDG_RELV register **/
#define IWDG_RELV_REL     ((uint16_t)0x3FFFU) /* Watchdog counter reload value */


/******************************************************************************/
/*                                                                            */
/*                        Comparators Peripheral Interface                    */
/*                                                                            */
/******************************************************************************/

/******** Bit definition for COMP_INTEN register  ********/
#define COMP_INTEN_CMP3IEN                                ((uint32_t)0x00000004)         /* Bit[2] */
#define COMP_INTEN_CMP2IEN                                ((uint32_t)0x00000002)         /* Bit[1] */
#define COMP_INTEN_CMP1IEN                                ((uint32_t)0x00000001)         /* Bit[0] */ 

/******** Bit definition for COMP_INTSTS register  ********/
#define COMP_INTSTS_CMP3IS                                ((uint32_t)0x00000004)         /* Bit[2] */
#define COMP_INTSTS_CMP2IS                                ((uint32_t)0x00000002)         /* Bit[1] */
#define COMP_INTSTS_CMP1IS                                ((uint32_t)0x00000001)         /* Bit[0] */

/******** Bit definition for COMP_LOCK register  ********/
#define COMP_LOCK_CMP3LK                                  ((uint32_t)0x00000004)         /* Bit[2] */
#define COMP_LOCK_CMP2LK                                  ((uint32_t)0x00000002)         /* Bit[1] */
#define COMP_LOCK_CMP1LK                                  ((uint32_t)0x00000001)         /* Bit[0] */

/********************  Bit definition for COMP_WINMODE register  ********************/
#define COMP_WINMODE_COMP23MD                             ((uint32_t)0x00000002)     /* Bit[1] */
#define COMP_WINMODE_COMP12MD                             ((uint32_t)0x00000001)     /* Bit[0]*/

/******** Bit definition for COMP_CTRL register  ********/
#define COMPx_CTRL_OUT                                     ((uint32_t)0x01000000)         /* Bit[24] */
#define COMPx_CTRL_CLKSEL                                  ((uint32_t)0x00200000)         /* Bit[21] */
#define COMPx_CTRL_PWRMD                                   ((uint32_t)0x00100000)         /* Bit[20] */

#define COMPx_CTRL_BLKING                                  ((uint32_t)0x00070000U)         /* Bit[18:16] */
#define COMPx_CTRL_BLKING_0                                ((uint32_t)0x00010000U)         /* Bit16*/
#define COMPx_CTRL_BLKING_1                                ((uint32_t)0x00020000U)         /* Bit17*/
#define COMPx_CTRL_BLKING_2                                ((uint32_t)0x00040000U)         /* Bit18*/

#define COMPx_CTRL_DOUHYSIEN                               ((uint32_t)0x00004000U)         /* Bit[14] */

#define COMPx_CTRL_HYST                                    ((uint32_t)0x00003000U)         /* Bit[13:12] */
#define COMPx_CTRL_HYST_0                                  ((uint32_t)0x00001000U)         /* Bit12*/
#define COMPx_CTRL_HYST_1                                  ((uint32_t)0x00002000U)         /* Bit13*/

#define COMPx_CTRL_POL                                     ((uint32_t)0x00000100U)         /* Bit[8] */

#define COMPx_CTRL_INMSEL                                  ((uint32_t)0x000000E0U)         /* Bit[7:5] */
#define COMPx_CTRL_INMSEL_0                                ((uint32_t)0x00000020U)         /* Bit5*/
#define COMPx_CTRL_INMSEL_1                                ((uint32_t)0x00000040U)         /* Bit6*/
#define COMPx_CTRL_INMSEL_2                                ((uint32_t)0x00000080U)         /* Bit7*/

#define COMPx_CTRL_INPSEL                                  ((uint32_t)0x0000001EU)         /* Bit[4:1] */
#define COMPx_CTRL_INPSEL_0                                ((uint32_t)0x00000002U)         /* Bit1*/
#define COMPx_CTRL_INPSEL_1                                ((uint32_t)0x00000004U)         /* Bit2*/
#define COMPx_CTRL_INPSEL_2                                ((uint32_t)0x00000008U)         /* Bit3*/
#define COMPx_CTRL_INPSEL_3                                ((uint32_t)0x00000010U)         /* Bit4*/

#define COMPx_CTRL_EN                                      ((uint32_t)0x00000001U)         /* Bit[0] */

/******** Bit definition for COMP_FILC register  ********/
#define COMPx_FILC_SAMPW                                   ((uint32_t)0x000007C0U)         /* Bit[10:6] */

#define COMPx_FILC_THRESH                                  ((uint32_t)0x0000003EU)         /* Bit[5:1] */

#define COMPx_FILC_FILEN                                   ((uint32_t)0x00000001U)         /* Bit[0] */

/******** Bit definition for COMP_FILP register  ********/
#define COMPx_FILP_CLKPSC                                  ((uint32_t)0x0000FFFFU)         /* Bit[15:0] */

/******** Bit definition for COMP_INVREF register  ********/
#define COMP_INVREF_VREFSEL                               ((uint32_t)0x000001FEU)         /* Bit[8:1] */

#define COMP_INVREF_VREFEN                                ((uint32_t)0x00000001U)         /* Bit[0] */


/*** Serial Peripheral Interface ***/
/** Bit definition for SPI_CTRL1 register **/
#define SPI_CTRL1_BR                          ((uint16_t)0x0007U) /* BR[2:0] bits (Baud Rate Control) */
#define SPI_CTRL1_BR0                         ((uint16_t)0x0001U) /* Bit 0 */
#define SPI_CTRL1_BR1                         ((uint16_t)0x0002U) /* Bit 1 */
#define SPI_CTRL1_BR2                         ((uint16_t)0x0004U) /* Bit 2 */

#define SPI_CTRL1_CLKPOL                      ((uint16_t)0x0010U) /* Clock Polarity */
#define SPI_CTRL1_CLKPHA                      ((uint16_t)0x0020U) /* Clock Phase */

#define SPI_CTRL1_MSEL                        ((uint16_t)0x0040U) /* Master Selection */
#define SPI_CTRL1_LSBFF                       ((uint16_t)0x0080U) /* Frame Format */
#define SPI_CTRL1_DATFF                       ((uint16_t)0x0100U) /* Data Frame Format */
#define SPI_CTRL1_CRCNEXT                     ((uint16_t)0x0200U) /* Transmit CRC next Software slave management */
#define SPI_CTRL1_SSOEN                       ((uint16_t)0x0400U) /* SS Output Enable */
#define SPI_CTRL1_SSEL                        ((uint16_t)0x0800U) /* Internal slave select  */
#define SPI_CTRL1_SSMEN                       ((uint16_t)0x1000U) /* Software slave management */
#define SPI_CTRL1_RONLY                       ((uint16_t)0x2000U) /* Receive only  */
#define SPI_CTRL1_BIDIROEN                    ((uint16_t)0x4000U) /* Output enable in bidirectional mode */
#define SPI_CTRL1_BIDIRMODE                   ((uint16_t)0x8000U) /* Bidirectional data mode enable */

/** Bit definition for SPI_CTRL2 register **/
#define SPI_CTRL2_SPIEN                       ((uint16_t)0x0001U) /* SPI enable */
#define SPI_CTRL2_RDMAEN                      ((uint16_t)0x0002U) /* Rx buffer DMA enable */
#define SPI_CTRL2_TDMAEN                      ((uint16_t)0x0004U) /* Tx buffer DMA enable */
#define SPI_CTRL2_CRCEN                       ((uint16_t)0x0008U) /* Hardware CRC calculation enable */
#define SPI_CTRL2_TEINTEN                     ((uint16_t)0x0010U) /* Tx buffer empty interrupt enable */
#define SPI_CTRL2_RNEINTEN                    ((uint16_t)0x0020U) /* RX buffer not empty interrupt enable */
#define SPI_CTRL2_ERRINTEN                    ((uint16_t)0x0040U) /* Error interrupt enable */
#define SPI_CTRL2_NSSPOL                      ((uint16_t)0x0080U) /* NSS polarity control */
#define SPI_CTRL2_CRCSTOP                     ((uint16_t)0x2000U) /* CRC stop calculation enable */
#define SPI_CTRL2_DATFF9                      ((uint16_t)0x8000U) /* 9-bit data frame format enable */


/** Bit definition for SPI_STS register **/
#define SPI_STS_TE                            ((uint16_t)0x0001U) /* Transmit buffer Empty */
#define SPI_STS_RNE                           ((uint16_t)0x0002U) /* Receive buffer Not Empty */
#define SPI_STS_BUSY                          ((uint16_t)0x0004U) /* Busy flag */
#define SPI_STS_CRCERR                        ((uint16_t)0x0008U) /* CRC Error flag */
#define SPI_STS_MODERR                        ((uint16_t)0x0010U) /* Mode fault */
#define SPI_STS_OVER                          ((uint16_t)0x0020U) /* Overrun flag */
#define SPI_STS_UNDER                         ((uint16_t)0x0040U) /* Underrun flag */
#define SPI_STS_CHSIDE                        ((uint16_t)0x0080U) /* Channel side */

/** Bit definition for SPI_DAT register **/
#define SPI_DAT_DAT                           ((uint16_t)0xFFFFU) /* Data Register */

/** Bit definition for SPI_CRCTDAT register **/
#define SPI_CRCTDAT_CRCTDAT                   ((uint16_t)0xFFFFU) /* Tx CRC Register */

/** Bit definition for SPI_CRCRDAT register **/
#define SPI_CRCRDAT_CRCRDAT                   ((uint16_t)0xFFFFU) /* Rx CRC Register */

/** Bit definition for SPI_CRCPOLY register **/
#define SPI_CRCPOLY_CRCPOLY                   ((uint16_t)0xFFFFU) /* CRC polynomial register */

/** Bit definition for SPI_I2SCFG register **/
#define SPI_I2SCFG_I2SEN                      ((uint16_t)0x0001U) /* I2S Enable */
#define SPI_I2SCFG_MODSEL                     ((uint16_t)0x0002U) /* I2S mode selection */
#define SPI_I2SCFG_STDSEL                     ((uint16_t)0x000CU) /* STDSEL[1:0] bits (I2S standard selection) */
#define SPI_I2SCFG_STDSEL0                    ((uint16_t)0x0004U) /* Bit 0 */
#define SPI_I2SCFG_STDSEL1                    ((uint16_t)0x0008U) /* Bit 1 */
#define SPI_I2SCFG_MODCFG                     ((uint16_t)0x0030U) /* MODCFG[1:0] bits (I2S configuration mode) */
#define SPI_I2SCFG_MODCFG0                    ((uint16_t)0x0010U) /* Bit 0 */
#define SPI_I2SCFG_MODCFG1                    ((uint16_t)0x0020U) /* Bit 1 */
#define SPI_I2SCFG_TDATLEN                    ((uint16_t)0x00C0U) /* TDATLEN[1:0] bits (Data length to be transferred) */
#define SPI_I2SCFG_TDATLEN0                   ((uint16_t)0x0040U) /* Bit 0 */
#define SPI_I2SCFG_TDATLEN1                   ((uint16_t)0x0080U) /* Bit 1 */
#define SPI_I2SCFG_CHBITS                     ((uint16_t)0x0100U) /* Channel length (number of bits per audio channel) */
#define SPI_I2SCFG_PCMFSYNC                   ((uint16_t)0x0200U) /* PCM frame synchronization */
#define SPI_I2SCFG_CLKPOL                     ((uint16_t)0x0400U) /* steady state clock polarity */
#define SPI_I2SCFG_PCMBYPASS                  ((uint16_t)0x0800U) /* pcm long for 13bit is bypass */

/** Bit definition for SPI_I2SPREDIV register **/
#define SPI_I2SPREDIV_LDIV                    ((uint16_t)0x03FFU) /* I2S Linear prescaler */
#define SPI_I2SPREDIV_ODDEVEN                 ((uint16_t)0x0400U) /* Odd factor for the prescaler */
#define SPI_I2SPREDIV_MCLKOEN                 ((uint16_t)0x0800U) /* Master Clock Output Enable */

/** Bit definition for SPI_CR3 register **/
#define SPI_CTRL3_DELAYTIME                   ((uint16_t)0x000FU) /* CTRL[3:0] bits (Clock Sample Delay Register) */
#define SPI_CTRL3_DELAYTIME0                  ((uint16_t)0x0001U) /* Bit 0 */
#define SPI_CTRL3_DELAYTIME1                  ((uint16_t)0x0002U) /* Bit 1 */
#define SPI_CTRL3_DELAYTIME2                  ((uint16_t)0x0004U) /* Bit 2 */
#define SPI_CTRL3_DELAYTIME3                  ((uint16_t)0x0008U) /* Bit 3 */


/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/

/** Bit definition for I2C_CTRL1 register **/
#define I2C_CTRL1_EN       ((uint32_t)0x00000001U) /* Peripheral Enable */
#define I2C_CTRL1_SMBMODE  ((uint32_t)0x00000002U) /* SMBus Mode */
#define I2C_CTRL1_SMBTYPE  ((uint32_t)0x00000004U) /* SMBus Type */
#define I2C_CTRL1_ARPEN    ((uint32_t)0x00000008U) /* ARP Enable */
#define I2C_CTRL1_PECEN    ((uint32_t)0x00000010U) /* PEC Enable */
#define I2C_CTRL1_GCEN     ((uint32_t)0x00000020U) /* General Call Enable */
#define I2C_CTRL1_NOEXTEND ((uint32_t)0x00000040U) /* Clock Stretching Disable (Slave mode) */
#define I2C_CTRL1_STARTGEN ((uint32_t)0x00000080U) /* Start Generation */
#define I2C_CTRL1_STOPGEN  ((uint32_t)0x00000100U) /* Stop Generation */
#define I2C_CTRL1_ACKEN    ((uint32_t)0x00000200U) /* Acknowledge Enable */
#define I2C_CTRL1_ACKPOS   ((uint32_t)0x00000400U) /* Acknowledge/PEC Position (for data reception) */
#define I2C_CTRL1_PEC      ((uint32_t)0x00000800U) /* Packet Error Checking */
#define I2C_CTRL1_SMBALERT ((uint32_t)0x00001000U) /* SMBus Alert */
#define I2C_CTRL1_SWRESET  ((uint32_t)0x00002000U) /* Software Reset */
#define I2C_CTRL1_DATACKTC ((uint32_t)0x00080000U) /* DATA and ACK timing conctrl in slaver receive mode*/

#define I2C_CTRL1_HTOSEL   ((uint32_t)0x18000000U) /* high timeout threshold selection */
#define I2C_CTRL1_HTOSEL_0 ((uint32_t)0x08000000U) /* Bit 0 */
#define I2C_CTRL1_HTOSEL_1 ((uint32_t)0x10000000U) /* Bit 1 */

#define I2C_CTRL1_LTOSEL   ((uint32_t)0x60000000U) /* low timeout threshold selection */
#define I2C_CTRL1_LTOSEL_0 ((uint32_t)0x20000000U) /* Bit 0 */
#define I2C_CTRL1_LTOSEL_1 ((uint32_t)0x40000000U) /* Bit 1 */

#define I2C_CTRL1_STPBP    ((uint32_t)0x80000000)  /* stop bypass */

/** Bit definition for I2C_CTRL2 register **/
#define I2C_CTRL2_CLKFREQ   ((uint32_t)0x0000007FU) /* FREQ[6:0] bits (Peripheral Clock Frequency) */
#define I2C_CTRL2_CLKFREQ_0 ((uint32_t)0x00000001U) /* Bit 0 */
#define I2C_CTRL2_CLKFREQ_1 ((uint32_t)0x00000002U) /* Bit 1 */
#define I2C_CTRL2_CLKFREQ_2 ((uint32_t)0x00000004U) /* Bit 2 */
#define I2C_CTRL2_CLKFREQ_3 ((uint32_t)0x00000008U) /* Bit 3 */
#define I2C_CTRL2_CLKFREQ_4 ((uint32_t)0x00000010U) /* Bit 4 */
#define I2C_CTRL2_CLKFREQ_5 ((uint32_t)0x00000020U) /* Bit 5 */
#define I2C_CTRL2_CLKFREQ_6 ((uint32_t)0x00000040U) /* Bit 6 */

#define I2C_CTRL2_DMALAST  ((uint32_t)0x00000100U) /* DMA Last Transfer */
#define I2C_CTRL2_BUFINTEN ((uint32_t)0x00001000U) /* Buffer Interrupt Enable */
#define I2C_CTRL2_EVTINTEN ((uint32_t)0x00002000U) /* Event Interrupt Enable */
#define I2C_CTRL2_ERRINTEN ((uint32_t)0x00004000U) /* Error Interrupt Enable */
#define I2C_CTRL2_DMAEN    ((uint32_t)0x00008000U) /* DMA Requests Enable */

#define I2C_CTRL2_SDALTOINTEN    ((uint32_t)0x04000000U) /* SDA low timeout error interrupt enable */
#define I2C_CTRL2_SCLHTOINTEN    ((uint32_t)0x08000000U) /* SCL high timeout error interrupt enable */
#define I2C_CTRL2_SCLLTOINTEN    ((uint32_t)0x10000000U) /* SCL low timeout error interrupt enable */
#define I2C_CTRL2_HTOEN          ((uint32_t)0x20000000U) /* high timeout function enable */
#define I2C_CTRL2_LTOEN          ((uint32_t)0x40000000U) /* low timeout function enable */

/** Bit definition for I2C_OADDR1 register **/
#define I2C_OADDR1_ADDR1_7 ((uint16_t)0x00FEU) /* Interface Address */
#define I2C_OADDR1_ADDR8_9 ((uint16_t)0x0300U) /* Interface Address */

#define I2C_OADDR1_ADDR0 ((uint16_t)0x0001U) /* Bit 0 */
#define I2C_OADDR1_ADDR1 ((uint16_t)0x0002U) /* Bit 1 */
#define I2C_OADDR1_ADDR2 ((uint16_t)0x0004U) /* Bit 2 */
#define I2C_OADDR1_ADDR3 ((uint16_t)0x0008U) /* Bit 3 */
#define I2C_OADDR1_ADDR4 ((uint16_t)0x0010U) /* Bit 4 */
#define I2C_OADDR1_ADDR5 ((uint16_t)0x0020U) /* Bit 5 */
#define I2C_OADDR1_ADDR6 ((uint16_t)0x0040U) /* Bit 6 */
#define I2C_OADDR1_ADDR7 ((uint16_t)0x0080U) /* Bit 7 */
#define I2C_OADDR1_ADDR8 ((uint16_t)0x0100U) /* Bit 8 */
#define I2C_OADDR1_ADDR9 ((uint16_t)0x0200U) /* Bit 9 */

#define I2C_OADDR1_ADDRMODE ((uint16_t)0x8000U) /* Addressing Mode (Slave mode) */

/** Bit definition for I2C_OADDR2 register **/
#define I2C_OADDR2_DUALEN ((uint8_t)0x01U) /* Dual addressing mode enable */
#define I2C_OADDR2_ADDR2  ((uint8_t)0xFEU) /* Interface address */

/** Bit definition for I2C_DAT register **/
#define I2C_DAT_DATA ((uint8_t)0xFFU) /* 8-bit Data Register */

/** Bit definition for I2C_STS1 register **/
#define I2C_STS1_STARTBF  ((uint16_t)0x0001U) /* Start Bit (Master mode) */
#define I2C_STS1_ADDRF    ((uint16_t)0x0002U) /* Address sent (master mode)/matched (slave mode) */
#define I2C_STS1_BSF      ((uint16_t)0x0004U) /* Byte Transfer Finished */
#define I2C_STS1_STOPF    ((uint16_t)0x0008U) /* Stop detection (Slave mode) */
#define I2C_STS1_RXDATNE  ((uint16_t)0x0010U) /* Data Register not Empty (receivers) */
#define I2C_STS1_TXDATE   ((uint16_t)0x0020U) /* Data Register Empty (transmitters) */
#define I2C_STS1_ADDR10F  ((uint16_t)0x0040U) /* 10-bit header sent (Master mode) */

#define I2C_STS1_ACKFAIL  ((uint16_t)0x0100U) /* Acknowledge Failure */
#define I2C_STS1_ARLOST   ((uint16_t)0x0200U) /* Arbitration Lost (master mode) */
#define I2C_STS1_BUSERR   ((uint16_t)0x0400U) /* Bus Error */
#define I2C_STS1_OVERRUN  ((uint16_t)0x0800U) /* Overrun/Underrun */
#define I2C_STS1_PECERR   ((uint16_t)0x1000U) /* PEC Error in reception */
#define I2C_STS1_TIMEOUT  ((uint16_t)0x2000U) /* Timeout */
#define I2C_STS1_SMBALERT ((uint16_t)0x4000U) /* SMBus Alert */

#define I2C_STS1_SDALTO   ((uint32_t)0x00800000U) /* SDA low timeout error */
#define I2C_STS1_SCLHTO   ((uint32_t)0x01000000U) /* SCL high timeout error */
#define I2C_STS1_SCLLTO   ((uint32_t)0x02000000U) /* SCL low timeout error */

/** Bit definition for I2C_STS2 register **/

#define I2C_STS2_BUSY      ((uint16_t)0x0001U) /* Bus Busy */
#define I2C_STS2_MSMODE    ((uint16_t)0x0002U) /* Master/Slave */
#define I2C_STS2_TRF       ((uint16_t)0x0004U) /* Transmitter/Receiver */

#define I2C_STS2_GCALLADDR ((uint16_t)0x0010U) /* General Call Address (Slave mode) */
#define I2C_STS2_DUALFLAG  ((uint16_t)0x0020U) /* Dual Flag (Slave mode) */
#define I2C_STS2_SMBDADDR  ((uint16_t)0x0040U) /* SMBus Device Default Address (Slave mode) */
#define I2C_STS2_SMBHADDR  ((uint16_t)0x0080U) /* SMBus Host Header (Slave mode) */

#define I2C_STS2_PECVAL    ((uint16_t)0xFF00U) /* Packet Error Checking Register */

/** Bit definition for I2C_CLKCTRL register **/
#define I2C_CLKCTRL_CLKCTRL ((uint16_t)0x0FFFU) /* Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CLKCTRL_FSMODE  ((uint16_t)0x4000U) /* I2C Master Mode Selection */
#define I2C_CLKCTRL_DUTY    ((uint16_t)0x8000U) /* Fast Mode Duty Cycle */

/**  Bit definition for I2C_TMRISE register  ***/
#define  I2C_TMRISE_TMRISE   ((uint8_t)0x3FU)               /* Maximum Rise Time in Fast/Standard mode (Master mode) */

/**  Bit definition for I2C_GFLTRCTRL register  ***/
#define  I2C_GFLTRCTRL_SDADFW   ((uint16_t)0x000FU) /* SDA digital gfilter width selection */
#define  I2C_GFLTRCTRL_SCLDFW   ((uint16_t)0x00F0U) /* SCL digital gfilter width selection */

#define  I2C_GFLTRCTRL_SDAAFW   ((uint16_t)0x0300U) /* SDA analog gfilter width selection */
#define  I2C_GFLTRCTRL_SDAAFW_0 ((uint16_t)0x0100U) /* Bit 0 */
#define  I2C_GFLTRCTRL_SDAAFW_1 ((uint16_t)0x0200U) /* Bit 1 */

#define  I2C_GFLTRCTRL_SDAAFENN ((uint16_t)0x0800U) /* SDA analog gfilter enable */

#define  I2C_GFLTRCTRL_SCLAFW   ((uint16_t)0x3000U) /* SCL analog gfilter width selection */
#define  I2C_GFLTRCTRL_SCLAFW_0 ((uint16_t)0x1000U) /* Bit 0 */
#define  I2C_GFLTRCTRL_SCLAFW_1 ((uint16_t)0x2000U) /* Bit 1 */

#define  I2C_GFLTRCTRL_SCLAFENN ((uint16_t)0x8000U) /* SCL analog gfilter enable */


/****       Controller Area Network     ****/
/**** CAN control and status registers ****/
/**  Bit definition for CAN_MCTRL register  ****/
#define CAN_MCTRL_INIRQ                         ((uint16_t)0x0001U) /* Initialization Request */
#define CAN_MCTRL_SLPRQ                         ((uint16_t)0x0002U) /* Sleep Mode Request */
#define CAN_MCTRL_TXFP                          ((uint16_t)0x0004U) /* Transmit DATFIFO Priority */
#define CAN_MCTRL_RFLM                          ((uint16_t)0x0008U) /* Receive DATFIFO Locked Mode */
#define CAN_MCTRL_NART                          ((uint16_t)0x0010U) /* No Automatic Retransmission */
#define CAN_MCTRL_AWKUM                         ((uint16_t)0x0020U) /* Automatic Wakeup Mode */
#define CAN_MCTRL_ABOM                          ((uint16_t)0x0040U) /* Automatic Bus-Off Management */
#define CAN_MCTRL_TTCM                          ((uint16_t)0x0080U) /* Time Triggered Communication Mode */
#define CAN_MCTRL_MRST                          ((uint16_t)0x8000U) /* CAN software master reset */
#define CAN_MCTRL_DBGF                          ((uint32_t)0x00010000U) /* CAN Debug freeze */

/**  Bit definition for CAN_MSTS register  ****/
#define CAN_MSTS_INIAK                          ((uint16_t)0x0001U) /* Initialization Acknowledge */
#define CAN_MSTS_SLPAK                          ((uint16_t)0x0002U) /* Sleep Acknowledge */
#define CAN_MSTS_ERRINT                         ((uint16_t)0x0004U) /* Error Interrupt */
#define CAN_MSTS_WKUINT                         ((uint16_t)0x0008U) /* Wakeup Interrupt */
#define CAN_MSTS_SLAKINT                        ((uint16_t)0x0010U) /* Sleep Acknowledge Interrupt */
#define CAN_MSTS_TXMD                           ((uint16_t)0x0100U) /* Transmit Mode */
#define CAN_MSTS_RXMD                           ((uint16_t)0x0200U) /* Receive Mode */
#define CAN_MSTS_LSMP                           ((uint16_t)0x0400U) /* Last Sample Point */
#define CAN_MSTS_RXS                            ((uint16_t)0x0800U) /* CAN Rx Signal */

/**  Bit definition for CAN_TSTS register  ****/
#define CAN_TSTS_RQCPM0                         ((uint32_t)0x00000001U) /* Request Completed Mailbox0 */
#define CAN_TSTS_TXOKM0                         ((uint32_t)0x00000002U) /* Transmission OK of Mailbox0 */
#define CAN_TSTS_ALSTM0                         ((uint32_t)0x00000004U) /* Arbitration Lost for Mailbox0 */
#define CAN_TSTS_TERRM0                         ((uint32_t)0x00000008U) /* Transmission Error of Mailbox0 */
#define CAN_TSTS_ABRQM0                         ((uint32_t)0x00000080U) /* Abort Request for Mailbox0 */
#define CAN_TSTS_RQCPM1                         ((uint32_t)0x00000100U) /* Request Completed Mailbox1 */
#define CAN_TSTS_TXOKM1                         ((uint32_t)0x00000200U) /* Transmission OK of Mailbox1 */
#define CAN_TSTS_ALSTM1                         ((uint32_t)0x00000400U) /* Arbitration Lost for Mailbox1 */
#define CAN_TSTS_TERRM1                         ((uint32_t)0x00000800U) /* Transmission Error of Mailbox1 */
#define CAN_TSTS_ABRQM1                         ((uint32_t)0x00008000U) /* Abort Request for Mailbox 1 */
#define CAN_TSTS_RQCPM2                         ((uint32_t)0x00010000U) /* Request Completed Mailbox2 */
#define CAN_TSTS_TXOKM2                         ((uint32_t)0x00020000U) /* Transmission OK of Mailbox 2 */
#define CAN_TSTS_ALSTM2                         ((uint32_t)0x00040000U) /* Arbitration Lost for mailbox 2 */
#define CAN_TSTS_TERRM2                         ((uint32_t)0x00080000U) /* Transmission Error of Mailbox 2 */
#define CAN_TSTS_ABRQM2                         ((uint32_t)0x00800000U) /* Abort Request for Mailbox 2 */

#define CAN_TSTS_CODE                           ((uint32_t)0x03000000U) /* Mailbox Code */
#define CAN_TSTS_CODE_0                         ((uint32_t)0x01000000U) /* Bit 0 */
#define CAN_TSTS_CODE_1                         ((uint32_t)0x02000000U) /* Bit 1 */

#define CAN_TSTS_TMEM  ((uint32_t)0x1C000000U) /* TME[2:0] bits */
#define CAN_TSTS_TMEM0 ((uint32_t)0x04000000U) /* Transmit Mailbox 0 Empty */
#define CAN_TSTS_TMEM1 ((uint32_t)0x08000000U) /* Transmit Mailbox 1 Empty */
#define CAN_TSTS_TMEM2 ((uint32_t)0x10000000U) /* Transmit Mailbox 2 Empty */

#define CAN_TSTS_LOWM  ((uint32_t)0xE0000000U) /* LOW[2:0] bits */
#define CAN_TSTS_LOWM0 ((uint32_t)0x20000000U) /* Lowest Priority Flag for Mailbox 0 */
#define CAN_TSTS_LOWM1 ((uint32_t)0x40000000U) /* Lowest Priority Flag for Mailbox 1 */
#define CAN_TSTS_LOWM2 ((uint32_t)0x80000000U) /* Lowest Priority Flag for Mailbox 2 */

/** Bit definition for CAN_RFF0 register **/
#define CAN_RFF0_FFMP0      ((uint8_t)0x03U) /* DATFIFO 0 Message Pending */
#define CAN_RFF0_FFMP0_0    ((uint8_t)0x01U) /* Bit 0 */
#define CAN_RFF0_FFMP0_1    ((uint8_t)0x02U) /* Bit 1 */

#define CAN_RFF0_FFULL0 ((uint8_t)0x08U) /* DATFIFO 0 Full */
#define CAN_RFF0_FFOVR0 ((uint8_t)0x10U) /* DATFIFO 0 Overrun */
#define CAN_RFF0_RFFOM0 ((uint8_t)0x20U) /* Release DATFIFO 0 Output Mailbox */

/** Bit definition for CAN_RFF1 register **/
#define CAN_RFF1_FFMP1      ((uint8_t)0x03U) /* DATFIFO 1 Message Pending */
#define CAN_RFF1_FFMP1_0    ((uint8_t)0x01U) /* Bit 0 */
#define CAN_RFF1_FFMP1_1    ((uint8_t)0x02U) /* Bit 1 */

#define CAN_RFF1_FFULL1     ((uint8_t)0x08U) /* DATFIFO 1 Full */
#define CAN_RFF1_FFOVR1     ((uint8_t)0x10U) /* DATFIFO 1 Overrun */
#define CAN_RFF1_RFFOM1     ((uint8_t)0x20U) /* Release DATFIFO 1 Output Mailbox */

/** Bit definition for CAN_INTE register **/
#define CAN_INTE_TMEITE  ((uint32_t)0x00000001U) /* Transmit Mailbox Empty Interrupt Enable */
#define CAN_INTE_FMPITE0 ((uint32_t)0x00000002U) /* DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE0  ((uint32_t)0x00000004U) /* DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE0 ((uint32_t)0x00000008U) /* DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_FMPITE1 ((uint32_t)0x00000010U) /* DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE1  ((uint32_t)0x00000020U) /* DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE1 ((uint32_t)0x00000040U) /* DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_EWGITE  ((uint32_t)0x00000100U) /* Error Warning Interrupt Enable */
#define CAN_INTE_EPVITE  ((uint32_t)0x00000200U) /* Error Passive Interrupt Enable */
#define CAN_INTE_BOFITE  ((uint32_t)0x00000400U) /* Bus-Off Interrupt Enable */
#define CAN_INTE_LECITE  ((uint32_t)0x00000800U) /* Last Error Code Interrupt Enable */
#define CAN_INTE_ERRITE  ((uint32_t)0x00008000U) /* Error Interrupt Enable */
#define CAN_INTE_WKUITE  ((uint32_t)0x00010000U) /* Wakeup Interrupt Enable */
#define CAN_INTE_SLKITE  ((uint32_t)0x00020000U) /* Sleep Interrupt Enable */

/** Bit definition for CAN_ESTS register **/
#define CAN_ESTS_EWGFL ((uint32_t)0x00000001U) /* Error Warning Flag */
#define CAN_ESTS_EPVFL ((uint32_t)0x00000002U) /* Error Passive Flag */
#define CAN_ESTS_BOFFL ((uint32_t)0x00000004U) /* Bus-Off Flag */

#define CAN_ESTS_LEC   ((uint32_t)0x00000070U) /* LEC[2:0] bits (Last Error Code) */
#define CAN_ESTS_LEC_0 ((uint32_t)0x00000010U) /* Bit 0 */
#define CAN_ESTS_LEC_1 ((uint32_t)0x00000020U) /* Bit 1 */
#define CAN_ESTS_LEC_2 ((uint32_t)0x00000040U) /* Bit 2 */

#define CAN_ESTS_TXEC  ((uint32_t)0x00FF0000U) /* Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_ESTS_RXEC  ((uint32_t)0xFF000000U) /* Receive Error Counter */

/** Bit definition for CAN_BTIM register **/
#define CAN_BTIM_BRTP   ((uint32_t)0x000003FFU) /* Baud Rate Prescaler */

#define CAN_BTIM_TBS1   ((uint32_t)0x000F0000U) /* Time Segment 1 */
#define CAN_BTIM_TBS1_0 ((uint32_t)0x00010000U) /* Bit 0 */
#define CAN_BTIM_TBS1_1 ((uint32_t)0x00020000U) /* Bit 1 */
#define CAN_BTIM_TBS1_2 ((uint32_t)0x00040000U) /* Bit 2 */
#define CAN_BTIM_TBS1_3 ((uint32_t)0x00080000U) /* Bit 3 */

#define CAN_BTIM_TBS2   ((uint32_t)0x00700000U) /* Time Segment 2 */
#define CAN_BTIM_TBS2_0 ((uint32_t)0x00100000U) /* Bit 0 */
#define CAN_BTIM_TBS2_1 ((uint32_t)0x00200000U) /* Bit 1 */
#define CAN_BTIM_TBS2_2 ((uint32_t)0x00400000U) /* Bit 2 */

#define CAN_BTIM_RSJW   ((uint32_t)0x03000000U) /* Resynchronization Jump Width */
#define CAN_BTIM_RSJW_0 ((uint32_t)0x01000000U) /* Bit 0 */
#define CAN_BTIM_RSJW_1 ((uint32_t)0x02000000U) /* Bit 1 */

#define CAN_BTIM_LBM  ((uint32_t)0x40000000U) /* Loop Back Mode (Debug) */
#define CAN_BTIM_SLM  ((uint32_t)0x80000000U) /* Silent Mode */

/*** Mailbox registers ***/
/** Bit definition for CAN_TMI0 register **/
#define CAN_TMI0_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI0_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI0_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI0_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_TMI0_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT0 register **/
#define CAN_TMDT0_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT0_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT0_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL0 register **/
#define CAN_TMDL0_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL0_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL0_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL0_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH0 register **/
#define CAN_TMDH0_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH0_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH0_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH0_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_TMI1 register **/
#define CAN_TMI1_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI1_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI1_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI1_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_TMI1_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT1 register **/
#define CAN_TMDT1_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT1_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT1_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL1 register **/
#define CAN_TMDL1_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL1_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL1_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL1_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH1 register **/
#define CAN_TMDH1_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH1_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH1_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH1_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_TMI2 register **/
#define CAN_TMI2_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI2_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI2_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI2_EXTID ((uint32_t)0x001FFFF8U) /* Extended identifier */
#define CAN_TMI2_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT2 register **/
#define CAN_TMDT2_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT2_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT2_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL2 register **/
#define CAN_TMDL2_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL2_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL2_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL2_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH2 register **/
#define CAN_TMDH2_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH2_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH2_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH2_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_RMI0 register **/
#define CAN_RMI0_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_RMI0_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_RMI0_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_RMI0_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_RMDT0 register **/
#define CAN_RMDT0_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_RMDT0_FMI  ((uint32_t)0x0000FF00U) /* Filter Match Index */
#define CAN_RMDT0_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_RMDL0 register **/
#define CAN_RMDL0_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_RMDL0_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_RMDL0_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_RMDL0_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_RMDH0 register **/
#define CAN_RMDH0_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_RMDH0_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_RMDH0_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_RMDH0_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_RMI1 register **/
#define CAN_RMI1_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_RMI1_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_RMI1_EXTID ((uint32_t)0x001FFFF8U) /* Extended identifier */
#define CAN_RMI1_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_RMDT1 register **/
#define CAN_RMDT1_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_RMDT1_FMI  ((uint32_t)0x0000FF00U) /* Filter Match Index */
#define CAN_RMDT1_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_RMDL1 register **/
#define CAN_RMDL1_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_RMDL1_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_RMDL1_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_RMDL1_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_RMDH1 register **/
#define CAN_RMDH1_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_RMDH1_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_RMDH1_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_RMDH1_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/*** CAN filter registers ***/
/** Bit definition for CAN_FMC register **/
#define CAN_FMC_FINITM ((uint8_t)0x01U) /* Filter Init Mode */

/**  Bit definition for CAN_FM1 register  ***/
#define CAN_FM1_FB                              ((uint16_t)0x3FFFU) /* Filter Mode */
#define CAN_FM1_FB0                             ((uint16_t)0x0001U) /* Filter Init Mode bit 0 */
#define CAN_FM1_FB1                             ((uint16_t)0x0002U) /* Filter Init Mode bit 1 */
#define CAN_FM1_FB2                             ((uint16_t)0x0004U) /* Filter Init Mode bit 2 */
#define CAN_FM1_FB3                             ((uint16_t)0x0008U) /* Filter Init Mode bit 3 */
#define CAN_FM1_FB4                             ((uint16_t)0x0010U) /* Filter Init Mode bit 4 */
#define CAN_FM1_FB5                             ((uint16_t)0x0020U) /* Filter Init Mode bit 5 */
#define CAN_FM1_FB6                             ((uint16_t)0x0040U) /* Filter Init Mode bit 6 */
#define CAN_FM1_FB7                             ((uint16_t)0x0080U) /* Filter Init Mode bit 7 */
#define CAN_FM1_FB8                             ((uint16_t)0x0100U) /* Filter Init Mode bit 8 */
#define CAN_FM1_FB9                             ((uint16_t)0x0200U) /* Filter Init Mode bit 9 */
#define CAN_FM1_FB10                            ((uint16_t)0x0400U) /* Filter Init Mode bit 10 */
#define CAN_FM1_FB11                            ((uint16_t)0x0800U) /* Filter Init Mode bit 11 */
#define CAN_FM1_FB12                            ((uint16_t)0x1000U) /* Filter Init Mode bit 12 */
#define CAN_FM1_FB13                            ((uint16_t)0x2000U) /* Filter Init Mode bit 13 */

/**  Bit definition for CAN_FS1 register  ***/
#define CAN_FS1_FSC                             ((uint16_t)0x3FFFU) /* Filter Scale Configuration */
#define CAN_FS1_FSC0                            ((uint16_t)0x0001U) /* Filter Scale Configuration bit 0 */
#define CAN_FS1_FSC1                            ((uint16_t)0x0002U) /* Filter Scale Configuration bit 1 */
#define CAN_FS1_FSC2                            ((uint16_t)0x0004U) /* Filter Scale Configuration bit 2 */
#define CAN_FS1_FSC3                            ((uint16_t)0x0008U) /* Filter Scale Configuration bit 3 */
#define CAN_FS1_FSC4                            ((uint16_t)0x0010U) /* Filter Scale Configuration bit 4 */
#define CAN_FS1_FSC5                            ((uint16_t)0x0020U) /* Filter Scale Configuration bit 5 */
#define CAN_FS1_FSC6                            ((uint16_t)0x0040U) /* Filter Scale Configuration bit 6 */
#define CAN_FS1_FSC7                            ((uint16_t)0x0080U) /* Filter Scale Configuration bit 7 */
#define CAN_FS1_FSC8                            ((uint16_t)0x0100U) /* Filter Scale Configuration bit 8 */
#define CAN_FS1_FSC9                            ((uint16_t)0x0200U) /* Filter Scale Configuration bit 9 */
#define CAN_FS1_FSC10                           ((uint16_t)0x0400U) /* Filter Scale Configuration bit 10 */
#define CAN_FS1_FSC11                           ((uint16_t)0x0800U) /* Filter Scale Configuration bit 11 */
#define CAN_FS1_FSC12                           ((uint16_t)0x1000U) /* Filter Scale Configuration bit 12 */
#define CAN_FS1_FSC13                           ((uint16_t)0x2000U) /* Filter Scale Configuration bit 13 */

/**  Bit definition for CAN_FFA1 register  ***/
#define CAN_FFA1_FAF                            ((uint16_t)0x3FFFU) /* Filter DATFIFO Assignment */
#define CAN_FFA1_FAF0                           ((uint16_t)0x0001U) /* Filter DATFIFO Assignment for Filter 0 */
#define CAN_FFA1_FAF1                           ((uint16_t)0x0002U) /* Filter DATFIFO Assignment for Filter 1 */
#define CAN_FFA1_FAF2                           ((uint16_t)0x0004U) /* Filter DATFIFO Assignment for Filter 2 */
#define CAN_FFA1_FAF3                           ((uint16_t)0x0008U) /* Filter DATFIFO Assignment for Filter 3 */
#define CAN_FFA1_FAF4                           ((uint16_t)0x0010U) /* Filter DATFIFO Assignment for Filter 4 */
#define CAN_FFA1_FAF5                           ((uint16_t)0x0020U) /* Filter DATFIFO Assignment for Filter 5 */
#define CAN_FFA1_FAF6                           ((uint16_t)0x0040U) /* Filter DATFIFO Assignment for Filter 6 */
#define CAN_FFA1_FAF7                           ((uint16_t)0x0080U) /* Filter DATFIFO Assignment for Filter 7 */
#define CAN_FFA1_FAF8                           ((uint16_t)0x0100U) /* Filter DATFIFO Assignment for Filter 8 */
#define CAN_FFA1_FAF9                           ((uint16_t)0x0200U) /* Filter DATFIFO Assignment for Filter 9 */
#define CAN_FFA1_FAF10                          ((uint16_t)0x0400U) /* Filter DATFIFO Assignment for Filter 10 */
#define CAN_FFA1_FAF11                          ((uint16_t)0x0800U) /* Filter DATFIFO Assignment for Filter 11 */
#define CAN_FFA1_FAF12                          ((uint16_t)0x1000U) /* Filter DATFIFO Assignment for Filter 12 */
#define CAN_FFA1_FAF13                          ((uint16_t)0x2000U) /* Filter DATFIFO Assignment for Filter 13 */

/**  Bit definition for CAN_FA1 register  ***/
#define CAN_FA1_FAC                             ((uint16_t)0x3FFFU) /* Filter Active */
#define CAN_FA1_FAC0                            ((uint16_t)0x0001U) /* Filter 0 Active */
#define CAN_FA1_FAC1                            ((uint16_t)0x0002U) /* Filter 1 Active */
#define CAN_FA1_FAC2                            ((uint16_t)0x0004U) /* Filter 2 Active */
#define CAN_FA1_FAC3                            ((uint16_t)0x0008U) /* Filter 3 Active */
#define CAN_FA1_FAC4                            ((uint16_t)0x0010U) /* Filter 4 Active */
#define CAN_FA1_FAC5                            ((uint16_t)0x0020U) /* Filter 5 Active */
#define CAN_FA1_FAC6                            ((uint16_t)0x0040U) /* Filter 6 Active */
#define CAN_FA1_FAC7                            ((uint16_t)0x0080U) /* Filter 7 Active */
#define CAN_FA1_FAC8                            ((uint16_t)0x0100U) /* Filter 8 Active */
#define CAN_FA1_FAC9                            ((uint16_t)0x0200U) /* Filter 9 Active */
#define CAN_FA1_FAC10                           ((uint16_t)0x0400U) /* Filter 10 Active */
#define CAN_FA1_FAC11                           ((uint16_t)0x0800U) /* Filter 11 Active */
#define CAN_FA1_FAC12                           ((uint16_t)0x1000U) /* Filter 12 Active */
#define CAN_FA1_FAC13                           ((uint16_t)0x2000U) /* Filter 13 Active */

/**  Bit definition for CAN_F0R1 register  ***/
#define CAN_F0R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F0R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F0R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F0R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F0R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F0R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F0R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F0R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F0R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F0R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F0R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F0R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F0R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F0R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F0R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F0R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F0R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F0R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F0R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F0R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F0R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F0R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F0R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F0R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F0R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F0R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F0R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F0R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F0R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F0R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F0R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F0R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F1R1 register  ***/
#define CAN_F1R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F1R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F1R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F1R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F1R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F1R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F1R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F1R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F1R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F1R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F1R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F1R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F1R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F1R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F1R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F1R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F1R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F1R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F1R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F1R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F1R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F1R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F1R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F1R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F1R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F1R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F1R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F1R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F1R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F1R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F1R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F1R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F2R1 register  ***/
#define CAN_F2R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F2R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F2R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F2R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F2R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F2R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F2R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F2R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F2R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F2R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F2R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F2R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F2R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F2R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F2R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F2R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F2R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F2R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F2R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F2R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F2R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F2R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F2R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F2R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F2R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F2R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F2R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F2R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F2R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F2R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F2R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F2R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F3R1 register  ***/
#define CAN_F3R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F3R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F3R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F3R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F3R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F3R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F3R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F3R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F3R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F3R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F3R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F3R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F3R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F3R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F3R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F3R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F3R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F3R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F3R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F3R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F3R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F3R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F3R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F3R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F3R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F3R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F3R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F3R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F3R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F3R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F3R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F3R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F4R1 register  ***/
#define CAN_F4R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F4R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F4R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F4R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F4R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F4R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F4R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F4R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F4R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F4R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F4R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F4R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F4R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F4R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F4R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F4R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F4R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F4R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F4R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F4R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F4R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F4R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F4R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F4R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F4R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F4R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F4R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F4R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F4R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F4R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F4R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F4R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F5R1 register  ***/
#define CAN_F5R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F5R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F5R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F5R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F5R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F5R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F5R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F5R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F5R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F5R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F5R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F5R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F5R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F5R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F5R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F5R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F5R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F5R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F5R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F5R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F5R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F5R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F5R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F5R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F5R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F5R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F5R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F5R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F5R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F5R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F5R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F5R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F6R1 register  ***/
#define CAN_F6R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F6R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F6R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F6R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F6R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F6R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F6R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F6R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F6R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F6R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F6R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F6R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F6R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F6R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F6R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F6R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F6R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F6R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F6R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F6R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F6R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F6R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F6R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F6R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F6R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F6R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F6R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F6R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F6R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F6R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F6R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F6R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F7R1 register  ***/
#define CAN_F7R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F7R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F7R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F7R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F7R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F7R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F7R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F7R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F7R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F7R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F7R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F7R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F7R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F7R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F7R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F7R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F7R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F7R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F7R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F7R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F7R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F7R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F7R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F7R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F7R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F7R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F7R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F7R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F7R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F7R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F7R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F7R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F8R1 register  ***/
#define CAN_F8R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F8R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F8R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F8R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F8R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F8R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F8R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F8R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F8R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F8R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F8R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F8R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F8R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F8R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F8R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F8R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F8R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F8R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F8R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F8R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F8R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F8R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F8R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F8R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F8R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F8R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F8R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F8R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F8R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F8R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F8R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F8R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F9R1 register  ***/
#define CAN_F9R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F9R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F9R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F9R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F9R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F9R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F9R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F9R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F9R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F9R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F9R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F9R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F9R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F9R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F9R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F9R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F9R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F9R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F9R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F9R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F9R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F9R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F9R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F9R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F9R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F9R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F9R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F9R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F9R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F9R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F9R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F9R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F10R1 register  **/
#define CAN_F10R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F10R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F10R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F10R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F10R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F10R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F10R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F10R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F10R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F10R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F10R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F10R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F10R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F10R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F10R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F10R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F10R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F10R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F10R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F10R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F10R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F10R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F10R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F10R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F10R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F10R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F10R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F10R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F10R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F10R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F10R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F10R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F11R1 register  **/
#define CAN_F11R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F11R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F11R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F11R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F11R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F11R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F11R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F11R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F11R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F11R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F11R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F11R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F11R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F11R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F11R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F11R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F11R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F11R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F11R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F11R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F11R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F11R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F11R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F11R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F11R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F11R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F11R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F11R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F11R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F11R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F11R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F11R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F12R1 register  **/
#define CAN_F12R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F12R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F12R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F12R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F12R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F12R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F12R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F12R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F12R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F12R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F12R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F12R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F12R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F12R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F12R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F12R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F12R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F12R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F12R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F12R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F12R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F12R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F12R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F12R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F12R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F12R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F12R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F12R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F12R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F12R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F12R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F12R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F13R1 register  **/
#define CAN_F13R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F13R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F13R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F13R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F13R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F13R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F13R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F13R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F13R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F13R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F13R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F13R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F13R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F13R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F13R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F13R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F13R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F13R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F13R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F13R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F13R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F13R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F13R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F13R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F13R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F13R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F13R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F13R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F13R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F13R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F13R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F13R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F0R2 register  ***/
#define CAN_F0R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F0R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F0R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F0R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F0R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F0R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F0R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F0R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F0R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F0R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F0R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F0R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F0R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F0R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F0R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F0R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F0R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F0R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F0R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F0R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F0R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F0R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F0R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F0R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F0R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F0R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F0R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F0R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F0R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F0R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F0R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F0R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F1R2 register  ***/
#define CAN_F1R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F1R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F1R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F1R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F1R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F1R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F1R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F1R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F1R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F1R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F1R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F1R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F1R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F1R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F1R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F1R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F1R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F1R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F1R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F1R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F1R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F1R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F1R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F1R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F1R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F1R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F1R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F1R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F1R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F1R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F1R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F1R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F2R2 register  ***/
#define CAN_F2R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F2R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F2R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F2R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F2R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F2R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F2R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F2R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F2R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F2R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F2R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F2R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F2R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F2R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F2R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F2R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F2R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F2R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F2R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F2R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F2R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F2R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F2R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F2R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F2R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F2R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F2R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F2R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F2R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F2R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F2R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F2R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F3R2 register  ***/
#define CAN_F3R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F3R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F3R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F3R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F3R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F3R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F3R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F3R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F3R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F3R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F3R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F3R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F3R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F3R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F3R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F3R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F3R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F3R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F3R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F3R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F3R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F3R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F3R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F3R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F3R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F3R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F3R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F3R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F3R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F3R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F3R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F3R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F4R2 register  ***/
#define CAN_F4R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F4R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F4R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F4R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F4R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F4R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F4R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F4R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F4R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F4R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F4R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F4R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F4R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F4R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F4R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F4R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F4R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F4R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F4R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F4R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F4R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F4R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F4R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F4R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F4R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F4R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F4R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F4R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F4R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F4R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F4R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F4R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F5R2 register  ***/
#define CAN_F5R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F5R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F5R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F5R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F5R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F5R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F5R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F5R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F5R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F5R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F5R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F5R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F5R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F5R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F5R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F5R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F5R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F5R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F5R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F5R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F5R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F5R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F5R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F5R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F5R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F5R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F5R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F5R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F5R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F5R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F5R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F5R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F6R2 register  ***/
#define CAN_F6R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F6R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F6R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F6R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F6R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F6R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F6R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F6R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F6R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F6R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F6R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F6R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F6R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F6R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F6R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F6R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F6R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F6R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F6R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F6R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F6R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F6R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F6R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F6R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F6R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F6R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F6R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F6R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F6R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F6R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F6R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F6R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F7R2 register  ***/
#define CAN_F7R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F7R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F7R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F7R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F7R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F7R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F7R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F7R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F7R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F7R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F7R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F7R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F7R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F7R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F7R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F7R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F7R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F7R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F7R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F7R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F7R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F7R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F7R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F7R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F7R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F7R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F7R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F7R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F7R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F7R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F7R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F7R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F8R2 register  ***/
#define CAN_F8R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F8R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F8R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F8R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F8R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F8R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F8R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F8R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F8R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F8R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F8R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F8R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F8R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F8R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F8R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F8R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F8R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F8R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F8R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F8R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F8R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F8R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F8R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F8R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F8R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F8R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F8R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F8R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F8R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F8R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F8R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F8R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F9R2 register  ***/
#define CAN_F9R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F9R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F9R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F9R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F9R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F9R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F9R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F9R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F9R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F9R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F9R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F9R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F9R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F9R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F9R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F9R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F9R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F9R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F9R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F9R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F9R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F9R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F9R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F9R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F9R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F9R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F9R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F9R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F9R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F9R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F9R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F9R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F10R2 register  **/
#define CAN_F10R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F10R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F10R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F10R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F10R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F10R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F10R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F10R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F10R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F10R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F10R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F10R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F10R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F10R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F10R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F10R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F10R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F10R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F10R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F10R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F10R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F10R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F10R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F10R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F10R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F10R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F10R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F10R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F10R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F10R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F10R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F10R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F11R2 register  **/
#define CAN_F11R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F11R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F11R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F11R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F11R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F11R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F11R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F11R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F11R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F11R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F11R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F11R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F11R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F11R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F11R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F11R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F11R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F11R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F11R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F11R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F11R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F11R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F11R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F11R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F11R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F11R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F11R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F11R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F11R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F11R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F11R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F11R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F12R2 register  **/
#define CAN_F12R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F12R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F12R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F12R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F12R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F12R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F12R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F12R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F12R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F12R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F12R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F12R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F12R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F12R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F12R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F12R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F12R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F12R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F12R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F12R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F12R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F12R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F12R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F12R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F12R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F12R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F12R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F12R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F12R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F12R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F12R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F12R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F13R2 register  **/
#define CAN_F13R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F13R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F13R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F13R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F13R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F13R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F13R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F13R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F13R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F13R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F13R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F13R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F13R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F13R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F13R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F13R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F13R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F13R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F13R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F13R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F13R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F13R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F13R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F13R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F13R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F13R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F13R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F13R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F13R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F13R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F13R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F13R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */


/** Universal Synchronous Asynchronous Receiver Transmitter **/

/** Bit definition for USART_CTRL1 register **/
#define USART_CTRL1_UEN         ((uint32_t)0x00000001U) /* USART Enable */
#define USART_CTRL1_RXEN        ((uint32_t)0x00000002U) /* Receiver Enable */
#define USART_CTRL1_TXEN        ((uint32_t)0x00000004U) /* Transmitter Enable */
#define USART_CTRL1_PSEL        ((uint32_t)0x00000008U) /* Parity Selection */
#define USART_CTRL1_PCEN        ((uint32_t)0x00000010U) /* Parity Control Enable */
#define USART_CTRL1_WL          ((uint32_t)0x00000020U) /* Word length */
#define USART_CTRL1_RCVWU       ((uint32_t)0x00000040U) /* Receiver wakeup */
#define USART_CTRL1_WUM         ((uint32_t)0x00000080U) /* Wakeup method */
#define USART_CTRL1_IDLEIEN     ((uint32_t)0x00000100U) /* IDLE Interrupt Enable */
#define USART_CTRL1_RXDNEIEN    ((uint32_t)0x00000200U) /* RXNE Interrupt Enable */
#define USART_CTRL1_TXDEIEN     ((uint32_t)0x00000400U) /* PE Interrupt Enable */
#define USART_CTRL1_TXCIEN      ((uint32_t)0x00000800U) /* Transmission Complete Interrupt Enable */
#define USART_CTRL1_PEIEN       ((uint32_t)0x00001000U) /* PE Interrupt Enable */
#define USART_CTRL1_SDBRK       ((uint32_t)0x00002000U) /* Send Break */
#define USART_CTRL1_DEM         ((uint32_t)0x00004000U) /* Driver enable mode */
#define USART_CTRL1_DEP         ((uint32_t)0x00008000U) /* Driver enable polarity selection */
#define USART_CTRL1_DEDT_MASK   ((uint32_t)0x001F0000U) /* Driver Enable deassertion time mask */
#define USART_CTRL1_DEAT_MASK   ((uint32_t)0x03E00000U) /* Driver Enable assertion time mask */
#define USART_CTRL1_OSPM        ((uint32_t)0x04000000U) /* Oversampling mode */
#define USART_CTRL1_SWAP        ((uint32_t)0x08000000U) /* Swap TX/RX pins */
#define USART_CTRL1_TEDEN       ((uint32_t)0x20000000U) /* First byte delay fixed enable */

/** Bit definition for USART_CTRL2 register **/
#define USART_CTRL2_ADDR        ((uint32_t)0x0000000FU) /* Address of the USART node */
#define USART_CTRL2_STPB        ((uint32_t)0x00000060U) /* STOP[1:0] bits (STOP bits) */
#define USART_CTRL2_STPB_0      ((uint32_t)0x00000020U) /* Bit 0 */
#define USART_CTRL2_STPB_1      ((uint32_t)0x00000040U) /* Bit 1 */
#define USART_CTRL2_CLKEN       ((uint32_t)0x00000100U) /* Clock Enable */
#define USART_CTRL2_CLKPOL      ((uint32_t)0x00000200U) /* Clock Polarity */
#define USART_CTRL2_CLKPHA      ((uint32_t)0x00000400U) /* Clock Phase */
#define USART_CTRL2_LBCLK       ((uint32_t)0x00000800U) /* Last Bit Clock pulse */
#define USART_CTRL2_LINMEN      ((uint32_t)0x00001000U) /* LIN mode enable */
#define USART_CTRL2_LINBDIEN    ((uint32_t)0x00002000U) /* LIN Break Detection Interrupt Enable */
#define USART_CTRL2_LINBDL      ((uint32_t)0x00004000U) /* LIN Break Detection Length */
#define USART_CTRL2_RTOEN       ((uint32_t)0x00008000U) /* Receiver timeout enable */
#define USART_CTRL2_RTOCF       ((uint32_t)0x00010000U) /* Receiver timeout clear flag */
#define USART_CTRL2_RTOIE      ((uint32_t)0x00020000U) /* Receiver timeout interrupt enable */

/** Bit definition for USART_CTRL3 register **/
#define USART_CTRL3_CTSEN       ((uint32_t)0x00000001U) /* CTS Enable */
#define USART_CTRL3_CTSIEN      ((uint32_t)0x00000002U) /* CTS Interrupt Enable */
#define USART_CTRL3_RTSEN       ((uint32_t)0x00000004U) /* RTS Enable */
#define USART_CTRL3_HDMEN       ((uint32_t)0x00000008U) /* Half-Duplex Selection */
#define USART_CTRL3_DMATXEN     ((uint32_t)0x00000010U) /* DMA Enable Transmitter */
#define USART_CTRL3_DMARXEN     ((uint32_t)0x00000020U) /* DMA Enable Receiver */
#define USART_CTRL3_ERRIEN      ((uint32_t)0x00000040U) /* Error Interrupt Enable */
#define USART_CTRL3_IRDAMEN     ((uint32_t)0x00000080U) /* IrDA mode Enable */
#define USART_CTRL3_IRDALP      ((uint32_t)0x00000100U) /* IrDA Low-Power */
#define USART_CTRL3_SCMEN       ((uint32_t)0x00000200U) /* Smartcard mode enable */
#define USART_CTRL3_SCNACK      ((uint32_t)0x00000400U) /* Smartcard NACK enable */

/** Bit definition for USART_STS register **/
#define USART_STS_IDLEF         ((uint32_t)0x00000040U) /* IDLE line detected */
#define USART_STS_TXDE          ((uint32_t)0x00000080U) /* Transmit Data Register Empty */
#define USART_STS_TXC           ((uint32_t)0x00000100U) /* Transmission Complete */
#define USART_STS_RXDNE         ((uint32_t)0x00000200U) /* Read Data Register Not Empty */
#define USART_STS_CTSF          ((uint32_t)0x00000400U) /* CTS Flag */
#define USART_STS_LINBDF        ((uint32_t)0x00000800U) /* LIN Break Detection Flag */
#define USART_STS_PEF           ((uint32_t)0x00001000U) /* Parity Error */
#define USART_STS_OREF          ((uint32_t)0x00002000U) /* OverRun Error */
#define USART_STS_NEF           ((uint32_t)0x00004000U) /* Noise Error Flag */
#define USART_STS_FEF           ((uint32_t)0x00008000U) /* Framing Error */
#define USART_STS_RTOF          ((uint32_t)0x00010000U) /* recevier timeout */

/** Bit definition for USART_DAT register **/
#define USART_DAT_DATV          ((uint32_t)0x000001FFU) /* Data value */

/** Bit definition for USART_BRCF register **/
#define USART_BRCF_DIV_Decimal  ((uint32_t)0x000FU) /* Fraction of USARTDIV */
#define USART_BRCF_DIV_Integer  ((uint32_t)0xFFF0U) /* Mantissa of USARTDIV */

/** Bit definition for USART_GTP register **/
#define USART_GTP_PSCV          ((uint32_t)0x00FFU) /* PSC[7:0] bits (Prescaler value) */

#define USART_GTP_GTV           ((uint32_t)0xFF00U) /* Guard time value */

/******** Bit definition for USART_RTO register  ********/
#define USART_RTO_TIME          ((uint32_t)0x0FFFFFFF)         /* Bit[27:0] */

/******** Bit definition for USART_WKUP register  ********/
#define USART_WKUP_DATCLR       ((uint32_t)0x00000002)         /* Bit[1] */
#define USART_WKUP_EN           ((uint32_t)0x00000001)         /* Bit[0] */

/*** Debug MCU  ***/

/** Bit definition for DBG_ID register **/
#define DBG_ID_DEV    ((uint32_t)0x00000FFFU) /* Device Identifier */

#define DBG_ID_REV    ((uint32_t)0xFFFF0000U) /* REV_ID[15:0] bits (Revision Identifier) */
#define DBG_ID_REV_0  ((uint32_t)0x00010000U) /* Bit 0 */
#define DBG_ID_REV_1  ((uint32_t)0x00020000U) /* Bit 1 */
#define DBG_ID_REV_2  ((uint32_t)0x00040000U) /* Bit 2 */
#define DBG_ID_REV_3  ((uint32_t)0x00080000U) /* Bit 3 */
#define DBG_ID_REV_4  ((uint32_t)0x00100000U) /* Bit 4 */
#define DBG_ID_REV_5  ((uint32_t)0x00200000U) /* Bit 5 */
#define DBG_ID_REV_6  ((uint32_t)0x00400000U) /* Bit 6 */
#define DBG_ID_REV_7  ((uint32_t)0x00800000U) /* Bit 7 */
#define DBG_ID_REV_8  ((uint32_t)0x01000000U) /* Bit 8 */
#define DBG_ID_REV_9  ((uint32_t)0x02000000U) /* Bit 9 */
#define DBG_ID_REV_10 ((uint32_t)0x04000000U) /* Bit 10 */
#define DBG_ID_REV_11 ((uint32_t)0x08000000U) /* Bit 11 */
#define DBG_ID_REV_12 ((uint32_t)0x10000000U) /* Bit 12 */
#define DBG_ID_REV_13 ((uint32_t)0x20000000U) /* Bit 13 */
#define DBG_ID_REV_14 ((uint32_t)0x40000000U) /* Bit 14 */
#define DBG_ID_REV_15 ((uint32_t)0x80000000U) /* Bit 15 */

/** Bit definition for DBG_CTRL register **/
#define DBG_CTRL_SLEEP        ((uint32_t)0x00000001U) /* Debug Sleep Mode */
#define DBG_CTRL_STOP         ((uint32_t)0x00000002U) /* Debug Stop Mode */

#define DBG_CTRL_IWDG_STOP    ((uint32_t)0x00000100U) /* Debug Independent Watchdog stopped when Core is halted */
#define DBG_CTRL_WWDG_STOP    ((uint32_t)0x00000200U) /* Debug Window Watchdog stopped when Core is halted */
#define DBG_CTRL_ATIM1_STOP   ((uint32_t)0x00000400U) /* ATIM1 counter stopped when core is halted */
#define DBG_CTRL_GTIM1_STOP   ((uint32_t)0x00000800U) /* GTIM1 counter stopped when core is halted */
#define DBG_CTRL_GTIM2_STOP   ((uint32_t)0x00001000U) /* GTIM2 counter stopped when core is halted */
#define DBG_CTRL_GTIM3_STOP   ((uint32_t)0x00002000U) /* GTIM3 counter stopped when core is halted */
#define DBG_CTRL_CAN_STOP     ((uint32_t)0x00004000U) /* CAN stopped when Core is halted */
#define DBG_CTRL_I2C1SMBUS_TO ((uint32_t)0x00008000U) /* I2C1 SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_I2C2SMBUS_TO ((uint32_t)0x00010000U) /* I2C2 SMBUS timeout mode stopped when Core is halted */
#define DBG_CTRL_ATIM2_STOP   ((uint32_t)0x00020000U) /* ATIM2 counter stopped when core is halted */
#define DBG_CTRL_GTIM4_STOP   ((uint32_t)0x00040000U) /* GTIM4 counter stopped when core is halted */
#define DBG_CTRL_BTIM1_STOP   ((uint32_t)0x00080000U) /* BTIM1 counter stopped when core is halted */
#define DBG_CTRL_BTIM2_STOP   ((uint32_t)0x00100000U) /* BTIM2 counter stopped when core is halted */


/*** FLASH and Option Bytes Registers ***/

/** Bit definition for FLASH_AC register **/
#define FLASH_AC_ICAHEN                                  ((uint32_t)0x00000080U)         /* Icache Enable */
#define FLASH_AC_ICAHRST                                 ((uint32_t)0x00000040U)         /* Icache Reset */
#define FLASH_AC_PRFTBFSTS                               ((uint32_t)0x00000020U)         /* Prefetch Buffer Status */
#define FLASH_AC_PRFTBFEN                                ((uint32_t)0x00000010U)         /* Prefetch Buffer Enable */

#define FLASH_AC_LATENCY                                 ((uint32_t)0x00000007U)         /* LATENCY[2:0] bits (Latency) */
#define FLASH_AC_LATENCY_0                               ((uint32_t)0x00000000U)         /* Bit 0 = 0 */
#define FLASH_AC_LATENCY_1                               ((uint32_t)0x00000001U)         /* Bit 0 = 1 */
#define FLASH_AC_LATENCY_2                               ((uint32_t)0x00000002U)         /* Bit 0 = 0; Bit 1 = 1 */

/** Bit definition for FLASH_KEY register **/
#define FLASH_KEY_FKEY                                   ((uint32_t)0xFFFFFFFFU)        /* FLASH Key */

/** Bit definition for FLASH_OPTKEY register **/
#define FLASH_OPTKEY_OPTKEY                              ((uint32_t)0xFFFFFFFFU)         /* Option Byte Key */

/** Bit definition for FLASH_STS register **/
#define FLASH_STS_FKEYF                                   ((uint32_t)0x80000000U)         /* FKEYR write KEY1 flag */
#define FLASH_STS_OPTKEYF                                 ((uint32_t)0x40000000U)         /* OPTKEYR write KEY1 flag */
#define FLASH_STS_EOP                                     ((uint32_t)0x00000020U)         /* End of operation */
#define FLASH_STS_WRPRTERR                                ((uint32_t)0x00000010U)         /* Write Protection Error */
#define FLASH_STS_PGERR                                   ((uint32_t)0x00000004U)         /* Programming Error */
#define FLASH_STS_BSY                                     ((uint32_t)0x00000001U)         /* Busy */

/** Bit definition for FLASH_CTRL register **/
#define  FLASH_CTRL_PG                         ((uint16_t)0x0001U)            /* Programming */
#define  FLASH_CTRL_PER                        ((uint16_t)0x0002U)            /* Page Erase */
#define  FLASH_CTRL_MER                        ((uint16_t)0x0004U)            /* Mass Erase */
#define  FLASH_CTRL_OPTPG                      ((uint16_t)0x0010U)            /* Option Byte Programming */
#define  FLASH_CTRL_OPTER                      ((uint16_t)0x0020U)            /* Option Byte Erase */
#define  FLASH_CTRL_START                      ((uint16_t)0x0040U)            /* Start */
#define  FLASH_CTRL_LOCK                       ((uint16_t)0x0080U)            /* Lock */
#define  FLASH_CTRL_OPTWE                      ((uint16_t)0x0200U)            /* Option Bytes Write Enable */
#define  FLASH_CTRL_ERRITE                     ((uint16_t)0x0400U)            /* Error Interrupt Enable */
#define  FLASH_CTRL_EOPITE                     ((uint16_t)0x1000U)            /* End of operation interrupt enable */

/** Bit definition for FLASH_ADD register **/
#define  FLASH_ADD_FADD                        ((uint32_t)0xFFFFFFFFU)        /* Flash Address */

/** Bit definition for FLASH_OB2 register  **/
#define FLASH_OB2_Data1                                   ((uint32_t)0xFF000000U)         /* Bit[31:24] */
#define FLASH_OB2_Data1_0                                 ((uint32_t)0x01000000U)         /* Bit24*/
#define FLASH_OB2_Data1_1                                 ((uint32_t)0x02000000U)         /* Bit25*/
#define FLASH_OB2_Data1_2                                 ((uint32_t)0x04000000U)         /* Bit26*/
#define FLASH_OB2_Data1_3                                 ((uint32_t)0x08000000U)         /* Bit27*/
#define FLASH_OB2_Data1_4                                 ((uint32_t)0x10000000U)         /* Bit28*/
#define FLASH_OB2_Data1_5                                 ((uint32_t)0x20000000U)         /* Bit29*/
#define FLASH_OB2_Data1_6                                 ((uint32_t)0x40000000U)         /* Bit30*/
#define FLASH_OB2_Data1_7                                 ((uint32_t)0x80000000U)         /* Bit31*/
#define FLASH_OB2_Data0                                   ((uint32_t)0x00FF0000U)         /* Bit[23:16] */
#define FLASH_OB2_Data0_0                                 ((uint32_t)0x00010000U)         /* Bit16*/
#define FLASH_OB2_Data0_1                                 ((uint32_t)0x00020000U)         /* Bit17*/
#define FLASH_OB2_Data0_2                                 ((uint32_t)0x00040000U)         /* Bit18*/
#define FLASH_OB2_Data0_3                                 ((uint32_t)0x00080000U)         /* Bit19*/
#define FLASH_OB2_Data0_4                                 ((uint32_t)0x00100000U)         /* Bit20*/
#define FLASH_OB2_Data0_5                                 ((uint32_t)0x00200000U)         /* Bit21*/
#define FLASH_OB2_Data0_6                                 ((uint32_t)0x00400000U)         /* Bit22*/
#define FLASH_OB2_Data0_7                                 ((uint32_t)0x00800000U)         /* Bit23*/
#define FLASH_OB2_BOOT_SEL_CAN                            ((uint32_t)0x0000FF00U)         /* Bit[15:8] */
#define FLASH_OB2_BOOT_SEL_I2C                            ((uint32_t)0x000000FFU)         /* Bit[7:0] */


/** Bit definition for FLASH_OB register  **/
#define FLASH_OB_RDPRT2                                  ((uint32_t)0x80000000U)         /* Bit[31] */
#define FLASH_OB_BOOT_WRP                                ((uint32_t)0x10000000U)         /* Bit[28] */
#define FLASH_OB_BOOT_SEL_UART                           ((uint32_t)0x0FF00000U)         /* Bit[27:20] */
#define FLASH_OB_BOOT_SEL_UART_0                         ((uint32_t)0x00100000U)         /* Bit20*/
#define FLASH_OB_BOOT_SEL_UART_1                         ((uint32_t)0x00200000U)         /* Bit21*/
#define FLASH_OB_BOOT_SEL_UART_2                         ((uint32_t)0x00400000U)         /* Bit22*/
#define FLASH_OB_BOOT_SEL_UART_3                         ((uint32_t)0x00800000U)         /* Bit23*/
#define FLASH_OB_BOOT_SEL_UART_4                         ((uint32_t)0x01000000U)         /* Bit24*/
#define FLASH_OB_BOOT_SEL_UART_5                         ((uint32_t)0x02000000U)         /* Bit25*/
#define FLASH_OB_BOOT_SEL_UART_6                         ((uint32_t)0x04000000U)         /* Bit26*/
#define FLASH_OB_BOOT_SEL_UART_7                         ((uint32_t)0x08000000U)         /* Bit27*/
#define FLASH_OB_IWDGSTOPFRZ                             ((uint32_t)0x00020000U)         /* Bit[17] */
#define FLASH_OB_IWDGSLEEPFRZ                            ((uint32_t)0x00010000U)         /* Bit[16] */
#define FLASH_OB_BOOT0_CFG                               ((uint32_t)0x00008000U)         /* Bit[15] */
#define FLASH_OB_nSWBOOT0                                ((uint32_t)0x00004000U)         /* Bit[14] */
#define FLASH_OB_nBOOT1                                  ((uint32_t)0x00002000U)         /* Bit[13] */
#define FLASH_OB_nBOOT0                                  ((uint32_t)0x00001000U)         /* Bit[12] */
#define FLASH_OB_POR_DELAY                               ((uint32_t)0x00000FF0U)         /* Bit[11:4] */
#define FLASH_OB_POR_DELAY_0                             ((uint32_t)0x00000010U)         /* Bit4*/
#define FLASH_OB_POR_DELAY_1                             ((uint32_t)0x00000020U)         /* Bit5*/
#define FLASH_OB_POR_DELAY_2                             ((uint32_t)0x00000040U)         /* Bit6*/
#define FLASH_OB_POR_DELAY_3                             ((uint32_t)0x00000080U)         /* Bit7*/
#define FLASH_OB_POR_DELAY_4                             ((uint32_t)0x00000100U)         /* Bit8*/
#define FLASH_OB_POR_DELAY_5                             ((uint32_t)0x00000200U)         /* Bit9*/
#define FLASH_OB_POR_DELAY_6                             ((uint32_t)0x00000400U)         /* Bit10*/
#define FLASH_OB_POR_DELAY_7                             ((uint32_t)0x00000800U)         /* Bit11*/
#define FLASH_OB_NRST_PD7                                ((uint32_t)0x00000008U)         /* Bit[3] */
#define FLASH_OB_IWDG_SW                                 ((uint32_t)0x00000004U)         /* Bit[2] */
#define FLASH_OB_RDPRT1                                  ((uint32_t)0x00000002U)         /* Bit[1] */
#define FLASH_OB_OBERR                                   ((uint32_t)0x00000001U)         /* Bit[0] */

/** Bit definition for FLASH_WRP register **/
#define FLASH_WRP_WRPT                          ((uint32_t)0xFFFFFFFFU) /* Write Protect */
#define FLASH_WRP_WRPT_0                        ((uint32_t)0x00000001U) /* bit 0  */
#define FLASH_WRP_WRPT_1                        ((uint32_t)0x00000002U) /* bit 1  */
#define FLASH_WRP_WRPT_2                        ((uint32_t)0x00000004U) /* bit 2  */
#define FLASH_WRP_WRPT_3                        ((uint32_t)0x00000008U) /* bit 3  */
#define FLASH_WRP_WRPT_4                        ((uint32_t)0x00000010U) /* bit 4  */
#define FLASH_WRP_WRPT_5                        ((uint32_t)0x00000020U) /* bit 5  */
#define FLASH_WRP_WRPT_6                        ((uint32_t)0x00000040U) /* bit 6  */
#define FLASH_WRP_WRPT_7                        ((uint32_t)0x00000080U) /* bit 7  */
#define FLASH_WRP_WRPT_8                        ((uint32_t)0x00000100U) /* bit 8  */
#define FLASH_WRP_WRPT_9                        ((uint32_t)0x00000200U) /* bit 9  */
#define FLASH_WRP_WRPT_10                       ((uint32_t)0x00000400U) /* bit 10 */
#define FLASH_WRP_WRPT_11                       ((uint32_t)0x00000800U) /* bit 11 */
#define FLASH_WRP_WRPT_12                       ((uint32_t)0x00001000U) /* bit 12 */
#define FLASH_WRP_WRPT_13                       ((uint32_t)0x00002000U) /* bit 13 */
#define FLASH_WRP_WRPT_14                       ((uint32_t)0x00004000U) /* bit 14 */
#define FLASH_WRP_WRPT_15                       ((uint32_t)0x00008000U) /* bit 15 */
#define FLASH_WRP_WRPT_16                       ((uint32_t)0x00010000U) /* bit 16 */
#define FLASH_WRP_WRPT_17                       ((uint32_t)0x00020000U) /* bit 17 */
#define FLASH_WRP_WRPT_18                       ((uint32_t)0x00040000U) /* bit 18 */
#define FLASH_WRP_WRPT_19                       ((uint32_t)0x00080000U) /* bit 19 */
#define FLASH_WRP_WRPT_20                       ((uint32_t)0x00100000U) /* bit 20 */
#define FLASH_WRP_WRPT_21                       ((uint32_t)0x00200000U) /* bit 21 */
#define FLASH_WRP_WRPT_22                       ((uint32_t)0x00400000U) /* bit 22 */
#define FLASH_WRP_WRPT_23                       ((uint32_t)0x00800000U) /* bit 23 */
#define FLASH_WRP_WRPT_24                       ((uint32_t)0x01000000U) /* bit 24 */
#define FLASH_WRP_WRPT_25                       ((uint32_t)0x02000000U) /* bit 25 */
#define FLASH_WRP_WRPT_26                       ((uint32_t)0x04000000U) /* bit 26 */
#define FLASH_WRP_WRPT_27                       ((uint32_t)0x08000000U) /* bit 27 */
#define FLASH_WRP_WRPT_28                       ((uint32_t)0x10000000U) /* bit 28 */
#define FLASH_WRP_WRPT_29                       ((uint32_t)0x20000000U) /* bit 29 */
#define FLASH_WRP_WRPT_30                       ((uint32_t)0x40000000U) /* bit 30 */
#define FLASH_WRP_WRPT_31                       ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for FLASH_CAHR register **/
#define FLASH_CAHR_LOCKSTRT_MSK ((uint32_t)0x0000000FU) /* LOCKSTRT Mask */
#define FLASH_CAHR_LOCKSTRT_0   ((uint32_t)0x00000001U)
#define FLASH_CAHR_LOCKSTRT_1   ((uint32_t)0x00000002U)
#define FLASH_CAHR_LOCKSTRT_2   ((uint32_t)0x00000004U)
#define FLASH_CAHR_LOCKSTRT_3   ((uint32_t)0x00000008U)

#define FLASH_CAHR_LOCKSTOP_MSK ((uint32_t)0x000000F0U) /* LOCKSTOP Mask */
#define FLASH_CAHR_LOCKSTOP_0   ((uint32_t)0x00000010U)
#define FLASH_CAHR_LOCKSTOP_1   ((uint32_t)0x00000020U)
#define FLASH_CAHR_LOCKSTOP_2   ((uint32_t)0x00000040U)
#define FLASH_CAHR_LOCKSTOP_3   ((uint32_t)0x00000080U)

/*** Option Bytes register ***/
#define FLASH_OB_BYTE1   ((uint32_t)0x000000FFU) /* The lower 8 bits of each word in the option byte */
#define FLASH_OB_NBYTE1  ((uint32_t)0x0000FF00U) /* The inverted value of the lower 8 bits of each word in the option byte */
#define FLASH_OB_BYTE3   ((uint32_t)0x00FF0000U) /* The [23:16] bits of each word in the option byte */
#define FLASH_OB_NBYTE3  ((uint32_t)0xFF000000U) /* The inverse value of the [23:16] bits of each word in the option byte */



/** CRC calculation unit **/
/** Bit definition for CRC_CRC32DAT register **/
#define CRC32_DAT_DAT           ((uint32_t)0xFFFFFFFFU) /* Data register bits */

/** Bit definition for CRC_CRC32IDAT register **/
#define CRC32_IDAT_IDAT         ((uint8_t)0xFFU) /* General-purpose 8-bit data register bits */

/** Bit definition for CRC_CRC32CTRL register **/
#define CRC32_CTRL_RESET        ((uint8_t)0x01U) /* RESET bit */

/** Bit definition for CRC16_CR register **/
#define CRC16_CTRL_LITTLE       ((uint8_t)0x02U)
#define CRC16_CTRL_BIG          ((uint8_t)0xFDU)

#define CRC16_CTRL_RESET        ((uint8_t)0x04U)
#define CRC16_CTRL_NO_RESET     ((uint8_t)0xFBU)


/*** General Purpose and Alternate Function I/O ***/

/** Bit definition for GPIO_PMODE register **/
#define GPIO_PMODE0_Pos            (uint32_t)(0U)
#define GPIO_PMODE0_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE0_Pos) /* 0x00000003 */
#define GPIO_PMODE0                (uint32_t)GPIO_PMODE0_Msk                            /* 0x00000003 */
#define GPIO_PMODE0_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE0_Pos) /* 0x00000000 */
#define GPIO_PMODE0_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE0_Pos) /* 0x00000001 */
#define GPIO_PMODE0_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE0_Pos) /* 0x00000002 */
#define GPIO_PMODE0_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE0_Pos) /* 0x00000003 */

#define GPIO_PMODE1_Pos            (uint32_t)(2U)
#define GPIO_PMODE1_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE1_Pos) /* 0x0000000C */
#define GPIO_PMODE1                (uint32_t)GPIO_PMODE1_Msk                            /* 0x0000000C */
#define GPIO_PMODE1_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE1_Pos) /* 0x00000000 */
#define GPIO_PMODE1_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE1_Pos) /* 0x00000004 */
#define GPIO_PMODE1_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE1_Pos) /* 0x00000008 */
#define GPIO_PMODE1_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE1_Pos) /* 0x0000000C */

#define GPIO_PMODE2_Pos            (uint32_t)(4U)
#define GPIO_PMODE2_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE2_Pos) /* 0x00000030 */
#define GPIO_PMODE2                (uint32_t)GPIO_PMODE2_Msk                            /* 0x00000030 */
#define GPIO_PMODE2_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE2_Pos) /* 0x00000000 */
#define GPIO_PMODE2_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE2_Pos) /* 0x00000010 */
#define GPIO_PMODE2_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE2_Pos) /* 0x00000020 */
#define GPIO_PMODE2_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE2_Pos) /* 0x00000030 */

#define GPIO_PMODE3_Pos            (uint32_t)(6U)
#define GPIO_PMODE3_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE3_Pos) /* 0x000000C0 */
#define GPIO_PMODE3                (uint32_t)GPIO_PMODE3_Msk                            /* 0x000000C0 */
#define GPIO_PMODE3_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE3_Pos) /* 0x00000000 */
#define GPIO_PMODE3_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE3_Pos) /* 0x00000040 */
#define GPIO_PMODE3_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE3_Pos) /* 0x00000080 */
#define GPIO_PMODE3_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE3_Pos) /* 0x000000C0 */

#define GPIO_PMODE4_Pos            (uint32_t)(8U)
#define GPIO_PMODE4_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE4_Pos) /* 0x00000300 */
#define GPIO_PMODE4                (uint32_t)GPIO_PMODE4_Msk                            /* 0x00000300 */
#define GPIO_PMODE4_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE4_Pos) /* 0x00000000 */
#define GPIO_PMODE4_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE4_Pos) /* 0x00000100 */
#define GPIO_PMODE4_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE4_Pos) /* 0x00000100 */
#define GPIO_PMODE4_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE4_Pos) /* 0x00000300 */

#define GPIO_PMODE5_Pos            (uint32_t)(10U)
#define GPIO_PMODE5_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE5_Pos) /* 0x00000C00 */
#define GPIO_PMODE5                (uint32_t)GPIO_PMODE5_Msk                            /* 0x00000C00 */
#define GPIO_PMODE5_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE5_Pos) /* 0x00000000 */
#define GPIO_PMODE5_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE5_Pos) /* 0x00000400 */
#define GPIO_PMODE5_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE5_Pos) /* 0x00000800 */
#define GPIO_PMODE5_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE5_Pos) /* 0x00000C00 */

#define GPIO_PMODE6_Pos            (uint32_t)(12U)
#define GPIO_PMODE6_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE6_Pos) /* 0x00003000 */
#define GPIO_PMODE6                (uint32_t)GPIO_PMODE6_Msk                            /* 0x00003000 */
#define GPIO_PMODE6_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE6_Pos) /* 0x00000000 */
#define GPIO_PMODE6_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE6_Pos) /* 0x00001000 */
#define GPIO_PMODE6_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE6_Pos) /* 0x00002000 */
#define GPIO_PMODE6_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE6_Pos) /* 0x00003000 */

#define GPIO_PMODE7_Pos            (uint32_t)(14U)
#define GPIO_PMODE7_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE7_Pos) /* 0x0000C000 */
#define GPIO_PMODE7                (uint32_t)GPIO_PMODE7_Msk                            /* 0x0000C000 */
#define GPIO_PMODE7_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE7_Pos) /* 0x00000000 */
#define GPIO_PMODE7_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE7_Pos) /* 0x00004000 */
#define GPIO_PMODE7_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE7_Pos) /* 0x00008000 */
#define GPIO_PMODE7_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE7_Pos) /* 0x0000C000 */

#define GPIO_PMODE8_Pos            (uint32_t)(16U)
#define GPIO_PMODE8_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE8_Pos) /* 0x00030000 */
#define GPIO_PMODE8                (uint32_t)GPIO_PMODE8_Msk                            /* 0x00030000 */
#define GPIO_PMODE8_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE8_Pos) /* 0x00000000 */
#define GPIO_PMODE8_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE8_Pos) /* 0x00010000 */
#define GPIO_PMODE8_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE8_Pos) /* 0x00020000 */
#define GPIO_PMODE8_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE8_Pos) /* 0x00030000 */

#define GPIO_PMODE9_Pos            (uint32_t)(18U)
#define GPIO_PMODE9_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE9_Pos) /* 0x000C0000 */
#define GPIO_PMODE9                (uint32_t)GPIO_PMODE9_Msk                            /* 0x000C0000 */
#define GPIO_PMODE9_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE9_Pos) /* 0x00000000 */
#define GPIO_PMODE9_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE9_Pos) /* 0x00040000 */
#define GPIO_PMODE9_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE9_Pos) /* 0x00080000 */
#define GPIO_PMODE9_3              (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE9_Pos) /* 0x000C0000 */

#define GPIO_PMODE10_Pos           (uint32_t)(20U)
#define GPIO_PMODE10_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE10_Pos) /* 0x00300000 */
#define GPIO_PMODE10               (uint32_t)GPIO_PMODE10_Msk                            /* 0x00300000 */
#define GPIO_PMODE10_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE10_Pos) /* 0x00000000 */
#define GPIO_PMODE10_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE10_Pos) /* 0x00100000 */
#define GPIO_PMODE10_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE10_Pos) /* 0x00200000 */
#define GPIO_PMODE10_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE10_Pos) /* 0x00300000 */

#define GPIO_PMODE11_Pos           (uint32_t)(22U)
#define GPIO_PMODE11_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE11_Pos) /* 0x00C00000 */
#define GPIO_PMODE11               (uint32_t)GPIO_PMODE11_Msk                            /* 0x00C00000 */
#define GPIO_PMODE11_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE11_Pos) /* 0x00000000 */
#define GPIO_PMODE11_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE11_Pos) /* 0x00400000 */
#define GPIO_PMODE11_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE11_Pos) /* 0x00800000 */
#define GPIO_PMODE11_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE11_Pos) /* 0x00C00000 */

#define GPIO_PMODE12_Pos           (uint32_t)(24U)
#define GPIO_PMODE12_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE12_Pos) /* 0x03000000 */
#define GPIO_PMODE12               (uint32_t)GPIO_PMODE12_Msk                            /* 0x03000000 */
#define GPIO_PMODE12_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE12_Pos) /* 0x00000000 */
#define GPIO_PMODE12_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE12_Pos) /* 0x01000000 */
#define GPIO_PMODE12_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE12_Pos) /* 0x02000000 */
#define GPIO_PMODE12_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE12_Pos) /* 0x03000000 */

#define GPIO_PMODE13_Pos           (uint32_t)(26U)
#define GPIO_PMODE13_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE13_Pos) /* 0x0C000000 */
#define GPIO_PMODE13               (uint32_t)GPIO_PMODE13_Msk                            /* 0x0C000000 */
#define GPIO_PMODE13_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE13_Pos) /* 0x00000000 */
#define GPIO_PMODE13_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE13_Pos) /* 0x04000000 */
#define GPIO_PMODE13_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE13_Pos) /* 0x08000000 */
#define GPIO_PMODE13_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE13_Pos) /* 0x0C000000 */

#define GPIO_PMODE14_Pos           (uint32_t)(28U)
#define GPIO_PMODE14_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE14_Pos) /* 0x30000000 */
#define GPIO_PMODE14               (uint32_t)GPIO_PMODE14_Msk                            /* 0x30000000 */
#define GPIO_PMODE14_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE14_Pos) /* 0x00000000 */
#define GPIO_PMODE14_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE14_Pos) /* 0x10000000 */
#define GPIO_PMODE14_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE14_Pos) /* 0x20000000 */
#define GPIO_PMODE14_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE14_Pos) /* 0x30000000 */

#define GPIO_PMODE15_Pos           (uint32_t)(30U)
#define GPIO_PMODE15_Msk           (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE15_Pos) /* 0xC0000000 */
#define GPIO_PMODE15               (uint32_t)GPIO_PMODE15_Msk                            /* 0xC0000000 */
#define GPIO_PMODE15_0             (uint32_t)((uint32_t)0x00000000U << GPIO_PMODE15_Pos) /* 0x00000000 */
#define GPIO_PMODE15_1             (uint32_t)((uint32_t)0x00000001U << GPIO_PMODE15_Pos) /* 0x40000000 */
#define GPIO_PMODE15_2             (uint32_t)((uint32_t)0x00000002U << GPIO_PMODE15_Pos) /* 0x80000000 */
#define GPIO_PMODE15_3             (uint32_t)((uint32_t)0x00000003U << GPIO_PMODE15_Pos) /* 0xC0000000 */

/** Bit definition for GPIO_POTYPE register **/
#define GPIO_POTYPE_POT0           ((uint16_t)0x0001U)
#define GPIO_POTYPE_POT1           ((uint16_t)0x0002U)
#define GPIO_POTYPE_POT2           ((uint16_t)0x0004U)
#define GPIO_POTYPE_POT3           ((uint16_t)0x0008U)
#define GPIO_POTYPE_POT4           ((uint16_t)0x0010U)
#define GPIO_POTYPE_POT5           ((uint16_t)0x0020U)
#define GPIO_POTYPE_POT6           ((uint16_t)0x0040U)
#define GPIO_POTYPE_POT7           ((uint16_t)0x0080U)
#define GPIO_POTYPE_POT8           ((uint16_t)0x0100U)
#define GPIO_POTYPE_POT9           ((uint16_t)0x0200U)
#define GPIO_POTYPE_POT10          ((uint16_t)0x0400U)
#define GPIO_POTYPE_POT11          ((uint16_t)0x0800U)
#define GPIO_POTYPE_POT12          ((uint16_t)0x1000U)
#define GPIO_POTYPE_POT13          ((uint16_t)0x2000U)
#define GPIO_POTYPE_POT14          ((uint16_t)0x4000U)
#define GPIO_POTYPE_POT15          ((uint16_t)0x8000U)

/** Bit definition for GPIO_PUPD register **/
#define GPIO_PUPD0_Pos             (uint32_t)(0U)
#define GPIO_PUPD0_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD0_Pos) /* 0x00000003 */
#define GPIO_PUPD0                 (uint32_t)GPIO_PUPD0_Msk                            /* 0x00000003 */
#define GPIO_PUPD0_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD0_Pos) /* 0x00000000 */
#define GPIO_PUPD0_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD0_Pos) /* 0x00000001 */
#define GPIO_PUPD0_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD0_Pos) /* 0x00000002 */

#define GPIO_PUPD1_Pos             (uint32_t)(2U)
#define GPIO_PUPD1_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD1_Pos) /* 0x0000000C */
#define GPIO_PUPD1                 (uint32_t)GPIO_PUPD1_Msk                            /* 0x0000000C */
#define GPIO_PUPD1_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD1_Pos) /* 0x00000000 */
#define GPIO_PUPD1_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD1_Pos) /* 0x00000004 */
#define GPIO_PUPD1_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD1_Pos) /* 0x00000008 */

#define GPIO_PUPD2_Pos             (uint32_t)(4U)
#define GPIO_PUPD2_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD2_Pos) /* 0x00000030 */
#define GPIO_PUPD2                 (uint32_t)GPIO_PUPD2_Msk                            /* 0x00000030 */
#define GPIO_PUPD2_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD2_Pos) /* 0x00000000 */
#define GPIO_PUPD2_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD2_Pos) /* 0x00000010 */
#define GPIO_PUPD2_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD2_Pos) /* 0x00000020 */

#define GPIO_PUPD3_Pos             (uint32_t)(6U)
#define GPIO_PUPD3_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD3_Pos) /* 0x000000C0 */
#define GPIO_PUPD3                 (uint32_t)GPIO_PUPD3_Msk                            /* 0x000000C0 */
#define GPIO_PUPD3_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD3_Pos) /* 0x00000000 */
#define GPIO_PUPD3_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD3_Pos) /* 0x00000040 */
#define GPIO_PUPD3_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD3_Pos) /* 0x00000080 */

#define GPIO_PUPD4_Pos             (uint32_t)(8U)
#define GPIO_PUPD4_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD4_Pos) /* 0x00000300 */
#define GPIO_PUPD4                 (uint32_t)GPIO_PUPD4_Msk                            /* 0x00000300 */
#define GPIO_PUPD4_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD4_Pos) /* 0x00000000 */
#define GPIO_PUPD4_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD4_Pos) /* 0x00000100 */
#define GPIO_PUPD4_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD4_Pos) /* 0x00000200 */

#define GPIO_PUPD5_Pos             (uint32_t)(10U)
#define GPIO_PUPD5_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD5_Pos) /* 0x00000C00 */
#define GPIO_PUPD5                 (uint32_t)GPIO_PUPD5_Msk                            /* 0x00000C00 */
#define GPIO_PUPD5_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD5_Pos) /* 0x00000000 */
#define GPIO_PUPD5_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD5_Pos) /* 0x00000400 */
#define GPIO_PUPD5_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD5_Pos) /* 0x00000800 */

#define GPIO_PUPD6_Pos             (uint32_t)(12U)
#define GPIO_PUPD6_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD6_Pos) /* 0x00003000 */
#define GPIO_PUPD6                 (uint32_t)GPIO_PUPD6_Msk                            /* 0x00003000 */
#define GPIO_PUPD6_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD6_Pos) /* 0x00000000 */
#define GPIO_PUPD6_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD6_Pos) /* 0x00001000 */
#define GPIO_PUPD6_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD6_Pos) /* 0x00002000 */

#define GPIO_PUPD7_Pos             (uint32_t)(14U)
#define GPIO_PUPD7_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD7_Pos) /* 0x0000C000 */
#define GPIO_PUPD7                 (uint32_t)GPIO_PUPD7_Msk                            /* 0x0000C000 */
#define GPIO_PUPD7_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD7_Pos) /* 0x00000000 */
#define GPIO_PUPD7_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD7_Pos) /* 0x00004000 */
#define GPIO_PUPD7_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD7_Pos) /* 0x00008000 */

#define GPIO_PUPD8_Pos             (uint32_t)(16U)
#define GPIO_PUPD8_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD8_Pos) /* 0x00030000 */
#define GPIO_PUPD8                 (uint32_t)GPIO_PUPD8_Msk                            /* 0x00030000 */
#define GPIO_PUPD8_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD8_Pos) /* 0x00000000 */
#define GPIO_PUPD8_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD8_Pos) /* 0x00010000 */
#define GPIO_PUPD8_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD8_Pos) /* 0x00020000 */

#define GPIO_PUPD9_Pos             (uint32_t)(18U)
#define GPIO_PUPD9_Msk             (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD9_Pos) /* 0x000C0000 */
#define GPIO_PUPD9                 (uint32_t)GPIO_PUPD9_Msk                            /* 0x000C0000 */
#define GPIO_PUPD9_0               (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD9_Pos) /* 0x00000000 */
#define GPIO_PUPD9_1               (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD9_Pos) /* 0x00040000 */
#define GPIO_PUPD9_2               (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD9_Pos) /* 0x00080000 */

#define GPIO_PUPD10_Pos            (uint32_t)(20U)
#define GPIO_PUPD10_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD10_Pos) /* 0x00300000 */
#define GPIO_PUPD10                (uint32_t)GPIO_PUPD10_Msk                            /* 0x00300000 */
#define GPIO_PUPD10_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD10_Pos) /* 0x00000000 */
#define GPIO_PUPD10_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD10_Pos) /* 0x00100000 */
#define GPIO_PUPD10_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD10_Pos) /* 0x00200000 */

#define GPIO_PUPD11_Pos            (uint32_t)(22U)
#define GPIO_PUPD11_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD11_Pos) /* 0x00C00000 */
#define GPIO_PUPD11                (uint32_t)GPIO_PUPD11_Msk                            /* 0x00C00000 */
#define GPIO_PUPD11_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD11_Pos) /* 0x00000000 */
#define GPIO_PUPD11_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD11_Pos) /* 0x00400000 */
#define GPIO_PUPD11_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD11_Pos) /* 0x00800000 */

#define GPIO_PUPD12_Pos            (uint32_t)(24U)
#define GPIO_PUPD12_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD12_Pos) /* 0x03000000 */
#define GPIO_PUPD12                (uint32_t)GPIO_PUPD12_Msk                            /* 0x03000000 */
#define GPIO_PUPD12_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD12_Pos) /* 0x00000000 */
#define GPIO_PUPD12_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD12_Pos) /* 0x01000000 */
#define GPIO_PUPD12_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD12_Pos) /* 0x02000000 */

#define GPIO_PUPD13_Pos            (uint32_t)(26U)
#define GPIO_PUPD13_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD13_Pos) /* 0x0C000000 */
#define GPIO_PUPD13                (uint32_t)GPIO_PUPD13_Msk                            /* 0x0C000000 */
#define GPIO_PUPD13_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD13_Pos) /* 0x00000000 */
#define GPIO_PUPD13_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD13_Pos) /* 0x04000000 */
#define GPIO_PUPD13_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD13_Pos) /* 0x08000000 */

#define GPIO_PUPD14_Pos            (uint32_t)(28U)
#define GPIO_PUPD14_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD14_Pos) /* 0x30000000 */
#define GPIO_PUPD14                (uint32_t)GPIO_PUPD14_Msk                            /* 0x30000000 */ 
#define GPIO_PUPD14_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD14_Pos) /* 0x00000000 */
#define GPIO_PUPD14_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD14_Pos) /* 0x10000000 */
#define GPIO_PUPD14_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD14_Pos) /* 0x30000000 */

#define GPIO_PUPD15_Pos            (uint32_t)(30U)
#define GPIO_PUPD15_Msk            (uint32_t)((uint32_t)0x00000003U << GPIO_PUPD15_Pos) /* 0xC0000000 */
#define GPIO_PUPD15                (uint32_t)GPIO_PUPD15_Msk                            /* 0xC0000000 */
#define GPIO_PUPD15_0              (uint32_t)((uint32_t)0x00000000U << GPIO_PUPD15_Pos) /* 0x00000000 */
#define GPIO_PUPD15_1              (uint32_t)((uint32_t)0x00000001U << GPIO_PUPD15_Pos) /* 0x40000000 */
#define GPIO_PUPD15_2              (uint32_t)((uint32_t)0x00000002U << GPIO_PUPD15_Pos) /* 0x80000000 */

/** Bit definition for GPIO_PID register **/
#define GPIO_PID_PID0              ((uint16_t)0x0001U) /* Port input data, bit 0  */
#define GPIO_PID_PID1              ((uint16_t)0x0002U) /* Port input data, bit 1  */
#define GPIO_PID_PID2              ((uint16_t)0x0004U) /* Port input data, bit 2  */
#define GPIO_PID_PID3              ((uint16_t)0x0008U) /* Port input data, bit 3  */
#define GPIO_PID_PID4              ((uint16_t)0x0010U) /* Port input data, bit 4  */
#define GPIO_PID_PID5              ((uint16_t)0x0020U) /* Port input data, bit 5  */
#define GPIO_PID_PID6              ((uint16_t)0x0040U) /* Port input data, bit 6  */
#define GPIO_PID_PID7              ((uint16_t)0x0080U) /* Port input data, bit 7  */
#define GPIO_PID_PID8              ((uint16_t)0x0100U) /* Port input data, bit 8  */
#define GPIO_PID_PID9              ((uint16_t)0x0200U) /* Port input data, bit 9  */
#define GPIO_PID_PID10             ((uint16_t)0x0400U) /* Port input data, bit 10 */
#define GPIO_PID_PID11             ((uint16_t)0x0800U) /* Port input data, bit 11 */
#define GPIO_PID_PID12             ((uint16_t)0x1000U) /* Port input data, bit 12 */
#define GPIO_PID_PID13             ((uint16_t)0x2000U) /* Port input data, bit 13 */
#define GPIO_PID_PID14             ((uint16_t)0x4000U) /* Port input data, bit 14 */
#define GPIO_PID_PID15             ((uint16_t)0x8000U) /* Port input data, bit 15 */

/** Bit definition for GPIO_POD register **/
#define GPIO_POD_POD0              ((uint16_t)0x0001U) /* Port output data, bit 0  */
#define GPIO_POD_POD1              ((uint16_t)0x0002U) /* Port output data, bit 1  */
#define GPIO_POD_POD2              ((uint16_t)0x0004U) /* Port output data, bit 2  */
#define GPIO_POD_POD3              ((uint16_t)0x0008U) /* Port output data, bit 3  */
#define GPIO_POD_POD4              ((uint16_t)0x0010U) /* Port output data, bit 4  */
#define GPIO_POD_POD5              ((uint16_t)0x0020U) /* Port output data, bit 5  */
#define GPIO_POD_POD6              ((uint16_t)0x0040U) /* Port output data, bit 6  */
#define GPIO_POD_POD7              ((uint16_t)0x0080U) /* Port output data, bit 7  */
#define GPIO_POD_POD8              ((uint16_t)0x0100U) /* Port output data, bit 8  */
#define GPIO_POD_POD9              ((uint16_t)0x0200U) /* Port output data, bit 9  */
#define GPIO_POD_POD10             ((uint16_t)0x0400U) /* Port output data, bit 10 */
#define GPIO_POD_POD11             ((uint16_t)0x0800U) /* Port output data, bit 11 */
#define GPIO_POD_POD12             ((uint16_t)0x1000U) /* Port output data, bit 12 */
#define GPIO_POD_POD13             ((uint16_t)0x2000U) /* Port output data, bit 13 */
#define GPIO_POD_POD14             ((uint16_t)0x4000U) /* Port output data, bit 14 */
#define GPIO_POD_POD15             ((uint16_t)0x8000U) /* Port output data, bit 15 */

/** Bit definition for GPIO_PBSC register **/
#define GPIO_PBSC_PBS0             ((uint32_t)0x00000001U) /* Port x Set bit 0  */
#define GPIO_PBSC_PBS1             ((uint32_t)0x00000002U) /* Port x Set bit 1  */
#define GPIO_PBSC_PBS2             ((uint32_t)0x00000004U) /* Port x Set bit 2  */
#define GPIO_PBSC_PBS3             ((uint32_t)0x00000008U) /* Port x Set bit 3  */
#define GPIO_PBSC_PBS4             ((uint32_t)0x00000010U) /* Port x Set bit 4  */
#define GPIO_PBSC_PBS5             ((uint32_t)0x00000020U) /* Port x Set bit 5  */
#define GPIO_PBSC_PBS6             ((uint32_t)0x00000040U) /* Port x Set bit 6  */
#define GPIO_PBSC_PBS7             ((uint32_t)0x00000080U) /* Port x Set bit 7  */
#define GPIO_PBSC_PBS8             ((uint32_t)0x00000100U) /* Port x Set bit 8  */
#define GPIO_PBSC_PBS9             ((uint32_t)0x00000200U) /* Port x Set bit 9  */
#define GPIO_PBSC_PBS10            ((uint32_t)0x00000400U) /* Port x Set bit 10 */
#define GPIO_PBSC_PBS11            ((uint32_t)0x00000800U) /* Port x Set bit 11 */
#define GPIO_PBSC_PBS12            ((uint32_t)0x00001000U) /* Port x Set bit 12 */
#define GPIO_PBSC_PBS13            ((uint32_t)0x00002000U) /* Port x Set bit 13 */
#define GPIO_PBSC_PBS14            ((uint32_t)0x00004000U) /* Port x Set bit 14 */
#define GPIO_PBSC_PBS15            ((uint32_t)0x00008000U) /* Port x Set bit 15 */

#define GPIO_PBSC_PBC0             ((uint32_t)0x00010000U) /* Port x Reset bit 0  */
#define GPIO_PBSC_PBC1             ((uint32_t)0x00020000U) /* Port x Reset bit 1  */
#define GPIO_PBSC_PBC2             ((uint32_t)0x00040000U) /* Port x Reset bit 2  */
#define GPIO_PBSC_PBC3             ((uint32_t)0x00080000U) /* Port x Reset bit 3  */
#define GPIO_PBSC_PBC4             ((uint32_t)0x00100000U) /* Port x Reset bit 4  */
#define GPIO_PBSC_PBC5             ((uint32_t)0x00200000U) /* Port x Reset bit 5  */
#define GPIO_PBSC_PBC6             ((uint32_t)0x00400000U) /* Port x Reset bit 6  */
#define GPIO_PBSC_PBC7             ((uint32_t)0x00800000U) /* Port x Reset bit 7  */
#define GPIO_PBSC_PBC8             ((uint32_t)0x01000000U) /* Port x Reset bit 8  */
#define GPIO_PBSC_PBC9             ((uint32_t)0x02000000U) /* Port x Reset bit 9  */
#define GPIO_PBSC_PBC10            ((uint32_t)0x04000000U) /* Port x Reset bit 10 */
#define GPIO_PBSC_PBC11            ((uint32_t)0x08000000U) /* Port x Reset bit 11 */
#define GPIO_PBSC_PBC12            ((uint32_t)0x10000000U) /* Port x Reset bit 12 */
#define GPIO_PBSC_PBC13            ((uint32_t)0x20000000U) /* Port x Reset bit 13 */
#define GPIO_PBSC_PBC14            ((uint32_t)0x40000000U) /* Port x Reset bit 14 */
#define GPIO_PBSC_PBC15            ((uint32_t)0x80000000U) /* Port x Reset bit 15 */

/**  Bit definition for GPIO_PLOCK register **/
#define GPIO_PLOCK_PLOCK0          ((uint32_t)0x00000001U) /* Port x Lock bit 0  */
#define GPIO_PLOCK_PLOCK1          ((uint32_t)0x00000002U) /* Port x Lock bit 1  */
#define GPIO_PLOCK_PLOCK2          ((uint32_t)0x00000004U) /* Port x Lock bit 2  */
#define GPIO_PLOCK_PLOCK3          ((uint32_t)0x00000008U) /* Port x Lock bit 3  */
#define GPIO_PLOCK_PLOCK4          ((uint32_t)0x00000010U) /* Port x Lock bit 4  */
#define GPIO_PLOCK_PLOCK5          ((uint32_t)0x00000020U) /* Port x Lock bit 5  */
#define GPIO_PLOCK_PLOCK6          ((uint32_t)0x00000040U) /* Port x Lock bit 6  */
#define GPIO_PLOCK_PLOCK7          ((uint32_t)0x00000080U) /* Port x Lock bit 7  */
#define GPIO_PLOCK_PLOCK8          ((uint32_t)0x00000100U) /* Port x Lock bit 8  */
#define GPIO_PLOCK_PLOCK9          ((uint32_t)0x00000200U) /* Port x Lock bit 9  */
#define GPIO_PLOCK_PLOCK10         ((uint32_t)0x00000400U) /* Port x Lock bit 10 */
#define GPIO_PLOCK_PLOCK11         ((uint32_t)0x00000800U) /* Port x Lock bit 11 */
#define GPIO_PLOCK_PLOCK12         ((uint32_t)0x00001000U) /* Port x Lock bit 12 */
#define GPIO_PLOCK_PLOCK13         ((uint32_t)0x00002000U) /* Port x Lock bit 13 */
#define GPIO_PLOCK_PLOCK14         ((uint32_t)0x00004000U) /* Port x Lock bit 14 */
#define GPIO_PLOCK_PLOCK15         ((uint32_t)0x00008000U) /* Port x Lock bit 15 */
#define GPIO_PLOCK_PLOCKK          ((uint32_t)0x00010000U) /* Lock key */

/** Bit definition for GPIO_AFL register **/
#define GPIO_AFL_AFSEL0            ((uint32_t)0x0000000FU) /* Port x AFL bit (0..3) */
#define GPIO_AFL_AFSEL1            ((uint32_t)0x000000F0U) /* Port x AFL bit (4..7) */
#define GPIO_AFL_AFSEL2            ((uint32_t)0x00000F00U) /* Port x AFL bit (8..11) */
#define GPIO_AFL_AFSEL3            ((uint32_t)0x0000F000U) /* Port x AFL bit (12..15) */
#define GPIO_AFL_AFSEL4            ((uint32_t)0x000F0000U) /* Port x AFL bit (16..19) */
#define GPIO_AFL_AFSEL5            ((uint32_t)0x00F00000U) /* Port x AFL bit (20..23) */
#define GPIO_AFL_AFSEL6            ((uint32_t)0x0F000000U) /* Port x AFL bit (24..27) */
#define GPIO_AFL_AFSEL7            ((uint32_t)0xF0000000U) /* Port x AFL bit (27..31) */

/** Bit definition for GPIO_AFH register **/
#define GPIO_AFH_AFSEL8            ((uint32_t)0x0000000FU) /* Port x AFH bit (0..3) */
#define GPIO_AFH_AFSEL9            ((uint32_t)0x000000F0U) /* Port x AFH bit (4..7) */
#define GPIO_AFH_AFSEL10           ((uint32_t)0x00000F00U) /* Port x AFH bit (8..11) */
#define GPIO_AFH_AFSEL11           ((uint32_t)0x0000F000U) /* Port x AFH bit (12..15) */
#define GPIO_AFH_AFSEL12           ((uint32_t)0x000F0000U) /* Port x AFH bit (16..19) */
#define GPIO_AFH_AFSEL13           ((uint32_t)0x00F00000U) /* Port x AFH bit (20..23) */
#define GPIO_AFH_AFSEL14           ((uint32_t)0x0F000000U) /* Port x AFH bit (24..27) */
#define GPIO_AFH_AFSEL15           ((uint32_t)0xF0000000U) /* Port x AFH bit (28..31) */

/** Bit definition for GPIO_PBC register **/
#define GPIO_PBC_PBC0              ((uint16_t)0x0001U) /* Port x Reset bit 0  */
#define GPIO_PBC_PBC1              ((uint16_t)0x0002U) /* Port x Reset bit 1  */
#define GPIO_PBC_PBC2              ((uint16_t)0x0004U) /* Port x Reset bit 2  */
#define GPIO_PBC_PBC3              ((uint16_t)0x0008U) /* Port x Reset bit 3  */
#define GPIO_PBC_PBC4              ((uint16_t)0x0010U) /* Port x Reset bit 4  */
#define GPIO_PBC_PBC5              ((uint16_t)0x0020U) /* Port x Reset bit 5  */
#define GPIO_PBC_PBC6              ((uint16_t)0x0040U) /* Port x Reset bit 6  */
#define GPIO_PBC_PBC7              ((uint16_t)0x0080U) /* Port x Reset bit 7  */
#define GPIO_PBC_PBC8              ((uint16_t)0x0100U) /* Port x Reset bit 8  */
#define GPIO_PBC_PBC9              ((uint16_t)0x0200U) /* Port x Reset bit 9  */
#define GPIO_PBC_PBC10             ((uint16_t)0x0400U) /* Port x Reset bit 10 */
#define GPIO_PBC_PBC11             ((uint16_t)0x0800U) /* Port x Reset bit 11 */
#define GPIO_PBC_PBC12             ((uint16_t)0x1000U) /* Port x Reset bit 12 */
#define GPIO_PBC_PBC13             ((uint16_t)0x2000U) /* Port x Reset bit 13 */
#define GPIO_PBC_PBC14             ((uint16_t)0x4000U) /* Port x Reset bit 14 */
#define GPIO_PBC_PBC15             ((uint16_t)0x8000U) /* Port x Reset bit 15 */

/** Bit definition for GPIO_DS register **/
#define GPIO_DS_DS0          ((uint32_t)0x00000001U) /* Port x DS bit 0  */
#define GPIO_DS_DS1          ((uint32_t)0x00000002U) /* Port x DS bit 1  */
#define GPIO_DS_DS2          ((uint32_t)0x00000004U) /* Port x DS bit 2  */
#define GPIO_DS_DS3          ((uint32_t)0x00000008U) /* Port x DS bit 3  */
#define GPIO_DS_DS4          ((uint32_t)0x00000010U) /* Port x DS bit 4  */
#define GPIO_DS_DS5          ((uint32_t)0x00000020U) /* Port x DS bit 5  */
#define GPIO_DS_DS6          ((uint32_t)0x00000040U) /* Port x DS bit 6  */
#define GPIO_DS_DS7          ((uint32_t)0x00000080U) /* Port x DS bit 7  */
#define GPIO_DS_DS8          ((uint32_t)0x00000100U) /* Port x DS bit 8  */
#define GPIO_DS_DS9          ((uint32_t)0x00000200U) /* Port x DS bit 9  */
#define GPIO_DS_DS10         ((uint32_t)0x00000400U) /* Port x DS bit 10 */
#define GPIO_DS_DS11         ((uint32_t)0x00000800U) /* Port x DS bit 11 */
#define GPIO_DS_DS12         ((uint32_t)0x00001000U) /* Port x DS bit 12 */
#define GPIO_DS_DS13         ((uint32_t)0x00002000U) /* Port x DS bit 13 */
#define GPIO_DS_DS14         ((uint32_t)0x00004000U) /* Port x DS bit 14 */
#define GPIO_DS_DS15         ((uint32_t)0x00008000U) /* Port x DS bit 15 */

/** Bit definition for GPIO_DS register **/
#define GPIO_DS_SR0          ((uint32_t)0x00010000U) /* GPIOA_DS bit 16 */
#define GPIO_DS_SR1          ((uint32_t)0x00020000U) /* GPIOA_DS bit 17 */
#define GPIO_DS_SR2          ((uint32_t)0x00040000U) /* GPIOA_DS bit 18 */
#define GPIO_DS_SR5          ((uint32_t)0x00200000U) /* GPIOB_DS bit 21 */
#define GPIO_DS_SR6          ((uint32_t)0x00400000U) /* GPIOB_DS bit 22 */
#define GPIO_DS_SR7          ((uint32_t)0x00800000U) /* GPIOB_DS bit 23 */

/** Bit definition for AFIO register **/

/******** Bit definition for AFIO_CFG register  ********/
#define AFIO_CFG_SPI2_NSS                                      ((uint32_t)0x00800000)         /* Bit[23] */
#define AFIO_CFG_SPI1_NSS                                      ((uint32_t)0x00400000)         /* Bit[22] */
#define AFIO_CFG_EXTIFLITEN                                    ((uint32_t)0x00000008)         /* Bit[3] */
#define AFIO_CFG_IOFILTCFG                                     ((uint32_t)0x00000003)         /* Bit[1:0] */
#define AFIO_CFG_IOFILTCFG_0                                   ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_CFG_IOFILTCFG_1                                   ((uint32_t)0x00000002)         /* Bit1*/

/******** Bit definition for AFIO_EXTI_CFG1 register  ********/
#define AFIO_EXTI_CFG1_EXTI3_CFG                               ((uint32_t)0x00007000)         /* Bit[14:12] */
#define AFIO_EXTI_CFG1_EXTI3_CFG_0                             ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_EXTI_CFG1_EXTI3_CFG_1                             ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_EXTI_CFG1_EXTI3_CFG_2                             ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_EXTI_CFG1_EXTI2_CFG                               ((uint32_t)0x00000700)         /* Bit[10:8] */
#define AFIO_EXTI_CFG1_EXTI2_CFG_0                             ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_EXTI_CFG1_EXTI2_CFG_1                             ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_EXTI_CFG1_EXTI2_CFG_2                             ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_EXTI_CFG1_EXTI1_CFG                               ((uint32_t)0x00000070)         /* Bit[6:4] */
#define AFIO_EXTI_CFG1_EXTI1_CFG_0                             ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_EXTI_CFG1_EXTI1_CFG_1                             ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_EXTI_CFG1_EXTI1_CFG_2                             ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_EXTI_CFG1_EXTI0_CFG                               ((uint32_t)0x00000007)         /* Bit[2:0] */
#define AFIO_EXTI_CFG1_EXTI0_CFG_0                             ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_EXTI_CFG1_EXTI0_CFG_1                             ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_EXTI_CFG1_EXTI0_CFG_2                             ((uint32_t)0x00000004)         /* Bit2*/

/******** Bit definition for AFIO_EXTI_CFG2 register  ********/
#define AFIO_EXTI_CFG2_EXTI7_CFG                               ((uint32_t)0x00007000)         /* Bit[14:12] */
#define AFIO_EXTI_CFG2_EXTI7_CFG_0                             ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_EXTI_CFG2_EXTI7_CFG_1                             ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_EXTI_CFG2_EXTI7_CFG_2                             ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_EXTI_CFG2_EXTI6_CFG                               ((uint32_t)0x00000700)         /* Bit[10:8] */
#define AFIO_EXTI_CFG2_EXTI6_CFG_0                             ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_EXTI_CFG2_EXTI6_CFG_1                             ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_EXTI_CFG2_EXTI6_CFG_2                             ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_EXTI_CFG2_EXTI5_CFG                               ((uint32_t)0x00000070)         /* Bit[6:4] */
#define AFIO_EXTI_CFG2_EXTI5_CFG_0                             ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_EXTI_CFG2_EXTI5_CFG_1                             ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_EXTI_CFG2_EXTI5_CFG_2                             ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_EXTI_CFG2_EXTI4_CFG                               ((uint32_t)0x00000007)         /* Bit[2:0] */
#define AFIO_EXTI_CFG2_EXTI4_CFG_0                             ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_EXTI_CFG2_EXTI4_CFG_1                             ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_EXTI_CFG2_EXTI4_CFG_2                             ((uint32_t)0x00000004)         /* Bit2*/

/******** Bit definition for AFIO_EXTI_CFG3 register  ********/
#define AFIO_EXTI_CFG3_EXTI11_CFG                              ((uint32_t)0x00007000)         /* Bit[14:12] */
#define AFIO_EXTI_CFG3_EXTI11_CFG_0                            ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_EXTI_CFG3_EXTI11_CFG_1                            ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_EXTI_CFG3_EXTI11_CFG_2                            ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_EXTI_CFG3_EXTI10_CFG                              ((uint32_t)0x00000700)         /* Bit[10:8] */
#define AFIO_EXTI_CFG3_EXTI10_CFG_0                            ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_EXTI_CFG3_EXTI10_CFG_1                            ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_EXTI_CFG3_EXTI10_CFG_2                            ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_EXTI_CFG3_EXTI9_CFG                               ((uint32_t)0x00000070)         /* Bit[6:4] */
#define AFIO_EXTI_CFG3_EXTI9_CFG_0                             ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_EXTI_CFG3_EXTI9_CFG_1                             ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_EXTI_CFG3_EXTI9_CFG_2                             ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_EXTI_CFG3_EXTI8_CFG                               ((uint32_t)0x00000007)         /* Bit[2:0] */
#define AFIO_EXTI_CFG3_EXTI8_CFG_0                             ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_EXTI_CFG3_EXTI8_CFG_1                             ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_EXTI_CFG3_EXTI8_CFG_2                             ((uint32_t)0x00000004)         /* Bit2*/

/******** Bit definition for AFIO_EXTI_CFG4 register  ********/
#define AFIO_EXTI_CFG4_EXTI15_CFG                              ((uint32_t)0x00007000)         /* Bit[14:12] */
#define AFIO_EXTI_CFG4_EXTI15_CFG_0                            ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_EXTI_CFG4_EXTI15_CFG_1                            ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_EXTI_CFG4_EXTI15_CFG_2                            ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_EXTI_CFG4_EXTI14_CFG                              ((uint32_t)0x00000700)         /* Bit[10:8] */
#define AFIO_EXTI_CFG4_EXTI14_CFG_0                            ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_EXTI_CFG4_EXTI14_CFG_1                            ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_EXTI_CFG4_EXTI14_CFG_2                            ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_EXTI_CFG4_EXTI13_CFG                              ((uint32_t)0x00000070)         /* Bit[6:4] */
#define AFIO_EXTI_CFG4_EXTI13_CFG_0                            ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_EXTI_CFG4_EXTI13_CFG_1                            ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_EXTI_CFG4_EXTI13_CFG_2                            ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_EXTI_CFG4_EXTI12_CFG                              ((uint32_t)0x00000007)         /* Bit[2:0] */
#define AFIO_EXTI_CFG4_EXTI12_CFG_0                            ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_EXTI_CFG4_EXTI12_CFG_1                            ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_EXTI_CFG4_EXTI12_CFG_2                            ((uint32_t)0x00000004)         /* Bit2*/

/******** Bit definition for AFIO_DIGEFT_CFG1 register  ********/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN                           ((uint32_t)0x0000FFFF)         /* Bit[15:0] */
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_0                         ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_1                         ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_2                         ((uint32_t)0x00000004)         /* Bit2*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_3                         ((uint32_t)0x00000008)         /* Bit3*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_4                         ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_5                         ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_6                         ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_7                         ((uint32_t)0x00000080)         /* Bit7*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_8                         ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_9                         ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_10                        ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_11                        ((uint32_t)0x00000800)         /* Bit11*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_12                        ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_13                        ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_14                        ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_DIGEFT_CFG1_PAyDIGEFTEN_15                        ((uint32_t)0x00008000)         /* Bit15*/

/******** Bit definition for AFIO_DIGEFT_CFG2 register  ********/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN                           ((uint32_t)0x0000FFFF)         /* Bit[15:0] */
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_0                         ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_1                         ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_2                         ((uint32_t)0x00000004)         /* Bit2*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_3                         ((uint32_t)0x00000008)         /* Bit3*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_4                         ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_5                         ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_6                         ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_7                         ((uint32_t)0x00000080)         /* Bit7*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_8                         ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_9                         ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_10                        ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_11                        ((uint32_t)0x00000800)         /* Bit11*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_12                        ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_13                        ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_14                        ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_DIGEFT_CFG2_PByDIGEFTEN_15                        ((uint32_t)0x00008000)         /* Bit15*/

/******** Bit definition for AFIO_DIGEFT_CFG3 register  ********/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN                           ((uint32_t)0x0000FFFF)         /* Bit[15:0] */
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_0                         ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_1                         ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_2                         ((uint32_t)0x00000004)         /* Bit2*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_3                         ((uint32_t)0x00000008)         /* Bit3*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_4                         ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_5                         ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_6                         ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_7                         ((uint32_t)0x00000080)         /* Bit7*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_8                         ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_9                         ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_10                        ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_11                        ((uint32_t)0x00000800)         /* Bit11*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_12                        ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_13                        ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_14                        ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_DIGEFT_CFG3_PCyDIGEFTEN_15                        ((uint32_t)0x00008000)         /* Bit15*/

/******** Bit definition for AFIO_DIGEFT_CFG3 register  ********/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN                           ((uint32_t)0x0000FFFF)         /* Bit[15:0] */
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_0                         ((uint32_t)0x00000001)         /* Bit0*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_1                         ((uint32_t)0x00000002)         /* Bit1*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_2                         ((uint32_t)0x00000004)         /* Bit2*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_3                         ((uint32_t)0x00000008)         /* Bit3*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_4                         ((uint32_t)0x00000010)         /* Bit4*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_5                         ((uint32_t)0x00000020)         /* Bit5*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_6                         ((uint32_t)0x00000040)         /* Bit6*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_7                         ((uint32_t)0x00000080)         /* Bit7*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_8                         ((uint32_t)0x00000100)         /* Bit8*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_9                         ((uint32_t)0x00000200)         /* Bit9*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_10                        ((uint32_t)0x00000400)         /* Bit10*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_11                        ((uint32_t)0x00000800)         /* Bit11*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_12                        ((uint32_t)0x00001000)         /* Bit12*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_13                        ((uint32_t)0x00002000)         /* Bit13*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_14                        ((uint32_t)0x00004000)         /* Bit14*/
#define AFIO_DIGEFT_CFG3_PDyDIGEFTEN_15                        ((uint32_t)0x00008000)         /* Bit15*/


/*** External Interrupt/Event Controller ***/

/** Bit definition for EXTI_EMASK register **/
#define EXTI_EMASK_EMASK0  ((uint32_t)0x00000001) /** Event Mask on line 0 */
#define EXTI_EMASK_EMASK1  ((uint32_t)0x00000002) /** Event Mask on line 1 */
#define EXTI_EMASK_EMASK2  ((uint32_t)0x00000004) /** Event Mask on line 2 */
#define EXTI_EMASK_EMASK3  ((uint32_t)0x00000008) /** Event Mask on line 3 */
#define EXTI_EMASK_EMASK4  ((uint32_t)0x00000010) /** Event Mask on line 4 */
#define EXTI_EMASK_EMASK5  ((uint32_t)0x00000020) /** Event Mask on line 5 */
#define EXTI_EMASK_EMASK6  ((uint32_t)0x00000040) /** Event Mask on line 6 */
#define EXTI_EMASK_EMASK7  ((uint32_t)0x00000080) /** Event Mask on line 7 */
#define EXTI_EMASK_EMASK8  ((uint32_t)0x00000100) /** Event Mask on line 8 */
#define EXTI_EMASK_EMASK9  ((uint32_t)0x00000200) /** Event Mask on line 9 */
#define EXTI_EMASK_EMASK10 ((uint32_t)0x00000400) /** Event Mask on line 10 */
#define EXTI_EMASK_EMASK11 ((uint32_t)0x00000800) /** Event Mask on line 11 */
#define EXTI_EMASK_EMASK12 ((uint32_t)0x00001000) /** Event Mask on line 12 */
#define EXTI_EMASK_EMASK13 ((uint32_t)0x00002000) /** Event Mask on line 13 */
#define EXTI_EMASK_EMASK14 ((uint32_t)0x00004000) /** Event Mask on line 14 */
#define EXTI_EMASK_EMASK15 ((uint32_t)0x00008000) /** Event Mask on line 15 */
#define EXTI_EMASK_EMASK16 ((uint32_t)0x00010000) /** Event Mask on line 16 */
#define EXTI_EMASK_EMASK17 ((uint32_t)0x00020000) /** Event Mask on line 17 */
#define EXTI_EMASK_EMASK18 ((uint32_t)0x00040000) /** Event Mask on line 18 */
#define EXTI_EMASK_EMASK19 ((uint32_t)0x00080000) /** Event Mask on line 19 */
#define EXTI_EMASK_EMASK20 ((uint32_t)0x00100000) /** Event Mask on line 20 */
#define EXTI_EMASK_EMASK21 ((uint32_t)0x00200000) /** Event Mask on line 21 */
#define EXTI_EMASK_EMASK22 ((uint32_t)0x00400000) /** Event Mask on line 22 */
#define EXTI_EMASK_EMASK23 ((uint32_t)0x00800000) /** Event Mask on line 23 */
#define EXTI_EMASK_EMASK24 ((uint32_t)0x01000000) /** Event Mask on line 24 */
#define EXTI_EMASK_EMASK25 ((uint32_t)0x02000000) /** Event Mask on line 25 */

/** Bit definition for EXTI_IMASK register **/
#define EXTI_IMASK_IMASK0  ((uint32_t)0x00000001) /** Interrupt Mask on line 0 */
#define EXTI_IMASK_IMASK1  ((uint32_t)0x00000002) /** Interrupt Mask on line 1 */
#define EXTI_IMASK_IMASK2  ((uint32_t)0x00000004) /** Interrupt Mask on line 2 */
#define EXTI_IMASK_IMASK3  ((uint32_t)0x00000008) /** Interrupt Mask on line 3 */
#define EXTI_IMASK_IMASK4  ((uint32_t)0x00000010) /** Interrupt Mask on line 4 */
#define EXTI_IMASK_IMASK5  ((uint32_t)0x00000020) /** Interrupt Mask on line 5 */
#define EXTI_IMASK_IMASK6  ((uint32_t)0x00000040) /** Interrupt Mask on line 6 */
#define EXTI_IMASK_IMASK7  ((uint32_t)0x00000080) /** Interrupt Mask on line 7 */
#define EXTI_IMASK_IMASK8  ((uint32_t)0x00000100) /** Interrupt Mask on line 8 */
#define EXTI_IMASK_IMASK9  ((uint32_t)0x00000200) /** Interrupt Mask on line 9 */
#define EXTI_IMASK_IMASK10 ((uint32_t)0x00000400) /** Interrupt Mask on line 10 */
#define EXTI_IMASK_IMASK11 ((uint32_t)0x00000800) /** Interrupt Mask on line 11 */
#define EXTI_IMASK_IMASK12 ((uint32_t)0x00001000) /** Interrupt Mask on line 12 */
#define EXTI_IMASK_IMASK13 ((uint32_t)0x00002000) /** Interrupt Mask on line 13 */
#define EXTI_IMASK_IMASK14 ((uint32_t)0x00004000) /** Interrupt Mask on line 14 */
#define EXTI_IMASK_IMASK15 ((uint32_t)0x00008000) /** Interrupt Mask on line 15 */
#define EXTI_IMASK_IMASK16 ((uint32_t)0x00010000) /** Interrupt Mask on line 16 */
#define EXTI_IMASK_IMASK17 ((uint32_t)0x00020000) /** Interrupt Mask on line 17 */
#define EXTI_IMASK_IMASK18 ((uint32_t)0x00040000) /** Interrupt Mask on line 18 */
#define EXTI_IMASK_IMASK19 ((uint32_t)0x00080000) /** Interrupt Mask on line 19 */
#define EXTI_IMASK_IMASK20 ((uint32_t)0x00100000) /** Interrupt Mask on line 20 */
#define EXTI_IMASK_IMASK21 ((uint32_t)0x00200000) /** Interrupt Mask on line 21 */
#define EXTI_IMASK_IMASK22 ((uint32_t)0x00400000) /** Interrupt Mask on line 22 */
#define EXTI_IMASK_IMASK23 ((uint32_t)0x00800000) /** Interrupt Mask on line 23 */
#define EXTI_IMASK_IMASK24 ((uint32_t)0x01000000) /** Interrupt Mask on line 24 */
#define EXTI_IMASK_IMASK25 ((uint32_t)0x02000000) /** Interrupt Mask on line 25 */

/** Bit definition for EXTI_FT_CFG register **/
#define EXTI_FT_CFG_FT_CFG0  ((uint32_t)0x00000001) /** Falling trigger event configuration bit of line 0 */
#define EXTI_FT_CFG_FT_CFG1  ((uint32_t)0x00000002) /** Falling trigger event configuration bit of line 1 */
#define EXTI_FT_CFG_FT_CFG2  ((uint32_t)0x00000004) /** Falling trigger event configuration bit of line 2 */
#define EXTI_FT_CFG_FT_CFG3  ((uint32_t)0x00000008) /** Falling trigger event configuration bit of line 3 */
#define EXTI_FT_CFG_FT_CFG4  ((uint32_t)0x00000010) /** Falling trigger event configuration bit of line 4 */
#define EXTI_FT_CFG_FT_CFG5  ((uint32_t)0x00000020) /** Falling trigger event configuration bit of line 5 */
#define EXTI_FT_CFG_FT_CFG6  ((uint32_t)0x00000040) /** Falling trigger event configuration bit of line 6 */
#define EXTI_FT_CFG_FT_CFG7  ((uint32_t)0x00000080) /** Falling trigger event configuration bit of line 7 */
#define EXTI_FT_CFG_FT_CFG8  ((uint32_t)0x00000100) /** Falling trigger event configuration bit of line 8 */
#define EXTI_FT_CFG_FT_CFG9  ((uint32_t)0x00000200) /** Falling trigger event configuration bit of line 9 */
#define EXTI_FT_CFG_FT_CFG10 ((uint32_t)0x00000400) /** Falling trigger event configuration bit of line 10 */
#define EXTI_FT_CFG_FT_CFG11 ((uint32_t)0x00000800) /** Falling trigger event configuration bit of line 11 */
#define EXTI_FT_CFG_FT_CFG12 ((uint32_t)0x00001000) /** Falling trigger event configuration bit of line 12 */
#define EXTI_FT_CFG_FT_CFG13 ((uint32_t)0x00002000) /** Falling trigger event configuration bit of line 13 */
#define EXTI_FT_CFG_FT_CFG14 ((uint32_t)0x00004000) /** Falling trigger event configuration bit of line 14 */
#define EXTI_FT_CFG_FT_CFG15 ((uint32_t)0x00008000) /** Falling trigger event configuration bit of line 15 */
#define EXTI_FT_CFG_FT_CFG16 ((uint32_t)0x00010000) /** Falling trigger event configuration bit of line 16 */
#define EXTI_FT_CFG_FT_CFG17 ((uint32_t)0x00020000) /** Falling trigger event configuration bit of line 17 */
#define EXTI_FT_CFG_FT_CFG18 ((uint32_t)0x00040000) /** Falling trigger event configuration bit of line 18 */
#define EXTI_FT_CFG_FT_CFG19 ((uint32_t)0x00080000) /** Falling trigger event configuration bit of line 19 */
#define EXTI_FT_CFG_FT_CFG20 ((uint32_t)0x00100000) /** Falling trigger event configuration bit of line 20 */
#define EXTI_FT_CFG_FT_CFG21 ((uint32_t)0x00200000) /** Falling trigger event configuration bit of line 21 */
#define EXTI_FT_CFG_FT_CFG22 ((uint32_t)0x00400000) /** Falling trigger event configuration bit of line 22 */
#define EXTI_FT_CFG_FT_CFG23 ((uint32_t)0x00800000) /** Falling trigger event configuration bit of line 23 */
#define EXTI_FT_CFG_FT_CFG24 ((uint32_t)0x01000000) /** Falling trigger event configuration bit of line 24 */
#define EXTI_FT_CFG_FT_CFG25 ((uint32_t)0x02000000) /** Falling trigger event configuration bit of line 25 */

/** Bit definition for EXTI_RT_CFG register **/
#define EXTI_RT_CFG_RT_CFG0  ((uint32_t)0x00000001) /** Rising trigger event configuration bit of line 0 */
#define EXTI_RT_CFG_RT_CFG1  ((uint32_t)0x00000002) /** Rising trigger event configuration bit of line 1 */
#define EXTI_RT_CFG_RT_CFG2  ((uint32_t)0x00000004) /** Rising trigger event configuration bit of line 2 */
#define EXTI_RT_CFG_RT_CFG3  ((uint32_t)0x00000008) /** Rising trigger event configuration bit of line 3 */
#define EXTI_RT_CFG_RT_CFG4  ((uint32_t)0x00000010) /** Rising trigger event configuration bit of line 4 */
#define EXTI_RT_CFG_RT_CFG5  ((uint32_t)0x00000020) /** Rising trigger event configuration bit of line 5 */
#define EXTI_RT_CFG_RT_CFG6  ((uint32_t)0x00000040) /** Rising trigger event configuration bit of line 6 */
#define EXTI_RT_CFG_RT_CFG7  ((uint32_t)0x00000080) /** Rising trigger event configuration bit of line 7 */
#define EXTI_RT_CFG_RT_CFG8  ((uint32_t)0x00000100) /** Rising trigger event configuration bit of line 8 */
#define EXTI_RT_CFG_RT_CFG9  ((uint32_t)0x00000200) /** Rising trigger event configuration bit of line 9 */
#define EXTI_RT_CFG_RT_CFG10 ((uint32_t)0x00000400) /** Rising trigger event configuration bit of line 10 */
#define EXTI_RT_CFG_RT_CFG11 ((uint32_t)0x00000800) /** Rising trigger event configuration bit of line 11 */
#define EXTI_RT_CFG_RT_CFG12 ((uint32_t)0x00001000) /** Rising trigger event configuration bit of line 12 */
#define EXTI_RT_CFG_RT_CFG13 ((uint32_t)0x00002000) /** Rising trigger event configuration bit of line 13 */
#define EXTI_RT_CFG_RT_CFG14 ((uint32_t)0x00004000) /** Rising trigger event configuration bit of line 14 */
#define EXTI_RT_CFG_RT_CFG15 ((uint32_t)0x00008000) /** Rising trigger event configuration bit of line 15 */
#define EXTI_RT_CFG_RT_CFG16 ((uint32_t)0x00010000) /** Rising trigger event configuration bit of line 16 */
#define EXTI_RT_CFG_RT_CFG17 ((uint32_t)0x00020000) /** Rising trigger event configuration bit of line 17 */
#define EXTI_RT_CFG_RT_CFG18 ((uint32_t)0x00040000) /** Rising trigger event configuration bit of line 18 */
#define EXTI_RT_CFG_RT_CFG19 ((uint32_t)0x00080000) /** Rising trigger event configuration bit of line 19 */
#define EXTI_RT_CFG_RT_CFG20 ((uint32_t)0x00100000) /** Rising trigger event configuration bit of line 20 */
#define EXTI_RT_CFG_RT_CFG21 ((uint32_t)0x00200000) /** Rising trigger event configuration bit of line 21 */
#define EXTI_RT_CFG_RT_CFG22 ((uint32_t)0x00400000) /** Rising trigger event configuration bit of line 22 */
#define EXTI_RT_CFG_RT_CFG23 ((uint32_t)0x00800000) /** Rising trigger event configuration bit of line 23 */
#define EXTI_RT_CFG_RT_CFG24 ((uint32_t)0x01000000) /** Rising trigger event configuration bit of line 24 */
#define EXTI_RT_CFG_RT_CFG25 ((uint32_t)0x02000000) /** Rising trigger event configuration bit of line 25 */

/** Bit definition for EXTI_PEND register **/
#define EXTI_PEND_PEND0  ((uint32_t)0x00000001) /** Pending bit for line 0 */
#define EXTI_PEND_PEND1  ((uint32_t)0x00000002) /** Pending bit for line 1 */
#define EXTI_PEND_PEND2  ((uint32_t)0x00000004) /** Pending bit for line 2 */
#define EXTI_PEND_PEND3  ((uint32_t)0x00000008) /** Pending bit for line 3 */
#define EXTI_PEND_PEND4  ((uint32_t)0x00000010) /** Pending bit for line 4 */
#define EXTI_PEND_PEND5  ((uint32_t)0x00000020) /** Pending bit for line 5 */
#define EXTI_PEND_PEND6  ((uint32_t)0x00000040) /** Pending bit for line 6 */
#define EXTI_PEND_PEND7  ((uint32_t)0x00000080) /** Pending bit for line 7 */
#define EXTI_PEND_PEND8  ((uint32_t)0x00000100) /** Pending bit for line 8 */
#define EXTI_PEND_PEND9  ((uint32_t)0x00000200) /** Pending bit for line 9 */
#define EXTI_PEND_PEND10 ((uint32_t)0x00000400) /** Pending bit for line 10 */
#define EXTI_PEND_PEND11 ((uint32_t)0x00000800) /** Pending bit for line 11 */
#define EXTI_PEND_PEND12 ((uint32_t)0x00001000) /** Pending bit for line 12 */
#define EXTI_PEND_PEND13 ((uint32_t)0x00002000) /** Pending bit for line 13 */
#define EXTI_PEND_PEND14 ((uint32_t)0x00004000) /** Pending bit for line 14 */
#define EXTI_PEND_PEND15 ((uint32_t)0x00008000) /** Pending bit for line 15 */
#define EXTI_PEND_PEND16 ((uint32_t)0x00010000) /** Pending bit for line 16 */
#define EXTI_PEND_PEND17 ((uint32_t)0x00020000) /** Pending bit for line 17 */
#define EXTI_PEND_PEND18 ((uint32_t)0x00040000) /** Pending bit for line 18 */
#define EXTI_PEND_PEND19 ((uint32_t)0x00080000) /** Pending bit for line 19 */
#define EXTI_PEND_PEND20 ((uint32_t)0x00100000) /** Pending bit for line 20 */
#define EXTI_PEND_PEND21 ((uint32_t)0x00200000) /** Pending bit for line 21 */
#define EXTI_PEND_PEND22 ((uint32_t)0x00400000) /** Pending bit for line 22 */
#define EXTI_PEND_PEND23 ((uint32_t)0x00800000) /** Pending bit for line 23 */
#define EXTI_PEND_PEND24 ((uint32_t)0x01000000) /** Pending bit for line 24 */
#define EXTI_PEND_PEND25 ((uint32_t)0x02000000) /** Pending bit for line 25 */

/** Bit definition for EXTI_SWIE register **/
#define EXTI_SWIE_SWIE0  ((uint32_t)0x00000001) /** Software Interrupt on line 0 */
#define EXTI_SWIE_SWIE1  ((uint32_t)0x00000002) /** Software Interrupt on line 1 */
#define EXTI_SWIE_SWIE2  ((uint32_t)0x00000004) /** Software Interrupt on line 2 */
#define EXTI_SWIE_SWIE3  ((uint32_t)0x00000008) /** Software Interrupt on line 3 */
#define EXTI_SWIE_SWIE4  ((uint32_t)0x00000010) /** Software Interrupt on line 4 */
#define EXTI_SWIE_SWIE5  ((uint32_t)0x00000020) /** Software Interrupt on line 5 */
#define EXTI_SWIE_SWIE6  ((uint32_t)0x00000040) /** Software Interrupt on line 6 */
#define EXTI_SWIE_SWIE7  ((uint32_t)0x00000080) /** Software Interrupt on line 7 */
#define EXTI_SWIE_SWIE8  ((uint32_t)0x00000100) /** Software Interrupt on line 8 */
#define EXTI_SWIE_SWIE9  ((uint32_t)0x00000200) /** Software Interrupt on line 9 */
#define EXTI_SWIE_SWIE10 ((uint32_t)0x00000400) /** Software Interrupt on line 10 */
#define EXTI_SWIE_SWIE11 ((uint32_t)0x00000800) /** Software Interrupt on line 11 */
#define EXTI_SWIE_SWIE12 ((uint32_t)0x00001000) /** Software Interrupt on line 12 */
#define EXTI_SWIE_SWIE13 ((uint32_t)0x00002000) /** Software Interrupt on line 13 */
#define EXTI_SWIE_SWIE14 ((uint32_t)0x00004000) /** Software Interrupt on line 14 */
#define EXTI_SWIE_SWIE15 ((uint32_t)0x00008000) /** Software Interrupt on line 15 */
#define EXTI_SWIE_SWIE16 ((uint32_t)0x00010000) /** Software Interrupt on line 16 */
#define EXTI_SWIE_SWIE17 ((uint32_t)0x00020000) /** Software Interrupt on line 17 */
#define EXTI_SWIE_SWIE18 ((uint32_t)0x00040000) /** Software Interrupt on line 18 */
#define EXTI_SWIE_SWIE19 ((uint32_t)0x00080000) /** Software Interrupt on line 19 */
#define EXTI_SWIE_SWIE20 ((uint32_t)0x00100000) /** Software Interrupt on line 20 */
#define EXTI_SWIE_SWIE21 ((uint32_t)0x00200000) /** Software Interrupt on line 21 */
#define EXTI_SWIE_SWIE22 ((uint32_t)0x00400000) /** Software Interrupt on line 22 */
#define EXTI_SWIE_SWIE23 ((uint32_t)0x00800000) /** Software Interrupt on line 23 */
#define EXTI_SWIE_SWIE24 ((uint32_t)0x01000000) /** Software Interrupt on line 24 */
#define EXTI_SWIE_SWIE25 ((uint32_t)0x02000000) /** Software Interrupt on line 25 */

/** Bit definition for EXTI_TS_SEL register **/
#define EXTI_TS_SEL_TSSEL   ((uint32_t)0x0000000F) /** EXTI Line input to the RTC TimeStamp */
#define EXTI_TS_SEL_TSSEL_0 ((uint32_t)0x00000001)
#define EXTI_TS_SEL_TSSEL_1 ((uint32_t)0x00000002)
#define EXTI_TS_SEL_TSSEL_2 ((uint32_t)0x00000004)
#define EXTI_TS_SEL_TSSEL_3 ((uint32_t)0x00000008)

/** Bit Offset register **/
#define REG_BIT1_OFFSET    ((uint32_t)0x00000001U)
#define REG_BIT2_OFFSET    ((uint32_t)0x00000002U)
#define REG_BIT3_OFFSET    ((uint32_t)0x00000003U)
#define REG_BIT4_OFFSET    ((uint32_t)0x00000004U)
#define REG_BIT5_OFFSET    ((uint32_t)0x00000005U)
#define REG_BIT6_OFFSET    ((uint32_t)0x00000006U)
#define REG_BIT7_OFFSET    ((uint32_t)0x00000007U)
#define REG_BIT8_OFFSET    ((uint32_t)0x00000008U)
#define REG_BIT9_OFFSET    ((uint32_t)0x00000009U)
#define REG_BIT10_OFFSET   ((uint32_t)0x0000000AU)
#define REG_BIT11_OFFSET   ((uint32_t)0x0000000BU)
#define REG_BIT12_OFFSET   ((uint32_t)0x0000000CU)
#define REG_BIT13_OFFSET   ((uint32_t)0x0000000DU)
#define REG_BIT14_OFFSET   ((uint32_t)0x0000000EU)
#define REG_BIT15_OFFSET   ((uint32_t)0x0000000FU)
#define REG_BIT16_OFFSET   ((uint32_t)0x00000010U)
#define REG_BIT17_OFFSET   ((uint32_t)0x00000011U)
#define REG_BIT18_OFFSET   ((uint32_t)0x00000012U)
#define REG_BIT19_OFFSET   ((uint32_t)0x00000013U)
#define REG_BIT20_OFFSET   ((uint32_t)0x00000014U)
#define REG_BIT21_OFFSET   ((uint32_t)0x00000015U)
#define REG_BIT22_OFFSET   ((uint32_t)0x00000016U)
#define REG_BIT23_OFFSET   ((uint32_t)0x00000017U)
#define REG_BIT24_OFFSET   ((uint32_t)0x00000018U)
#define REG_BIT25_OFFSET   ((uint32_t)0x00000019U)
#define REG_BIT26_OFFSET   ((uint32_t)0x0000001AU)
#define REG_BIT27_OFFSET   ((uint32_t)0x0000001BU)
#define REG_BIT28_OFFSET   ((uint32_t)0x0000001CU)
#define REG_BIT29_OFFSET   ((uint32_t)0x0000001DU)
#define REG_BIT30_OFFSET   ((uint32_t)0x0000001EU)
#define REG_BIT31_OFFSET   ((uint32_t)0x0000001FU)
#define REG_BIT32_OFFSET   ((uint32_t)0x00000020U)

/***********************  Common macro fuction define       *******************/

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK))) 

#define UNUSED(X)             (void)X

#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_H__ */
