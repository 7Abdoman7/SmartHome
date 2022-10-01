#include "Basic.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#ifndef Buzzer_H_
#define Buzzer_H_

#define Buzzer_DDR DDRC
#define Buzzer_PORT PORTC
#define Buzzer_PIN PINC

void Buzzer_init(); // Initialize the buzzer settings 
void Buzzer_On(); // Turn the buzzer on
void Buzzer_Off(); // Turn the buzzer off

#endif
