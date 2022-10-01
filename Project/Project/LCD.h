#include <string.h>
#define F_CPU 8000000
#include <util/delay.h>
#define RS PB0
#define EN PB1
#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_PIN  PINB

#ifndef LCD_H_
#define LCD_H_

void LCD_init(); // Initialize the LCD settings
void LCD_cmd(unsigned char cmnd); // Enter the commands of the LCD
void LCD_sendchar(unsigned char data); // Show a given character on the LCD
void LCD_sendstring(char* str); // Show a given string on the LCD
void LCD_sendint(int input); // Show a given integer on the LCD
void LCD_Sec(); // Activate security mode on the LCD

#endif
