/**
 * @brief Soubor funkcí pro komunikaci I2C na nejnižší úrovni, tyto funkce READ a WRITE jsou volány jinými funkcemi. Slouží k zápisu do I2C
 * @file Sensor.c
 *
 *  Created on: 4 Mar 2023
 *      Author: radek
 */
#include "sensor.h"
#include "i2c.h"

/**
 * @brief Funkce pro zápis na zařízení I2C
 * @param device ukazatel na strukturu snímače
 * @param data ukazatel na zapisované data
 * @param size počet zapisovaných dat
 */
void I2C_Write(I2C_Sensor *device)
{
	LL_I2C_HandleTransfer(device->i2c, (device->device_address)<<1, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	while(!LL_I2C_IsActiveFlag_STOP(device->i2c))
		{
			if(LL_I2C_IsActiveFlag_TXE(device->i2c))
		  	{
			  LL_I2C_TransmitData8(device->i2c, *device->data_send);
	  	  	}
	 	}
	 	HAL_Delay(10);
	 	LL_I2C_ClearFlag_STOP(device->i2c);
}

/**
 * @brief Funkce pro čtení na zařízení I2C
 * @param device ukazatel na strukturu snímače
 * @param data ukazatel na přečtená data
 * @param size počet zapisovaných dat
 */

void I2C_Read(I2C_Sensor *device)
{
    LL_I2C_HandleTransfer(device->i2c, (device->device_address)<<1, LL_I2C_ADDRSLAVE_7BIT, device->data_receive_lenght, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
 	HAL_Delay(100);
    int i = 0;
		  while(!LL_I2C_IsActiveFlag_STOP(device->i2c))
		  {
			  if(LL_I2C_IsActiveFlag_RXNE(device->i2c))
			  {
				  device->data_receive[i++] = LL_I2C_ReceiveData8(device->i2c);
			  }
		  }
		  i=0;
		  HAL_Delay(30);
		  LL_I2C_ClearFlag_STOP(I2C1);
}
/*
void I2C_Read(I2C_Sensor *device)
{
    // Nastavení adresy senzoru
    LL_I2C_HandleTransfer(device->i2c, device->device_address, LL_I2C_ADDRSLAVE_7BIT, device->data_send_length, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
    // Odeslání datového bufferu
    LL_I2C_HandleTransfer(device->i2c,(uint8_t) device->data_send, device->data_send_length, LL_I2C_MODE_SOFTEND, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_START_READ);
    // Čtení datového bufferu
    LL_I2C_HandleTransfer(device->i2c, device->data_receive, device->data_receive_lenght, LL_I2C_MODE_AUTOEND, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_STOP);
    LL_I2C_HandleTransfer(I2Cx, SlaveAddr, SlaveAddrSize, TransferSize, EndMode, Request)
}
*/
void I2C_WriteMulti(I2C_Sensor *device, uint8_t *data, uint16_t size)
{
	LL_I2C_HandleTransfer(device->i2c, device->device_address, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	while(!LL_I2C_IsActiveFlag_STOP(device->i2c))
		{
		for(size_t i=0; i<size;i++)
		{
		HAL_Delay(100);
			if(LL_I2C_IsActiveFlag_TXE(device->i2c))
		  	{
			  LL_I2C_TransmitData8(device->i2c, *data);
	  	  	}
	  	  }
	 	}
	 	HAL_Delay(10);
	 	LL_I2C_ClearFlag_STOP(device->i2c);
}

void I2C_Read_Sensor(I2C_Sensor* sensor) {
    if (sensor->comm_type_read == COMM_TYPE_READ_1) {
        // provádíme čtení dat s typem komunikace 1, napr. HTU21d
    	I2C_Read_select1(sensor);
    }
    else if (sensor->comm_type_read == COMM_TYPE_READ_2) {
        // provádíme čtení dat s typem komunikace 2
    }
}

/*
void I2C_Write_Sensor(I2C_Sensor* sensor) {
    if (sensor->comm_type == COMM_TYPE_1) {
    	I2C_Write(sensor->i2c, sensor->data_send, sensor->data_send_length);
        // provádíme zápis dat s typem komunikace 1
    }
    else if (sensor->comm_type == COMM_TYPE_2) {
        // provádíme zápis dat s typem komunikace 2
    }
}
*/
