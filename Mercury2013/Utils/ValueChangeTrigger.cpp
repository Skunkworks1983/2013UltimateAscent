#include "ValueChangeTrigger.h"
#include <math.h>

ValueChangeTrigger::ValueChangeTrigger(GET_DOUBLE getValue, double changeThreshold) {
	this->changeThreshold = changeThreshold;
	this->getValue = getValue;
}

ValueChangeTrigger::~ValueChangeTrigger() {
}

bool ValueChangeTrigger::Get() {
	double value = getValue();
	bool changed = fabs(value - lastValue) > changeThreshold;
	lastValue = value;
	return changed;
}
