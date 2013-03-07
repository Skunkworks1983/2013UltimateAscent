#ifndef __SYS_COLLECTORARMS_H
#define __SYS_COLLECTORARMS_H

#include "WPILib.h"
#include "../Utils/DualLiveSpeed.h"
#include "../RobotMap.h"

class ArmController;

/**
 * @brief CollectorArms subsystem, provides functions to get and set speed for the 
 * Collecting commands 
 * 
 * CollectorArms includes interfaces to opperate the external end effector, along 
 * with functions to opperate the interior, with things like getters for IR 
 * sensor states, and othe logic to opperate the collectors management
 * 
 * @author Ross Bajocich, Westin Miller
 */
class CollectorArms: public Subsystem {
public:
	/**
	 * Initializes all objects, and deletes them in the destructor, using ports
	 * from robot map to initialize the devices 
	 */
	CollectorArms();
	~CollectorArms();

	void setSetpoint(float angle);
	void setPIDState(bool enabled);
	bool isPIDDone();

	double getAngle();
	
	void killPitchMotors();
	double getLeftAngle();
	double getRightAngle();

	/**
	 * Sets the default command for this subsystem
	 */
	virtual void InitDefaultCommand();
	
private:
	ArmController *leftArmController;
	ArmController *rightArmController;
};

#endif
