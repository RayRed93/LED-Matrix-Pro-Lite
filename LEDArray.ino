
#include <TimerOne.h>
#include "RGLEDMatrix80x7.h"
int g=1;
byte buffer[80];
//LEDMatrix80x7 ledMatrix;
RGLEDMatrix80x7Class ledMatrix;
void LED()
{
	ledMatrix.Refresh();
}
void setup()
{
	Serial.begin(11000);

	Timer1.initialize();
	Timer1.attachInterrupt(LED, 5000);
	Timer1.start();

	for (size_t i = 1; i <= 80; i++)
	{
		/*float d = (i / 80.)*16.;
		byte value = (3.01*sin(d))+4;
		ledMatrix.SetPixel(i, value, GREEN);*/
		//buffer[i] = 1;
	}
}
float k = 1;
void loop()
{
	
	ledMatrix.ClearBuffer();
	
	for (byte i = 1; i <= 80; i++)
	{
		
		for (byte j = 1; j < buffer[i-1]; j++)
		{
			
			ledMatrix.SetPixel(i, j, GREEN);
		}
		
		if (buffer[i-1]==7)
			ledMatrix.SetPixel(i, buffer[i-1], RED);
		else
			ledMatrix.SetPixel(i, buffer[i-1], ORANGE);
	}
	
	delay(20);
}

void SinAnimation()
{
	ledMatrix.ClearBuffer();
	for (byte i = 1; i <=80; i++)
	{
		float d = (i / 80.)*32. + k;
		byte value1 = (3*sin(d)) + 4;
		byte value2 = value1 + PI / 2;
		ledMatrix.SetPixel(i, value1, GREEN);
		ledMatrix.SetPixel(i, value2, RED);
	}
	k += 0.5;
	
	
	delay(1000);
	
}

void serialEvent()
{
	if (Serial.available())
	{
		Serial.readBytes(buffer, 80);
	}
}