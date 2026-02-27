/*
 * main.h
 *
 * Created: 03.11.2023 15:53:50
 *  Author: yaroalsv kozmenko
 
  this is the header file for the primary module
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "USART0.h"

// function prototypes
void Init_PORTs (void);

// input definitions

// output definitions

//global variables
volatile uint8_t receivedData;
volatile uint8_t arrayIndex = 0;
volatile uint8_t LCD_update;
volatile char rx_buffer[25];


#endif /* MAIN_H_ */