#ifndef __SYS_COLLECTOR_H
#define __SYS_COLLECTOR_H

#include "WPILib.h"
#include "../Utils/DualLiveSpeed.h"
#include "../RobotMap.h"

class ArmController;

/**
 * @brief Collector subsystem, provides functions to get and set speed for the 
 * Collecting commands 
 * 
 * Collector includes interfaces to opperate the external end effector, along 
 * with functions to opperate the interior, with things like getters for IR 
 * sensor states, and othe logic to opperate the collectors management
 * 
 * @author Ross Bajocich, Westin Miller
 */
class Collector: public Subsystem {

public:
	enum MotorDirection {
			/**
			 * Motors push frisbees forward
			 */
			kForward,
			/**
			 * Motors push frisbees backwards
			 */
			kBackward,
			/**
			 * Motors aren't running
			 */
			kStop
		};
	/**
	 * Initializes all objects, and deletes them in the destructor, using ports
	 * from robot map to initialize the devices 
	 */
	Collector();
	~Collector();

	void setSetpoint(float angle);
	void setPIDState(bool enabled);
	bool isPIDDone();

	double getRawAngle();

	int getFrisbeeSensorCount();
	void setCollectorMotor(Collector::MotorDirection state);
	void killPitchMotors();
	double getLeftAngle();
	double getRightAngle();
	
	void setFrisbeeStop(bool enabled);

	bool isSpinnerOn();

	/**
	 * Sets the default command for this subsystem
	 */
	virtual void InitDefaultCommand();
	
private:
	COLLECTOR_MOTOR_TYPE *collectorMotor;
	ArmController *leftArmController;
	ArmController *rightArmController;
	
	Servo *frisbeeStop;

	DigitalInput **frisbeeSensors;
	MotorDirection myMotorDirection;
};

#endif
