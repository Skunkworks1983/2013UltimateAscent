#include "TankDrive.h"
#include <math.h>

TankDrive::TankDrive(float speedMultiplier) :
	CommandBase("TankDrive") {
	Requires(driveBase);
	SetInterruptible(true);
	this->speedMultiplier = speedMultiplier;
}

void TankDrive::Initialize() {
}

void TankDrive::Execute() {
	float leftY = -oi->getDriveJoystickLeft()->GetAxis(Joystick::kYAxis);
	float rightY = -oi->getDriveJoystickRight()->GetAxis(Joystick::kYAxis);
	if (fabs(leftY) <= OI_JOYSTICK_DEADBAND) {
		leftY = 0.0;
	}
	if (fabs(rightY) <= OI_JOYSTICK_DEADBAND) {
		rightY = 0.0;
	}
	if (speedMultiplier > 0.0) {
		driveBase->setSpeed(leftY * speedMultiplier, rightY * speedMultiplier);
	} else {
		driveBase->setSpeed(rightY * speedMultiplier, leftY * speedMultiplier);
	}
}

void TankDrive::setMotorScalingFactor(float f) {
	this->speedMultiplier = f;
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
