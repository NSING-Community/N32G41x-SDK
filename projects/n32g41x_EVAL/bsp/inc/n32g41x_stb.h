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
*\*\file n32g41x_stb.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __N32G41X_STB_H__
#define __N32G41X_STB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include "n32g41x_gpio.h"
#include "n32g41x_rcc.h"

/* LED defines ------------------------------------------------------------------*/
#define LED1_STB
#define LED1_PORT                      GPIOA
#define LED1_PIN                       GPIO_PIN_1
#define LED1_CLOCK                     RCC_AHB_PERIPH_GPIO
#define LED1_CLOCK_ENABLE              RCC_EnableAHBPeriphClk(LED1_CLOCK, ENABLE)
#define LED1_ON_STATE                  Bit_SET

#define LED2_STB
#define LED2_PORT                      GPIOA
#define LED2_PIN                       GPIO_PIN_7
#define LED2_CLOCK                     RCC_AHB_PERIPH_GPIO
#define LED2_CLOCK_ENABLE              RCC_EnableAHBPeriphClk(LED2_CLOCK, ENABLE)
#define LED2_ON_STATE                  Bit_SET

#define LED3_STB
#define LED3_PORT                      GPIOB
#define LED3_PIN                       GPIO_PIN_1
#define LED3_CLOCK                     RCC_AHB_PERIPH_GPIO
#define LED3_CLOCK_ENABLE              RCC_EnableAHBPeriphClk(LED3_CLOCK, ENABLE)
#define LED3_ON_STATE                  Bit_SET

/* KEY defines ------------------------------------------------------------------*/
#define BUTTON_KEY1_STB
#define BUTTON_KEY1_CLK                RCC_AHB_PERIPH_GPIO
#define BUTTON_KEY1_CLK_ENABLE         RCC_EnableAHBPeriphClk(BUTTON_KEY1_CLK, ENABLE)
#define BUTTON_KEY1_PORT               GPIOA
#define BUTTON_KEY1_PIN                GPIO_PIN_4
#define BUTTON_KEY1_PULL               GPIO_PULL_UP
#define BUTTON_KEY1_STATE              Bit_RESET

#define BUTTON_KEY2_STB
#define BUTTON_KEY2_CLK                RCC_AHB_PERIPH_GPIO
#define BUTTON_KEY2_CLK_ENABLE         RCC_EnableAHBPeriphClk(BUTTON_KEY2_CLK, ENABLE)
#define BUTTON_KEY2_PORT               GPIOA
#define BUTTON_KEY2_PIN                GPIO_PIN_5
#define BUTTON_KEY2_PULL               GPIO_PULL_UP
#define BUTTON_KEY2_STATE              Bit_RESET

#define BUTTON_KEY3_STB
#define BUTTON_KEY3_CLK                RCC_AHB_PERIPH_GPIO
#define BUTTON_KEY3_CLK_ENABLE         RCC_EnableAHBPeriphClk(BUTTON_KEY3_CLK, ENABLE)
#define BUTTON_KEY3_PORT               GPIOA
#define BUTTON_KEY3_PIN                GPIO_PIN_6
#define BUTTON_KEY3_PULL               GPIO_PULL_UP
#define BUTTON_KEY3_STATE              Bit_RESET

/* WKUP defines (PA0, idle-low / active-high) ------------------------------------*/
#define BUTTON_WKUP_STB
#define BUTTON_WKUP_CLK                RCC_AHB_PERIPH_GPIO
#define BUTTON_WKUP_CLK_ENABLE         RCC_EnableAHBPeriphClk(BUTTON_WKUP_CLK, ENABLE)
#define BUTTON_WKUP_PORT               GPIOA
#define BUTTON_WKUP_PIN                GPIO_PIN_0
#define BUTTON_WKUP_PULL               GPIO_PULL_DOWN
#define BUTTON_WKUP_STATE              Bit_SET

#ifdef __cplusplus
}
#endif

#endif /* __N32G41X_STB_H__ */
