#ifndef __SYS_CLIMBER_H
#define __SYS_CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/DualLiveSpeed.h"

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
	DualLiveSpeed *sliderMotor;

	/**  
	 * The buttons on the first and second hook to check state
	 */
	DigitalInput *hookButton1;
	DigitalInput *hookButton2;

	/**  
	 * Solenoid to operate the two pokeys ticks
	 */
	SolenoidPair *pokey;

	/**
	 * Solenoid to control slider brake
	 */
	SolenoidPair *sliderBrake;

	/**
	 * The pid controller for controlling the motors with a velocity.
	 */
	PIDController *velocityController;

	Notifier *climberSaftey;
	static void callSaftey(void *climber);
	void saftey();
public:
	Climber();
	~Climber();
	/**  
	 * Mokes the pokey stick to a state specified
	 */
	void setPokey(bool pos);

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
	 * Writes the speed to two motors.
	 * @param speed the scalar speed
	 */
	virtual void PIDWrite(float speed);

	/**
	 * Gets the position of the climber.
	 * @return the position, 0-1
	 */
	virtual double PIDGet();

	void setVelocityPIDState(bool state);
};

#endif
