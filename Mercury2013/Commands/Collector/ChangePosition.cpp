#include "ChangePosition.h"

ChangePosition::ChangePosition(raise_or_lower desiredPosition) {
	Requires(collector);
	this->desiredPosition = targetPosition;
}

ChangePosition::~ChangePosition() {
}

void ChangePosition::Initialize() {
	isFinished = false;
	speed = COLLECTOR_PITCH_LOWEST_SPEED;
}

void ChangePosition::Execute() {
	
	if (desiredPosition == lower) {
		if (collector->getRealPosition() >= COLLECTOR_DOWN_AMOUNT) {
			// Finsishes the command
			isFinished = true;
		}

		if (collector->getRealPosition() < COLLECTOR_DOWN_AMOUNT) {
			// Increases ther speed ever so slightly
			if (collector->getRealPosition() < (COLLECTOR_DOWN_AMOUNT/2)) {
				speed = speed*COLLECTOR_PITCH_SPEED_SCALAR;
			} else {
				speed = speed*(1-(COLLECTOR_PITCH_SPEED_SCALAR-1));
			}
		}
	} else {
		if (collector->getRealPosition() >= COLLECTOR_DOWN_AMOUNT) {
			// Finsishes the command
			isFinished = true;
		}

		if (collector->getRealPosition() > 0)
			if (collector->getRealPosition() > (COLLECTOR_DOWN_AMOUNT/2)) {
				speed = speed*COLLECTOR_PITCH_SPEED_SCALAR;
			} else {
				speed = speed*(1-(COLLECTOR_PITCH_SPEED_SCALAR-1));
			}
		// This makes the difference between 1 and COLLECTOR_PITCH_SPEED_SCALAR minused from one so it incrementally gets smaller
	}
}

bool ChangePosition::IsFinished() {
	return isFinished;
}

void ChangePosition::End() {
	this->speed = 0;
	collector->setCollectorPitchMotor(0);
}

void ChangePosition::Interrupted() {
}
