#include "ValueChangeTrigger.h"
#include <math.h>

ValueChangeTrigger::ValueChangeTrigger(GET_DOUBLE getValue,
		double changeThreshold) {
	this->changeThreshold = changeThreshold;
	this->getValue = getValue;
}

ValueChangeTrigger::~ValueChangeTrigger() {
}

bool ValueChangeTrigger::Get() {
	double value = getValue();
	bool changed = fabs(value - lastValue)
			> changeThreshold;
	if (changed) {
		lastValue = value;
	}
	return changed && value != FORCE_VALUE_CHANGE;
}
