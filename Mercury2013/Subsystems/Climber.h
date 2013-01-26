#ifndef __CLIMBER_H
#define __CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"

class Climber {
private:

	/**  The encoder for the arm movement motor
	 */
	Encoder *armsEncoder;

	/**  The motor for the arm movement
	 */
	SpeedController *armsMotor;

	/**  The buttons on the first and second hook to check state
	 */
	DigitalInput *arm1Button;
	DigitalInput *arm2Button;

	/**  Solenoids to operate the two pokeys ticks
	 */
	Solenoid *pokey1;
	Solenoid *pokey2;

public:
	Climber();
	~Climber();

	/**  Mokes the pokey stick to a state specified
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
