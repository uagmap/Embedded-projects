/*
 * eeprom.c
 *
 * Created: 03.12.2023 17:31:59
 * Author : yarma
 
 
 so there is a read and write functions now
 In this example i used the write function to write value 128 to a start location of 0x0000 then i comment out the write line and restart my board and the value is still there
 You give an address and a 8-bit value to a write function and it stores it there even when powered off
 if we need to record many values we can use a for loop to record them sequentially - eeprom_address++ 
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "serial.c"
#include "eeprom.h"
//#include <avr/eeprom.h>

uint8_t eeprom_value;
uint16_t *eeprom_address;


int main(void)
{
	init_UART();
	
    eeprom_address = EEPROM_start_address;
	//eeprom_write(eeprom_address, 128);
	
	eeprom_value = eeprom_read(eeprom_address);
	
	printf("%d\r", eeprom_value);
    while (1) 
    {
    }
}

