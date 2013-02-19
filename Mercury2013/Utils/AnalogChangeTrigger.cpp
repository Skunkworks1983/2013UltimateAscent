#include "AnalogChangeTrigger.h"
#include "DriverStation.h"
#include <math.h>

AnalogChangeTrigger::AnalogChangeTrigger(int port, double changeThreshold,
		Trigger *active) {
	this->port = port;
	this->changeThreshold = changeThreshold;
	this->lastValue = 0;
	this->active = active;
}

AnalogChangeTrigger::~AnalogChangeTrigger() {
}

bool AnalogChangeTrigger::Get() {
	if (this->active != NULL && !this->active->Get()) {
		return false;
	}
	double volts = OI_POT_GENERIC_CONVERT(
			DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(port));
	bool changed = fabs(volts - lastValue) > changeThreshold;
	lastValue = volts;
	return changed;
}
