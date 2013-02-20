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
	SmartDashboard::PutBoolean("Is Low Gear", driveBase->isLowGear());
	SmartDashboard::PutBoolean("Is Below Pressure",
			pneumatics->isBelowPressure());
	SmartDashboard::PutNumber("Collector Avg. Angle", collector->getRawAngle());
	SmartDashboard::PutNumber("Collector Left Angle", collector->getLeftAngle());
	SmartDashboard::PutNumber("Collector Right Angle",
			collector->getRightAngle());
	SmartDashboard::PutNumber("Collector Frisbee Trigger",
			collector->getFrisbeeSensorCount());
}

bool UpdateOI::IsFinished() {
	return false;
}

void UpdateOI::End() {
}

void UpdateOI::Interrupted() {
}
