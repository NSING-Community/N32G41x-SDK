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
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "n32g41x_flash.h"
#include <stdio.h>

#define FLASH_PAGE_SIZE        ((uint32_t)0x200)  /* 512 bytes per page */
#define FLASH_WRITE_START_ADDR ((uint32_t)0x08008000)
#define FLASH_WRITE_END_ADDR   ((uint32_t)0x08008200)

volatile TestStatus MemoryProgramStatus = PASSED;

/**
*\*\name    main.
*\*\fun     Flash program demo: erase a page, program words, then verify.
*\*\return  none
**/
int main(void)
{
    uint32_t Address = 0;
    uint32_t Data    = 0x12345678;
    
    /* Initialize USART for log output */
    log_init();
    printf("\r\nFlash Program Demo\r\n");
    
    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock();
    
    /* Erase one page */
    printf("Erasing page at 0x%08X...\r\n", (uint32_t)FLASH_WRITE_START_ADDR);
    if (FLASH_EraseOnePage(FLASH_WRITE_START_ADDR) != FLASH_EOP)
    {
        printf("Erase FAILED!\r\n");
        while (1) {}
    }
    printf("Erase OK\r\n");
    
    /* Program Flash word by word */
    printf("Programming...\r\n");
    Address = FLASH_WRITE_START_ADDR;
    while (Address < FLASH_WRITE_END_ADDR)
    {
        if (FLASH_ProgramWord(Address, Data) != FLASH_EOP)
        {
            printf("Program FAILED at 0x%08X!\r\n", (uint32_t)Address);
            while (1) {}
        }
        Address += 4;
    }
    printf("Program OK\r\n");
    
    /* Lock the Flash */
    FLASH_Lock();
    
    /* Verify programmed data */
    printf("Verifying...\r\n");
    Address = FLASH_WRITE_START_ADDR;
    MemoryProgramStatus = PASSED;
    while (Address < FLASH_WRITE_END_ADDR)
    {
        if ((*(__IO uint32_t*)Address) != Data)
        {
            MemoryProgramStatus = FAILED;
            printf("Verify FAILED at 0x%08X! (read 0x%08X, expected 0x%08X)\r\n",
                   (uint32_t)Address,
                   (uint32_t)(*(__IO uint32_t*)Address),
                   (uint32_t)Data);
            break;
        }
        Address += 4;
    }
    
    if (MemoryProgramStatus == PASSED)
    {
        printf("Flash Program Test PASSED!\r\n");
    }
    else
    {
        printf("Flash Program Test FAILED!\r\n");
    }
    
    while (1)
    {
    }
}
