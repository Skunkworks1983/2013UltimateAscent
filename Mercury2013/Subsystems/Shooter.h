#ifndef __SYS_SHOOTER_H // TODO
#define __SYS_SHOOTER_H // TODO

#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"

/**
 * @brief Shooter subsystem
 * 
 * The subsystem that controls the shooter.
 * Contains the main motor for shooting as well as a pitch motor for pitching up and down.
 * @author Mark Old, Westin Miller
 */
class Shooter: public Subsystem {
private:
	SHOOTER_MOTOR_TYPE *frontMotor;
	SHOOTER_MOTOR_TYPE *middleMotor;
	SHOOTER_MOTOR_TYPE *rearMotor;
	
	SHOOTER_PITCH_MOTOR_TYPE *pitchMotor;
	Encoder *pitchEncoder;
	DigitalInput *pitchLimitSwitch;
	
	SolenoidPair *shootSolenoid;
	
	double timeTillShootReady;
public:
	Shooter();
	~Shooter();
	
	void setArmed(bool arming);
	bool isArmed();
	void shoot(bool shooting);
	void flush(bool flushing);
	
	bool readyToShoot();

	float getCurrentPitch();
	void setPitchMotorSpeed(float f);
	bool isPitchGrounded();
	
	virtual void InitDefaultCommand();
};

#endif
