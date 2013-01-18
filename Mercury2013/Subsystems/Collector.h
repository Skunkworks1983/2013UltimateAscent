#ifndef _COLLECTOR_H
#define _COLLECTOR_H

class Collector {
private:
	Encoder *collectorEncoder;
	Encoder *pitchEncoder;
	SpeedController *collectorMotor;
	SpeedController *collectorPitchMotor;
	float currentAngle;
	float startAngle;
public:
	*Encoder getCollectorEncoder;
	*Encoder getPitchEncoder;
	void changePitch(float);
	void startCollector();
	void stopCollector();
};

#endif