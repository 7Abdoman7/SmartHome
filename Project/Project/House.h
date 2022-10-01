#include "Basic.h"
#include "servo.h"
#include "Motor.h"
#include "Dimmer.h"
#include "Leds.h"
#include "Sensor.h"
#include "LCD.h"
#include "Keypad.h"
#include "Bluetooth.h"
#include "Buzzer.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#ifndef House_H_
#define House_H_
#define Reset_DDR DDRD
#define Reset_PORT PORTD
#define Reset_PIN PIND
#define Shutdown_DDR DDRD
#define Shutdown_PORT PORTD
 
void Reset_init(); // Initialize reset settings
void Shutdown_init(); // Initialize shutdown settings
void House_init(); // Initialize the initial state of the house
void HouseShutDown(); // Shutdown all the electronics
unsigned char SecMode(char* pass); // Mode to check the password before entering the house
void Check_Emer(char* pass); // Mode to check if there is an emergency
unsigned char EmerMode(unsigned char alert); // Mode on if there is an emergency
void OpeningMode(char* name); // Mode to greet the user
void ShowStatus(); // Show the status of all the components
char ActiveMode(); // Mode if you are inside the house to control all the electronics
void ClosingMode(); // Mode activated if you left the house

#endif