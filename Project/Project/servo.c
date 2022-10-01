#include "servo.h"
#include "Basic.h"
#define F_CPU 8000000

void Timer1_init()
{
	TCCR1A = 0x23;
	TCCR1B = 0x1B;
	OCR1A = 2499;
}

void Servo_init(int input)
{
	Timer1_init();
	SetBit(Servo_DDR ,PD4);
	OCR1B = input; // Entering the top variable from 125 to 250
}

void DoorOpen()
{
	Servo_init(187);
}

void DoorClose()
{
	Servo_init(125);
}