#include "CollectorChangePosition.h"

CollectorChangePosition::CollectorChangePosition(bool position) {
	Requires(collector);
	this->position = position;
}

CollectorChangePosition::~CollectorChangePosition() {

}

void CollectorChangePosition::Initialize() {
	speed = 0;
}

void CollectorChangePosition::Execute() {
	if (this->position == true) { //true == up, false == down
		if (left < (COLLECTOR_UP_AMOUNT - COLLECTOR_PITCH_THRESHOLD)) {
			if (collector->getRealPosition() < COLLECTOR_UP_AMOUNT) {
				collector->setCollectorPitchMotor(speed);
			}
		}
	} else {
		if (left < (COLLECTOR_DOWN_AMOUNT - COLLECTOR_PITCH_THRESHOLD)) {
			if (collector->getRealPosition() >= COLLECTOR_DOWN_AMOUNT) {
				collector->setCollectorPitchMotor(-speed);
			}
		}
	}
	left--;
}

bool CollectorChangePosition::IsFinished() {
	return true;
}

void CollectorChangePosition::End() {
	this->speed = 0;
	collector->setCollectorPitchMotor(0);
}

void CollectorChangePosition::Interrupted() {
}
