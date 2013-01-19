#ifndef __CLIMBER_H
#define __CLIMBER_H

#include "WPILib.h"

class Climber {
private:
	Encoder *armsEncoder;
	SpeedController *armsMotor;
	
	DigitalInput *arm1Switch;
	DigitalInput *arm2Switch;
	
public:
	Climber();
	~Climber();
	void moveMotor(double dist);
	void movePokey(bool pos);
	
	double getPosition();
	bool getPokey();
	bool getSwitch();
};

#endif
