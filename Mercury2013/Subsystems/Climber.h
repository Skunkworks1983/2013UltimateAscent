#ifndef __CLIMBER_H
#define __CLIMBER_H
#include "WPILib.h"
#include "../RobotMap.h"

class Climber {
private:
	Encoder *armsEncoder;
	SpeedController *armsMotor;
	
	DigitalInput *arm1Button;
	DigitalInput *arm2Button;
	
public:
	Climber();
	~Climber();
	void moveMotor(float dist);
	void movePokey(bool pos);
	void setArmsMotor(float speed);
	
	float getPosition();
	bool getPokey();
	bool getButton(int button);
};

#endif
