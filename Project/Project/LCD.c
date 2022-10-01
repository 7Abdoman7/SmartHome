#include "LCD.h"
#include "Basic.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void LCD_init()
{
	LCD_DDR = 0xFF;
	_delay_ms(20);
	LCD_cmd(0x02);
	LCD_cmd(0x28);
	LCD_cmd(0x0E);
	LCD_cmd(0x06);
	LCD_cmd(0x01);
	_delay_ms(2);
}

void LCD_cmd(unsigned char cmnd)
{
	LCD_PORT = (cmnd & 0xF0) | (LCD_PORT & 0x0F);
	ClearBit(LCD_PORT ,RS); 
	SetBit(LCD_PORT ,EN);
	_delay_ms(1);
	ClearBit(LCD_PORT ,EN);
	_delay_ms(10);
	LCD_PORT = (cmnd << 4) | (LCD_PORT & 0x0F);
	SetBit(LCD_PORT ,EN);
	_delay_ms(1);
	ClearBit(LCD_PORT ,EN);
}

void LCD_sendchar(unsigned char data)
{
	LCD_PORT = (data & 0xF0) | (LCD_PORT & 0x0F);
	SetBit(LCD_PORT ,RS); // To write on the LCD
	SetBit(LCD_PORT ,EN); // Pulse to read the data
	_delay_ms(1);
	ClearBit(LCD_PORT ,EN);
	_delay_ms(10);
	LCD_PORT = (data << 4) | (LCD_PORT & 0x0F); // Getting the other four bits by shifting the bits
	SetBit(LCD_PORT ,EN);
	_delay_ms(1);
	ClearBit(LCD_PORT ,EN);
}

void LCD_sendstring(char * str)
{
	for(int i = 0 ; i < strlen(str) ; i++) // Send strings as chars.
		LCD_sendchar(str[i]);
}

void LCD_sendint(int input)
{
	char str[10];
	itoa(input ,str ,10); // Converting the integer into string
	LCD_sendstring(str);	
}

void LCD_Sec()
{
	LCD_sendstring(" >Security Mode<");
	LCD_cmd(0xC0);
	LCD_sendstring("Password: ");
}
