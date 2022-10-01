#include "Basic.h"
#include "Bluetooth.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#define LivingRoomLed_DDR DDRC
#define LivingRoomLed_PORT PORTC
#define Leds_DDR DDRA
#define Leds_PORT PORTA

#ifndef Leds_H_
#define Leds_H_

void Leds_init(); // Initialize lamps settings
void Leds_TurnOnAll(); // Turn all the lamps on
void Leds_TGL(char input); // If the selected lamp is on, turn it off and the reverse
void Leds_TurnOffAll(); // Turn all the lamps off
void Show_Leds(); // Show the state of all the lamps on the phone of the user via bluetooth
 
#endif
