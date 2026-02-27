/*
 * manual_control.h
 *
 * Created: 07.11.2023 22:44:22
 *  Author: yaroslav kozmenko
 */ 


#ifndef MANUAL_CONTROL_H_
#define MANUAL_CONTROL_H_

#include <avr/io.h>
#include "stepper_motor.h"

// function prototypes


// input definitions
#define controls_input PINA
#define CW_button PA0
#define CCW_button PA1
#define home_switch PA2

//global variables
void ports_init(void);

#endif /* MANUAL_CONTROL_H_ */