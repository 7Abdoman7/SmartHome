#include "Basic.h"
#include <avr//io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <string.h>
#include <ctype.h>

#ifndef TicTacToe_H_
#define TicTacToe_H_

typedef struct
{
	char b[9];
}Board;

Board* New_Board();

void Display(Board* x);

char Check_place(Board *y ,char x);

char Get_place(Board *y ,char x);

char Enter_number(char x ,char* turn ,Board* y);

char Check_End (char *turn ,Board *y);

void Two_Players(char *turn ,Board *board);

#endif