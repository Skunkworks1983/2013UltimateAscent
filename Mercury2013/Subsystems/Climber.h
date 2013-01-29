#ifndef __CLIMBER_H
#define __CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/DualPIDOutput.h"

/**
 * @brief All of the necessary methods and accessors for Climb and its child commands
 * 
 * @author Connor Barlow
 */
class Climber: public Subsystem {
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
	 * Both slider motors contained in one fancy object
	 */
	DualPIDOutput *sliderMotors;

	/**  
	 * The buttons on the first and second hook to check state
	 */
	DigitalInput *hookButton1;
	DigitalInput *hookButton2;

	/**  
	 * Solenoids to operate the two pokeys ticks
	 */
	Solenoid *pokey1;
	Solenoid *pokey2;
	
	/**
	 * Solenoid to control slider brake
	 */
	Solenoid *sliderBrake;
	
	/**
	 * Controller for the slider motor
	 */
	PIDController *sliderPID;
	
	/**
	 * The cached state of the brake
	 */
	bool cachedBrakeState;
	
public:
	Climber();
	~Climber();

	/**  
	 * Mokes the pokey stick to a state specified
	 */
	void movePokey(bool pos);

	/**  
	 * Set the arms motor to a specified speed
	 */
	void setSliderMotors(float speed);

	/**  
	 * Gets the position of the arms at a current point
	 */
	float getPosition();

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
};

#endif
