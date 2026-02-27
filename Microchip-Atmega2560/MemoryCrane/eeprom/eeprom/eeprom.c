/*
 * eeprom.c
 *
 * Created: 03.12.2023 17:32:53
 *  Author: yarma
 */ 

#include "eeprom.h"


void eeprom_write(uint16_t address, uint8_t data)
{
	EECR = 0x00;
	while(EECR & (1 << EEPE));	//wait for completion of previous write
	
	//set up registers for data transfer
	EEAR = address;
	EEDR = data;
	
	//write the data by setting these bits
	EECR = (1 << EEMPE);
	EECR |= (1 << EEPE);
}


uint8_t eeprom_read(uint16_t address)
{
	while(EECR & (1 << EEPE));	//wait for completion of previous write
	EEAR = address;	//set up the address register to read from
	EECR |= (1 << EERE);	//read from eeprom
	return EEDR;	//return read data from the data register
}
