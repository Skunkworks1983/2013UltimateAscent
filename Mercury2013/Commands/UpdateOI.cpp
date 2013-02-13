#include "UpdateOI.h"
#include "WPILib.h"

UpdateOI::UpdateOI() :
	CommandBase("UpdateOI") {
	// Depends on any subsystems with visible output, but doesn't need a lock.
}

UpdateOI::~UpdateOI() {

}

void UpdateOI::Initialize() {
}

void UpdateOI::Execute() {
	//oi->setLightState(OI::kLightClimberHook1, climber->getButton(0));
	//oi->setLightState(OI::kLightClimberHook2, climber->getButton(1));
	SmartDashboard::PutBoolean("Is low gear", driveBase->isLowGear());
}

bool UpdateOI::IsFinished() {
	return false;
}

void UpdateOI::End() {
}

void UpdateOI::Interrupted() {
}
