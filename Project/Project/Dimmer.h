#include "Basic.h"
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#define Dimmer_DDR DDRD
#define Dimmer_PORT PORTD

#ifndef Dimmer_H_
#define Dimmer_H_

void Dimmer_init(); // Initialize the dimmer settings
void Dimmmer_input(char input); // Enter the power of the dimmer from 0 to 100
char Dimmer_TGL(); // If the dimmer is off, turn it on (100%) and if it is on (any power), turn it off 
int Dimmer_Power(); // Get the power of the dimmer

#endif
