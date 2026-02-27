/*
 * Project name: LCD_UART
 * Filename: LCD.h
 *
 * Created: 10/27/2023 8:38 AM
 * Author : Yaroslav Kozmenko
 * 
 * Operations: 
 *	This is the header file for LCD.c
 *
 */ 

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL // F_CPU must be defined BEFORE the #include <util/delay.h>
#define INSTR_WR	0
#define DATA_WR		1

#include <avr/io.h>
#include <util/delay.h>

// function prototypes
void Init_LCD (void);
void LCD_write (unsigned char RS, unsigned char data);
void Print_string(char *data_ptr);
void myPutString(volatile char *str_ptr);

// input definitions

// output definitions

//global variables



#endif /* LCD_H_ */