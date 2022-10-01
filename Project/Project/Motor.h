#include <avr/io.h>
#include "Basic.h"
#define F_CPU 8000000
#include <util/delay.h>

#ifndef Motor_H_
#define Motor_H_ 
#define Motor_DDR DDRD
#define Motor_PORT PORTD

void Motor_init(); // Initialize AC settings
void AC_TurnOn(); // Turn on the AC
void AC_TurnOff(); // Turn off the AC
char AC_Auto(char input); // Turn on/off the AC based on the temp. of the room 
void AC_TGL(); // If the AC is on, turn it off and the reverse

#endif 
