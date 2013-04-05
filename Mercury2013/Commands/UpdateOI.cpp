#include "UpdateOI.h"
#include "WPILib.h"
#include "../Utils/Time.h"

UpdateOI::UpdateOI() :
	CommandBase("UpdateOI") {
	lastUpdate = 0.0;
	// Depends on any subsystems with visible output, but doesn't need a lock.
}

UpdateOI::~UpdateOI() {

}

void UpdateOI::Initialize() {
}

void UpdateOI::Execute() {
	if (lastUpdate + OI_DASH_UPDATE_SPEED < getCurrentMillis()) {
		lastUpdate = getCurrentMillis();
		DriverStation::GetInstance()->GetEnhancedIO().SetDigitalOutput(6,
				driveBase->getLeftDiddler()->Get());
		DriverStation::GetInstance()->GetEnhancedIO().SetDigitalOutput(8,
				driveBase->getRightDiddler()->Get());
#if (DEBUG_LEVEL>=DEBUG_INFO)
		SmartDashboard::PutBoolean("Is Below Pressure",
				pneumatics->isBelowPressure());
		SmartDashboard::PutNumber("Collector Avg. Angle",
				collectorArms->getAngle());
		SmartDashboard::PutNumber("Collector L Angle",
				collectorArms->getLeftAngle());
		SmartDashboard::PutNumber("Collector R Angle",
				collectorArms->getRightAngle());
		SmartDashboard::PutNumber("Collector Frisbee Count",
				collector->getFrisbeeSensorCount());
		SmartDashboard::PutNumber("Shooter Angle", shooterPitch->getRealPitch());
		SmartDashboard::PutNumber("Shooter Screw Scalar",
				shooterPitch->getCurrentPitch());
		SmartDashboard::PutNumber("Shooter Front Speed",
				shooter->getFrontSpeed());
		SmartDashboard::PutNumber("Shooter Rear Speed", shooter->getRearSpeed());
#endif
	}
}

bool UpdateOI::IsFinished() {
	return false;
}

void UpdateOI::End() {
}

void UpdateOI::Interrupted() {
}
