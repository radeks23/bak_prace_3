/**
 * @file Operation.c
 *	@brief Obsluha operace sensoru na základě přijaté zprávy
 *
 *  Created on: 12 Mar 2023
 *      Author: radek
 */
#include "Operation.h"
/**
 * @brief Funkce obsluhujici vykonavanou funkci sensoru na zaklade prijaté zprávy
 * Dle 2 bytu přijaté zprávy je rozhodnuto o vykonávané operaci
 * @return 0 (operace se nezdařila), 1 operace s ezdařila
 * @param device ukazatel na strukturu sensoru
 * @param Msg ukazatel na data v přijat modbus zprávě
 */
uint8_t OperationMsg(I2C_Sensor *device, uint8_t *Msg){
	uint8_t Command = Msg[1];		///< promena s hodnotou kodu operace (pouze pro zprehledneni)
	switch(Command){
		case ReadHoldingRegister:
			I2C_Read_Sensor(device);
			return 1;
			break;

		case WriteSingleRegister:
			return 1;
			break;

		default:
			return 0;
			break;
	}
}

