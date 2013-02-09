#ifndef __SYS_CLIMBER_H
#define __SYS_CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/DualPIDOutput.h"

/**
 * @brief All of the necessary methods and accessors for Climb and its child commands
 * 
 * @author Connor Barlow, Westin Miller
 */
class Climber: public Subsystem, public PIDOutput, public PIDSource {
public:
	enum SliderState {
		kDown, kUp, kOther
	};

private:
	/**  
	 * The encoder for the arm movement motor
	 */
	Encoder *sliderEncoder;

	/**  
	 * The motor for the arm movement
	 */
	SpeedController *sliderMotor1;
	SpeedController *sliderMotor2;

	/**  
	 * The buttons on the first and second hook to check state
	 */
	DigitalInput *hookButton1;
	DigitalInput *hookButton2;

	/**  
	 * Solenoid to operate the two pokeys ticks
	 */
	Solenoid *pokeyUp;
	Solenoid *pokeyDown;

	/**
	 * Solenoid to control slider brake
	 */
	Solenoid *sliderBrake;

	/**
	 * The cached state of the brake
	 */
	bool cachedBrakeState;

	/**
	 * The pid controller for controlling the motors with a velocity.
	 */
	PIDController *velocityController;

public:
	Climber();
	~Climber();

	/**  
	 * Mokes the pokey stick to a state specified
	 */
	void movePokey(bool pos);

	/**  
	 * Gets the pokey state with a specific pokey number given
	 */
	bool getPokey(int num);

	/**  
	 * Gets the state of the button given on the button number given
	 */
	bool getButton(int button);

	/**
	 * Set whether we are braking or not
	 */
	void setBrakeState(bool isBraking);

	/**
	 * Get whether we are broken or not
	 */
	bool getBrakeState();

	/**
	 * Gets the state of the slider.
	 */
	SliderState getSliderState();

	/**
	 * Resets the velocity PID, to keep it from running away, and makes sure that it's started.
	 */
	void resetVelocityPID();
	

	/**
	 * Writes the speed to two motors.
	 * @param speed the scalar speed
	 */
	virtual void PIDWrite(float speed);

	/**
	 * Gets the position of the climber.
	 * @return the position, 0-1
	 */
	virtual double PIDGet();
};

#endif
