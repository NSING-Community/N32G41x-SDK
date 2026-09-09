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
*\*\file      main.h
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include "n32g41x_gpio.h"
#include "n32g41x_rcc.h"
#include "n32g41x_comp.h"
#include "n32g41x_tim.h"

/* -------- COMP1 pins -------- */
/* COMP1 INP: PB10 (analog) */
#define COMP1_INP_PIN             GPIO_PIN_10
#define COMP1_INP_GPIO            GPIOB

/* COMP1 INM: PB1 (analog) */
#define COMP1_INM_PIN             GPIO_PIN_1
#define COMP1_INM_GPIO            GPIOB

/* COMP1 OUT: PB6 (for observation) */
#define COMP1_OUT_PIN             GPIO_PIN_6
#define COMP1_OUT_GPIO            GPIOB
#define COMP1_OUT_AF              GPIO_AF7    /* G412 & G415: PB6 COMP1_OUT = AF7 */

/* -------- ATIM1 (TIM1) pins -------- */
/* CH1: PA8 */
#define ATIM1_CH1_PIN             GPIO_PIN_8
#define ATIM1_CH1_GPIO            GPIOA
/* CH2: PA9 */
#define ATIM1_CH2_PIN             GPIO_PIN_9
#define ATIM1_CH2_GPIO            GPIOA
/* CH3: PA10 */
#define ATIM1_CH3_PIN             GPIO_PIN_10
#define ATIM1_CH3_GPIO            GPIOA
/* CH4: PA11 */
#define ATIM1_CH4_PIN             GPIO_PIN_11
#define ATIM1_CH4_GPIO            GPIOA

#if defined(N32G412)
/* G412: PA8=AF2, PA9=AF2 for ATIM1_CH1/CH2 */
#define ATIM1_CH1_AF              GPIO_AF2
#define ATIM1_CH2_AF              GPIO_AF2
#elif defined(N32G415)
/* G415: PA8=AF1, PA9=AF1 for ATIM1_CH1/CH2 */
#define ATIM1_CH1_AF              GPIO_AF1
#define ATIM1_CH2_AF              GPIO_AF1
#endif
/* G412 & G415: PA10=AF2, PA11=AF2 for ATIM1_CH3/CH4 */
#define ATIM1_CH3_AF              GPIO_AF2
#define ATIM1_CH4_AF              GPIO_AF2

/* CH1N: PB13, CH2N: PB14, CH3N: PB15 */
#define ATIM1_CH1N_PIN            GPIO_PIN_13
#define ATIM1_CH1N_GPIO           GPIOB
#define ATIM1_CH2N_PIN            GPIO_PIN_14
#define ATIM1_CH2N_GPIO           GPIOB
#define ATIM1_CH3N_PIN            GPIO_PIN_15
#define ATIM1_CH3N_GPIO           GPIOB
/* G412 & G415: PB13/PB14/PB15 ATIM1_CH1N/CH2N/CH3N = AF5 */
#define ATIM1_CHN_AF              GPIO_AF5

/* -------- ATIM2 (TIM8) pins -------- */
/* CH1: PC1 */
#define ATIM2_CH1_PIN             GPIO_PIN_1
#define ATIM2_CH1_GPIO            GPIOC
/* CH2: PC2 */
#define ATIM2_CH2_PIN             GPIO_PIN_2
#define ATIM2_CH2_GPIO            GPIOC
/* CH3: PA12 */
#define ATIM2_CH3_PIN             GPIO_PIN_12
#define ATIM2_CH3_GPIO            GPIOA
/* CH4: PC13 */
#define ATIM2_CH4_PIN             GPIO_PIN_13
#define ATIM2_CH4_GPIO            GPIOC
/* G412 & G415: PC1=AF6, PC2=AF6, PC13=AF6 for ATIM2_CH1/CH2/CH4 */
#define ATIM2_CH1_AF              GPIO_AF6
#define ATIM2_CH2_AF              GPIO_AF6
#define ATIM2_CH4_AF              GPIO_AF6
/* G412 & G415: PA12 ATIM2_CH3 = AF13 */
#define ATIM2_CH3_AF              GPIO_AF13

/* CH1N: PA7 */
#define ATIM2_CH1N_PIN            GPIO_PIN_7
#define ATIM2_CH1N_GPIO           GPIOA
/* CH2N: PB0 */
#define ATIM2_CH2N_PIN            GPIO_PIN_0
#define ATIM2_CH2N_GPIO           GPIOB
/* CH3N: PB12 */
#define ATIM2_CH3N_PIN            GPIO_PIN_12
#define ATIM2_CH3N_GPIO           GPIOB
/* G412 & G415: PA7 ATIM2_CH1N = AF6 */
#define ATIM2_CH1N_AF             GPIO_AF6
/* G412 & G415: PB0 ATIM2_CH2N = AF13 */
#define ATIM2_CH2N_AF             GPIO_AF13
/* G412 & G415: PB12 ATIM2_CH3N = AF12 */
#define ATIM2_CH3N_AF             GPIO_AF12

/* -------- Pulse generator pins -------- */
/* PB2 -> connect to INP(PB10), PB3 -> connect to INM(PB1) */
#define PULSE_INP_PIN             GPIO_PIN_2
#define PULSE_INP_GPIO            GPIOB
#define PULSE_INM_PIN             GPIO_PIN_3
#define PULSE_INM_GPIO            GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
