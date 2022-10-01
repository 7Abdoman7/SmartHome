#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Basic.h"

#ifndef Bluetooth_H_
#define Bluetooth_H_

void Bluetooth_init(); //Initialize bluetooth settings  
char Data_avail(); //Check if there is a data sent by the user or not
char Receive(); //Get data from the user (characters)
int Receive_int(); // Get data from the user (integer)
void Send(unsigned char data); // Send data (characters) to the user via bluetooth
void Send_String(char* str); // Send data (strings) to the user via bluetooth
void Send_int(int input); // Send data (integers) to the user via bluetooth

#endif