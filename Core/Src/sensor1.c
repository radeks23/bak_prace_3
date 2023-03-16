/**
 * 	@file	sensor1.c
 *	@brief	Soubor definice struktury a funkcí pro snímač typu 1. Snímače patřicí do této skupiny: HTU21D
 *  Created on: 11 Mar 2023
 *  @author	radek
 */
#include "sensor1.h"

  //uint8_t data_buffer[] = {0xE3};	///< pole dat pro zápis
  //uint8_t data_rec[2];				///< pole dat pro uložení přečtených dat

/// \brief Funkc epro inializaci snímače s danými parametry, dané parametry lze měnit
/// \param sensor_struct ukazatel na předanou strukturu obecného snímače
  void initalize_sensor_struct(I2C_Sensor *sensor_struct, uint8_t *data_send, uint8_t *data_receive){
	  sensor_struct->device_address = (0x40);
	  sensor_struct->i2c = I2C1;
	  sensor_struct->comm_type_read = COMM_TYPE_READ_1;
	  sensor_struct->comm_type_write = COMM_TYPE_WRITE_1;
	  sensor_struct->data_receive = data_receive;
	  sensor_struct->data_receive_lenght = 2;
	  sensor_struct->data_send = data_send;
	  sensor_struct->data_send_length = 1;
  }

 /**
  * @brief Funkce pro čtení na typu sensoru 1
  * Nejjednonušší způsob, zapíše se příkaz, a ihned se čte
  * @param sensor ukzatel na strukturu sensoru
  */
void I2C_Read_select1(I2C_Sensor *sensor){
	I2C_Write(sensor);
	I2C_Read(sensor);
}
