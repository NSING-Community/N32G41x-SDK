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
*\*\file portmacro.h
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/

#ifndef __PORTMACRO_H__
#define __PORTMACRO_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Guard name deliberately differs from the upstream PORTMACRO_H: the real
 * portmacro.h below must still see PORTMACRO_H undefined, otherwise its own
 * include guard would make its entire body expand to nothing. **/

/**
 *
 * \brief  Compiler-dispatched FreeRTOS portmacro.h - the second half of the
 * \        port auto-selection layer, see src/port_select.c.
 *
 * \note   FreeRTOS-Kernel/include/portable.h does an unconditional
 * \        #include "portmacro.h", so this header has to be reachable through
 * \        the project's include path. Normally that is solved by putting the
 * \        concrete port directory (portable/<toolchain>/ARM_CM3) on the include
 * \        path - but that hard-codes the toolchain, which is exactly what
 * \        port_select.c is meant to avoid.
 *
 * \        This file is the dispatcher: it lives in the example's inc/ folder,
 * \        which is already on the include path, and forwards to the portmacro.h
 * \        that matches the compiler in use. The three upstream portmacro.h
 * \        files all use the same PORTMACRO_H include guard and do not include
 * \        each other, so the forwarding is safe.
 *
 * \        Together with src/port_select.c this lets the Keil "ARM Compiler"
 * \        drop-down be switched between AC5 and AC6 without touching the
 * \        project's file list or include paths.
**/

/** Paths below are relative to this file (inc/); inc/ and src/ sit at the same
 * depth, so the same "six levels up to the SDK root" path applies. **/
#if defined(__ICCARM__)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/IAR/ARM_CM3/portmacro.h"

/** ARM Compiler 6 uses the GCC port; armclang also defines __GNUC__, so this
 * branch must precede the __GNUC__ one. **/
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/GCC/ARM_CM3/portmacro.h"

#elif defined(__CC_ARM)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/RVDS/ARM_CM3/portmacro.h"

#elif defined(__GNUC__)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/GCC/ARM_CM3/portmacro.h"

#else
#error "FreeRTOS: unsupported compiler, cannot select an ARM_CM3 portmacro.h."
#endif

#ifdef __cplusplus
}
#endif
#endif /* __PORTMACRO_H__ */

