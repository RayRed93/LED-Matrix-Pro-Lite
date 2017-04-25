// RGLEDMatrix80x7.h
#define ZEROMASK B11000000
#define Serial_RED PORTB0
#define Serial_GREEN PORTB1
#define Serial_CLK PORTB2
#define SELECT_INPUT_A PORTB3
#define SELECT_INPUT_B PORTB4
#define SELECT_INPUT_C PORTB5

#ifndef _RGLEDMATRIX80X7_h
#define _RGLEDMATRIX80X7_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
enum color
{
	RED,
	GREEN,
	ORANGE,
	BLANK
};
class RGLEDMatrix80x7Class
{
 protected:

 private:
	 void FeedLine(byte lineBytesGREEN[10], byte lineBytesRED[10]);

	 


 public:
	 RGLEDMatrix80x7Class();
	 void RandomPattern();
	 void Refresh();
	 void printBits(byte);
	 void ClearBuffer();
	 void SetPixel(byte x, byte y, color ledCol);
	 byte flipByte(byte c);

	 byte LEDBufferRED[10][7];
	 byte LEDBufferGREEN[10][7]; 
	 color ledColor;
	 
	
};

extern RGLEDMatrix80x7Class RGLEDMatrix80x7;

#endif

