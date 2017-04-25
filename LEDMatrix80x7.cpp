#include "LEDMatrix80x7.h"

#include <Arduino.h>

LEDMatrix80x7::LEDMatrix80x7()
{
	DDRB |= B00111011;
	PORTB &= ZEROMASK;
}


LEDMatrix80x7::~LEDMatrix80x7()
{



}

void LEDMatrix80x7::VerticalRefresh()
{
	//PORTB &= ZEROMASK;
	//analogWrite(10, 250);
	for (byte i = 0; i < 8; i++)
	{
		byte setMask = i << 3;
		setMask |= B00000011;
		
		
		PORTB &= B11000111;
		delayMicroseconds(1000);  //line off
		//here data write 10x8bits for 2 colors (x2)
		PORTB = (PORTB & B11000100) | setMask;
		delayMicroseconds(100);	  //line on
		
		
		//printBits(PORTB);
		//Serial.println();
		
		
	}
}



void LEDMatrix80x7::printBits(int myByte) 
{
	for (byte mask = 0x80; mask; mask >>= 1) {
		if (mask  & myByte)
			Serial.print('1');
		else
			Serial.print('0');
	}
}

void LEDMatrix80x7::FeedLine(int *lineBytes)
{
	for (int8_t i = 0; i < 80; i++)
	{

	}
}


