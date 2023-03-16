/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include <stdbool.h>
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f303k8_i2c.h"
#include "Sensor.h"
#include "Message_process.h"
#include "Operation.h"
#define SENSOR_TYPE 1 // nebo 2 podle toho, jaký senzor chcete použít

#ifdef SENSOR_TYPE
  #if SENSOR_TYPE == 1
    #include "sensor1.h"
  #elif SENSOR_TYPE == 2
    #include "sensor1.h"
  #else
    #error "Unsupported sensor type"
  #endif
#else
  #error "Sensor type not defined"
#endif

uint8_t i2c_recData[2] ={0};
uint8_t Rx_count = 0;
#define BUFFER_SIZE_REC 8
uint8_t RxData[BUFFER_SIZE_REC];
 uint8_t buffer_index_rec;
uint8_t recvComplete;
typedef enum{
	 	STATE_START,
	    STATE_IDLE,
	    STATE_PROCESS_MESSAGE,
	    STATE_SENSOR_OPERATION,
	    STATE_MODBUS_RESPONSE,
	    STATE_MODBUS_ERROR_MSG
} State_t;
fedfasdefsef;
void SystemClock_Config(void);

int main(void)
{
  State_t currentState = STATE_START;

  while (1)
  {
	 switch(currentState){
	  case STATE_START:
		  HAL_Init();
		  SystemClock_Config();
		  MX_GPIO_Init();
		  MX_DMA_Init();
		  MX_USART2_UART_Init();
		  MX_I2C1_Init();
		  I2C_Sensor sensor;
		  //initalize_sensor_struct(&sensor);


		  currentState = STATE_IDLE;
		  break;

	  case STATE_IDLE:
		  if(recvComplete)
		  {
			  currentState = STATE_PROCESS_MESSAGE;
		  	  recvComplete = 0;
		  }
		  else if(!recvComplete)
			  currentState = STATE_IDLE;
		  break;

	  case STATE_PROCESS_MESSAGE:
	  {
		  if(Msg_process(&sensor, RxData, 8))
			  currentState = STATE_SENSOR_OPERATION;
		  else
			  currentState = STATE_MODBUS_ERROR_MSG;
		  break;
	  }
	  case STATE_SENSOR_OPERATION:
		  if(OperationMsg(&sensor, RxData))
			  currentState = STATE_MODBUS_RESPONSE;
		  else
			  currentState = STATE_MODBUS_ERROR_MSG;
		  break;

	  case STATE_MODBUS_RESPONSE:
		  TxData[0]=sensor.data_receive[0];
		  DMA_TransmitData();
		  currentState = STATE_IDLE;		//nezapomenout zmenit
		  break;

	  case STATE_MODBUS_ERROR_MSG:
		  currentState = STATE_IDLE;
		  break;

	  default:
		  currentState = STATE_START;
		  break;
	  }//end switch
  }//end while
}//end main


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void USART2_IRQHandler(void)
{

  static uint8_t counter = 0;
  /* USER CODE BEGIN USART2_IRQn 0 */
  if (LL_USART_IsActiveFlag_ORE(USART2)) // Over run error
  {
    LL_USART_ReceiveData9(USART2); // read away
    counter = 0;
  }
  else if (LL_USART_IsActiveFlag_PE(USART2)) // Parity error
  {
    LL_USART_ReceiveData9(USART2); // read and discard
    counter = 0;
  }
   else if (LL_USART_IsActiveFlag_FE(USART2)) // Framing error
  {
    LL_USART_ReceiveData9(USART2); // read away
    counter = 0;
  }
  else if (LL_USART_IsActiveFlag_RXNE(USART2))
  {
    RxData[counter++] = (uint32_t)LL_USART_ReceiveData9(USART2);
    if (8 <= counter)
    {
      counter = 0;
      recvComplete = 1;
      LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_3);
    }
	// receive processing
  }
}

void clearArray(uint8_t* arr, size_t size) {
    for(int i = 0; i < size; i++) {
        *(arr + i) = 0;
    }
}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
