#include "TankDrive.h"

TankDrive::TankDrive() :
	CommandBase("TankDrive") {
	Requires(driveBase);
	SetInterruptible(true);
}

void TankDrive::Initialize() {
}

void TankDrive::Execute() {
	driveBase->setSpeed(-oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis),
			-oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis));
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
