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
	
	SolenoidPair *shootSolenoid;
	
	double timeTillShootReady;
	bool enableShooterBang;
public:
	Shooter();
	~Shooter();
	
	void setArmed(bool arming);
	bool isArmed();
	void shoot(bool shooting);
	void flush(bool flushing);
	void setShooterBang(bool shouldBang);
	void update();
	
	bool readyToShoot();
	bool isShooterBangEnabled();
	
	virtual void InitDefaultCommand();
};

#endif
