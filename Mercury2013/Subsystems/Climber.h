#ifndef _CLIMBER_H
#define _CLIMBER_H

class Climber {
private:
	Encoder *armsEncoder;
	SpeedController *armsMotor;
	
	SpeedController *arm1Hook1;
	SpeedController *arm1Hook2;
	SpeedController *arm1Hook3;
	
	SpeedController *arm2Hook1;
	SpeedController *arm2Hook2;
	SpeedController *arm2Hook3;
	
	DigitalInput *arm1Button;
	DigitalInput *arm2Button;
	
public:
	Climber();
	~Climber();
	void extendArm(double distance);
	void retractArm(double distance);
	void latchHook();
	void unlatchHook();
	
	bool getButton();
	double getDistance();
};

#endif