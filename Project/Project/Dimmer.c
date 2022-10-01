#include "Basic.h"
#include "Dimmer.h"

void Dimmer_init()
{
	SetBit(Dimmer_DDR, PD7); // Outgoing data
	TCCR2 = 0x6F;
}

void Dimmmer_input(char input)
{
	OCR2 = (input * 255) / 100.0; // Entering the input as a percentage 
}

char Dimmer_TGL()
{
	if(Dimmer_Power() == 0) 
	{
		Dimmmer_input(100);
		return 1; 
	}
	else
	{
		Dimmmer_input(0);
		return 0;
	}
	// Also return the state of the dimmer
}

int Dimmer_Power()
{
	return (OCR2 * 100) / 255.0; // Giving the value as a percentage
}