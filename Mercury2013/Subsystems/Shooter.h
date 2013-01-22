#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "WPILib.h"
#include "../Robotmap.h"

class Shooter : public Subsystem {
private:
	SpeedController *shooterMotor;
	SpeedController *pitchMotor;
	Encoder *speedEncoder;
	AnalogChannel *pitchPot;
	
	Notifier *motorUpdateLoop;
	
	static void callUpdateMotors(void* shooter);
	void updateMotors();
	
	float targetSpeed;
	float targetPitch;
	
	int speedStability;
	int pitchStability;
public:
	Shooter();
	~Shooter();
	
	void startUpdateLoop();
	void endUpdateLoop();
	
	void setTargetSpeed(float rpm);
	float getCurrentSpeed();
	bool isSpeedStable();
	
	void setTargetPitch(float degree);
	float getCurrentPitch();
	bool isPitchStable();
	
	Encoder *getShooterEncoder();
	Encoder *getPitchEncoder();

	virtual void InitDefaultCommand();
	
	bool isStableReady();
};

#endif
