#include "DriveBase.h"

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
	
	delete leftEncoder;
	delete rightEncoder;
	delete gyro;
}

void DriveBase::setSpeed(float leftSpeed, float rightSpeed) {
	motorLeft->Set(leftSpeed);
#ifdef DRIVE_MOTOR_LEFT_2
	motorLeft2->Set(leftSpeed);
#endif

	motorRight->Set(rightSpeed);
#ifdef DRIVE_MOTOR_RIGHT_2
	motorRight2->Set(rightSpeed);
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
	// TODO Something
}
