#ifndef _DRIVE_BASE_H
#define _DRIVE_BASE_H

#include "WPILib.h"
#include "../Robotmap.h"

/**
 * @brief Drive base subsystem for a parallel wheel configuration, with a shifter.
 * 
 * Drive base subsystem with 2-4 motor controllers, in a normal left-right configuration.
 * Also includes two encoders and a gyroscope if needed.
 * @author Westin Miller
 */
class DriveBase: public Subsystem {
private:
	SpeedController *motorLeft;
#ifdef DRIVE_MOTOR_LEFT_2
	SpeedController *motorLeft2;
#endif
	SpeedController *motorRight;
#ifdef DRIVE_MOTOR_RIGHT_2
	SpeedController *motorRight2;
#endif

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Gyro *gyro;

	Relay *shifter;
	bool cachedLowState;
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
	 * This is the cached value from shift(), so it may not actually reflect the gear at robot initialization.
	 * @return true if in low gear, otherwise false
	 */
	bool isLowGear();

	/**
	 * Resets all encoders and the gyropscope.
	 */
	void reset();
	
	virtual void InitDefaultCommand();
};

#endif
