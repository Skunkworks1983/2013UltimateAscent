#ifndef __SYS_COLLECTOR_H
#define __SYS_COLLECTOR_H

#include "WPILib.h"
#include "../Utils/DualLiveSpeed.h"
#include "../RobotMap.h"

/**
 * @brief Collector subsystem, provides functions to get and set speed for the 
 * Collecting commands 
 * 
 * Collector includes interfaces to opperate the external end effector, along 
 * with functions to opperate the interior, with things like getters for IR 
 * sensor states, and othe logic to opperate the collectors management
 * 
 * @author Ross Bajocich
 */
class Collector: public Subsystem, public PIDOutput, public PIDSource {
private:
	AnalogChannel *pitchPot;
	DualLiveSpeed *collectorPitchMotor;
	COLLECTOR_MOTOR_TYPE *collectorMotor;

	PIDController *pitchPID;

	DigitalInput **frisbeeSensors;
public:
	/**
	 * Initializes all objects, and deletes them in the destructor, using ports
	 * from robot map to initialize the devices 
	 */
	Collector();
	~Collector();

	virtual void PIDWrite(float val);
	virtual double PIDGet();

	void setSetpoint(float angle);
	void setPIDState(bool enabled);
	bool isPIDDone();

	double getRawAngle();
	
	int getFrisbeeSensorCount();
	void setCollectorMotor(bool state);
	
	bool isSpinnerOn();

	/**
	 * Sets the default command for this subsystem
	 */
	virtual void InitDefaultCommand();
};

#endif
