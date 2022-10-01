#include "Basic.h"
#include "Bluetooth.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <avr/io.h>

char Data_avail() 
{
	return GetBit(UCSRA ,RXC);
}

char Receive()
{
	while(!GetBit(UCSRA ,RXC));
	return UDR;
}

int Receive_int() 
{
	int res = 0;
	char num;
	while(1)	
	{
		num = Receive(); 
		if((num == '\n' || num == '\0' || num == '\r') && res) // Check if the data reaches the end
			break;
		res = res * 10 + num - '0'; // Converting chars. into integers
	}
	return res; // Return the integer that user sent
}

void Send(unsigned char data)
{
	while(!GetBit(UCSRA ,UDRE)); // Check if there is a data 
	UDR = data;	
}

void Bluetooth_init()
{
	SetBit(UCSRA ,U2X);
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = 103;
	UBRRH = 0;
}

void Send_String(char* str)
{
	for(int i = 0 ; i < strlen(str) ; i++) // Send string as chars.
	{
		Send(str[i]);
		_delay_ms(20);
	}
}

void Send_int(int input)
{
	char str[10];
	itoa(input ,str ,10); // Converting the integer into string
	Send_String(str); 
}


