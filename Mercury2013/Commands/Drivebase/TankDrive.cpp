#include "TankDrive.h"

TankDrive::TankDrive(float speedMultiplier) :
	CommandBase("TankDrive") {
	Requires(driveBase);
	SetInterruptible(true);
	this->speedMultiplier = speedMultiplier;
}

void TankDrive::Initialize() {
}

void TankDrive::Execute() {
	driveBase->setSpeed(
			-oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis)
					* speedMultiplier,
			-oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis)
					* speedMultiplier);
}

bool TankDrive::IsFinished() {
	return false;
}

void TankDrive::End() {
	driveBase->setSpeed(0, 0);
}

void TankDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}
