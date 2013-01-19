#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include "WPILib.h"

class Collector : public Subsystem {
private:
	Encoder *collectorEncoder;
	AnalogChannel *pitchPot;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
public:
	Collector();
	~Collector();
	Encoder *getCollectorEncoder();
	void setCollectorState(bool state);
	bool isUp();
	float getRealPosition();
	void setCollectorPitchMotor(float);
	void setCollectorSpeed(float);

	virtual void InitDefaultCommand();
};

#endif
