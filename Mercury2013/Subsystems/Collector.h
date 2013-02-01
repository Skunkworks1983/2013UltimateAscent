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
class Collector : public Subsystem {
private:
	Encoder *collectorEncoder;
	AnalogChannel *pitchPot;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
	DigitalInput * IRLow;
	DigitalInput * IRMid;
	DigitalInput * IRHigh;
public:
	/**
	 * Initializes all objects, and deletes them in the destructor, using ports
	 * from robot map to initialize the devices 
	 */
	Collector();
	~Collector();
	
	/**
	 * Getter for the encoder object for the collector motor
	 */
	Encoder *getCollectorEncoder();
	
	/**
	 * Sets the collector either up or down, which then translates over to the
	 * motor
	 * 
	 * @param state raises the collector with true or lowers it with false 
	 */
	void setCollectorState(bool state);
	
	/**
	 * Checks to see if the collector is up, giving true if it is and false if
	 * it is down
	 */
	bool isUp();
	
	/**
	 * Gets the real position of the motor, and not just a bool to either 
	 * check if it is in the up or down states 
	 */
	float getRealPosition();
	
	/**
	 * Sets the speed of the motor to the end effector to move up or down
	 * 
	 * @param speed sets the speed of the motor moving the collector
     */
	void setCollectorPitchMotor(float speed);
	
	/**
	 * Sets the speed of collector that actually moves the frisbees up to the
	 * the actuall shooter 
	 * 
	 * @param speed sets the speed of the motor opperating the collector rod
	 */
	void setCollectorSpeed(float speed);
	
	/**
	 * Senses whether an IR sensor is sensing something or not, with a given
	 * sensor set with different set values
	 * 
	 * @param height is height of the certain IR sensor you want to access
	 */
	int getSense(int height);
	
	/**
	 * Sets the default command for this subsystem
	 */
	virtual void InitDefaultCommand();
};

#endif
