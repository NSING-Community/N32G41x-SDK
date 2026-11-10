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
*\*\file main.c
*\*\author NSING
*\*\version v1.0.0
*\*\copyright Copyright (c) 2026, NSING Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"
#include "n32g41x_gpio.h"
#include "n32g41x_usart.h"
#include "n32g41x_rcc.h"
#include "n32g41x_flash.h"
#include "n32g41x_iwdg.h"
#include "n32g41x_stb.h"

#ifdef N32G415
#define SYSTEMCLK_FREQ 96000000U
#else /* N32G412 */
#define SYSTEMCLK_FREQ 80000000U
#endif

/* Constant for BOOT */
uint32_t BootAddr, SPAddr;

/* The pointer of function */
typedef void (*pFunction)(void);

/* Init a button for test */
void Button_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO Clock */
    BUTTON_WKUP_CLK_ENABLE;

    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStructure.Pin       = BUTTON_WKUP_PIN;
    GPIO_InitStructure.GPIO_Pull = BUTTON_WKUP_PULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(BUTTON_WKUP_PORT, &GPIO_InitStructure);
}

/* Get the state of button */
Bit_OperateType Button_Read(void)
{
    return ((GPIO_ReadInputDataBit(BUTTON_WKUP_PORT, BUTTON_WKUP_PIN) == BUTTON_WKUP_STATE) ? Bit_SET : Bit_RESET);
}

/* Set HSI as systerm clock  */
ErrorStatus SetSysClockToPLL(uint32_t PLL_src, uint32_t SYS_freq)
{
    uint32_t timeout_value = 0xFFFFFFFF;
    ErrorStatus ClockStatus;
    uint32_t latency;
    uint32_t pllmul, pllinpre, plloutdiv;
    FunctionalState pllsysdiv;

    if ((PLL_src == RCC_PLL_SRC_HSE) && (HSE_VALUE != 8000000))
    {
        /* HSE_VALUE == 8000000 is needed in this project */
        return ERROR;
    }

    /* RCC system reset */
    FLASH_SetLatency(FLASH_LATENCY_2);
    RCC_DeInit();

    if (PLL_src == RCC_PLL_SRC_HSE)
    {
        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Wait till HSE is ready */
        ClockStatus = RCC_WaitHseStable();
    }
    else
    {
        /* Enable HSI */
        RCC_EnableHsi(ENABLE);

        /* Wait till HSI is ready */
        ClockStatus = RCC_WaitHsiStable();
    }

    if (ClockStatus != SUCCESS)
    {
        return ERROR;
    }

    /** Configure PLL input prescaler based on clock source
     * HSI = 16MHz -> PLLINPRES = /4 -> 4MHz 
     * HSE = 8MHz  -> PLLINPRES = /2 -> 4MHz  **/
    if (PLL_src == RCC_PLL_SRC_HSI)
    {
        pllinpre = 4;
    }
    else
    {
        pllinpre = 2;
    }

    switch (SYS_freq)
    {
        case 72000000:
            /* 4MHz * 36 = 144MHz(FVCO) / 1(PLLOD) /1 = 144MHz(Fpll) */
            latency   = FLASH_LATENCY_1;   /* 36MHz < SYSCLK <= 72MHz */
            pllmul    = 36;
            plloutdiv = RCC_PLL_OD_DIV_1;
            pllsysdiv = ENABLE;
            break;
        case 80000000:
            /* 4MHz * 40 = 160MHz(FVCO) / 2(PLLOD) /1 = 80MHz(Fpll) */
            latency   = FLASH_LATENCY_2;   /* 72MHz < SYSCLK <= 80MHz */
            pllmul    = 40;
            plloutdiv = RCC_PLL_OD_DIV_2;
            pllsysdiv = DISABLE;
            break;
        case 96000000:
            /* 4MHz * 48 = 192MHz(FVCO) / 2(PLLOD) /1 = 96MHz(Fpll) */
            latency   = FLASH_LATENCY_2;   /* 72MHz < SYSCLK <= 96MHz */
            pllmul    = 48;
            plloutdiv = RCC_PLL_OD_DIV_2;
            pllsysdiv = DISABLE;
            break;
        default:
            return ERROR;
    }

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(RCC_HCLK_DIV1);

    /* PCLK1 = HCLK/2 */
    RCC_ConfigPclk1(RCC_HCLK_DIV2);

    /* Configure PLL: source, input prescaler, multiplier, output prescaler */
    RCC_ConfigPll(PLL_src, pllinpre, pllmul, plloutdiv);

    /* Enable PLL */
    RCC_EnablePll(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) != SET)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }

    /* Enable or Disable PLLSYSDIV (SYSCLK = FPLL / pllsysdiv) */
    RCC_EnablePllSysclkDiv(pllsysdiv);

    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL);

    /* Wait till PLL is used as system clock source */
    timeout_value = 0xFFFFFFFF;
    while (RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }

    FLASH_SetLatency(latency);
    return SUCCESS;
}

/* Function of how to jump to Boot */
void Jump_To_BOOT(void)
{
    /* Disable all interrupt */
    __disable_irq();

    /* Config IWDG */
    IWDG_ReloadKey();
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV256);

    USART_DeInit(USART1);

    /* Config HSI as system clock */
    if (SetSysClockToPLL(RCC_PLL_SRC_HSI, SYSTEMCLK_FREQ) != ERROR)
    {
        BootAddr = *(uint32_t *)0x1FFF0004;
        SPAddr   = *(uint32_t *)0x1FFF0000;

        /* Set JumpBoot addr */
        pFunction JumpBoot = (pFunction)BootAddr;

        /* Initalize Stack Pointer */
        __set_MSP(SPAddr);

        /* Enable interrupt */
        __enable_irq();

        /* Jump to BOOT */
        JumpBoot();
    }
    else
    {
        log_init();
        printf("Config HSI as system clock failure!\n");
    }
}

/* Main program. */
int main(void)
{
    /* Init debug usart */
    log_init();

    /* Init Button */
    Button_Config();

    /* Debug information */
    printf("Jump to Boot demo start with normal state!\r\n");
    printf("If you press WKUP Button,system will jump to BOOT!\r\n\r\n");

    /* Wait button to be pressed */
    while (Button_Read() != Bit_SET)
    {
    }

    printf("System jumped to BOOT!\r\n\r\n");

    /** Jump to BOOT 
     * Note: need to turn off other peripherals before jumping to the boot.
     **/
    Jump_To_BOOT();

    /* Infinite loop */
    while (1);
}





