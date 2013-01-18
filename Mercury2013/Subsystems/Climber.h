#ifndef _CLIMBER_H
#define _CLIMBER_H

class Climber {
private:
	Encoder *arm1Encoder;
	Encoder *arm2Encoder;
	
	SpeedController *arm1Motor;
	SpeedController *arm2Motor;
	
	SpeedController *arm1Hook1;
	SpeedController *arm1Hook2;
	SpeedController *arm1Hook3;
	
	SpeedController *arm2Hook1;
	SpeedController *arm2Hook2;
	SpeedController *arm2Hook3;
	
	SpeedController *arm3Hook1;
	SpeedController *arm3Hook2;
	SpeedController *arm3Hook3;
	
	DigitalInput *arm1Button;
	DigitalInput *arm2Button;
	
public:
	void moveArm(float distance);
	void moveHook(float distance);
	
	bool getButton();
	float getDistance();
};

#endif