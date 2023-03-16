/**
 * @file	Message_process.c
 * @brief	Soubor funkcí pro stav STATE_MESSAGE_PROCESS
 *
 *  Created on: 11 Mar 2023
 *      Author: radek
 */
#include "Message_process.h"
#define INIT_COMMAND 0xFE	///< hodnota init Msg
uint8_t Sensor_init = 0;	///< Proměnná značí stav, jestli byl snímač jíž inicializován

/**
 * @brief	Kontrola pro správnost přijaté zprávy
 * Proběhne kontrola, zdali se jedná o inicializační Msg, v takovém připadě další kontrola zda-li není již snímač inicializován
 * @return	hodnota 0 (kontrola se nezdařila) nebo 1 (kontrola v pořádku)
 * @param	device Ukazatel na strukturu snímače
 * @param	data Ukazatel na přijaté data
 * @param	data_size počet rpvků dat (nejspíš není nutné)
 */
uint8_t Msg_process(I2C_Sensor *device,uint8_t *data, uint8_t data_size){
	if(data[0]==INIT_COMMAND){
		if(Sensor_init==0){
			//I2C_Sensor sensor;
			uint8_t data_buffer[1] = {0xE3};	///< pole dat pro zápis
			uint8_t data_rec[2];
			initalize_sensor_struct(device, data_buffer, data_rec);
			Sensor_init = 1;
			return 1;
		}
		else{				//init_command ale snimac jiz inicializovan
			return 0;
		}
	}
	else{
		if(recData_check(device,data, data_size))
			return 1;
		else
			return 0;
	}
}

/// \brief Funkce pro kontrolu prijatych dat v bufferu RxData
///	\param device je ukazatel na strukturu sniamce se kterou program pracuje
/// \param data je ukazatel na data, které se kontrolují
/// \param data_size je pocet prvku buffer -- tato je asi blblost kontrolovat, navic to do funkce napišu napevno
/// \return hodnota 0 nebo 1, pokud uspesnosti validace dat
uint8_t recData_check(I2C_Sensor *device,uint8_t *data, uint8_t data_size)
{
	if(data[0]!=device->device_address)	//kontrola adresy
		return 0;
	else if(data_size>8)
		return 0;
	else
		return 1;
}
