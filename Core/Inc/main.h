/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_i2c.h"
#include "stm32f3xx_ll_usart.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"

extern uint8_t TxData[16];

void Error_Handler(void);
void clearArray(uint8_t* arr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
