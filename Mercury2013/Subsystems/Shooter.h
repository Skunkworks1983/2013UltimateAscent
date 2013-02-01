#ifndef __SYS_SHOOTER_H
#define __SYS_SHOOTER_H

#include "WPILib.h"
#include "../Robotmap.h"

/**
 * @brief Shooter subsystem
 * 
 * The subsystem that controls the shooter.
 * Contains the main motor for shooting as well as a pitch motor for pitching up and down.
 * @author Mark Old
 */
class Shooter: public Subsystem {
private:
	/**
	 * The speed controller driving the actual flywheel.
	 */
	SpeedController *shooterMotor;
	/**
	 * The speed controller driving the pitch change of the shooting apparatus.
	 */
	SpeedController *pitchMotor;
	/**
	 * The encoder measuring the speed of the flywheel.
	 */
	Encoder *speedEncoder;
	/**
	 * The potentiometer that measures the angle of the shooting apparatus.
	 */
	AnalogChannel *pitchPot;

	/**
	 * The timer that runs the motor update loop for speed control.
	 */
	Notifier *motorUpdateLoop;

	/**
	 * The static method that acts as a callback for the @link Shooter::updateMotors method.
	 * @param shooter the shooter update to call the method ons
	 */
	static void callUpdateMotors(void* shooter);
	/**
	 * Updates the speed of both the shooter motor and pitch motor to reach the current targets.
	 */
	void updateMotors();

	/**
	 * The target speed, in RPM, of the shooter motor.
	 * @see setTargetSpeed(float)
	 * @see getTargetSpeed
	 */
	float targetSpeed;
	/**
	 * The target pitch, in degrees from parallel to the drivebase, of the shooter.
	 * @see setTargetPitch(float)
	 * @see getTargetPitch()
	 */
	float targetPitch;

	/**
	 * The number of ticks the flywheel speed has been in the accepted range.
	 * @see isSpeedStable()
	 */
	int speedStability;
	/**
	 * The number of ticks the pitch has been in the accepted range.
	 * @see isPitchStable()
	 */
	int pitchStability;

	/**
	 * If the motor update loop is currently controlling the flywheel.
	 * @see setArmed(bool)
	 * @see isArmed
	 */
	bool armed;
public:
	Shooter();
	~Shooter();

	/**
	 * Starts the motor update loop.
	 * @see Notifier::start()
	 */
	void startUpdateLoop();
	/**
	 * Stops the motor update loop.
	 * @see Notifier::stop()
	 */
	void endUpdateLoop();

	/**
	 * Sets the target speed of the flywheel in RPM.  This only causes the motors to be updated if the {@link armed} variable is set to true.
	 * @param rpm the target speed
	 */
	void setTargetSpeed(float rpm);
	/**
	 * Gets the current target speed of the flywheel in RPM.  This may not be the actual speed, and is independent of the armed variable.
	 * @return the target speed
	 */
	float getTargetSpeed();
	/**
	 * Gets the current actual speed of the flywheel in RPM.
	 * @return the actual speed
	 */
	float getCurrentSpeed();
	/**
	 * Checks if the flywheel speed has been within the accepted range for at least the accepted length of time.
	 * @return the stability as a boolean
	 */
	bool isSpeedStable();

	/**
	 * Checks if the shooter is armed.
	 * More specifically, this checks if the motor update loop is trying to achieve the flywheel's target speed.
	 * @return the armed state
	 */
	bool isArmed();
	/**
	 * Sets the armed state of this shooter.
	 * @param armed if the shooter is armed
	 */
	void setArmed(bool armed);

	/**
	 * Sets the target pitch of the shooter apparatus, in degrees from parallel to the drive base.
	 * @param degree the angle
	 */
	void setTargetPitch(float degree);
	/**
	 * Gets the actual pitch of the shooter apparatus, in degrees from parallel to the ground.
	 * @return the angle
	 */
	float getCurrentPitch();
	/**
	 * Checks if the shooter apparatus angle has been within the accepted range for at least the accepted length of time.
	 * @return the stability as a boolean
	 */
	bool isPitchStable();

//	Encoder *getShooterEncoder();  TODO Deprecated
//	Encoder *getPitchEncoder();

	virtual void InitDefaultCommand();
};

#endif
