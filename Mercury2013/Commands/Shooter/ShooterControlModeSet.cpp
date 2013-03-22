#include "ShooterControlModeSet.h"

ShooterControlModeSet::ShooterControlModeSet(int sControl, int waitType) :
	CommandBase("ShooterBang") {
	this->controlType = sControl;
	this->waitType = waitType;
	SetInterruptible(true);
}

void ShooterControlModeSet::Initialize() {
	if (waitType == CONTROL_NOCHANGE) {
		waitType = shooter->getWaitScheme();
	}
	if (controlType == CONTROL_NOCHANGE) {
		controlType = shooter->getControlScheme();
	}
}

void ShooterControlModeSet::Execute() {
	shooter->setControlScheme((Shooter::ControlType) controlType);
	shooter->setWaitScheme((Shooter::WaitType) waitType);
}

bool ShooterControlModeSet::IsFinished() {
	return shooter->getControlScheme() == controlType
			&& shooter->getWaitScheme() == waitType;
}

void ShooterControlModeSet::End() {
	SmartDashboard::PutString("Shooter Control Mode",
			Shooter::getControlTypeName(shooter->getControlScheme()));
	SmartDashboard::PutString("Shooter Wait Mode",
			Shooter::getWaitTypeName(shooter->getWaitScheme()));
}

void ShooterControlModeSet::Interrupted() {
}
