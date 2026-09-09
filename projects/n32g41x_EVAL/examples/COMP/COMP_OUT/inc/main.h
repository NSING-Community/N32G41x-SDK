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
#include "n32g41x_exti.h"
#include "misc.h"

/* COMP1 INP pin: PB10 (analog) */
#define COMP1_INP_PIN             GPIO_PIN_10
#define COMP1_INP_GPIO            GPIOB

/* COMP1 INM pin: PB1 (analog) */
#define COMP1_INM_PIN             GPIO_PIN_1
#define COMP1_INM_GPIO            GPIOB

/* COMP1 OUT pin: PA11 */
#define COMP1_OUT_PIN             GPIO_PIN_11
#define COMP1_OUT_GPIO            GPIOA

#if defined(N32G412)
#define COMP1_OUT_AF              GPIO_AF7
#elif defined(N32G415)
#define COMP1_OUT_AF              GPIO_AF7
#endif

/* Pulse generator pins: PB2 -> connect to INP(PB10), PB3 -> connect to INM(PB1) */
#define PULSE_INP_PIN             GPIO_PIN_2
#define PULSE_INP_GPIO            GPIOB
#define PULSE_INM_PIN             GPIO_PIN_3
#define PULSE_INM_GPIO            GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
