#include "CollectorChangePosition.h"

CollectorChangePosition::CollectorChangePosition() {
	Requires(collector);
}

CollectorChangePosition::~CollectorChangePosition() {
	
}

void CollectorChangePosition::Initialize() {
	speed = 0;
}

void CollectorChangePosition::Execute(bool position) {
	if (collector->getRealPosition() <= COLLECTOR_DOWN_AMOUNT) {
		if (position == collector->getPosition()) {
			collector->setCollectorPitchMotor(speed);
		}
	if (collector->getRealPosition() >= COLLECTOR_UP_AMOUNT) {
			collector->setCollectorPitchMotor(-speed);
		}
	}
}

bool CollectorChangePosition::IsFinished() {
	return true;
}

void CollectorChangePosition::End() {
	this->speed = 0;
}

void CollectorChangePosition::Interrupted() {
}

bool CollectorChangePosition::IsInterruptible() {
	return false;
}
