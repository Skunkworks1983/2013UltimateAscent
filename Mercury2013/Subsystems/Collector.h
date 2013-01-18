#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include "WPILib.h"
#include "../Robotmap.h"

class Collector : public Subsystem {
	Encoder *collectorEncoder;
	Encoder *pitchEncoder;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	float currentAngle;
	float startAngle;
public:
	Collector();
	~Collector();
	Encoder *getCollectorEncoder();
	Encoder *getPitchEncoder();
	void changePitch(float);
	void startCollector();
	void stopCollector();
	
	virtual void InitDefaultCommand();
};

#endif
