#include "TankDrive.h"

TankDrive::TankDrive() {
	Requires(driveBase);
}

void TankDrive::Initialize() {
}

void TankDrive::Execute() {
	driveBase->setSpeed(oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis),
			oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis));
}

bool TankDrive::IsFinished() {
	return true;
}

void TankDrive::End() {
}

void TankDrive::Interrupted() {
}

bool TankDrive::IsInterruptible() {
	return false;
}
