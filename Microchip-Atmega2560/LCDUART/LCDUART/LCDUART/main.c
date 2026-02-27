/*
 * Project name: LCD_UART
 * Filename: main.c
 *
 * Created: 10/27/2023 8:17 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This program is used to receive a serial character array 
 *	from a computer serial terminal and then to display the text on the LCD.
 *	
 *
 * Hardware Connection:
 * Atmega2560			Hardware
 * 
 */ 

/****************************************************/
/*													*/
/* Project name:	LCD_Test_8bit_parallel			*/
/* Displays a two line test message:				*/
/*													*/
/*		Test message: LCD is OK						*/
/*		in 8bit parallel mode						*/
/*   												*/
/* on the 2x16 dot matrix LCD at a specific 		*/
/* position using the ATMEL ATmega2560				*/
/*													*/
/* PORTL for LCD data:							 	*/
/* 													*/
/* L.0  LCD D0								        */
/* L.1  LCD D1 								        */
/* etc.									    		*/
/* L.7  LCD D7								        */
/*													*/
/* PORTD for LCD control:							*/
/*													*/
/*	D.0	LCD RS							         	*/
/*	D.1	LCD R/!W						        	*/
/*	D.2	LCD E							            */
/*													*/
/* 	The code is written as a single .c module		*/
/*													*/
/*	Author:		Prof A Oxtoby		*/
/*	Modified:	April Cheung						*/
/*	Date:		3-13-17								*/
/*	Ver:		1.0									*/
/*	Filename:	LCD_8bit_parallel.c		*/
/*													*/
/****************************************************/


/*includes*/
#include "main.h"


ISR(USART0_RX_vect)	//RXR interrupt
{

	receivedData = UDR0;
	
	if (receivedData != 0x0D)	//if it is not a carriage return
	{
		rx_buffer[arrayIndex] = receivedData;	//put received in array
		arrayIndex++;
	}
	else //once hit enter
	{
		rx_buffer[arrayIndex] = '\0';	//write Null terminator to an array
		arrayIndex = 0;	//reset array index
		LCD_update = 1;	//flag meaning ready to send to LCD
	}
}


int main(void)
{
	/* MUST initialize PORTs BEFORE initializing LCD */
	/* since need to write to LCD to initialize it */
	
	Init_PORTs();
	Init_LCD();
	USART_init();
	sei();


	LCD_write(INSTR_WR, 0x01);	//clear and home the display
	_delay_ms(2);	//can remove if use Busy Flag check

	LCD_write(INSTR_WR, 0x02);
	_delay_ms(2);  //can remove if use Busy Flag check

	//LCD_write(INSTR_WR, 0x83);
	//Print_string (T_mess);


	//LCD_write(INSTR_WR, 0xC0);
	//_delay_us(50);	//can remove if use Busy Flag check


	while(1) /* start of super loop */
	{	
		if (LCD_update)	//this happens when hit enter
		{
			LCD_update = 0;
			
			LCD_write(INSTR_WR, 0x01);	//clear display
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x80);	//cursor top
			_delay_us(50);
			
			Print_string(rx_buffer);
			/*while(rx_buffer[arrayIndex] != '\0')	//while not null write to LCD one character at a time
			{
				//Print_string(rx_buffer[arrayIndex]);
				LCD_write(DATA_WR, rx_buffer[arrayIndex]);
				arrayIndex++;
			}*/
		} 
		else //otherwise should do nothing
		{
		}
	} 

}


void Init_PORTs (void)
{
	DDRL = 0xFF;	/* PORTL all outputs */
	PORTL = 0x00;	/* Set all outputs to 0 initially */
	DDRD = 0x07;	/* Set D.0 through A.2 to outputs for LCD control */
	DDRA = 0x00;	//port A switches input with pull ups
	PORTA = 0xFF;
}

