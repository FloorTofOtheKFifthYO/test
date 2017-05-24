#include "digit.h"

void Digit_left_show(int number)
{
	PAout(15)=number%2;
	PCout(10)=(number/2)%2;
	PCout(11)=(number/4)%2;
	PAout(14)=(number/8)%2;
}

void Digit_right_show(int number){
	PBout(8)=number%2;
	PEout(1)=(number/2)%2;
	PEout(0)=(number/4)%2;
	PBout(9)=(number/8)%2;
}


