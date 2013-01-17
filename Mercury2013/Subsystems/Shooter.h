#ifndef _SHOOTER_H
#define _SHOOTER_H

class Shooter : public Subsystem {
	SpeedController *shooterMotor;
	SpeedController *pitchMotor;
	Encoder *shooterEncoder;
	Encoder *pitchEncoder;
public:
	Shooter;
	~Shooter;
	void setSpeed(float rpm);
	void loadDisk();
	void fire();
	void InitDefaultCommand();
};

#endif
