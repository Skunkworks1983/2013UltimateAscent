#include "DriveBase.h"
#include "../Commands/Drivebase/TankDrive.h"

DriveBase::DriveBase() :
		Subsystem("DriveBase") {
	printf("Creating drive base...\t");
	motorLeft = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT_2));
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Left Motor",
			motorLeft);

	motorRight = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT_2));
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Right Motor",
			motorRight);

	shiftSolenoid = new SolenoidPair(DRIVE_SHIFT);
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Shifter",
			shiftSolenoid);

	leftEncoder = new Encoder(DRIVE_ENCODER_LEFT);
	if (isLowGear()) {
		leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_LOW);
	} else {
		leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	}
	leftEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("DriveBase", "LeftEncoder",
			leftEncoder);

	rightEncoder = new Encoder(DRIVE_ENCODER_RIGHT);
	if (isLowGear()) {
		rightEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_LOW);
	} else {
		rightEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	}
	rightEncoder->Start();
	LiveWindow::GetInstance()->AddSensor("DriveBase", "RightEncoder",
			rightEncoder);
	
	gyro = new Gyro(DRIVE_GYRO);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "Gyro", gyro);
	
	printf("Done\n");
}

DriveBase::~DriveBase() {
	delete motorLeft;
	delete motorRight;

	delete leftEncoder;
	delete rightEncoder;
	
	delete gyro;
	
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
	if (lowGear) {
		leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_LOW);
		rightEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_LOW);
	} else {
		leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
		rightEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	}
}

void DriveBase::reset() {
	leftEncoder->Reset();
	rightEncoder->Reset();

	gyro->Reset();
}

bool DriveBase::isLowGear() {
	return shiftSolenoid->Get();
}
