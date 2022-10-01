#include "Buzzer.h"

void Buzzer_init()
{
	SetBit(Buzzer_DDR ,PC0); // Outgoing data
	ClearBit(Buzzer_PORT, PC0);
}

void Buzzer_On()
{
	SetBit(Buzzer_PORT ,PC0);
}

void Buzzer_Off()
{
	ClearBit(Buzzer_PORT ,PC0);
}