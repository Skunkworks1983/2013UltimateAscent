#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include "WPILib.h"

#define LOW (low->get() == 0)
#define MID (mid->get() == 0)
#define HIGH (high->get() == 0)

class Collector : public Subsystem {
private:
	Encoder *collectorEncoder;
	AnalogChannel *pitchPot;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	bool currentPosition;
	DigitalInput * low;
	DigitalInput * mid;
	DigitalInput * high;
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
	bool getSense(int height);
};

#endif
