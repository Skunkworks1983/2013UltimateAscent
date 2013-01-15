#include "robotGlobal.h"

Joystick joystick1 = new Joystick;
Joystick joystick2 = new Joystick;

Victor leftMotor = new Victor;
Victor rightMotor = new Victor;

Gyro gyroscope = new Gyro;

Encoder leftEncoder = new Encoder;
Encoder rightEncoder = new Encoder;

void DriveBase::autoDrive(float distance){
	
}

void DriveBase::autoTurn(float angle){
	
}

void DriveBase::autoMove(float distance, float angle){
	
}

void DriveBase::tankDrive(float leftSpeed, float rightSpeed){
	leftMotor.SetSpeed(joystick1.GetYAxis());
	righmotor.SetSpeed(joystick1.GetYAxis());
}