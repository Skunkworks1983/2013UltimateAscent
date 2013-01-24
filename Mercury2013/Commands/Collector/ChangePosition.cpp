#include "ChangePosition.h"

ChangePosition::ChangePosition(bool position) {
	Requires(collector);
	this->position = position;
}

ChangePosition::~ChangePosition() {

}

void ChangePosition::Initialize() {
	isFinished = false;
	speed = COLLECTOR_PITCH_LOWEST_SPEED;
}

void ChangePosition::Execute() {
	if (position == false) {
		if (collector->getRealPosition() >= COLLECTOR_DOWN_AMOUNT) {
			//finsishes the command
			isFinished = true;
		}
		
		if (collector->getRealPosition() < COLLECTOR_DOWN_AMOUNT) {
			//increases ther speed ever so slightly
			speed = speed*COLLECTOR_PITCH_SPEED_SCALAR;
		}
	} else {
		if (collector->getRealPosition() >= COLLECTOR_DOWN_AMOUNT) {
			//finsishes the command
			isFinished = true;
		}
		
		if (collector->getRealPosition() > 0)
			speed = speed*(1-(COLLECTOR_PITCH_SPEED_SCALAR-1));
		/*This makes the difference between 1 and COLLECTOR_PITCH_SPEED_SCALAR minused from one so it incrementally gets smaller*/
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
