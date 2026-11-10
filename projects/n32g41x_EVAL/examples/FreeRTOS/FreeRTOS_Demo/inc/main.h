/**
*     Copyright (c) 2026, NSING Technologies Inc.
*
*     All rights reserved.
*
*     This software is the exclusive property of NSING Technologies Inc. (Hereinafter
* referred to as NSING). This software, and the product of NSING described herein
* (Hereinafter referred to as the Product) are owned by NSING under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NSING does not grant any license under its patents, copyrights, trademarks, or other
* intellectual property rights. Names and brands of third party may be mentioned or referred
* thereto (if any) for identification purposes only.
*
*     NSING reserves the right to make changes, corrections, enhancements, modifications, and
* improvements to this software at any time without notice. Please contact NSING and obtain
* the latest version of this software before placing orders.

*     Although NSING has attempted to provide accurate and reliable information, NSING assumes
* no responsibility for the accuracy and reliability of this software.
*
*     It is the responsibility of the user of this software to properly design, program, and test
* the functionality and safety of any application made of this information and any resulting product.
* In no event shall NSING be liable for any direct, indirect, incidental, special,exemplary, or
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NSING Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NSING and hold NSING
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NSING, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NSING products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations.
* User shall comply with any applicable export control laws and regulations promulgated and administered by
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.h
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/

#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g41x.h"
#include "n32g41x_stb.h"

/** Mark a function that never returns to its caller (infinite loop handlers and
 * FreeRTOS task bodies). Without it the ARM Compiler 6 build reports
 * -Wmissing-noreturn for every one of them. **/
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
#define APP_NORETURN __attribute__((noreturn))
#else
#define APP_NORETURN
#endif

/*** Task parameters ***/
/** This header deliberately avoids FreeRTOS types so that it can still be
 * included by non RTOS code. Stack depth is expressed in words, not bytes:
 * 128 words = 512 bytes, 256 words = 1KB. The print task uses printf() and
 * therefore needs the larger stack. **/
#define LED_TASK_STACK_SIZE   128
#define LED_TASK_PRIORITY     2

#define PRINT_TASK_STACK_SIZE 256
#define PRINT_TASK_PRIORITY   3

/* Task period in milliseconds */
#define LED_TASK_PERIOD_MS    500
#define PRINT_TASK_PERIOD_MS  1000

/*** LED helpers ***/
void LED_Init(GPIO_Module *GPIOx, uint16_t Pin, uint32_t clock);
void LED_On(GPIO_Module *GPIOx, uint16_t Pin);
void LED_Off(GPIO_Module *GPIOx, uint16_t Pin);
void LED_Blink(GPIO_Module *GPIOx, uint16_t Pin);

#ifdef __cplusplus
}
#endif
#endif /* __MAIN_H__ */

