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
*\*\file can_config.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "can_config.h"

#define CAN_TXDLC_8    ((uint8_t)8)
#define CAN_FILTERNUM0 ((uint8_t)0)

CanTxMessage CAN_TxMessage;
CanRxMessage CAN_RxMessage;

CAN_InitType        CAN_InitStructure;
CAN_FilterInitType  CAN_FilterInitStructure;

/**
*\*\name    CAN_CONFIG.
*\*\fun     Initialize CAN in loopback mode.
*\*\param   none
*\*\return  none
**/
void CAN_CONFIG(void)
{
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN, ENABLE);

    CAN_NVIC_Configuration();
    CAN_GPIO_Configuration();

    CAN_DeInit(CAN);
    CAN_InitStruct(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.TTCM          = DISABLE;
    CAN_InitStructure.ABOM          = DISABLE;
    CAN_InitStructure.AWKUM         = DISABLE;
    CAN_InitStructure.NART          = DISABLE;
    CAN_InitStructure.RFLM          = DISABLE;
    CAN_InitStructure.TXFP          = ENABLE;
    CAN_InitStructure.OperatingMode = CAN_LoopBack_Mode;

#ifdef N32G415
    /* Baud rate = APB1CLK / (BaudRatePrescaler * (TBS1 + TBS2 + 1))
       APB1CLK = 48MHz, 48000000 / (6 * (11 + 4 + 1)) = 500000 = 500Kbps */
    CAN_InitStructure.RSJW              = CAN_RSJW_4tq;
    CAN_InitStructure.TBS1              = CAN_TBS1_11tq;
    CAN_InitStructure.TBS2              = CAN_TBS2_4tq;
    CAN_InitStructure.BaudRatePrescaler = 6;
#else
    /* Baud rate = APB1CLK / (BaudRatePrescaler * (TBS1 + TBS2 + 1))
       APB1CLK = 40MHz, 40000000 / (5 * (11 + 4 + 1)) = 500000 = 500Kbps */
    CAN_InitStructure.RSJW              = CAN_RSJW_4tq;
    CAN_InitStructure.TBS1              = CAN_TBS1_11tq;
    CAN_InitStructure.TBS2              = CAN_TBS2_4tq;
    CAN_InitStructure.BaudRatePrescaler = 5;
#endif

    CAN_Init(CAN, &CAN_InitStructure);

    /* CAN filter init */
    CAN_FilterInitStructure.Filter_Num            = 0;
    CAN_FilterInitStructure.Filter_Mode           = CAN_Filter_IdMaskMode;
    CAN_FilterInitStructure.Filter_Scale          = CAN_Filter_32bitScale;
    CAN_FilterInitStructure.Filter_HighId         = CAN_STD_ID_LIST_32BIT_H(0x00000400);
    CAN_FilterInitStructure.Filter_LowId          = CAN_STD_ID_LIST_32BIT_L(0x00000400);
    CAN_FilterInitStructure.FilterMask_HighId     = CAN_STD_ID_LIST_32BIT_H(0x00000200);
    CAN_FilterInitStructure.FilterMask_LowId      = CAN_STD_ID_LIST_32BIT_L(0x00000200);
    CAN_FilterInitStructure.Filter_FIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.Filter_Act            = ENABLE;
    CAN_InitFilter(&CAN_FilterInitStructure);

    /* IT Configuration for CAN */
    CAN_INTConfig(CAN, CAN_INT_FMP0, ENABLE);
}

/**
*\*\name    CAN_NVIC_Configuration.
*\*\fun     Configure CAN NVIC interrupt.
*\*\param   none
*\*\return  none
**/
void CAN_NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = CAN_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    CAN_GPIO_Configuration.
*\*\fun     Configure CAN TX/RX GPIO pins.
*\*\param   none
*\*\return  none
**/
void CAN_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_GPIO, ENABLE);

    /* Configure CAN RX pin */
    GPIO_InitStructure.Pin            = CAN_RX_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = CAN_RX_AF;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(CAN_RX_PORT, &GPIO_InitStructure);

    /* Configure CAN TX pin */
    GPIO_InitStructure.Pin            = CAN_TX_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = CAN_TX_AF;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_HIGH;
    GPIO_InitPeripheral(CAN_TX_PORT, &GPIO_InitStructure);
}

/**
*\*\name    Check_CanRecData.
*\*\fun     Verify received CAN message matches expected values.
*\*\param   RxMessage: pointer to received message
*\*\param   StdId, ExtId, IDE, RTR, DLC: expected message fields
*\*\param   Data0~Data7: expected data bytes
*\*\param   FMI: expected filter match index
*\*\return  Pass: match, Fail: mismatch
**/
uint8_t Check_CanRecData(CanRxMessage* RxMessage, uint32_t StdId, uint32_t ExtId, uint8_t IDE, uint8_t RTR, uint8_t DLC,
                         uint8_t Data0, uint8_t Data1, uint8_t Data2, uint8_t Data3,
                         uint8_t Data4, uint8_t Data5, uint8_t Data6, uint8_t Data7, uint8_t FMI)
{
    if(IDE == CAN_Extended_Id)
    {
        if(RxMessage->ExtId != ExtId)
            return Fail;
    }
    else if(IDE == CAN_Standard_Id)
    {
        if(RxMessage->StdId != StdId)
            return Fail;
    }

    if( (RxMessage->IDE != IDE) ||
        (RxMessage->RTR != RTR) ||
        (RxMessage->DLC != DLC) )
    {
        return Fail;
    }

    if(RTR == CAN_RTRQ_Data)
    {
        if(DLC >= 1) { if(RxMessage->Data[0] != Data0) return Fail; }
        if(DLC >= 2) { if(RxMessage->Data[1] != Data1) return Fail; }
        if(DLC >= 3) { if(RxMessage->Data[2] != Data2) return Fail; }
        if(DLC >= 4) { if(RxMessage->Data[3] != Data3) return Fail; }
        if(DLC >= 5) { if(RxMessage->Data[4] != Data4) return Fail; }
        if(DLC >= 6) { if(RxMessage->Data[5] != Data5) return Fail; }
        if(DLC >= 7) { if(RxMessage->Data[6] != Data6) return Fail; }
        if(DLC == 8) { if(RxMessage->Data[7] != Data7) return Fail; }
        if(DLC > 8)  return Fail;
    }

    if(RxMessage->FMI != FMI)
        return Fail;

    return Pass;
}
