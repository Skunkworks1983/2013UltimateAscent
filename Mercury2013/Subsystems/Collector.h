#ifndef __SYS_COLLECTOR_H
#define __SYS_COLLECTOR_H

#include "WPILib.h"

class Collector : public Subsystem {
private:
	Encoder *collectorEncoder;
	AnalogChannel *pitchPot;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
	DigitalInput * IRLow;
	DigitalInput * IRMid;
	DigitalInput * IRHigh;
public:
	Collector();
	~Collector();
	Encoder *getCollectorEncoder();
	void setCollectorState(bool state);
	bool isUp();
	float getRealPosition();
	void setCollectorPitchMotor(float);
	void setCollectorSpeed(float);
	int getSense(int height);
	virtual void InitDefaultCommand();
};

#endif
