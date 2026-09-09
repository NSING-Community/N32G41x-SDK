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
*\*\file system_n32g41x.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32g41x.h"

/* Chip selection: define exactly one of N32G412 or N32G415 in the project (e.g. via -D flag). */
#if !defined(N32G412) && !defined(N32G415)
#error Define N32G412 or N32G415 to select the target chip.
#endif
#if defined(N32G412) && defined(N32G415)
#error Define only one of N32G412 or N32G415, not both.
#endif

/* Configure SYSCLK_FREQ (Hz) and SYSCLK_SRC before compiling.
 * Default: HSI_PLL at the chip's maximum rated SYSCLK. HSI is used as SYSCLK source after reset. */

#define SYSCLK_USE_HSI     0U
#define SYSCLK_USE_HSE     1U
#define SYSCLK_USE_HSI_PLL 2U
#define SYSCLK_USE_HSE_PLL 3U

#ifndef SYSCLK_FREQ
#ifdef N32G415
#define SYSCLK_FREQ    96000000U
#else  /* N32G412 */
#define SYSCLK_FREQ    80000000U
#endif
#endif

#ifndef SYSCLK_SRC
#define SYSCLK_SRC   SYSCLK_USE_HSI_PLL
#endif

#ifdef N32G415
#if SYSCLK_FREQ > 96000000U
#error SYSCLK_FREQ must not exceed 96MHz for N32G415 (SYSCLK specification limit)
#endif
#else  /* N32G412 */
#if SYSCLK_FREQ > 80000000U
#error SYSCLK_FREQ must not exceed 80MHz for N32G412 (SYSCLK specification limit)
#endif
#endif

/* When any ATIM clock source is set to PLL (RCC_CFG2.ATIMnCLKSEL=11), the spec requires
 * FPLL <= 144MHz and SYSCLK <= 72MHz. Define ATIM_USE_PLL_CLK in the project to enforce this. */
#if defined(ATIM_USE_PLL_CLK)
#if SYSCLK_FREQ > 72000000U
#error ATIM_USE_PLL_CLK: SYSCLK must not exceed 72MHz when ATIM uses PLL clock (spec: FPLL<=144MHz, SYSCLK<=72MHz)
#endif
#endif

/*
 * N32G41x PLL clock chain:
 *   FIN -> /N(PLLINPRES) -> *M(PLLMUL) -> FVCO -> /OD(PLLOD) -> FPLL -> /S(PLLSYSDIV) -> SYSCLK
 *
 *   FIN:          HSI(16MHz fixed) or HSE; HSE crystal 8~32MHz, bypass (external clock) 1~32MHz
 *   PLLINPRES(N): 1~63  (PLLCTRL[13:8], direct value)
 *   PLLMUL(M):    2~127 (RCC_CFG[22:16], direct encoding)
 *   PLLOD(OD):    1 or 2 (RCC_CFG[14], 0=DIV1 1=DIV2)
 *   PLLSYSDIV(S): 1 or 2 (RCC_CFG[23], 0=DIV1 1=DIV2)
 *
 *   PLL frequency constraints:
 *     FIN: 8~32MHz (PLL input); 
 *     FIN/N: 8~32MHz; 
 *     FVCO: 96~160MHz; 
 *     FPLL: 64~160MHz
 *     SYSCLK constraints:
 *         N32G412: SYSCLK <= 80MHz;  
 *         N32G415: SYSCLK <= 96MHz
 * 
 *     ATIM_USE_PLL_CLK: FPLL <= 144MHz AND SYSCLK <= 72MHz (both chips)
 * 
 *     WARNING: 
 *         SYSCLK_FREQ defaults to 80MHz for N32G412
 *         SYSCLK_FREQ defaults to 96MHz for N32G415. 
 *     If any ATIM (ATIM1/ATIM2) clock source is configured to PLL via RCC_CFG2.ATIM1CLKSEL or RCC_CFG2.ATIM2CLKSEL, 
 *     the application must reduce SYSCLK_FREQ to <= 72MHz and define ATIM_USE_PLL_CLK.
 */

#if SYSCLK_SRC == SYSCLK_USE_HSI

#if SYSCLK_FREQ != HSI_VALUE
#error SYSCLK_FREQ must be set to HSI_VALUE when using HSI as system clock
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE

#ifndef HSE_VALUE
#error HSE_VALUE must be defined!
#endif

/* HSE hardware range: crystal/resonator mode 8~32MHz, bypass (external clock) mode 1~32MHz.
 * Define HSE_BYPASS_MODE if using an external clock source (bypass mode supports 1~32MHz); omit for crystal mode.
 */
#if HSE_VALUE > 32000000U
#error HSE_VALUE exceeds 32MHz (hardware max for both crystal and bypass mode)
#endif

#ifndef HSE_BYPASS_MODE
#if HSE_VALUE < 8000000U
#error HSE_VALUE below 8MHz: crystal/resonator mode requires 8~32MHz.
#endif
#else
#if HSE_VALUE < 1000000U
#error HSE_VALUE must be at least 1MHz (min HSE bypass clock frequency)
#endif
#endif

#if SYSCLK_FREQ != HSE_VALUE
#error SYSCLK_FREQ must be set to HSE_VALUE when using HSE as system clock
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL

#if HSI_VALUE != 16000000U
#error HSI_VALUE must be 16000000; HSI is hardware-fixed at 16MHz on N32G41x
#endif

/*
 * FVCO = SYSCLK * OD * S,  M = FVCO * N / FIN  (must be integer in 2~127)
 * FIN/N constraint: 8MHz <= FIN/N <= 32MHz; with HSI=16MHz fixed: N <= 2
 * Group A: OD=2 S=1  FVCO=2*SYSCLK  FPLL=SYSCLK    64~80MHz
 * Group B: OD=1 S=2  FVCO=2*SYSCLK  FPLL=2*SYSCLK  48~63MHz (fallback when Group A fails)
 * Group C: OD=2 S=2  FVCO=4*SYSCLK  FPLL=2*SYSCLK  32~40MHz
 * Group D: OD=1 S=1  FVCO=SYSCLK    FPLL=SYSCLK    96MHz     (N32G415 only)
 */

/* --- Group A: OD=2, S=1, FVCO=2*SYSCLK, FPLL=SYSCLK --- */
/* N=1: M = 2*SYSCLK/HSI */
#if (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (2U*SYSCLK_FREQ % HSI_VALUE == 0U) && (2U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U
/* N=2: M = 4*SYSCLK/HSI; FIN/N = HSI/2 = 8MHz (valid, HSI=16MHz fixed) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (4U*SYSCLK_FREQ % HSI_VALUE == 0U) && (4U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U

/* --- Group B: OD=1, S=2, FVCO=2*SYSCLK, FPLL=2*SYSCLK --- */
/* N=1: M = 2*SYSCLK/HSI; FPLL=2*SYSCLK >= 96MHz satisfies FPLL>=64MHz automatically */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (2U*SYSCLK_FREQ % HSI_VALUE == 0U) && (2U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U
/* N=2: M = 4*SYSCLK/HSI; FIN/N = HSI/2 = 8MHz (valid, HSI=16MHz fixed) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (4U*SYSCLK_FREQ % HSI_VALUE == 0U) && (4U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U

/* --- Group C: OD=2, S=2, FVCO=4*SYSCLK, FPLL=2*SYSCLK --- */
/* N=1: M = 4*SYSCLK/HSI */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (4U*SYSCLK_FREQ % HSI_VALUE == 0U) && (4U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U
/* N=2: M = 8*SYSCLK/HSI; FIN/N = HSI/2 = 8MHz (valid, HSI=16MHz fixed) */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (8U*SYSCLK_FREQ % HSI_VALUE == 0U) && (8U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (8U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(8U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U

/* --- Group D: OD=1, S=1, FVCO=SYSCLK, FPLL=SYSCLK (N32G415 only; SYSCLK=96MHz) --- */
/* N=1: M = SYSCLK/HSI; FIN/N = HSI = 16MHz (within 8~32MHz constraint) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (SYSCLK_FREQ % HSI_VALUE == 0U) && (SYSCLK_FREQ / HSI_VALUE >= 2U) && (SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U
/* N=2: M = 2*SYSCLK/HSI; FIN/N = HSI/2 = 8MHz (valid, HSI=16MHz fixed) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (2U*SYSCLK_FREQ % HSI_VALUE == 0U) && (2U*SYSCLK_FREQ / HSI_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSI_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSI_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U

#else
#error Cannot find valid PLL factors with HSI: check SYSCLK_FREQ limit and divisibility by HSI_VALUE. N is limited to 1~2 (HSI=16MHz fixed; FIN/N>=8MHz). N32G412: SYSCLK<=80MHz; N32G415: SYSCLK<=96MHz (Group D covers 96MHz).
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE_PLL

#ifndef HSE_VALUE
#error HSE_VALUE must be defined!
#endif

/* HSE as PLL input: crystal 8~32MHz; bypass 1~32MHz physical but PLL requires FIN>=8MHz */
#if (HSE_VALUE < 8000000U) || (HSE_VALUE > 32000000U)
#error HSE_VALUE must be 8~32MHz for PLL input (spec requires FIN>=8MHz; bypass clocks <8MHz cannot drive the PLL)
#endif

/* --- Group A: OD=2, S=1, FVCO=2*SYSCLK, FPLL=SYSCLK --- */
/* N=1: M = 2*SYSCLK/HSE */
#if (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (2U*SYSCLK_FREQ % HSE_VALUE == 0U) && (2U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U
/* N=2: M = 4*SYSCLK/HSE, requires HSE >= 16MHz (satisfies FIN/N = HSE/2 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 16000000U) \
    && (4U*SYSCLK_FREQ % HSE_VALUE == 0U) && (4U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U
/* N=3: M = 6*SYSCLK/HSE, requires HSE >= 24MHz (satisfies FIN/N = HSE/3 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 24000000U) \
    && (6U*SYSCLK_FREQ % HSE_VALUE == 0U) && (6U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (6U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  3U
#define PLL_MUL    ((uint32_t)(6U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U
/* N=4: M = 8*SYSCLK/HSE, requires HSE >= 32MHz (satisfies FIN/N = HSE/4 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) && (SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 32000000U) \
    && (8U*SYSCLK_FREQ % HSE_VALUE == 0U) && (8U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (8U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  4U
#define PLL_MUL    ((uint32_t)(8U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 1U

/* --- Group B: OD=1, S=2, FVCO=2*SYSCLK, FPLL=2*SYSCLK --- */
/* N=1: M = 2*SYSCLK/HSE */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (2U*SYSCLK_FREQ % HSE_VALUE == 0U) && (2U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U
/* N=2: M = 4*SYSCLK/HSE, requires HSE >= 16MHz (satisfies FIN/N = HSE/2 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 16000000U) \
    && (4U*SYSCLK_FREQ % HSE_VALUE == 0U) && (4U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U
/* N=3: M = 6*SYSCLK/HSE, requires HSE >= 24MHz (satisfies FIN/N = HSE/3 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 24000000U) \
    && (6U*SYSCLK_FREQ % HSE_VALUE == 0U) && (6U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (6U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  3U
#define PLL_MUL    ((uint32_t)(6U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U
/* N=4: M = 8*SYSCLK/HSE, requires HSE >= 32MHz (satisfies FIN/N = HSE/4 >= 8MHz) */
#elif (2U*SYSCLK_FREQ >= 96000000U) && (2U*SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 32000000U) \
    && (8U*SYSCLK_FREQ % HSE_VALUE == 0U) && (8U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (8U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  4U
#define PLL_MUL    ((uint32_t)(8U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 2U

/* --- Group C: OD=2, S=2, FVCO=4*SYSCLK, FPLL=2*SYSCLK --- */
/* N=1: M = 4*SYSCLK/HSE */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (4U*SYSCLK_FREQ % HSE_VALUE == 0U) && (4U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U
/* N=2: M = 8*SYSCLK/HSE, requires HSE >= 16MHz (satisfies FIN/N = HSE/2 >= 8MHz) */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 16000000U) \
    && (8U*SYSCLK_FREQ % HSE_VALUE == 0U) && (8U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (8U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(8U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U
/* N=3: M = 12*SYSCLK/HSE, requires HSE >= 24MHz (satisfies FIN/N = HSE/3 >= 8MHz) */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 24000000U) \
    && (12U*SYSCLK_FREQ % HSE_VALUE == 0U) && (12U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (12U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  3U
#define PLL_MUL    ((uint32_t)(12U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U
/* N=4: M = 16*SYSCLK/HSE, requires HSE >= 32MHz (satisfies FIN/N = HSE/4 >= 8MHz) */
#elif (4U*SYSCLK_FREQ >= 96000000U) && (4U*SYSCLK_FREQ <= 160000000U) && (2U*SYSCLK_FREQ >= 64000000U) \
    && (HSE_VALUE >= 32000000U) \
    && (16U*SYSCLK_FREQ % HSE_VALUE == 0U) && (16U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (16U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  4U
#define PLL_MUL    ((uint32_t)(16U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     2U
#define PLL_SYSDIV 2U

/* --- Group D: OD=1, S=1, FVCO=SYSCLK, FPLL=SYSCLK (N32G415 only; SYSCLK=96MHz) --- */
/* N=1: M = SYSCLK/HSE; FIN/N = HSE (8~32MHz, already range-checked above) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (SYSCLK_FREQ % HSE_VALUE == 0U) && (SYSCLK_FREQ / HSE_VALUE >= 2U) && (SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  1U
#define PLL_MUL    ((uint32_t)(SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U
/* N=2: M = 2*SYSCLK/HSE, requires HSE >= 16MHz (satisfies FIN/N = HSE/2 >= 8MHz) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 16000000U) \
    && (2U*SYSCLK_FREQ % HSE_VALUE == 0U) && (2U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (2U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  2U
#define PLL_MUL    ((uint32_t)(2U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U
/* N=3: M = 3*SYSCLK/HSE, requires HSE >= 24MHz (satisfies FIN/N = HSE/3 >= 8MHz) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 24000000U) \
    && (3U*SYSCLK_FREQ % HSE_VALUE == 0U) && (3U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (3U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  3U
#define PLL_MUL    ((uint32_t)(3U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U
/* N=4: M = 4*SYSCLK/HSE, requires HSE >= 32MHz (satisfies FIN/N = HSE/4 >= 8MHz) */
#elif defined(N32G415) && (SYSCLK_FREQ >= 96000000U) && (SYSCLK_FREQ <= 160000000U) \
    && (HSE_VALUE >= 32000000U) \
    && (4U*SYSCLK_FREQ % HSE_VALUE == 0U) && (4U*SYSCLK_FREQ / HSE_VALUE >= 2U) && (4U*SYSCLK_FREQ / HSE_VALUE <= 127U)
#define PLL_INPRE  4U
#define PLL_MUL    ((uint32_t)(4U*SYSCLK_FREQ) / HSE_VALUE)
#define PLL_OD     1U
#define PLL_SYSDIV 1U

#else
#error Cannot find valid PLL factors with HSE: check SYSCLK_FREQ limit and that SYSCLK_FREQ is divisible by HSE_VALUE. N32G412: Groups A/B/C (SYSCLK<=80MHz, N=1~4). N32G415: additionally Group D (SYSCLK=96MHz, N=1~4, FIN/N>=8MHz requires HSE>=8/16/24/32MHz for N=1/2/3/4).
#endif

#else
#error wrong value for SYSCLK_SRC
#endif

#ifndef VECT_TAB_OFFSET
#define VECT_TAB_OFFSET 0x0U /*!< Vector Table base offset field. This value must be a multiple of 0x200. */
#endif

/*******************************************************************************
 *  Clock Definitions
 *******************************************************************************/
uint32_t SystemCoreClock = SYSCLK_FREQ; /*!< System Clock Frequency (Core Clock) */



static void SetSysClock(void);

#ifdef DATA_IN_ExtSRAM
extern void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM */

/**
 * @brief  Setup the microcontroller system
 *         Initialize the Embedded Flash Interface, the PLL and update the
 *         SystemCoreClock variable.
 * @note   Intended to be called at startup (after reset or after a secondary bootloader
 *         jump). Handles residual clock state left by a secondary bootloader.
 */
void SystemInit(void)
{
    /* Ensure HSI is running */
    RCC->CTRL |= RCC_CTRL_HSIEN;
    while((RCC->CTRL & RCC_CTRL_HSIRDF) != RCC_CTRL_HSIRDF)
    {}

    /* Clear CLKSSEN before SYSCLK switch: a secondary bootloader may have left it set,
     * causing a spurious NMI if HSE glitches during the switch. */
    RCC->CTRL &= (uint32_t)(~RCC_CTRL_CLKSSEN);

    /* Switch SYSCLK to HSI */
    RCC->CFG &= (~RCC_CFG_SCLKSW);
    while((RCC->CFG & RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSI)
    {}

    /* Disable HSE and PLL. PLLBP is NOT cleared here: it is cleared after PLLRDF de-asserts
     * (line below) to ensure the PLL is fully stopped before changing bypass configuration.
     * HSEBP is NOT cleared here: HSEEN=0 AND HSERDFDLY=1 are both required at write time. */
    RCC->CTRL &= (uint32_t)(~(RCC_CTRL_HSEEN | RCC_CTRL_PLLEN));
    /* Wait for HSERDF to clear: the manual requires 6 HSE clock cycles after HSEEN=0.
     * Explicit polling eliminates any dependence on software timing or boot context. */
    while((RCC->CTRL & RCC_CTRL_HSERDF) == RCC_CTRL_HSERDF)
    {}
    while((RCC->CTRL & RCC_CTRL_PLLRDF) == RCC_CTRL_PLLRDF)
    {}
    

    /* Reset AHBPRES, APB1PRES, APB2PRES, PLLOD, PLLSRC, PLLMUL, PLLSYSDIV bits */
    RCC->CFG &= (uint32_t)0x00000003U;
    /* crystal mode: disable bypass */
    RCC->CTRL &= (uint32_t)(~RCC_CTRL_HSEBP);  

    /* LSI is left enabled: hardware reset default is LSIEN=1 (CTRL reset bit 31).
     * Closing it here would deviate from reset state; applications may rely on LSI
     * (RTC, BTIM1, IWDG, etc.) without explicitly re-enabling it. */

    /* Reset PLLCTRL (PLL is off). PLLINPRES=0 is forbidden as an operational value (range
     * 1~63) but acceptable while PLL is disabled; matches hardware reset state. */
    RCC->PLLCTRL = 0x00000000U;

    /* Clear all interrupt flags and disable all RCC clock-ready interrupts (LSESSIEN,
     * PLLRDIEN, HSERDIEN, HSIRDIEN, LSERDIEN, LSIRDIEN). The direct "=" write intentionally
     * zeros those rw enable bits — establishing a clean state regardless of what a secondary
     * bootloader may have configured. Application code must re-enable them as needed.
     * NOTE: LSECSSEN (RCC_CTRL bit29) is NOT cleared here. The manual has contradictory
     * descriptions: the register bit table marks it "rw", but the functional description
     * states it can only be cleared by system reset or LSE fault detection. Treating it
     * as effectively write-once is the safer assumption; if a secondary bootloader left
     * LSECSSEN=1, it persists for this boot session.
     * LSESSICLR (bit26 of CLKINT) below clears only the pending interrupt flag, not
     * the LSECSSEN enable bit itself. */
    RCC->CLKINT = (RCC_CLKINT_LSIRDICLR | RCC_CLKINT_HSIRDICLR | RCC_CLKINT_HSERDICLR
                  | RCC_CLKINT_LSERDICLR | RCC_CLKINT_PLLRDICLR | RCC_CLKINT_CLKSSICLR
                  | RCC_CLKINT_LSESSICLR);

    /* Enable ICACHE and disable Prefetch Buffer */
#ifdef N32G412
#if (SYSCLK_FREQ <= 72000000U)
    FLASH->AC |= (uint32_t)(FLASH_AC_ICAHEN);
    FLASH->AC &= (uint32_t)(~FLASH_AC_PRFTBFEN);
#else
    FLASH->AC &= (uint32_t)(~FLASH_AC_ICAHEN);
    FLASH->AC |= (uint32_t)(FLASH_AC_PRFTBFEN);
#endif
#else
    FLASH->AC |= (uint32_t)(FLASH_AC_ICAHEN);
    FLASH->AC &= (uint32_t)(~FLASH_AC_PRFTBFEN);
#endif
  
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();

#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif

#ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM */
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or
 * configure other parameters.
 *
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any
 * configuration based on this variable will be incorrect.
 *
 * @note   - The system frequency computed by this function is not the real
 *           frequency in the chip. It is calculated based on the predefined
 *           constant and the selected clock source:
 *
 *           - If SYSCLK source is HSI, SystemCoreClock will contain the
 * HSI_VALUE(*)
 *
 *           - If SYSCLK source is HSE, SystemCoreClock will contain the
 * HSE_VALUE(**)
 *
 *           - If SYSCLK source is PLL, SystemCoreClock will contain the
 * HSE_VALUE(**) or HSI_VALUE(*) multiplied/divided by the PLL factors.
 *
 *         (*) HSI_VALUE is a constant defined in n32g41x.h file (default value
 *             16 MHz) but the real value may vary depending on the variations
 *             in voltage and temperature.
 *
 *         (**) HSE_VALUE is a constant defined in n32g41x.h file (default value
 *              8 MHz), user has to ensure that HSE_VALUE is same as the real
 *              frequency of the crystal used. Otherwise, this function may
 *              have wrong result.
 *
 *         - The result of this function could be not correct when using
 * fractional value for HSE crystal.
 */
void SystemCoreClockUpdate(void)
{
    const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 7, 7};
    uint32_t tmp, pllclk, pllmull, pllpre, pllod, pllsysdiv, pllsource;

    /* Get SYSCLK source
     * -------------------------------------------------------*/
    tmp = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (tmp)
    {
    case RCC_CFG_SCLKSTS_HSI: /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    case RCC_CFG_SCLKSTS_HSE: /* HSE used as system clock */
        SystemCoreClock = HSE_VALUE;
        break;
    case RCC_CFG_SCLKSTS_PLL: /* PLL used as system clock */

        /* Get PLL parameters */
        pllmull   = ((RCC->CFG & RCC_CFG_PLLMUL) >> 16U);
        pllpre    = ((RCC->PLLCTRL & RCC_PLLCTRL_PLLINPRES) >> 8U);   /* register value = divider directly */
        pllod     = ((RCC->CFG & RCC_CFG_PLLOD) != 0U) ? 2U : 1U;
        pllsysdiv = ((RCC->CFG & RCC_CFG_PLLSYSDIV) != 0U) ? 2U : 1U;
        pllsource = RCC->CFG & RCC_CFG_PLLSRC;

        if (pllsource == 0U)
        {
            /* HSI selected as PLL clock entry */
            pllclk = HSI_VALUE;
        }
        else
        {
            /* HSE selected as PLL clock entry */
            pllclk = HSE_VALUE;
        }

        /* SYSCLK = FIN / N * M / OD / S */
        if (pllpre != 0U)
        {
            SystemCoreClock = pllclk / pllpre * pllmull / pllod / pllsysdiv;
        }
        else
        {
            SystemCoreClock = HSI_VALUE;
        }
        break;

    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }

    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFG & RCC_CFG_AHBPRES) >> 4U)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

/**
 * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1
 * prescalers.
 */
static void SetSysClock(void)
{
    uint32_t tmpregister;

#if ((SYSCLK_SRC == SYSCLK_USE_HSE) || (SYSCLK_SRC == SYSCLK_USE_HSE_PLL))
    uint32_t HSEStatus;
    uint32_t StartUpCounter = 0;
    /* Enable HSE */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CTRL & RCC_CTRL_HSERDF;
        StartUpCounter++;
    } while ((HSEStatus == 0U) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTRL & RCC_CTRL_HSERDF) != RCC_CTRL_HSERDF)
    {
        SystemCoreClock = HSI_VALUE;
        return;
    }
#endif

    /* Flash wait state per spec: 0WS for 0<SYSCLK<=36MHz, 1WS for <=72MHz, 2WS for >72MHz.
     * iCache/Prefetch configuration is done in SystemInit() before this call. */
    tmpregister = FLASH->AC;
    tmpregister &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    tmpregister |= (uint32_t)((SYSCLK_FREQ - 1U) / 36000000U);
    FLASH->AC = tmpregister;

    /* APB1 (PCLK1) prescaler: divide HCLK by 2 when SYSCLK exceeds the chip's PCLK1 limit. */
#ifdef N32G415
    if (SYSCLK_FREQ > 48000000U)  /* N32G415: PCLK1 max 48MHz */
#else
    if (SYSCLK_FREQ > 40000000U)  /* N32G412: PCLK1 max 40MHz */
#endif
    {
        tmpregister = RCC->CFG;
        tmpregister &= (uint32_t)(~RCC_CFG_APB1PRES);
        tmpregister |= (uint32_t)RCC_CFG_APB1PRES_2;
        RCC->CFG = tmpregister;
    }
    /* APB2 (PCLK2) prescaler is not configured here; relies on APB2PRES=0 from SystemInit(). */

#if SYSCLK_SRC == SYSCLK_USE_HSI
    tmpregister = RCC->CFG;
    tmpregister &= (uint32_t)((uint32_t)~(RCC_CFG_SCLKSW));
    tmpregister |= (uint32_t)RCC_CFG_SCLKSW_HSI;
    RCC->CFG = tmpregister;

    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSI)
    {
    }

#elif SYSCLK_SRC == SYSCLK_USE_HSE
    tmpregister = RCC->CFG;
    tmpregister &= (uint32_t)((uint32_t)~(RCC_CFG_SCLKSW));
    tmpregister |= (uint32_t)RCC_CFG_SCLKSW_HSE;
    RCC->CFG = tmpregister;
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSE)
    {
    }

#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL || SYSCLK_SRC == SYSCLK_USE_HSE_PLL

    /* Configure PLL source, multiplication factor, PLLOD and PLLSYSDIV in RCC_CFG */
    tmpregister = RCC->CFG;
    /* Clear PLLSRC, PLLMUL, PLLOD bits */
    tmpregister &= (uint32_t)(~(RCC_CFG_PLLSRC | RCC_CFG_PLLMUL | RCC_CFG_PLLOD ));

    /* Set PLL source */
#if SYSCLK_SRC == SYSCLK_USE_HSE_PLL
    tmpregister |= RCC_CFG_PLLSRC;  /* HSE as PLL source */
#endif
    /* Set PLL multiply factor (direct encoding) */
    tmpregister |= ((uint32_t)PLL_MUL) << 16U;
    /* Set PLLOD */
#if defined(PLL_OD) && (PLL_OD == 2U)
    tmpregister |= RCC_CFG_PLLOD;
#endif
    RCC->CFG = tmpregister;

    /* Configure PLL input prescaler in RCC_PLLCTRL */
    tmpregister = RCC->PLLCTRL;
    /* Clear PLLINPRES and PLLOUTPRES bits */
    tmpregister &= (uint32_t)(~(RCC_PLLCTRL_PLLINPRES | ((uint32_t)0x0000C000U)));
    /* Set PLLINPRES (register value = divider directly) */
    tmpregister |= ((uint32_t)PLL_INPRE) << 8U;

    RCC->PLLCTRL = tmpregister;

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0U)
    {
    }

    tmpregister = RCC->CFG;
    /* Clear RCC_CFG_PLLSYSDIV and RCC_CFG_SCLKSW bits */
    tmpregister &= (uint32_t)(~(RCC_CFG_PLLSYSDIV | RCC_CFG_SCLKSW));
    /* Set PLLSYSDIV */
#if defined(PLL_SYSDIV) && (PLL_SYSDIV == 2U)
    tmpregister |= RCC_CFG_PLLSYSDIV;
#endif
    /* Select PLL as system clock source */
    tmpregister |= (uint32_t)RCC_CFG_SCLKSW_PLL;
    RCC->CFG = tmpregister;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_PLL)
    {
    }

#endif
}
