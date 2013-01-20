#ifndef _DRIVE_BASE_H
#define _DRIVE_BASE_H

#include "WPILib.h"
#include "../Robotmap.h"

class DriveBase : public Subsystem {
private:
	SpeedController *motorLeft;
#ifdef DRIVE_MOTOR_LEFT_2
	SpeedController *motorLeft2;
#endif
	SpeedController *motorRight;
#ifdef DRIVE_MOTOR_RIGHT_2
	SpeedController *motorRight2;
#endif

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Gyro *gyro;
	
	Relay *shifter;
	bool cachedLowState;
public:
	DriveBase();
	~DriveBase();

	void setSpeed(float leftSpeed, float rightSpeed);

	Gyro *getGyro();
	Encoder *getLeftEncoder();
	Encoder *getRightEncoder();
	
	void shift(bool lowGear);
	bool isLowGear();
	
	virtual void InitDefaultCommand();
};

#endif
