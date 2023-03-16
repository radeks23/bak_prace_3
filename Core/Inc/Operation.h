/*
 * file Operation.h
 *
 *
 *  Created on: 12 Mar 2023
 *      Author: radek
 */

#ifndef INC_OPERATION_H_
#define INC_OPERATION_H_
#include "Sensor.h"

#define ReadHoldingRegister 0x03
#define WriteSingleRegister 0x06
#define ReadWriteMultipleRegisters 0x23
uint8_t OperationMsg(I2C_Sensor *device, uint8_t *Msg);

#endif /* INC_OPERATION_H_ */
