
#include <TimerOne.h>
#include "RGLEDMatrix80x7.h"


//LEDMatrix80x7 ledMatrix;
RGLEDMatrix80x7Class ledMatrix;
void LED()
{
	ledMatrix.Refresh();
}
void setup()
{
	
	Serial.begin(9600);

	Timer1.initialize(10000);
	Timer1.attachInterrupt(LED, 10000);
	Timer1.start();
}

void loop()
{
	/*rgled.VerticalRefresh();
	if (millis()%1000 <=10)
	{
		rgled.RandomLED();
		Serial.println(millis());
	}*/
	//Serial.println(millis());
	//ledMatrix.RandomPatern();
	ledMatrix.SetPixel(1,1, RED);
	delay(1000);

}


