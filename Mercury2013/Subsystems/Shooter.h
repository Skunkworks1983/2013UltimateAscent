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
public:
	enum ControlType {
		kPower, kPowerBang, kSpeed, kPowerNoWait, kPowerBangNoWait
	};
private:
	SHOOTER_MOTOR_TYPE *frontMotor;SHOOTER_MOTOR_TYPE *middleMotor;SHOOTER_MOTOR_TYPE
			*rearMotor;

	SolenoidPair *shootSolenoid;

	ControlType controlScheme;

	// Power and PowerBang information
	double timeTillShootReady;

	// Speed Information
	Notifier *controlLoop;
	int updateStability;
	static void callUpdateMotors(void *shooter);
	void updateMotors();
	void updateMotor(AnalogChannel *src, SpeedController *dst, float target);
	AnalogChannel *frontSpeed;
	AnalogChannel *middleSpeed;
	AnalogChannel *rearSpeed;
public:
	Shooter();
	~Shooter();

	void setArmed(bool arming);
	bool isArmed();

	void shoot(bool shooting);
	void flush(bool flushing);

	void setControlScheme(ControlType type);
	ControlType getControlScheme();

	bool readyToShoot();

	virtual void InitDefaultCommand();
};

#endif
