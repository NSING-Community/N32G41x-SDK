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
*\*\file n32g41x_rcc.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
*/
#ifndef __N32G41X_RCC_H__
#define __N32G41X_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"


/** RCC_Exported_Types **/

typedef struct
{
    uint32_t SysclkFreq;    /* returns SYSCLK clock frequency expressed in Hz */
    uint32_t HclkFreq;      /* returns HCLK clock frequency expressed in Hz */
    uint32_t Pclk1Freq;     /* returns PCLK1 clock frequency expressed in Hz */
    uint32_t Pclk2Freq;     /* returns PCLK2 clock frequency expressed in Hz */
    uint32_t PllFreq;       /* returns PLL clock frequency expressed in Hz */
} RCC_ClocksType;


/** RCC RCC_REG_BIT_MASK **/
#define RCC_REG_BIT_MASK  				((uint32_t)0x00000000)

/* CTRL register bit mask */
#define CTRL_HSITRIM_MASK               (~RCC_CTRL_HSITRIM)
#define CTRL_LSITRIM_MASK               (~RCC_CTRL_LSITRIM)

#define CFG_SCLKSTS_MASK                 (~RCC_CFG_SCLKSTS)
#define CFG_SCLKSW_MASK                  (~RCC_CFG_SCLKSW)

/* EMCCTRL register bit mask */
#define EMCCTRL_GVDETSEL_MASK             (~RCC_EMCCTRL_GVDETSEL)
#define EMCCTRL_GBDETSEL_MASK             (~RCC_EMCCTRL_GBDETSEL)
#define EMCCTRL_GBNDETSEL_MASK            (~RCC_EMCCTRL_GBNDETSEL)

/* CLK Source ENABLE*/
#define RCC_LSI_ENABLE       			  (RCC_CTRL_LSIEN)
/** LSE_configuration **/
#define RCC_LSE_DISABLE                   (RCC_REG_BIT_MASK)
#define RCC_LSE_ENABLE                    (RCC_CTRL_LSEEN)
#define RCC_LSE_BYPASS                    (RCC_CTRL_LSEBP)

#define RCC_LSECSS_ENABLE     		      (RCC_CTRL_LSECSSEN)
#define RCC_PLL_ENABLE       			  (RCC_CTRL_PLLEN)
#define RCC_LSECAP_ENABLE			  	  (RCC_CTRL_LSECAPEN)
#define RCC_HSECAP_ENABLE			  	  (RCC_CTRL_HSECAPEN)
#define RCC_CLKSS_ENABLE			  	  (RCC_CTRL_CLKSSEN)
/** HSE_configuration **/
#define RCC_HSE_DISABLE                   (RCC_REG_BIT_MASK)
#define RCC_HSE_ENABLE                    (RCC_CTRL_HSEEN)
#define RCC_HSE_BYPASS                    (RCC_CTRL_HSEBP)

#define RCC_HSI_ENABLE                    (RCC_CTRL_HSIEN)

/* MCO DIV prescaler */
#define RCC_MCO_DIV_MASK  		(~RCC_CFG_MCOPRES)
#define RCC_MCO_CLK_DIV1  		(RCC_REG_BIT_MASK)
#define RCC_MCO_CLK_DIV2  		(RCC_CFG_MCOPRES_0)
#define RCC_MCO_CLK_DIV4  		(RCC_CFG_MCOPRES_1)
#define RCC_MCO_CLK_DIV8  		(RCC_CFG_MCOPRES_0|RCC_CFG_MCOPRES_1)
#define RCC_MCO_CLK_DIV16 		(RCC_CFG_MCOPRES_2)

/* RCC Flag Clock_source_to_output_on_MCO_pin */
#define RCC_MCO_MASK       	 	(~RCC_CFG_MCO)
#define RCC_MCO_NOCLK      	 	(RCC_REG_BIT_MASK)
#define RCC_MCO_LSI         	(RCC_CFG_MCO_0)
#define RCC_MCO_LSE         	(RCC_CFG_MCO_1)
#define RCC_MCO_SYSCLK      	(RCC_CFG_MCO_0 | RCC_CFG_MCO_1)
#define RCC_MCO_HSI         	(RCC_CFG_MCO_2)
#define RCC_MCO_HSE      		(RCC_CFG_MCO_0 | RCC_CFG_MCO_2)
#define RCC_MCO_PLLDIV      	(RCC_CFG_MCO_1 | RCC_CFG_MCO_2)

#define RCC_PLLSYSDIV2_ENABLE   (RCC_CFG_PLLSYSDIV)

/* PLL_entry_clock_source */
#define RCC_PLL_SRC_HSI 	   (RCC_REG_BIT_MASK)
#define RCC_PLL_SRC_HSE 	   (RCC_CFG_PLLSRC)

/* PLL_od_clock_source */
#define RCC_PLL_OD_DIV_1 	   (RCC_REG_BIT_MASK)
#define RCC_PLL_OD_DIV_2 	   (RCC_CFG_PLLOD)

/* System_clock_source */
#define RCC_SYSCLK_SRC_HSI     (RCC_CFG_SCLKSW_HSI)
#define RCC_SYSCLK_SRC_HSE     (RCC_CFG_SCLKSW_HSE)
#define RCC_SYSCLK_SRC_PLL     (RCC_CFG_SCLKSW_PLL)

/* System clock switch status */
#define RCC_SYSCLK_STS_HSI     (RCC_CFG_SCLKSTS_HSI)
#define RCC_SYSCLK_STS_HSE     (RCC_CFG_SCLKSTS_HSE)
#define RCC_SYSCLK_STS_PLL     (RCC_CFG_SCLKSTS_PLL)

/* RCC Interrupts Clear */
#define RCC_CLR_LSESSIF        (RCC_CLKINT_LSESSICLR)
#define RCC_CLR_CLKSSIF        (RCC_CLKINT_CLKSSICLR)
#define RCC_CLR_PLLRDIF        (RCC_CLKINT_PLLRDICLR)
#define RCC_CLR_HSERDIF        (RCC_CLKINT_HSERDICLR)
#define RCC_CLR_HSIRDIF        (RCC_CLKINT_HSIRDICLR)
#define RCC_CLR_LSERDIF        (RCC_CLKINT_LSERDICLR)
#define RCC_CLR_LSIRDIF        (RCC_CLKINT_LSIRDICLR)

/* RCC Interrupts Enable */
#define RCC_ENABLE_LSESSI      (RCC_CLKINT_LSESSIEN)
#define RCC_ENABLE_PLLRDI      (RCC_CLKINT_PLLRDIEN)
#define RCC_ENABLE_HSERDI      (RCC_CLKINT_HSERDIEN)
#define RCC_ENABLE_HSIRDI      (RCC_CLKINT_HSIRDIEN)
#define RCC_ENABLE_LSERDI      (RCC_CLKINT_LSERDIEN)
#define RCC_ENABLE_LSIRDI      (RCC_CLKINT_LSIRDIEN)

/* RCC Interrupts FLAG */
#define RCC_INT_LSESSIF        (RCC_CLKINT_LSESSIF)
#define RCC_INT_CLKSSIF        (RCC_CLKINT_CLKSSIF)
#define RCC_INT_PLLRDIF        (RCC_CLKINT_PLLRDIF)
#define RCC_INT_HSERDIF        (RCC_CLKINT_HSERDIF)
#define RCC_INT_HSIRDIF        (RCC_CLKINT_HSIRDIF)
#define RCC_INT_LSERDIF        (RCC_CLKINT_LSERDIF)
#define RCC_INT_LSIRDIF        (RCC_CLKINT_LSIRDIF)

/* AHBPCLKEN_peripheral */
#define RCC_AHB_PERIPH_ADC2    	 (RCC_AHBPCLKEN_ADC2EN|RCC_AHBPCLKEN_ADC1EN)
#define RCC_AHB_PERIPH_ADC1   	 (RCC_AHBPCLKEN_ADC1EN)
#define RCC_AHB_PERIPH_CRC     	 (RCC_AHBPCLKEN_CRCEN)
#define RCC_AHB_PERIPH_GPIO    	 (RCC_AHBPCLKEN_GPIOEN)
#define RCC_AHB_PERIPH_DMA    	 (RCC_AHBPCLKEN_DMAEN)

/* APB2PCLKEN_peripheral */
#define RCC_APB2_PERIPH_SPI2     	 (RCC_APB2PCLKEN_SPI2EN)
#define RCC_APB2_PERIPH_USART4       (RCC_APB2PCLKEN_USART4EN)
#define RCC_APB2_PERIPH_USART1   	 (RCC_APB2PCLKEN_USART1EN)
#define RCC_APB2_PERIPH_ATIM2    	 (RCC_APB2PCLKEN_ATIM2EN)
#define RCC_APB2_PERIPH_SPI1     	 (RCC_APB2PCLKEN_SPI1EN)
#define RCC_APB2_PERIPH_ATIM1    	 (RCC_APB2PCLKEN_ATIM1EN)

/* APB1PCLKEN_peripheral */
#define RCC_APB1_PERIPH_OPAMP      (RCC_APB1PCLKEN_OPAMPEN)
#define RCC_APB1_PERIPH_CAN        (RCC_APB1PCLKEN_CANEN)
#define RCC_APB1_PERIPH_I2C2       (RCC_APB1PCLKEN_I2C2EN)
#define RCC_APB1_PERIPH_I2C1       (RCC_APB1PCLKEN_I2C1EN)
#define RCC_APB1_PERIPH_USART3     (RCC_APB1PCLKEN_USART3EN)
#define RCC_APB1_PERIPH_USART2     (RCC_APB1PCLKEN_USART2EN)
#define RCC_APB1_PERIPH_WWDG       (RCC_APB1PCLKEN_WWDGEN)
#define RCC_APB1_PERIPH_RTC        (RCC_APB1PCLKEN_RTCEN)
#define RCC_APB1_PERIPH_COMPFILT   (RCC_APB1PCLKEN_COMPFILTEN)
#define RCC_APB1_PERIPH_COMP       (RCC_APB1PCLKEN_COMPEN)
#define RCC_APB1_PERIPH_BTIM2      (RCC_APB1PCLKEN_BTIM2EN)
#define RCC_APB1_PERIPH_BTIM1      (RCC_APB1PCLKEN_BTIM1EN)
#define RCC_APB1_PERIPH_GTIM4      (RCC_APB1PCLKEN_GTIM4EN)
#define RCC_APB1_PERIPH_GTIM3      (RCC_APB1PCLKEN_GTIM3EN)
#define RCC_APB1_PERIPH_GTIM2      (RCC_APB1PCLKEN_GTIM2EN)
#define RCC_APB1_PERIPH_GTIM1      (RCC_APB1PCLKEN_GTIM1EN)


/* GTIM1 clock source selsect */
#define RCC_GTIM1_CLKSEL_MASK        (~RCC_CFG2_GTIM1CLKSEL)
#define RCC_GTIM1_CLKSEL_SYS     	 (RCC_REG_BIT_MASK)
#define RCC_GTIM1_CLKSEL_AHB   	     (RCC_CFG2_GTIM1CLKSEL)

/* ATIM1 clock source selsect */
#define RCC_ATIM1_CLKSEL_MASK        (~RCC_CFG2_ATIM1CLKSEL)
#define RCC_ATIM1_CLKSEL_SYS   		 (RCC_CFG2_ATIM1CLKSEL_0)
#define RCC_ATIM1_CLKSEL_AHB    	 (RCC_CFG2_ATIM1CLKSEL_1)
#define RCC_ATIM1_CLKSEL_PLL    	 (RCC_CFG2_ATIM1CLKSEL_1|RCC_CFG2_ATIM1CLKSEL_0)

/* BTIM1 clock source selsect */
#define RCC_BTIM1_CLKSEL_MASK        (~RCC_CFG2_BTIM1CLKSEL)
#define RCC_BTIM1_CLKSEL_LSI     	 (RCC_CFG2_BTIM1CLKSEL_0)
#define RCC_BTIM1_CLKSEL_LSE     	 (RCC_CFG2_BTIM1CLKSEL_1)
#define RCC_BTIM1_CLKSEL_APB1     	 (RCC_CFG2_BTIM1CLKSEL_1|RCC_CFG2_BTIM1CLKSEL_0)

/* RTC clock source selsect */
#define RCC_RTC_CLKSEL_MASK          (~RCC_CFG2_RTCCLKSEL)
#define RCC_RTC_CLKSEL_LSI           (RCC_CFG2_RTCCLKSEL_0)
#define RCC_RTC_CLKSEL_LSE           (RCC_CFG2_RTCCLKSEL_1)
#define RCC_RTC_CLKSEL_HSE_DIV128    (RCC_CFG2_RTCCLKSEL_1|RCC_CFG2_RTCCLKSEL_0)

/* USART1  clock source selsect */
#define RCC_USART1_CLKSEL_MASK       (~RCC_CFG2_USART1CLKSEL)
#define RCC_USART1_CLKSEL_LSI        (RCC_CFG2_USART1CLKSEL_0)
#define RCC_USART1_CLKSEL_LSE        (RCC_CFG2_USART1CLKSEL_1)
#define RCC_USART1_CLKSEL_APB2       (RCC_CFG2_USART1CLKSEL_1|RCC_CFG2_USART1CLKSEL_0)

/* LSX clock source selsect */
#define RCC_LP_CLKSEL_MASK  		(~RCC_CFG2_LPCLKSEL)
#define RCC_LP_CLKSEL_LSI			(RCC_REG_BIT_MASK)
#define RCC_LP_CLKSEL_LSE			(RCC_CFG2_LPCLKSEL)

/* USART4  clock source selsect */
#define RCC_USART4_CLKSEL_MASK       (~RCC_CFG2_USART4CLKSEL)
#define RCC_USART4_CLKSEL_LSI        (RCC_CFG2_USART4CLKSEL_0)
#define RCC_USART4_CLKSEL_LSE        (RCC_CFG2_USART4CLKSEL_1)
#define RCC_USART4_CLKSEL_APB2       (RCC_CFG2_USART4CLKSEL_1|RCC_CFG2_USART4CLKSEL_0)

/* ADC 1M clock source selsect */
#define RCC_ADC1M_CLKSEL_HSI         (RCC_REG_BIT_MASK)
#define RCC_ADC1M_CLKSEL_HSE         (RCC_CFG2_ADC1MSEL)

/* I2S clock source selsect */
#define RCC_I2S_CLKSEL_MASK       	 (~RCC_CFG2_I2SCLKSEL)
#define RCC_I2S_CLKSEL_SYS           (RCC_REG_BIT_MASK)
#define RCC_I2S_CLKSEL_IOM           (RCC_CFG2_I2SCLKSEL)

/* ADC 1M prescaler */
#define RCC_ADC1MCLK_SRC_MASK     (~RCC_CFG2_ADC1MSEL)
#define RCC_ADC1MCLK_SRC_HSI      (RCC_REG_BIT_MASK)
#define RCC_ADC1MCLK_SRC_HSE      (RCC_CFG2_ADC1MSEL)

#define RCC_ADC1MCLK_DIV_MASK       (~RCC_CFG2_ADC1MPRE)
#define RCC_ADC1MCLK_DIV1			(RCC_REG_BIT_MASK)
#define RCC_ADC1MCLK_DIV2			(RCC_CFG2_ADC1MPRE_0)
#define RCC_ADC1MCLK_DIV4			(RCC_CFG2_ADC1MPRE_1)
#define RCC_ADC1MCLK_DIV6			(RCC_CFG2_ADC1MPRE_1|RCC_CFG2_ADC1MPRE_0)
#define RCC_ADC1MCLK_DIV8			(RCC_CFG2_ADC1MPRE_2)
#define RCC_ADC1MCLK_DIV10			(RCC_CFG2_ADC1MPRE_2|RCC_CFG2_ADC1MPRE_0)
#define RCC_ADC1MCLK_DIV12			(RCC_CFG2_ADC1MPRE_2|RCC_CFG2_ADC1MPRE_1)
#define RCC_ADC1MCLK_DIV16			(RCC_CFG2_ADC1MPRE_2|RCC_CFG2_ADC1MPRE_1|RCC_CFG2_ADC1MPRE_0)
#define RCC_ADC1MCLK_DIV32			(RCC_CFG2_ADC1MPRE_3)

/* ATIM2 clock source selsect */
#define RCC_ATIM2_CLKSEL_MASK        (~RCC_CFG2_ATIM2CLKSEL)
#define RCC_ATIM2_CLKSEL_SYS    	 (RCC_CFG2_ATIM2CLKSEL_0)
#define RCC_ATIM2_CLKSEL_AHB         (RCC_CFG2_ATIM2CLKSEL_1)
#define RCC_ATIM2_CLKSEL_PLL         (RCC_CFG2_ATIM2CLKSEL_1|RCC_CFG2_ATIM2CLKSEL_0)

/* GTIM2 clock source selsect */
#define RCC_GTIM2_CLKSEL_MASK        (~RCC_CFG2_GTIM2CLKSEL)
#define RCC_GTIM2_CLKSEL_SYS         (RCC_REG_BIT_MASK)
#define RCC_GTIM2_CLKSEL_AHB         (RCC_CFG2_GTIM2CLKSEL)

/* ADC sysclk divide */
#define RCC_ADCSPRE_MASK             (~RCC_CFG2_ADCSYSPRES)
#define RCC_ADCSYSCLK_DIV1       	 (RCC_REG_BIT_MASK)
#define RCC_ADCSYSCLK_DIV2       	 (RCC_CFG2_ADCSYSPRES_0)
#define RCC_ADCSYSCLK_DIV3  	   	 (RCC_CFG2_ADCSYSPRES_1)
#define RCC_ADCSYSCLK_DIV4   	   	 (RCC_CFG2_ADCSYSPRES_1|RCC_CFG2_ADCSYSPRES_0)
#define RCC_ADCSYSCLK_DIV5   	   	 (RCC_CFG2_ADCSYSPRES_2)
#define RCC_ADCSYSCLK_DIV6    	     (RCC_CFG2_ADCSYSPRES_2|RCC_CFG2_ADCSYSPRES_0)
#define RCC_ADCSYSCLK_DIV8    	     (RCC_CFG2_ADCSYSPRES_2|RCC_CFG2_ADCSYSPRES_1)
#define RCC_ADCSYSCLK_DIV10   	     (RCC_CFG2_ADCSYSPRES_2|RCC_CFG2_ADCSYSPRES_1|RCC_CFG2_ADCSYSPRES_0)
#define RCC_ADCSYSCLK_DIV12   	     (RCC_CFG2_ADCSYSPRES_3)
#define RCC_ADCSYSCLK_DIV16  	   	 (RCC_CFG2_ADCSYSPRES_3|RCC_CFG2_ADCSYSPRES_0)
#define RCC_ADCSYSCLK_DIV32       	 (RCC_CFG2_ADCSYSPRES_3|RCC_CFG2_ADCSYSPRES_1)
#define RCC_ADCSYSCLK_DIV64        	 (RCC_CFG2_ADCSYSPRES_3|RCC_CFG2_ADCSYSPRES_1|RCC_CFG2_ADCSYSPRES_0)

/* GTIM3 clock source selsect */
#define RCC_GTIM3_CLKSEL_MASK        (~RCC_CFG2_GTIM3CLKSEL)
#define RCC_GTIM3_CLKSEL_SYS         (RCC_REG_BIT_MASK)
#define RCC_GTIM3_CLKSEL_AHB         (RCC_CFG2_GTIM3CLKSEL)

/* GTIM4 clock source selsect */
#define RCC_GTIM4_CLKSEL_MASK        (~RCC_CFG2_GTIM4CLKSEL)
#define RCC_GTIM4_CLKSEL_SYS         (RCC_REG_BIT_MASK)
#define RCC_GTIM4_CLKSEL_AHB         (RCC_CFG2_GTIM4CLKSEL)

/* ATIM1 filter clock div */
#define RCC_ATIM1FILTCLK_MASK				(~RCC_CFG3_ATIM1FILTCLK)

/* ATIM2 filter clock div */
#define RCC_ATIM2FILTCLK_MASK				(~RCC_CFG3_ATIM2FILTCLK)

/* GTIM1 filter clock div */
#define RCC_GTIM1FILTCLK_MASK				(~RCC_CFG3_GTIM1FILTCLK)

/* GTIM2 filter clock div */
#define RCC_GTIM2FILTCLK_MASK				(~RCC_CFG3_GTIM2FILTCLK)

/* GTIM3 filter clock div */
#define RCC_GTIM3FILTCLK_MASK				(~RCC_CFG3_GTIM3FILTCLK)

/* GTIM4 filter clock div */
#define RCC_GTIM4FILTCLK_MASK				(~RCC_CFG3_GTIM4FILTCLK)

/* PLL OUT prescaler*/
#define RCC_PLL_CFG_MASK  				(~(RCC_CFG_PLLSRC|RCC_CFG_PLLMUL|RCC_CFG_PLLOD))
#define RCC_PLL_PLLCTRL_MASK  		    (~(((uint32_t)0x0000C000U)|RCC_PLLCTRL_PLLINPRES))

#define	RCC_LSE_BUFFOPT_MASK				(~RCC_CFG4_LSEBUFFOPT)
#define	RCC_LSE_GLITCHFILTER_MASK			(~RCC_CFG4_LSEGFSEL)
#define	RCC_LSE_GLITCHFILTER_25ns			(RCC_CFG4_LSEGFSEL_0)
#define	RCC_LSE_GLITCHFILTER_50ns			(RCC_CFG4_LSEGFSEL_1)
#define	RCC_LSE_GLITCHFILTER_100ns			(RCC_CFG4_LSEGFSEL_2)
#define	RCC_LSE_GLITCHFILTER_250ns			(RCC_CFG4_LSEGFSEL_3)

#define	RCC_LSE_BIASTRIM_MASK					(~RCC_CFG4_LSEBIASTRIM)
#define	RCC_LSE_LSEDRVTRIM_MASK	  		(~RCC_CFG4_LSEDRVTRIM)


/** APB1_APB2_clock_source **/
#define RCC_APB1_DIV_MASK                   (~RCC_CFG_APB1PRES)
#define RCC_APB2_DIV_MASK                   (~RCC_CFG_APB2PRES)
#define RCC_HCLK_DIV1                       (RCC_REG_BIT_MASK)
#define RCC_HCLK_DIV2                       (RCC_CFG_APB1PRES_2)
#define RCC_HCLK_DIV4                       (RCC_CFG_APB1PRES_2 | RCC_CFG_APB1PRES_0)
#define RCC_HCLK_DIV8                       (RCC_CFG_APB1PRES_2 | RCC_CFG_APB1PRES_1)
#define RCC_HCLK_DIV16                      (RCC_CFG_APB1PRES_2 | RCC_CFG_APB1PRES_1 | RCC_CFG_APB1PRES_0)

/* AHB prescaler */
#define RCC_SYSCLKPRE_MASK            	  	(~RCC_CFG_AHBPRES)
#define RCC_SYSCLK_DIV1   					(RCC_REG_BIT_MASK)
#define RCC_SYSCLK_DIV2    					(RCC_CFG_AHBPRES_3)
#define RCC_SYSCLK_DIV4  				    (RCC_CFG_AHBPRES_3|RCC_CFG_AHBPRES_0)
#define RCC_SYSCLK_DIV8    					(RCC_CFG_AHBPRES_3|RCC_CFG_AHBPRES_1)
#define RCC_SYSCLK_DIV16      				(RCC_CFG_AHBPRES_3|RCC_CFG_AHBPRES_1|RCC_CFG_AHBPRES_0)
#define RCC_SYSCLK_DIV64      			    (RCC_CFG_AHBPRES_3|RCC_CFG_AHBPRES_2)
#define RCC_SYSCLK_DIV128 			  		(RCC_CFG_AHBPRES_3|RCC_CFG_AHBPRES_2|RCC_CFG_AHBPRES_0)

/* POWER CTRL */
#define RCC_PWRUP_STEPWID_MASK 						(~RCC_PWRCTRL_UPSTEPWID)
#define RCC_PWRDOWN_STEPWID_ENABLE			  (RCC_PWRCTRL_DOWNSTEPEN)
#define RCC_PWRUP_STEPWID_ENABLE			 	  (RCC_PWRCTRL_UPSTEPEN)

#define RCC_PWRUP_PSTEPSFDIV_MASK					(~RCC_PWRCTRL_PSTEPSFDIV)
#define RCC_PWRUP_PSTEPSFDIV_1						(RCC_REG_BIT_MASK)
#define RCC_PWRUP_PSTEPSFDIV_2						(RCC_PWRCTRL_PSTEPSFDIV_0)
#define RCC_PWRUP_PSTEPSFDIV_4						(RCC_PWRCTRL_PSTEPSFDIV_1)
#define RCC_PWRUP_PSTEPSFDIV_8						(RCC_PWRCTRL_PSTEPSFDIV_1|RCC_PWRCTRL_PSTEPSFDIV_0)
#define RCC_PWRUP_PSTEPSFDIV_16						(RCC_PWRCTRL_PSTEPSFDIV_2)

/* EMC CTRL */
#define RCC_EMC_GB     					    (RCC_EMCCTRL_GBDET)
#define RCC_EMC_GBN   				        (RCC_EMCCTRL_GBNDET)

/* HSERDY TIME Value */
#define RCC_HSERDFDIV_MASK 					(~(RCC_CFG5_HSERDFDIV|RCC_CFG5_HSERDFDLY))
#define RCC_HSERDFDIV_1MS      			    (RCC_CFG5_HSERDFDLY)
#define RCC_HSERDFDIV_2MS      			    (RCC_CFG5_HSERDFDIV_0|RCC_CFG5_HSERDFDLY)
#define RCC_HSERDFDIV_3MS      			    (RCC_CFG5_HSERDFDIV_1|RCC_CFG5_HSERDFDLY)
#define RCC_HSERDFDIV_4MS      			    (RCC_CFG5_HSERDFDIV_0|RCC_CFG5_HSERDFDIV_1|RCC_CFG5_HSERDFDLY)
#define RCC_HSERDFDLY_128HSE      		  	(RCC_REG_BIT_MASK)

/* IOM FIL CLK DIV */
#define RCC_IOMFILCLK_MASK      		    (~RCC_CFG5_GPIOFCLKDIV)

/* RCC Flag */
#define RCC_FLAG_MASK                 ((uint8_t)0x1FU)
#define RCC_CTRL_FLAG_HSIRDF          ((uint8_t)0x21U)
#define RCC_CTRL_FLAG_HSERDF          ((uint8_t)0x32U)
#define RCC_CTRL_FLAG_PLLRDF          ((uint8_t)0x39U)
#define RCC_CTRL_FLAG_LSIRDF          ((uint8_t)0x3AU)
#define RCC_CTRL_FLAG_LSERDF          ((uint8_t)0x3BU)

#define RCC_CTRLSTS_FLAG_PORRSTF      ((uint8_t)0x62U)
#define RCC_CTRLSTS_FLAG_PINRSTF      ((uint8_t)0x63U)
#define RCC_CTRLSTS_FLAG_WWDGRSTF     ((uint8_t)0x64U)
#define RCC_CTRLSTS_FLAG_SFTRSTF      ((uint8_t)0x65U)
#define RCC_CTRLSTS_FLAG_IWDGRSTF     ((uint8_t)0x66U)
#define RCC_CTRLSTS_FLAG_GLITCHRSTF   ((uint8_t)0x67U)
#define RCC_CTRLSTS_FLAG_EMCGBRSTF     ((uint8_t)0x68U)
#define RCC_CTRLSTS_FLAG_EMCGBNRSTF    ((uint8_t)0x69U)
#define RCC_CTRLSTS_FLAG_LKUPRSTF      ((uint8_t)0x6BU)

#define RCC_CTRLSTS_FLAG_RMRSTF	       (RCC_CTRLSTS_RMRSTF)


/*** RCC Macro Definition End ***/

/*** RCC Driving Functions Declaration ***/

/* Reset */
void RCC_DeInit(void);

/* HSI configuration */
void RCC_EnableHsi(FunctionalState Cmd);
void RCC_SetHsiCalibValue(uint16_t calibration_value);
ErrorStatus RCC_WaitHsiStable(void);

/* HSE configuration */
void RCC_ConfigHse(uint32_t RCC_HSE);
void RCC_ConfigHseReadyDly(uint32_t hse_dlydiv);
ErrorStatus RCC_WaitHseStable(void);

/* LSI configuration */
void RCC_EnableLsi(FunctionalState Cmd);
void RCC_SetLsiCalibValue(uint16_t calibration_value);
ErrorStatus RCC_WaitLsiStable(void);

/* LSE configuration */
void RCC_ConfigLse(uint32_t RCC_LSE);
ErrorStatus RCC_WaitLseStable(void);
void RCC_EnableLseNim(FunctionalState Cmd);
void RCC_ConfigLseGlitchFilter(uint32_t lsegliterflit);
void RCC_ConfigLseBuffOpt(uint32_t lsebuffopt);
void RCC_ConfigLseBiasTrim(uint32_t LseBiasTrim);
void RCC_ConfigLseDrvTrim(uint32_t lsedrvtrim);

/* PLL configuration */
void RCC_ConfigPll(uint32_t PLL_source, uint32_t PLL_inpre, uint32_t PLL_mul, uint32_t PLL_od);
void RCC_EnablePll(FunctionalState Cmd);
void RCC_EnablePllBypass(FunctionalState Cmd);
void RCC_EnablePllSysclkDiv(FunctionalState Cmd);

/* System clock and bus prescaler configuration */
void RCC_ConfigSysclk(uint32_t sysclk_source);
uint32_t RCC_GetSysclkSrc(void);
void RCC_ConfigHclk(uint32_t sysclk_div);
void RCC_ConfigPclk1(uint32_t RCC_HCLK);
void RCC_ConfigPclk2(uint32_t RCC_HCLK);
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_Clocks);

/* Peripheral clock enable and reset */
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd);
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd);
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd);
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph);
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph);
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph);

/* Peripheral clock source configuration */
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler);
void RCC_ConfigAdcSysclk(uint32_t sclk_prescaler);
void RCC_ConfigI2SClk(uint32_t i2s_clksrc);
void RCC_ConfigUsart1Clk(uint32_t usart1_clksrc);
void RCC_ConfigUsart4Clk(uint32_t usart4_clksrc);
void RCC_ConfigRTCClk(uint32_t rtc_clksrc);
void RCC_ConfigLowPowerClk(uint32_t lp_clksrc);

/* Timer clock source configuration */
void RCC_ConfigAtim1Clk(uint32_t atimer1_clksrc);
void RCC_ConfigAtim2Clk(uint32_t atimer2_clksrc);
void RCC_ConfigGtim1Clk(uint32_t gtimer1_clksrc);
void RCC_ConfigGtim2Clk(uint32_t gtimer2_clksrc);
void RCC_ConfigGtim3Clk(uint32_t gtimer3_clksrc);
void RCC_ConfigGtim4Clk(uint32_t gtimer4_clksrc);
void RCC_ConfigBtim1Clk(uint32_t btimer1_clksrc);

/* Timer and IO filter clock divider configuration */
void RCC_ConfigIOFilter(uint32_t ioflitclk_div);
void RCC_ConfigATIM1Filter(uint32_t atim1flitclk_div);
void RCC_ConfigATIM2Filter(uint32_t atim2flitclk_div);
void RCC_ConfigGTIM1Filter(uint32_t gtim1flitclk_div);
void RCC_ConfigGTIM2Filter(uint32_t gtim2flitclk_div);
void RCC_ConfigGTIM3Filter(uint32_t gtim3flitclk_div);
void RCC_ConfigGTIM4Filter(uint32_t gtim4flitclk_div);

/* MCO output configuration */
void RCC_ConfigMco(uint32_t MCO_source);
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler);

/* Clock security system */
void RCC_EnableHSEClockSecuritySystem(FunctionalState Cmd);
void RCC_EnableLSEClockSecuritySystem(FunctionalState Cmd);
void RCC_EnableHSECaptureRequest(FunctionalState Cmd);
void RCC_EnableLSECaptureRequest(FunctionalState Cmd);

/* EMC detection and protection */
void RCC_EnableEMCDetect(uint32_t EMC_type, FunctionalState Cmd);
void RCC_ConfigEMCDetectLevel(uint32_t EMC_type, uint8_t level);
void RCC_EnableEMCReset(uint32_t EMC_type, FunctionalState Cmd);
void RCC_EnableEMCSwitch(uint32_t EMC_type, FunctionalState Cmd);
void RCC_EnableEMCGBInt(FunctionalState Cmd);
void RCC_EnableEMCGBNInt(FunctionalState Cmd);

/* Glitch detection and protection */
void RCC_EnableGlitchDetect(FunctionalState Cmd);
void RCC_ConfigGlitchDetectLevel(uint8_t level);
void RCC_EnableGlitchReset(FunctionalState Cmd);
void RCC_EnableGlitchSwitch(FunctionalState Cmd);
void RCC_EnableGlitchInt(FunctionalState Cmd);
void RCC_EnableM4LockupReset(FunctionalState Cmd);

/* Power step configuration */
void RCC_EnablePwrUpStep(FunctionalState Cmd);
void RCC_EnablePwrDownStep(FunctionalState Cmd);
void RCC_ConfigPwrUpStepWidth(uint32_t pwrupstepwidth);
void RCC_ConfigPwrDownStepWidth(uint32_t pwrdownstepwidth);
void RCC_EnablePStepSf(FunctionalState Cmd);
void RCC_PStepSfDiv(uint32_t pstepsfdiv);
void RCC_ClearPwrDownStepFlag(void);
FlagStatus RCC_GetPwrDownStepFlag(void);
uint32_t RCC_GetPwrStepFsm(void);

/* Interrupt and flag management */
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd);
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag);
void RCC_ClrIntPendingBit(uint32_t interrupt_clear);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag);
void RCC_ClearResetFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_RCC_H__ */
