#include "SlowTankDrive.h"

SlowTankDrive::SlowTankDrive() :
	CommandBase("SlowTankDrive") {
	Requires(driveBase);
	SetInterruptible(true);
}

void SlowTankDrive::Initialize() {
}

void SlowTankDrive::Execute() {
	//Divides the input of the motors by 10.
	if (-oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis) + -oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis) == 0) {
		driveBase->setSpeed(0.0,0.0);
	} else {
		driveBase->setSpeed((-oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis) / 10) + .16,
				-oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis) / 10);
	}
}

bool SlowTankDrive::IsFinished() {
return false;
}

void SlowTankDrive::End() {
	driveBase->setSpeed(0, 0);
}

void SlowTankDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}
