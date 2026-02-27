/*
 * eeprom.h
 *
 * Created: 03.12.2023 17:32:44
 *  Author: yarma
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

#define EEPROM_start_address 0x0000


// function prototypes
void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);

// Mode input definitions


//global variables


#endif /* EEPROM_H_ */