#ifndef __COLLECTOR_ARMS_H_
#define __COLLECTOR_ARMS_H_
#include "WPILib.h"
#include "../Robotmap.h"

class Collector;
class ArmController: public PIDOutput, public PIDSource {
protected:
	AnalogChannel *pot;
	PIDController *pid;
	COLLECTOR_PITCH_MOTOR_TYPE *motor;
	Collector *collect;
public:
	ArmController(Collector *collect, COLLECTOR_PITCH_MOTOR_TYPE *motor, AnalogChannel *pot);
	virtual ~ArmController();
	double PIDGet();
	virtual void PIDWrite(float f) = 0;
	void setPIDState(bool b);
	bool isPIDDone();
	void setSetpoint(float f);
};

class LeftArmController: public ArmController {
public:
	LeftArmController(Collector *collect);
	~LeftArmController();
	virtual void PIDWrite(float f);
};
class RightArmController: public ArmController {
public:
	RightArmController(Collector *collect);
	~RightArmController();
	virtual void PIDWrite(float f);
};
#endif