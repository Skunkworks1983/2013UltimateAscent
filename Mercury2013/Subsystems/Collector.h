#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include "WPILib.h"

class Collector : public Subsystem {
private:
	Encoder *collectorEncoder;
	AnalogModule *pitchPot;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
public:
	Collector();
	~Collector();
	Encoder *getCollectorEncoder();
	void startCollector();
	void stopCollector();
	bool getPosition();
	float getRealPosition();

	virtual void InitDefaultCommand();
};

#endif
