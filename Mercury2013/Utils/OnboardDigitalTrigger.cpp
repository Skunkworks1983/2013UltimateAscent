#include "OnboardDigitalTrigger.h"
#include <math.h>

OnboardDigitalTrigger::OnboardDigitalTrigger(DigitalInput *src, bool l) {
	this->source = src;
	this->expected = l;
}

OnboardDigitalTrigger::~OnboardDigitalTrigger() {
}

bool OnboardDigitalTrigger::Get() {
	return source->Get() == expected;
}
