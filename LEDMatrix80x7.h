#pragma once
#define ZEROMASK B11000000
class LEDMatrix80x7
{
public:
	LEDMatrix80x7();
	~LEDMatrix80x7();
	void VerticalRefresh();
	void printBits(int);
	void FeedLine(int*);

};

