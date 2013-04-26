#include "DistanceTrigger.h"
#include <math.h>

DistanceTrigger::DistanceTrigger(double lowerRange, Encoder *srcA,
		Encoder *srcB) {
	this->srcA = srcA;
	this->srcB = srcB;
	this->lowerRange = lowerRange;
}

DistanceTrigger::~DistanceTrigger() {
}

bool DistanceTrigger::Get() {
	double current = srcA->GetDistance();
	if (srcB != NULL) {
		current += srcB->GetDistance();
		current /= 2.0;
	}
	return current > lowerRange;
}
