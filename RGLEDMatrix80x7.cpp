#include "RGLEDMatrix80x7.h"

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
			LEDBufferRED[i][j] = random() % 255;
			LEDBufferGREEN[i][j] = random() % 255;
		}
	}
}

void RGLEDMatrix80x7Class::Refresh()
{
	byte setMask;
	for (byte selectInput = 1; selectInput <= 7; selectInput++)
	{
		setMask = selectInput << 3;

		memcpy(&lineArrayGREEN[0], LEDBufferGREEN[selectInput - 1], sizeof(byte) * 10);
		
		memcpy(&lineArrayRED[0], LEDBufferRED[selectInput - 1], sizeof(byte) * 10);
		
		FeedLine(lineArrayGREEN, lineArrayRED);
		
		PORTB = (PORTB & B11000111) | setMask;
		delayMicroseconds(100);	  //line on (PWM)

		PORTB = (PORTB & B11000111);
		//delayMicroseconds(200);  //line off
		

	}
}

void RGLEDMatrix80x7Class::FeedLine(byte lineBytesGREEN[10], byte lineBytesRED[10])
{
	byte redByte, greenByte;
	bool bit;

	for (uint8_t i = 0; i < 10; i++)
	{
		greenByte =  flipByte(lineBytesGREEN[i]);
		redByte = flipByte(lineArrayRED[i]);
			
		for (byte mask = B00000001; mask; mask <<= 1)
		{					
			//bit = GreenByte % 2;
			//GreenByte = GreenByte >> 1;
					
			if (greenByte & mask)
				PORTB = PORTB | (1 << Serial_GREEN);
			else
				PORTB = PORTB & ~(1 << Serial_GREEN);
			
			/*bit = RedByte % 2;
			RedByte = RedByte >> 1;*/

			if (redByte & mask)
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
	memset(&LEDBufferGREEN, 0, sizeof(LEDBufferGREEN));
	memset(&LEDBufferRED, 0, sizeof(LEDBufferRED));
}

void RGLEDMatrix80x7Class::printBits(byte myByte)
{
	for (byte mask = 0x80; mask; mask >>= 1) 
	{
		if (mask  & myByte)
			Serial.print('1');
		else
			Serial.print('0');
	}
}
byte RGLEDMatrix80x7Class::flipByte(byte c) //TODO
{
	c = ((c >> 1) & 0x55) | ((c << 1) & 0xAA);
	c = ((c >> 2) & 0x33) | ((c << 2) & 0xCC);
	c = (c >> 4) | (c << 4);

	return c;
}
void RGLEDMatrix80x7Class::DisplaySpectrum(byte data[80])
{
	ClearBuffer();
	for (byte i = 0; i < 80; i++)
	{
		SetPixel(i + 1, data[i], RED);
	}
}
void RGLEDMatrix80x7Class::SetPixel(byte x, byte y, color ledColor)
{
	
	if (x < 1 || x > 80 || y < 1 || y > 7) return;

	x--;
	y--;

	switch (ledColor)
	{
	case GREEN:
		LEDBufferGREEN[6 - y][x / 8] |= flipByte((1 << (x % 8)));
		break;
	case RED:
		LEDBufferRED[6 - y][x / 8] |= flipByte((1 << (x % 8)));
		break;
	case ORANGE:
		LEDBufferRED[6 - y][x / 8] |= flipByte((1 << (x % 8)));
		LEDBufferGREEN[6 - y][x / 8] |= flipByte((1 << (x % 8)));
		break;
	case BLANK:
		LEDBufferRED[6 - y][x / 8] &= flipByte(~(1 << (x % 8)));
		LEDBufferGREEN[6 - y][x / 8] &= flipByte(~(1 << (x % 8)));
		break;
	default:
		break;
	}
}
RGLEDMatrix80x7Class RGLEDMatrix80x7;

