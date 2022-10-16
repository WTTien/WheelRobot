#include <iostream>
#include <cmath>
#include <unistd.h>
#include <wiringpi.h>

using namespace std;


///////////////////////////////////////////////////////////
//Stepper motor controlled through Raspberry Pi GPIO pins//
///////////////////////////////////////////////////////////

//28byj-48 stepper motor have 2048 steps to achieve a revolution.
//2048 =  32 steps a revolution + gear ratio 64:1. (64x32)

class stepperPi
{
	public:
		stepperPi(int rPiPins);
		int targetPins[4];
		int prevStep = 0;
		int inputStep;
		const int sequence[4][4] = {	{1,0,0,0},
						{0,1,0,0},
						{0,0,1,0},
						{0,0,0,1} };
		void rotate();
};

stepperPi::stepperPi(int rPiPins)
{
	targetPins = rPiPins;
	
	//setup
	for(int pin=0; pin<4; pin++)
	{
		int xpin = targetPins[pin];
		pinMode(xpin, OUTPUT);
		digitalWrite(xpin, LOW);
	}
}

void stepperPi::rotate()
{
	int step = 0;
	int xpin;
	
	for(int x=0; x<(abs(inputStep)/4 + 1); x++)			//1 sequence can achieve 4 step thus divide by 4, plus 1 to accomodate for steps of amount not a multiple of 4. 
	{
		if(inputStep>0)
		{	
			for(int i=0; i<4; i++)
			{
				if(step < inputStep)				//Carry out if the step is not fulfilled.
				{
					for(int pin=0; pin<4; pin++)
					{
						xpin = targetPins[pin];		//Taking information of rPiPins and digitalWrite it.
						if(sequence[i][pin]==1)		//Assigning values for all 4 pins accordingly.
						{
							digitalWrite(xpin,HIGH);
						}
						
						else
						{
							digitalWrite(xpin,LOW);
						}
						
						step++;
					}
					sleep(0.005);
				}
				
				else
				{
					break;
				}
			}
		}
		
		else if(inputStep<0)
		{
			for(int i=3; i>=0; i--)					//If step value is negative, spin in opposite direction.
			{
				if(step > inputStep)				//Step value input will be negative, thus value higher than it is when step not fulfilled.
				{
					for(int pin=0; pin<4; pin++)
					{
						xpin = targetPins[pin];
						if(sequence[i][pin]==1)
						{
							digitalWrite(xpin, HIGH);
						}
						
						else
						{
							digitalWrite(xpin, LOW);
						}
						
						step--;
					}
					sleep(0.005);
				}
				
				else
				{
					break;
				}
			}
		}
	}
	
	for(int pin=0; pin<4; pin++)
	{
		xpin = targetPins[pin];
		digitalWrite(xpin, LOW);
	}	
}


////////////////////////////////////////////
//DC motor controlled through Raspberry Pi//
////////////////////////////////////////////
class dcPi
{
	public:
		dcPi(int rPiDirPins, int rPiPwmPin);
		int directionPins[2];
		int pwmPin;
		int inputPWM;
		int pol[2] = {1,0}; 
		void rotate();
};

dcPi::dcPi
{
	directionPins = rPiDirPins;
	pwmPin = rPiPwmPin;
	
	//setup
	for(int pin=0; pin<2; pin++)
	{
		int xpin = directionPins[pin];
		pinMode(xpin, OUTPUT);
		digitalWrite(xpin, LOW);
	}
	
	pinMode(pwmPin, PWM_OUTPUT);
	pwmWrite(pwmPin, 0);
}

void dcPi::rotate()
{
	int xpin;
	
	if(inputPWM > 0)
	{
		for (int pin=0; pin<2; pin++)
		{
			xpin = directionPins[pin];
			if (pol[pin] == 1)
			{
				digitalWrite(xpin, HIGH);
			}
			
			else
			{
				digitalWrite(xpin, LOW);
			}
		}
	}
		
	else if(inputPWM < 0)
	{
		for (int pin=0; pin<2; pin++)
		{
			xpin = directionPins[pin]
			if (pol[pin] == 1)
			{
				digitalWrite(xpin, LOW);
			}
			
			else
			{
				digitalWrite(xpin, HIGH);
			}
		}
	}
	
	pwmWrite(pwmPin, inputPWM);
}
