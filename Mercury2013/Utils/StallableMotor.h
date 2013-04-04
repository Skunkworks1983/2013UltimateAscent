#ifndef __STALLABLE_MOTOR_H_
#define __STALLABLE_MOTOR_H_

#include "WPILib.h"

class StallableMotor: public SpeedController {
private:
	SpeedController *backend;
	Encoder *stallEncoder;
	float cacheSpeed;
	UINT8 cacheSyncGroup;
	double stallStart;
	double stallTimeThreshold;
	bool stalled;
public:
	StallableMotor(SpeedController *backend, Encoder *stallEncoder, double stallTimeTreshold = 500);
	virtual void Set(float speed, UINT8 syncGroup = 0);
	virtual float Get();
	virtual void Disable();
	bool isStalled();
	void updateController();
	void PIDWrite(float speed);
};

#endif
