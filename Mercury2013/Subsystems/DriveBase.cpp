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

	shiftSolenoid = new DoubleSolenoid(DRIVE_SHIFT_LOW, DRIVE_SHIFT_HIGH);

#ifdef DRIVE_ENCODER_LEFT
	leftEncoder = new Encoder(DRIVE_ENCODER_LEFT);
	leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK);
	leftEncoder->Start();
#else
	leftEncoder = NULL;
#endif
#ifdef DRIVE_ENCODER_RIGHT
	rightEncoder = new Encoder(DRIVE_ENCODER_RIGHT);
	rightEncoder->SetDistancePerPulse(DRIVE_ENCODER_INCH_PER_TICK);
	rightEncoder->Start();
#else
	rightEncoder = NULL;
#endif

	LiveWindow::GetInstance()->AddSensor("DriveBase", "LeftEncoder",
			leftEncoder);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "RightEncoder",
			rightEncoder);

#ifdef DRIVE_GYRO
	gyro = new Gyro(DRIVE_GYRO);
#endif
	cachedLowState = false;
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

#ifdef DRIVE_ENCODER_LEFT
	delete leftEncoder;
#endif
#ifdef DRIVE_ENCODER_RIGHT
	delete rightEncoder;
#endif
#ifdef DRIVE_GYRO
	delete gyro;
#endif
	delete shiftSolenoid;

	LiveWindow::GetInstance()->AddSensor("DriveBase", "DriveGyro", gyro);
}

void DriveBase::setSpeed(float leftSpeed, float rightSpeed) {
	motorLeft->Set(-leftSpeed);
#ifdef DRIVE_MOTOR_LEFT_2
	motorLeft2->Set(-leftSpeed);
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
	SetDefaultCommand(new TankDrive());
}

void DriveBase::shift(bool lowGear) {
	cachedLowState = lowGear;
	shiftSolenoid->Set(
			lowGear ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
}

void DriveBase::reset() {
#ifdef DRIVE_ENCODER_LEFT
	leftEncoder->Reset();
#endif
#ifdef DRIVE_ENCODER_RIGHT
	rightEncoder->Reset();
#endif
#ifdef DRIVE_GYRO
	gyro->Reset();
#endif
}

bool DriveBase::isLowGear() {
	return cachedLowState;
}
