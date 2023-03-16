/*
 * Sensor.h
 *
 *  Created on: 4 Mar 2023
 *      Author: radek
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_
#include <stdint.h>
#include "stm32f3xx_ll_i2c.h"
typedef enum {
    COMM_TYPE_READ_1,
    COMM_TYPE_READ_2
} CommTypeRead;
typedef enum {
    COMM_TYPE_WRITE_1,
    COMM_TYPE_WRITE_2
} CommTypeWrite;

typedef struct {
	I2C_TypeDef *i2c;
    uint8_t device_address;
    CommTypeRead comm_type_read;
    CommTypeWrite comm_type_write;
    uint8_t* data_send;
    uint8_t data_send_length;
    uint8_t *data_receive;
    uint8_t data_receive_lenght;
    uint32_t delay_time;
} I2C_Sensor;
void initalize_sensor_struct(I2C_Sensor *sensor_struct, uint8_t *data_send, uint8_t *data_receive);

void I2C_Write(I2C_Sensor *device);
void I2C_Read(I2C_Sensor *device);
uint8_t I2C_ReadByte(I2C_Sensor *device);
void I2C_WriteMulti(I2C_Sensor *device, uint8_t *data, uint16_t size);
void I2C_Read_Sensor(I2C_Sensor* sensor);

#endif /* INC_SENSOR_H_ */
