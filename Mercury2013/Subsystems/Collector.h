#ifndef __SYS_COLLECTOR_H
#define __SYS_COLLECTOR_H

#include "WPILib.h"

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
public:
	enum CollectorState {
		kOtherUp = 0, kOtherDown = 1, kUp = 2, kDown = 3
	};
private:
	AnalogChannel *pitchPot;
	SpeedController *collectorPitchMotorA;
	SpeedController *collectorPitchMotorB;
	SpeedController *collectorMotor;

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

	/**
	 * Checks to see if the collector is up, giving true if it is and false if
	 * it is down
	 */
	CollectorState getArmState();
	
	int getFrisbeeSensorCount();
	void setCollectorMotor(bool state);
	
	bool isSpinnerOn();

	/**
	 * Sets the default command for this subsystem
	 */
	virtual void InitDefaultCommand();
};

#endif
