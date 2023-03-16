/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"
#include "main.h"
uint8_t TxData[16]= {0};
void MX_DMA_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  NVIC_SetPriority(DMA1_Channel7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void DMA_TransmitData()
{
	 LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);

	  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, sizeof(TxData));

	  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);

	  LL_USART_EnableDMAReq_TX(USART2);
}

