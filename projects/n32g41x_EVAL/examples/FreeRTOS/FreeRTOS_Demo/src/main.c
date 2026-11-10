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
#include "n32g41x_rcc.h"
#include "n32g41x_gpio.h"
#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

/* Task handles */
static TaskHandle_t LedTaskHandle   = NULL;
static TaskHandle_t PrintTaskHandle = NULL;

/** Both hooks are enabled in FreeRTOSConfig.h, so they must be implemented here
 * or the link would fail with undefined symbols. **/

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
/**
 *\*\name   vApplicationStackOverflowHook.
 *\*\fun    Stack overflow hook.
 *\*\param  xTask      : handle of the task that overflowed
 *\*\param  pcTaskName : name of the task that overflowed
 *\*\return none
**/
APP_NORETURN void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    printf("Stack overflow in task: %s\r\n", pcTaskName);
    taskDISABLE_INTERRUPTS();
    for (;;)
    {
    }
}
#endif

#if (configUSE_MALLOC_FAILED_HOOK == 1)
/**
 *\*\name   vApplicationMallocFailedHook.
 *\*\fun    Heap allocation failure hook, normally means configTOTAL_HEAP_SIZE
 *\*\        is too small.
 *\*\param  none
 *\*\return none
**/
APP_NORETURN void vApplicationMallocFailedHook(void)
{
    printf("Malloc failed, please increase configTOTAL_HEAP_SIZE\r\n");
    taskDISABLE_INTERRUPTS();
    for (;;)
    {
    }
}
#endif

/**
 *\*\name   LedTask.
 *\*\fun    Blinks LED1 every 500ms.
 *\*\param  pvParameters : not used
 *\*\return none
**/
static void LedTask(void *pvParameters) APP_NORETURN;
static void LedTask(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        LED_Blink(LED1_PORT, LED1_PIN);

        /** Inside a task always use vTaskDelay() to give up the CPU.
         * Do NOT use the BSP SysTick_Delay_Ms(): it reprograms SysTick and
         * disables its interrupt, which would break the FreeRTOS tick. **/
        vTaskDelay(pdMS_TO_TICKS(LED_TASK_PERIOD_MS));
    }
}

/**
 *\*\name   PrintTask.
 *\*\fun    Prints a counter and the remaining stack once per second.
 *\*\param  pvParameters : not used
 *\*\return none
**/
static void PrintTask(void *pvParameters) APP_NORETURN;
static void PrintTask(void *pvParameters)
{
    uint32_t count = 0;

    (void)pvParameters;

    log_info("FreeRTOS template running on N32G41x.\r\n");
    log_info("SystemCoreClock = %u Hz, tick = %u Hz\r\n",
             (unsigned int)SystemCoreClock,
             (unsigned int)configTICK_RATE_HZ);

    for (;;)
    {
        count++;
        log_info("PrintTask count = %u, stack free = %u words\r\n",
                 (unsigned int)count,
                 (unsigned int)uxTaskGetStackHighWaterMark(NULL));

        vTaskDelay(pdMS_TO_TICKS(PRINT_TASK_PERIOD_MS));
    }
}

/**
 *\*\name   main.
 *\*\fun    Initializes the peripherals, creates the tasks and starts the
 *\*\        scheduler.
 *\*\param  none
 *\*\return none
**/
int main(void)
{
    BaseType_t xReturn = pdFAIL;

    /* Serial log init: USART1, PA9(TX) / PA10(RX), 115200-8-N-1 */
    log_init();

    /* LED port init */
    LED_Init(LED1_PORT, LED1_PIN, LED1_CLOCK);
    LED_Init(LED2_PORT, LED2_PIN, LED2_CLOCK);
    LED_Init(LED3_PORT, LED3_PIN, LED3_CLOCK);

    log_info("\r\nFreeRTOS template demo start...\r\n");

    /* Create the LED blink task */
    xReturn = xTaskCreate((TaskFunction_t)LedTask,
                          (const char *)"LedTask",
                          (configSTACK_DEPTH_TYPE)LED_TASK_STACK_SIZE,
                          (void *)NULL,
                          (UBaseType_t)LED_TASK_PRIORITY,
                          (TaskHandle_t *)&LedTaskHandle);
    if (xReturn != pdPASS)
    {
        log_info("Task <<LedTask>> creation failed!!\r\n");
    }

    /* Create the serial print task */
    xReturn = xTaskCreate((TaskFunction_t)PrintTask,
                          (const char *)"PrintTask",
                          (configSTACK_DEPTH_TYPE)PRINT_TASK_STACK_SIZE,
                          (void *)NULL,
                          (UBaseType_t)PRINT_TASK_PRIORITY,
                          (TaskHandle_t *)&PrintTaskHandle);
    if (xReturn != pdPASS)
    {
        log_info("Task <<PrintTask>> creation failed!!\r\n");
    }

    /* Start the scheduler, this call does not return when it succeeds */
    vTaskStartScheduler();

    /** Reaching this point means the heap was too small to create the idle and
     * timer tasks. **/
    log_info("Scheduler start failed, heap may be insufficient!!\r\n");
    while (1)
    {
    }
}

/**
 *\*\name   LED_Init.
 *\*\fun    Initializes a GPIO as an LED output.
 *\*\param  GPIOx : port
 *\*\param  Pin   : pin
 *\*\param  clock : port clock
 *\*\return none
**/
void LED_Init(GPIO_Module *GPIOx, uint16_t Pin, uint32_t clock)
{
    GPIO_InitType InitStruct;

    GPIO_InitStruct(&InitStruct);

    /* Enable GPIO clock */
    RCC_EnableAHBPeriphClk(clock, ENABLE);

    /* Configure as push-pull output */
    InitStruct.Pin            = Pin;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    InitStruct.GPIO_Alternate = GPIO_NO_AF;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_HIGH;

    GPIO_InitPeripheral(GPIOx, &InitStruct);
}

/**
 *\*\name   LED_On.
 *\*\fun    Turns on the LED.
 *\*\param  GPIOx : port
 *\*\param  Pin   : pin
 *\*\return none
**/
void LED_On(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIO_SetBits(GPIOx, Pin);
}

/**
 *\*\name   LED_Off.
 *\*\fun    Turns off the LED.
 *\*\param  GPIOx : port
 *\*\param  Pin   : pin
 *\*\return none
**/
void LED_Off(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIO_ResetBits(GPIOx, Pin);
}

/**
 *\*\name   LED_Blink.
 *\*\fun    Toggles the LED.
 *\*\param  GPIOx : port
 *\*\param  Pin   : pin
 *\*\return none
**/
void LED_Blink(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIO_TogglePin(GPIOx, Pin);
}
