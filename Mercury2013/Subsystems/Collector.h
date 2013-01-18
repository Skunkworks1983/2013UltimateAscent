#ifndef _COLLECTOR_H
#define _COLLECTOR_H

class Collector {
private:
	Encoder *collectorEncoder;
	Encoder *pitchEncoder;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
public:
	void changePitch();
	void startCollector();
	void stopCollector();
};

#endif