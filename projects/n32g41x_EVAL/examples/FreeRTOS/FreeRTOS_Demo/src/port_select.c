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
*\*\file port_select.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/

/**
*\*\file port_select.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
*
*\*\brief  FreeRTOS port auto-selection layer.
*
*\*\note   N32G41x is a Cortex-M4 without FPU and without MPU, so the ARM_CM3
*\*\        ports are used. Which port *file* has to be compiled depends on the
*\*\        toolchain, because each one uses compiler specific syntax:
*
*\*\            Keil AC5 (armcc)         -> portable/RVDS/ARM_CM3/port.c
*\*\            Keil AC6 (armclang)      -> portable/GCC/ARM_CM3/port.c
*\*\            IAR      (iccarm)        -> portable/IAR/ARM_CM3/port.c (+ portasm.s)
*\*\            GCC      (arm-none-eabi) -> portable/GCC/ARM_CM3/port.c
*
*\*\        Listing a specific port.c in the project means the compiler can no
*\*\        longer be switched freely - selecting ARM Compiler 6 on a project that
*\*\        contains the RVDS port fails with "unknown type name '__forceinline'"
*\*\        and similar, and vice versa.
*
*\*\        Adding this one file to the project instead of a concrete port.c
*\*\        makes the selection automatic: the preprocessor macros below are
*\*\        defined by the compilers themselves, so switching the compiler
*\*\        (for example the "ARM Compiler" drop-down in Keil) just works.
*
*\*\        IMPORTANT: the IAR port also has an assembly part, portasm.s, which
*\*\        cannot be reached from C. IAR projects must therefore list
*\*\        portable/IAR/ARM_CM3/portasm.s in addition to this file.
**/

/** IAR: the C part of the IAR port. portasm.s is added separately by the
 * project. __ICCARM__ must be tested first because IAR also defines __GNUC__
 * when "GNU extensions" are enabled in some configurations.
 *
 * The paths below are relative to this file:
 *   src/ -> FreeRTOS_Demo -> FreeRTOS -> examples -> n32g41x_EVAL
 *        -> projects -> SDK root
 * They are written out in full because adjacent string literals are not
 * concatenated until after preprocessing, so "#include A B" would not work. **/
#if defined(__ICCARM__)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/IAR/ARM_CM3/port.c"

/** ARM Compiler 6 (armclang) reuses the GCC port - see
 * portable/ARMClang/Use-the-GCC-ports.txt. armclang also defines __GNUC__,
 * so this branch must come before the __GNUC__ one. **/
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/GCC/ARM_CM3/port.c"

/* ARM Compiler 5 (armcc). */
#elif defined(__CC_ARM)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/RVDS/ARM_CM3/port.c"

/* GCC (arm-none-eabi-gcc). */
#elif defined(__GNUC__)
#include "../../../../../../Middlewares/FreeRTOSv202604.01-LTS/FreeRTOS-Kernel/portable/GCC/ARM_CM3/port.c"

#else
#error "FreeRTOS: unsupported compiler, cannot select an ARM_CM3 port."
#endif
