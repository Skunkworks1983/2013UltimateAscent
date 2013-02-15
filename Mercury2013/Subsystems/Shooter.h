#ifndef __SYS_SHOOTER_H // TODO
#define __SYS_SHOOTER_H // TODO

#include "WPILib.h"
#include "../Robotmap.h"

/**
 * @brief Shooter subsystem
 * 
 * The subsystem that controls the shooter.
 * Contains the main motor for shooting as well as a pitch motor for pitching up and down.
 * @author Mark Old
 */
class Shooter: public Subsystem {
private:
	SpeedController *frontMotor;
	SpeedController *middleMotor;
	SpeedController *rearMotor;
	
	SpeedController *pitchMotor;
	Encoder *pitchEncoder;
	
	DoubleSolenoid *shootSolenoid;
	
	double timeTillShootReady;
public:
	Shooter();
	~Shooter();
	
	void setArmed(bool arming);
	bool isArmed();
	void shoot(bool shooting);
	void flush(bool flushing);
	
	bool readyToShoot();
	
	void setPitchMotorSpeed(float speed);
	float getCurrentPitch();

	virtual void InitDefaultCommand();
};

#endif
