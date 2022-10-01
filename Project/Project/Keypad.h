#include "Basic.h"
#include <avr/io.h>

#ifndef Keypad_H_
#define Keypad_H_ 
#define Key_DDR1 DDRA
#define Key_PORT1 PORTA
#define Key_PIN1 PINA

#define Key_DDR2 DDRC
#define Key_PORT2 PORTC
#define Key_PIN2 PINC

void Keypad_init(); // Initialize the keypad settings
unsigned char Keypad_read(); // Read inputs from the user  
unsigned char Keypad_Get(); // Get the data if there is an input from the user 

#endif 
