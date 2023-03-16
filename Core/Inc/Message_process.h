/*
 * Message_process.h
 *
 *  Created on: 11 Mar 2023
 *      Author: radek
 */

#ifndef INC_MESSAGE_PROCESS_H_
#define INC_MESSAGE_PROCESS_H_
#include "Sensor.h"

uint8_t Msg_process(I2C_Sensor *device,uint8_t *data, uint8_t data_size);
uint8_t recData_check(I2C_Sensor *device,uint8_t *data, uint8_t data_size);
#endif /* INC_MESSAGE_PROCESS_H_ */
