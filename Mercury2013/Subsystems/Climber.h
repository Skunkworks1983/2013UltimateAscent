#ifndef __CLIMBER_H
#define __CLIMBER_H
#include "WPILib.h"
#include "../RobotMap.h"

class Climber {
private:
	Encoder *armsEncoder;
	SpeedController *armsMotor;
	
	DigitalInput *arm1Switch;
	DigitalInput *arm2Switch;
	
public:
	Climber();
	~Climber();
	void moveMotor(float dist);
	void movePokey(bool pos);
	void setArmsMotor(float speed);
	
	float getPosition();
	bool getPokey();
	bool getSwitch(int num);
};

#endif
