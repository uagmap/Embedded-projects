/*
 * USART0.c
 *
 * Created: 02.11.2023 15:04:21
 *  Author: Yaroslav Kozmenko
 *
 *	Operations:	This module initializes the asynchronous serial communication
 *	and is used for either sending or receiving a byte of data from serial pins
 */ 


#include "USART0.h"

void USART_init(void)
{
	UCSR0A |= 0x00;	//no settings in register A, only flags
	UCSR0B |= ((1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0));	//enable TX/RX bits as well as RXR interrupt
	UCSR0C |= ((1<<UCSZ00) | (1<<UCSZ01));	//async mode, no parity, 1 stop bit, 8 data bits
	
	UBRR0L = (F_CPU/(16UL * (uint16_t)baud)) - 1;
	UBRR0H = 0x00;
	
}


void USART_TX(uint8_t byte)	//transmit single byte of data
{
	while ((UCSR0A & (1 << UDRE0)) == 0)	//wait while the buffer is busy, while register is not empty
	UDR0 = byte;	//load the information to the buffer
}


uint8_t USART_RX(void)
{
	while ((UCSR0A & (1 << RXC0)) == 0){
		
	}
	return UDR0;
}