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
public:
	Shooter();
	~Shooter();
	
	void setSpeed(float rpm);
	void setPitch(float degree);
	void loadDisk();
	void fire();
	
	Encoder *getShooterEncoder();
	Encoder *getPitchEncoder();
	
	virtual void InitDefaultCommand();
};

#endif
