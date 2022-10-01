#include "Leds.h"
#include "Basic.h"

void Leds_init()
{
	SetBit(LivingRoomLed_DDR ,PC2);
	SetBit(Leds_DDR ,PA4);
	SetBit(Leds_DDR ,PA5);
	SetBit(Leds_DDR ,PA6);
	SetBit(Leds_DDR ,PA7);
}

void Leds_TurnOnAll()
{
	SetBit(LivingRoomLed_PORT ,PC2);
	SetBit(Leds_PORT ,PA4);
	SetBit(Leds_PORT ,PA5);
	SetBit(Leds_PORT ,PA6);
	SetBit(Leds_PORT ,PA7);
}

void Leds_TurnOffAll()
{
	ClearBit(LivingRoomLed_PORT ,PC2);
	ClearBit(Leds_PORT ,PA4);
	ClearBit(Leds_PORT ,PA5);
	ClearBit(Leds_PORT ,PA6);
	ClearBit(Leds_PORT ,PA7);
}

void Leds_TGL(char input)
{
	switch (input) // Choose the desired lamp by its number
	{
		case 1:
		{
			TogBit(LivingRoomLed_PORT ,PC2);
			break;
		}
		case 2:
		{
			TogBit(Leds_PORT ,PA4);
			break;
		}
		case 3:
		{
			TogBit(Leds_PORT ,PA5);
			break;
		}
		case 4:
		{
			TogBit(Leds_PORT ,PA6);
			break;
		}
		case 5:
		{
			TogBit(Leds_PORT ,PA7);
			break;
		}
	}
}

void Show_Leds()
{
	if(GetBit(LivingRoomLed_PORT ,PC2) == 0)
		Send_String("Living room lamp: OFF");
	else
		Send_String("Living room lamp: ON");
	Send('\n');
	if(GetBit(Leds_PORT ,PA4) == 0)
		Send_String("Bedroom lamp: OFF");
	else
		Send_String("Bedroom lamp: ON");
	Send('\n');
	if(GetBit(Leds_PORT ,PA5) == 0)
		Send_String("Kitchen lamp: OFF");
	else
		Send_String("Kitchen lamp: ON");
	Send('\n');
	if(GetBit(Leds_PORT ,PA6) == 0)
		Send_String("Bathroom lamp: OFF");
	else
		Send_String("Bathroom lamp: ON");
	Send('\n');
	if(GetBit(Leds_PORT ,PA7) == 0)
		Send_String("Kidsroom lamp: OFF");
	else
		Send_String("Kidsroom lamp: ON");
	Send('\n');
}
