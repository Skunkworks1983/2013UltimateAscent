#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include "WPILib.h"

class Collector : public Subsystem {
	Encoder *collectorEncoder;
	Encoder *pitchEncoder;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
public:
	Collector();
	~Collector();
	Encoder *getCollectorEncoder();
	Encoder *getPitchEncoder();
	void changePosition(bool);
	void startCollector();
	void stopCollector();
	bool getPosition();
	
	virtual void InitDefaultCommand();
};

#endif
