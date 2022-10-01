#include "Motor.h"
#include "Basic.h"
 
void Motor_init()
{
	SetBit(Motor_DDR ,PD3);
}

void AC_TurnOn()
{
	SetBit(Motor_PORT ,PD3);
}

void AC_TurnOff()
{
	ClearBit(Motor_PORT ,PD3);
}

void AC_TGL()
{
	TogBit(Motor_PORT ,PD3);
}

char AC_Auto(char input)
{
	// Checks the data sent (temp)
	if(input > 28)
	{
		AC_TurnOn();
		return 1;
	}
	else if(input < 21)
		AC_TurnOff();
	return 0;
}