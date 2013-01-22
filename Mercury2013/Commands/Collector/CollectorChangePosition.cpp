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
	if (position == false){
		if (collector->getRealPosition() < COLLECTOR_DOWN_AMOUNT){
			//increases ther speed ever so slightly
			speed = speed*COLLECTOR_PITCH_SPEED_SCALAR;
		}
		else{
			speed = speed*(1-(COLLECTOR_PITCH_SPEED_SCALAR-1));
			/*the COLLECTOR_PITCH_SPEED_SCALAR is a scalar larger than 1 (.995 in this case)*/
		}
	}
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
