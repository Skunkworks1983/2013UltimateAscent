#include "CollectorChangePosition.h"

CollectorChangePosition::CollectorChangePosition() {
	Requires(collector);
}

void CollectorChangePosition::Initialize() {
	speed = 0;
}

void CollectorChangePosition::Execute(bool position) {
	/*if (collector->getPosition()) {
		if (position == collector->getPosition()) {
			collector->collectorPitchMotor->Set(speed);
		} else {
			collector->collectorPitchMotor->Set(-speed);
		}
	}*/
}

bool CollectorChangePosition::IsFinished() {
	return true;
}

void CollectorChangePosition::End() {
	speed = 0;
}

void CollectorChangePosition::Interrupted() {
}

bool CollectorChangePosition::IsInterruptible() {
	return false;
}
