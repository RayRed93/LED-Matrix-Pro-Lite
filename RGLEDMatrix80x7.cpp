#include "RGLEDMatrix80x7.h"


byte LEDBuffArrayGREEN[7][10] = { 
					  {0,1,1,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,1,0,1,1,1,1,1,1,1},
					  {0,0,0,0,0,0,0,0,0,0},
					  {1,1,1,1,1,1,1,1,1,1},
					  {255,0,0,0,0,0,0,0,0,0},
					  {255,1,1,1,1,1,1,1,1,0}
						   };
byte LEDBuffArrayRED[7][10] = {
					  { 255,1,1,1,1,1,1,1,1,1 },
					  { 255,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0 },
					  { 0,1,1,1,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,6 },
					  { 0,1,1,1,1,1,1,1,1,6 }
};

byte lineArrayGREEN[10];
byte lineArrayRED[10];


RGLEDMatrix80x7Class::RGLEDMatrix80x7Class()
{
	DDRB |= B00111111;
	PORTB &= B11000000;
	ClearBuffer();
	
	
}
void RGLEDMatrix80x7Class::RandomPattern()
{
	for (byte i = 0; i < 7; i++)
	{
		for (byte j = 0; j < 10; j++)
		{
			LEDBuffArrayRED[i][j] = random() % 255;
			LEDBuffArrayGREEN[i][j] = random() % 255;
		}
	}
}

void RGLEDMatrix80x7Class::Refresh()
{
	byte setMask;
	for (byte line = 1; line <= 7; line++)
	{
		setMask = line << 3;

		memcpy(&lineArrayGREEN[0], LEDBufferGREEN[line - 1], sizeof(byte) * 10);
		memcpy(&lineArrayRED[0], LEDBufferRED[line - 1], sizeof(byte) * 10);
		
		FeedLine(lineArrayGREEN, lineArrayRED);
		
		PORTB = (PORTB & B11000111) | setMask;
		delayMicroseconds(100);	  //line on (PWM)

		PORTB = (PORTB & B11000111);
		delayMicroseconds(100);  //line off
		

	}
}

void RGLEDMatrix80x7Class::FeedLine(byte lineBytesGREEN[10], byte lineBytesRED[10])
{
	byte RedByte, GreenByte;
	bool bit;

	for (uint8_t i = 0; i < 10; i++)
	{
		GreenByte =  flipByte(lineBytesGREEN[i]);
		RedByte = flipByte(lineArrayRED[i]);
			
		for (byte mask = 0; mask < 8; mask++) //should be bit shifed but it doesnt work...
		{			
			bit = GreenByte % 2;
			GreenByte = GreenByte >> 1;
					
			if (bit == 1)
				PORTB = PORTB | (1 << Serial_GREEN);
			else
				PORTB = PORTB & ~(1 << Serial_GREEN);

			bit = RedByte % 2;
			RedByte = RedByte >> 1;

			if (bit == 1)
				PORTB = PORTB | (1 << Serial_RED);
			else
				PORTB = PORTB & ~(1 << Serial_RED);
			

			PORTB = PORTB | (1 << Serial_CLK); //set		//serial clock tick
			PORTB = PORTB & ~(1 << Serial_CLK); //clear

			
		}
		
		
	}

}

void RGLEDMatrix80x7Class::ClearBuffer()
{
	for (byte i = 0; i < 7; i++)
	{
		for (byte j = 0; j < 10; j++)
		{
			LEDBufferGREEN[i][j] = 0;
			LEDBufferRED[i][j] = 0;
		}
	}
}

void RGLEDMatrix80x7Class::printBits(byte myByte)
{
	for (byte mask = 0x80; mask; mask >>= 1) {
		if (mask  & myByte)
			Serial.print('1');
		else
			Serial.print('0');
	}
}
byte RGLEDMatrix80x7Class::flipByte(byte c)
{
	c = ((c >> 1) & 0x55) | ((c << 1) & 0xAA);
	c = ((c >> 2) & 0x33) | ((c << 2) & 0xCC);
	c = (c >> 4) | (c << 4);

	return c;
}
void RGLEDMatrix80x7Class::SetPixel(byte x, byte y, color ledColor)
{
	
	if (x < 1 || x > 80 || y < 1 || y > 7) return;

	switch (ledColor)
	{
	case GREEN:
		LEDBufferGREEN[7-(y-1)][(x-1) / 10] |= flipByte((1 << (x % 8)));
		break;
	case RED:
		LEDBufferRED[7-(y-1)][(x-1) / 10] |= flipByte((1 << (x % 8)));
		break;
	case ORANGE:
		LEDBufferRED[7-(y-1)][(x-1) / 10] |= flipByte((1 << (x % 8)));
		LEDBufferGREEN[7-(y-1)][(x-1) / 10] |= flipByte((1 << (x % 8)));
		break;
	case BLANK:
		LEDBufferRED[7-(y-1)][(x-1) / 10] &= flipByte(~(1 << (x % 8)));
		break;
	default:
		break;
	}
}
RGLEDMatrix80x7Class RGLEDMatrix80x7;

