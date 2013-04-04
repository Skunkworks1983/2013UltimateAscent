#ifndef __SYS_DRIVEBASE_H
#define __SYS_DRIVEBASE_H

#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/DualLiveSpeed.h"
#include "../Utils/OnboardDigitalTrigger.h"

/**
 * @brief Drive base subsystem for a parallel wheel configuration, with a shifter.
 * 
 * Drive base subsystem with 2-4 motor controllers, in a normal left-right configuration.
 * Also includes two encoders and a gyroscope if needed.
 * @author Westin Miller
 */
class DriveBase: public Subsystem {
private:
	DualLiveSpeed *motorLeft;
	DualLiveSpeed *motorRight;

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Gyro *gyro;

	SolenoidPair *shiftSolenoid;
	
	Trigger *leftWhisker;
	Trigger *rightWhisker;
public:
	/**
	 * Creates the drive base motors, encoders, and any other components.
	 * The left and right primary motors are created with DRIVE_MOTOR_LEFT and DRIVE_MOTOR_RIGHT as ports.
	 * If the DRIVE_MOTOR_*_2 ports are defined, it also creates a secondary motor controller, or two if both are defineds.
	 */
	DriveBase();
	~DriveBase();

	/**
	 * Sets the speed of both the left and right motor controller(s) to the given values.
	 * @param leftSpeed the scalar left speed.  [-1,1]
	 * @param rightSpeed the scalar right speed.  [-1,1]
	 */
	void setSpeed(float leftSpeed, float rightSpeed);

	/**
	 * Gets a pointer to this drive base's gyroscope, or NULL if one doesn't exist.
	 */
	Gyro *getGyro();
	
	/**
	 * Gets a pointer to this drive base's left encoder, or NULL if one doesn't exist.
	 */
	Encoder *getLeftEncoder();
	
	/**
	 * Gets a pointer to this drive base's right encoder, or NULL if one doesn't exist.
	 */
	Encoder *getRightEncoder();

	/**
	 * Shifts the drive base to the given gear.
	 * @param lowGear true if shifting to low gear, false if shifting high.
	 */
	void shift(bool lowGear);
	
	/**
	 * Gets the current shifted state.
	 * @return true if in low gear, otherwise false
	 */
	bool isLowGear();

	/**
	 * Resets all encoders and the gyropscope.
	 */
	void reset();
	
	void setMotorScalingFactor(float f);
	
	Trigger *getLeftWhisker();
	Trigger *getRightWhisker();
	
	virtual void InitDefaultCommand();
};

#endif
