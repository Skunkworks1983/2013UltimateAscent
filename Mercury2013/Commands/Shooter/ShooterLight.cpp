#include "ShooterLight.h"

ShooterLight::ShooterLight(LightType controlType) :
			CommandBase(
					CommandBase::createNameFromString(
							"ShooterLight",
							controlType == kOn ? "On"
									: (controlType == kOff ? "Off" : "Toggle"))) {
	// It requires the shooter, but we don't need a lock on it.
	this->controlType = controlType;
	SetInterruptible(true);
}

void ShooterLight::Initialize() {
	switch (controlType) {
	case kOff:
		toLightState = false;
		break;
	case kOn:
		toLightState = true;
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
