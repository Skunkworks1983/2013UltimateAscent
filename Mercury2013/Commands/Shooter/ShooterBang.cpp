#include "ShooterBang.h"

ShooterBang::ShooterBang(ControlType shiftingType) :
	CommandBase("ShooterBang") {
	// It requires the shooter, but we don't need a lock on it.
	this->controlType = shiftingType;
	SetInterruptible(true);
}

void ShooterBang::Initialize() {
	switch (controlType) {
	case kOff:
		enableShooterBang = true;
		break;
	case kOn:
		enableShooterBang = false;
		break;
	case kToggle:
		//enableShooterBang = !shooter->isShooterBangEnabled();
		break;
	default:
		enableShooterBang = true;
		break;
	}
}

void ShooterBang::Execute() {
	//shooter->setShooterBang(enableShooterBang);
}

bool ShooterBang::IsFinished() {
	return true;//shooter->isShooterBangEnabled() == enableShooterBang;
}

void ShooterBang::End() {
}

void ShooterBang::Interrupted() {
}
