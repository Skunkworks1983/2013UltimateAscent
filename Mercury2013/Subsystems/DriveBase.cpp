#include "DriveBase.h"
#include "../Commands/Drivebase/TankDrive.h"

DriveBase::DriveBase() :
		Subsystem("DriveBase") {
	printf("Creating drive base...\t");
#ifdef DRIVE_MOTOR_LEFT_2		// Same thing ad infinitum
	motorLeft = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT_2));
#else
	motorLeft = new DualLiveSpeed(
			motorLeft = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT),NULL);
#endif
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Left Motor",
			motorLeft);

#ifdef DRIVE_MOTOR_RIGHT_2		// Same thing ad infinitum
	motorRight = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT_2));
#else
	motorRight = new DualLiveSpeed(
			motorRight = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT),NULL);
#endif
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Right Motor",
			motorRight);

	shiftSolenoid = new SolenoidPair(DRIVE_SHIFT);
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Shifter",
			shiftSolenoid);

#ifdef DRIVE_ENCODER_LEFT
	leftEncoder = new Encoder(DRIVE_ENCODER_LEFT);
	leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK);
	leftEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("DriveBase", "LeftEncoder",
			leftEncoder);
#else
	leftEncoder = NULL;
#endif
#ifdef DRIVE_ENCODER_RIGHT
	rightEncoder = new Encoder(DRIVE_ENCODER_RIGHT);
	rightEncoder->SetDistancePerPulse(DRIVE_ENCODER_INCH_PER_TICK);
	rightEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("DriveBase", "RightEncoder",
			rightEncoder);
#else
	rightEncoder = NULL;
#endif

#ifdef DRIVE_GYRO
	gyro = new Gyro(DRIVE_GYRO);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "Gyro", gyro);
#endif
	printf("Done\n");
}

DriveBase::~DriveBase() {
	delete motorLeft;
	delete motorRight;

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
	//TODO Check on Competition Bot
	motorLeft->Set(leftSpeed);
	motorRight->Set(-rightSpeed);
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
	shiftSolenoid->Set(lowGear);
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
	return shiftSolenoid->Get();
}
