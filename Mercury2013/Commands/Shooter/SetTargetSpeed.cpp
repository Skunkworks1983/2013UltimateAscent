#include "SetTargetSpeed.h"

SetTargetSpeed::SetTargetSpeed(float targetSpeed) :
	CommandBase("SetTargetSpeed") {
	this->targetSpeed = targetSpeed;
}

void SetTargetSpeed::Initialize() {
	
}

void SetTargetSpeed::Execute() {
	shooter->setTargetSpeed(targetSpeed);
}

bool SetTargetSpeed::IsFinished() {
	return shooter->getTargetSpeed() == targetSpeed;
}

void SetTargetSpeed::End() {

}

void SetTargetSpeed::Interrupted() {

}
