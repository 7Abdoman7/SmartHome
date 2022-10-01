#include "Basic.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#define Sensor_DDR DDRA
#define Sensor_PORT PORTA

#ifndef Sensor_H_
#define Sensor_H_

void ADC_init(); // Initialize the settings required to use the sensor
void Sensor_init(); // Initialize the temp. sensor settings
int GetTemp(); // Get the temp. of the room

#endif
