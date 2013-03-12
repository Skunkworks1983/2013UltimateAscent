#include "UpdateOI.h"
#include "WPILib.h"

UpdateOI::UpdateOI() :
	CommandBase("UpdateOI") {
	// Depends on any subsystems with visible output, but doesn't need a lock.
}

UpdateOI::~UpdateOI() {

}

void UpdateOI::Initialize() {
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line1, 1,
			"Version: %f", 1.15);
	DriverStationLCD::GetInstance()->UpdateLCD();
}

void UpdateOI::Execute() {
	//oi->setLightState(OI::kLightClimberHook1, climber->getButton(0));
	//oi->setLightState(OI::kLightClimberHook2, climber->getButton(1));
	SmartDashboard::PutBoolean("Is Low Gear", driveBase->isLowGear());
	SmartDashboard::PutBoolean("Is Below Pressure",
			pneumatics->isBelowPressure());
	SmartDashboard::PutNumber("Collector Avg. Angle", collectorArms->getAngle());
	SmartDashboard::PutNumber("Collector Frisbee Trigger",
			collector->getFrisbeeSensorCount());
	SmartDashboard::PutNumber("Shooter Angle", shooterPitch->getRealPitch());
	SmartDashboard::PutNumber("Shooter Absolute Angle",
			shooterPitch->getCurrentPitch());
}

bool UpdateOI::IsFinished() {
	return false;
}

void UpdateOI::End() {
}

void UpdateOI::Interrupted() {
}
