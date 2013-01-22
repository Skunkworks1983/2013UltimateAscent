#include "UpdateLights.h"

UpdateLights::UpdateLights() {
	// Depends on any subsystems with visible output, but doesn't need a lock.
}

UpdateLights::~UpdateLights() {

}

void UpdateLights::Initialize() {
}

void UpdateLights::Execute() {
	oi->setLightState(OI::kLightClimberHook1, climber->getButton(0));
	oi->setLightState(OI::kLightClimberHook2, climber->getButton(1));
}

bool UpdateLights::IsFinished() {
	return false;
}

void UpdateLights::End() {
}

void UpdateLights::Interrupted() {
}
