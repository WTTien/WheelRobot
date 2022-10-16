#include "motor.h"
#include <math.h>

///////
//Arm//
///////
/*
class arm
{
	public:
		arm(int rPiRotatePins, int rPiGrabPins);
		int rotatePins[4];
		int grabPins[4];
		int rotateAngle;
		int grabAngle;
		int rotateStep;
		int grabStep;
		stepperPi rotateStepper(rotatePins);
		stepperPi grabStepper(grabPins);
		void inputRotateAngle(int rotateAngleIn);
		void inputGrabAngle(int grabAngleIn);
};


arm::arm(int rPiRotatePins, int rPiGrabPins)
{
	rotatePins = rPiRotatePins;
	grabPins = rPiGrabPins;
}

void arm::inputRotateAngle(int rotateAngleIn)
{
	rotateAngle = rotateAngleIn;
	rotateStep = round(rotateAngle/360*2048);
	rotateStepper.inputStep = rotateStep - rotateStepper.prevStep;
	rotateStepper.rotate();
	rotateStepper.prevStep = rotateStep;
}

void arm::inputGrabAngle(int grabAngleIn)
{
	grabAngle = grabAngleIn;
	grabStep = round(grabAngle/360*2048);
	grabStepper.inputStep = grabStep - grabStepper.prevStep;
	grabStepper.rotate();
	grabStepper.prevStep = grabStep;
}
*/

///////
//Leg//
///////
class leg
{
	public:
		leg(/*int ioUpperAddress, char ioUpperPort,*/ int ioUpperPins,/* int ioLowerAddress, char ioLowerPort,*/ int ioLowerPins);
//		int upperAddress;
//		int lowerAddress;
//		char upperPort;
//		char lowerPort;
		int upperPins[4];
		int lowerPins[4];
		int upperAngle;
		int lowerAngle;
		int upperStep;
		int lowerStep;
		stepperIo upperStepper(upperAddress, upperPort, upperPins);
		stepperIo lowerStepper(lowerAddress, lowerPort, lowerPins);
		void inputUpperAngle(int upperAngleIn);
		void inputLowerAngle(int lowerAngleIn);
};


leg::leg(int ioUpperAddress, char ioUpperPort, int ioUpperPins, int ioLowerAddress, char ioLowerPort, int ioLowerPins)
{
//	upperAddress = ioUpperAddress;	//MCP23017 IO Expander address for upper leg
//	upperPort = ioUpperPort;		//MCP23017 IO Expander port for upper leg
	upperPins = ioUpperPins;		//MCP23017 IO Expander pins for upper leg
//	lowerAddress = ioLowerAddress;	//MCP23017 IO Expander address for lower leg
//	lowerPort = ioLowerPort;		//MCP23017 IO Expander port for lower leg
	lowerPins = ioLowerPins;		//MCP23017 IO Expander pins for lower leg
}
	
void leg::inputUppperAngle(int upperAngleIn)
{
	upperAngle = upperAngleIn;
	upperStep = round(upperAngle/360*2048);
	upperStepper.inputStep = upperStep - upperStepper.prevStep;
	upperStepper.rotate();
	upperStepper.prevStep = upperStep;
}

void leg::inputLowerAngle(int lowerAngleIn)
{
	lowerAngle = lowerAngleIn;
	lowerStep = round(lowerAngle/360*2048);
	lowerStepper.inputStep = lowerStep - lowerStepper.prevStep;
	lowerStepper.rotate();
	lowerStepper.prevStep = lowerStep;
}


/////////
//Wheel//
/////////
class wheel
{
	public:
		wheel(int rPiDirectionPins, int rPiEnablePin, int rPiSteerPins);
		int directionPins[2];				//Rotation speed of four wheels are controlled together
		int enablePin;
		int steerPins[4];
		dcPi driveDC(directionPins, enablePin);
		stepperPi steerStepper(steerPins);
		int joystickValue;
		int pwmValue;
		void inputDriveSpeed(int joystickValueIn, int steerAngleIn);
		int steerAngle;
		int steerStep;
		void inputSteerAngle(int steerAngleIn);
};

wheel::wheel(int rPiDirectionPins, int rPiEnablePin, int rPiSteerPins)
{
	directionPins = rPiDirectionPins;
	enablePin = rPiEnablePin;
	steerPins = rPiSteerPins;
}

void wheel::inputSteerAngle(int steerAngleIn);
{
	if(steerAngleIn < 40 || steerAngleIn > 320)
	{
		steerAngle = 40-90;
	}
	
	else if(steerAngleIn > 140 && steerAngleIn < 220)
	{
		steerAngle = 140-90;
	}
	
	else
	{
		if(steerAngleIn < 180)
		{
			steerAngle = steerAngleIn-90;
		}
		
		else
		{
			steerAngle = 270-steerAngleIn;
		}
	}

	steerStep = round(steerAngle/360*2048);
	steerStepper.inputStep = steerStep - steerStepper.prevStep;
	steerStepper.rotate();
	steerStepper.prevStep = steerStep;
}

void wheel::inputDriveSpeed(int joystickValueIn, int steerAngleIn)
{
	joyStickValue = joyStickValueIn;
	pwmValue = round(joyStickValue/100*1024);
	
	if(0 <= steerAngleIn <= 180)
	{
		driveDC.inputPWM = pwmValue;
	}
	
	else if(180 < steerAngleIn < 360)
	{
		driveDC.inputPWM = -pwmvalue;
	}
	
	driveDC.rotate();
}
