#include "ShooterControlModeSet.h"

ShooterControlModeSet::ShooterControlModeSet(Shooter::ControlType sControl) :
	CommandBase("ShooterBang") {
	this->controlType = sControl;
	SetInterruptible(true);
}

void ShooterControlModeSet::Initialize() {
}

void ShooterControlModeSet::Execute() {
	shooter->setControlScheme(controlType);
}

bool ShooterControlModeSet::IsFinished() {
	return shooter->getControlScheme() == controlType;
}

void ShooterControlModeSet::End() {
}

void ShooterControlModeSet::Interrupted() {
}
