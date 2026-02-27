/*
 * Project name: LCD_UART
 * Filename: main.c
 *
 * Created: 10/27/2023 8:40 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This module contains the functions for interacting with LCD
 * LCD_Write is used to either send a character or an instruction byte
 * PrintString is used to send a string array using its memory locations
 *	
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * PORTD.0				RS
 * PORTD.1				RW
 * PORTD.2				EN
 * PORTL.0-7			D0-D7
 */ 

#include "LCD.h"

/* Perform LCD initialization */
void Init_LCD (void)
{
	_delay_ms(35);				/* wait for more than 30mS after VDD rises to 4.5V */
	LCD_write(INSTR_WR,0x38); 	/* function set 8bits, 2line, display off */
	_delay_us(50);				/* wait for more than 39microS */
	LCD_write(INSTR_WR,0x0C);	/* display on, cursor off, blink off */
	_delay_us(50);				/* wait for more than 39microS */
	LCD_write(INSTR_WR,0x01);	/* display clear */
	_delay_ms(2);				/* wait for more than 1.53mS */
	LCD_write(INSTR_WR,0x06);	/* entry mode set, increment mode */
}
/* End of LCD initialization */

void LCD_write (unsigned char RS, unsigned char data)
{
	if(RS==DATA_WR) PORTD = 0b00000001;	/* write data: E = 0 R/!W=0, (write)RS = 1 ,   */
	else			PORTD = 0b00000000;	/* Write instruction: RS = 0 E = 0, R/!W=0 (write) */


	PORTD = PORTD | 0x04;	/* Take E HIGH (logic 1) */
	PORTL = data;
	_delay_us(50);			/* needs to be at least 30uS or no display - use 50 */
	PORTD = PORTD & 0x01;	/* Take E LOW (logic 0) */
	_delay_us(50);			/* Delay REQUIRED */
}

void Print_string(char *str_ptr)
{
	PORTD = 0b00000001;	/* write data: RS = 1 E = 0, R/!W=0 (write) */

	while(*str_ptr != '\0')
	{
		PORTD = PORTD | 0x04;	/* Take E HIGH (logic 1) */
		PORTL = *str_ptr++;
		_delay_us(50);			/* needs to be at least 30uS or no display - use 50 */
		PORTD = PORTD & 0x01;	/* Take E LOW (logic 0) */
		_delay_us(50);			/* Delay REQUIRED */
	}
}

void myPutString(volatile char *str_ptr)
{
	while (*str_ptr != '\0')
	{
		LCD_write(DATA_WR, *str_ptr);
		str_ptr++;
	}
}