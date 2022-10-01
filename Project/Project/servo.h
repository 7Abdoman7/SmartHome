#include "Basic.h"
#include <avr/io.h>

#ifndef servo_H_
#define servo_H_
#define Servo_DDR DDRD
#define Servo_PORT PORTD

void Timer1_init(); // Initialize the settings required to use the servo 
void Servo_init(int input); // Initialize the door settings
void DoorOpen(); // Open the door
void DoorClose(); // Close the door

#endif
