#include "AnalogChangeTrigger.h"
#include "DriverStation.h"
#include <math.h>

AnalogChangeTrigger::AnalogChangeTrigger(int port, double changeThreshold) {
	this->port = port;
	this->changeThreshold = changeThreshold;
	this->lastValue = 0;
}

AnalogChangeTrigger::~AnalogChangeTrigger() {
}

bool AnalogChangeTrigger::Get() {
	double volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
			port);
	bool changed = fabs(volts - lastValue) > changeThreshold;
	lastValue = volts;
	return changed;
}
