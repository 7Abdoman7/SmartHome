#include "Keypad.h"
#include "Basic.h"

unsigned char Keypad[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','x'}}; 
// Entering the values of the buttons of the keypad

void Keypad_init()
{
	SetBit(Key_DDR2 ,PC4);
	SetBit(Key_DDR2 ,PC5);
	SetBit(Key_DDR2 ,PC6);
	SetBit(Key_DDR2 ,PC7);
	ClearBit(Key_DDR2, PA1);
	ClearBit(Key_DDR2, PA2);
	ClearBit(Key_DDR2, PA3);
	SetBit(Key_PORT1, PA1);
	SetBit(Key_PORT1, PA2);
	SetBit(Key_PORT1, PA3);
}

unsigned char Keypad_read()
{
	unsigned char value = 'x' ,temp;
	while(value == 'x') // Check if the user click any of the buttons of the keypad 
	{
		for(int row = 4 ; row < 8 ; row++)
		{
			ClearBit(Key_PORT2 ,row); // Set the ports A, B ,C ,D to 0 one after another
			for(int col = 1 ; col < 4 ; col++)
			{
				temp = GetBit(Key_PIN1 ,col); // 0 if any button was pushed otherwise 1
				if(temp == 0) // Check if a button is pushed
				{
					while(GetBit(Key_PIN1, col) == 0); // To avoid the bouncing of the buttons
					value = Keypad[row - 4][col - 1]; // Getting value depending on the row and the col.
				}
			}
			SetBit(Key_PORT2 ,row); // Returning the port to 1 
		}
	}
	return value;
}

unsigned char Keypad_Get()
{
	// Only check once on all the buttons to not wait for an input from the user
	unsigned char value = 'x' ,temp;
	for(int row = 4 ; row < 8 ; row++)
	{
		ClearBit(Key_PORT2 ,row);
		for(int col = 1 ; col < 4 ; col++)
		{
			temp = GetBit(Key_PIN1 ,col);
			if(temp == 0)
			{
				while(GetBit(Key_PIN1, col) == 0);
				value = Keypad[row - 4][col - 1];
			}
		}
		SetBit(Key_PORT2 ,row);
	}
	return value;
}