#include "DriveBase.h"
#include "../Commands/Drivebase/TankDrive.h"

DriveBase::DriveBase() :
	Subsystem("DriveBase") {
	motorLeft = DRIVE_MOTOR_CREATE(DRIVE_MOTOR_LEFT);
#ifdef DRIVE_MOTOR_LEFT_2		// Only create the second motor if it's needed
	motorLeft2 = DRIVE_MOTOR_CREATE(DRIVE_MOTOR_LEFT_2);
#endif

	motorRight = DRIVE_MOTOR_CREATE(DRIVE_MOTOR_RIGHT);
#ifdef DRIVE_MOTOR_RIGHT_2		// Same thing ad infinitum
	motorRight2 = DRIVE_MOTOR_CREATE(DRIVE_MOTOR_RIGHT_2);
#endif

	shifter = new Relay(DRIVE_SHIFT_RELAY);
}

DriveBase::~DriveBase() {
	delete motorLeft;
#ifdef DRIVE_MOTOR_LEFT_2		// Only create the second motor if it's needed
	delete motorLeft2;
#endif

	delete motorRight;
#ifdef DRIVE_MOTOR_RIGHT_2		// Same thing ad infinitum
	delete motorRight2;
#endif

	//TODO delete leftEncoder;
	//TODO delete rightEncoder;
	//TODO delete gyro;

	delete shifter;
}

void DriveBase::setSpeed(float leftSpeed, float rightSpeed) {
	motorLeft->Set(leftSpeed);
#ifdef DRIVE_MOTOR_LEFT_2
	motorLeft2->Set(leftSpeed);
#endif

	motorRight->Set(-rightSpeed);
#ifdef DRIVE_MOTOR_RIGHT_2
	motorRight2->Set(-rightSpeed);
#endif
}

Gyro *DriveBase::getGyro() {
	return gyro;
}

Encoder *DriveBase::getLeftEncoder() {
	return leftEncoder;
}

Encoder *DriveBase::getRightEncoder() {
	return rightEncoder;
}

void DriveBase::InitDefaultCommand() {
	SetDefaultCommand(new TankDrive());
}

void DriveBase::shift(bool lowGear) {
	cachedLowState = lowGear;
	shifter->Set(lowGear ? Relay::kForward : Relay::kReverse);
}

bool DriveBase::isLowGear() {
	return cachedLowState;
}
