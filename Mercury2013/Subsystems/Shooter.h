#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "WPILib.h"
#include "../Robotmap.h"

class Shooter : public Subsystem {
private:
	SpeedController *shooterMotor;
	SpeedController *pitchMotor;
	Encoder *shooterEncoder;
	Encoder *pitchEncoder;
	
	Notifier *bangLoop;
	static void callUpdateMotors(void* shooter);
	void updateMotors();
	
	float targetSpeed;
	int stableCount;
public:
	Shooter();
	~Shooter();
	
	void setTargetSpeed(float rpm);
	void setPitch(float degree);
	void loadDisk();
	void fire();
	
	Encoder *getShooterEncoder();
	Encoder *getPitchEncoder();

	virtual void InitDefaultCommand();
	
	bool isStableReady();
};

#endif
