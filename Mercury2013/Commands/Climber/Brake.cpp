#include "Brake.h"

Brake::Brake(bool isBraking) :
	CommandBase("Brake") {
	Requires(climber);
	this->isBraking = isBraking;
	SetInterruptible(true);
}

void Brake::Initialize() {
	
}

void Brake::Execute() {
	climber->setBrakeState(isBraking);
}

bool Brake::IsFinished() {
	return climber->getBrakeState() == isBraking;
}

void Brake::End() {
}

void Brake::Interrupted() {
}
