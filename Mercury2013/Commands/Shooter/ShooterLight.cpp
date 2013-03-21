#include "ShooterLight.h"

ShooterLight::ShooterLight(LightType controlType) :
	CommandBase(CommandBase::createNameFor("ShooterLight", controlType)) {
	// It requires the shooter, but we don't need a lock on it.
	this->controlType = controlType;
	SetInterruptible(true);
}

void ShooterLight::Initialize() {
	switch (controlType) {
	case kOff:
		toLightState = true;
		break;
	case kOn:
		toLightState = false;
		break;
	case kToggle:
		toLightState = !shooter->isLightOn();
		break;
	default:
		toLightState = true;
		break;
	}
}

void ShooterLight::Execute() {
	shooter->setLight(toLightState);
}

bool ShooterLight::IsFinished() {
	return shooter->isLightOn() == toLightState;
}

void ShooterLight::End() {
}

void ShooterLight::Interrupted() {
}
