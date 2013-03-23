#include "UpdateOI.h"
#include "WPILib.h"

UpdateOI::UpdateOI() :
	CommandBase("UpdateOI") {
	countsSinceUpdate = 0;
	// Depends on any subsystems with visible output, but doesn't need a lock.
}

UpdateOI::~UpdateOI() {

}

void UpdateOI::Initialize() {
}

void UpdateOI::Execute() {
	if (++countsSinceUpdate > OI_DASH_UPDATE_SPEED) {
		countsSinceUpdate = 0;
		SmartDashboard::PutBoolean("Is Below Pressure",
				pneumatics->isBelowPressure());
		SmartDashboard::PutNumber("Collector Avg. Angle",
				collectorArms->getAngle());
		SmartDashboard::PutNumber("Collector Frisbee Count",
				collector->getFrisbeeSensorCount());
		SmartDashboard::PutNumber("Shooter Angle", shooterPitch->getRealPitch());
		SmartDashboard::PutNumber("Shooter Screw Scalar",
				shooterPitch->getCurrentPitch());
		SmartDashboard::PutNumber("Shooter Front Speed",
				shooter->getFrontSpeed());
		SmartDashboard::PutNumber("Shooter Rear Speed", shooter->getRearSpeed());
		SmartDashboard::PutNumber("Loops per Second", CommandBase::loopsPerSecond);
	}
}

bool UpdateOI::IsFinished() {
	return false;
}

void UpdateOI::End() {
}

void UpdateOI::Interrupted() {
}
