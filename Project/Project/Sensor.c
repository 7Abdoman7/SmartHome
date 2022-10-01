#include "Basic.h"
#include "Sensor.h"

void ADC_init()
{
	SetBit(ADMUX ,REFS0);
	SetBit(ADCSRA ,ADPS2);
	SetBit(ADCSRA ,ADEN);
	SetBit(ADCSRA ,ADSC);
}

void Sensor_init()
{
	int input;
	ClearBit(Sensor_DDR ,PA0);
	ADC_init();
	while(GetBit(ADCSRA ,ADIF) == 0); // Check if the conversion is complete
	SetBit(ADCSRA ,ADIF);
}

int GetTemp()
{
	SetBit(ADCSRA ,ADSC);
	while(GetBit(ADCSRA ,ADIF) == 0);
	SetBit(ADCSRA ,ADIF);
	return (0.488 * ADC); // Return the value of the temp after cal. the formula
}
