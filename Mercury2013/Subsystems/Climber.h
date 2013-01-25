#ifndef __CLIMBER_H
#define __CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"

class Climber {
private:

	/**
	 * The encoder for the arm movement motor
	 */
	Encoder *armsEncoder;

	/**
	 * The motor for the arm movement
	 */
	SpeedController *armsMotor;

	/**
	 * The button on the first hook to check state
	 */
	DigitalInput *arm1Button;

	/**
	 * The button on the second hook to check state
	 */
	DigitalInput *arm2Button;

	Solenoid *pokey1;
	Solenoid *pokey2;

public:
	Climber();
	~Climber();

	/**  
	 */
	void movePokey(bool pos);

	/**  
	 */
	void setArmsMotor(float speed);

	/**  
	 */
	float getPosition();

	/**  
	 */
	bool getPokey(int num);

	/**  Gets the state of the button given on the button number given
	 */
	bool getButton(int button);
};

#endif
