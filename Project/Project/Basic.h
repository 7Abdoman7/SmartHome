#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#ifndef Basic_H_
#define Basic_H_
#define SetAll(DDR) DDR = 0xFF // Set all bits of the registers to 1
#define ClearAll(DDR) DDR = 0  // Set all bits of the registers to 0
#define SetBit(DDR ,Bit) DDR |= (1 << Bit) // Set the selected bit of the register to 1
#define ClearBit(DDR ,Bit) DDR &= ~(1 << Bit) // Set the selected bit of the register to 0
#define TogBit(DDR ,Bit) DDR ^= (1 << Bit) // If the selected bit is 1 set it to 0 and from 0 to 1
#define GetBit(DDR ,Bit) ((DDR >> Bit) & 1) //Get the state of the selected bit of the register
#endif
