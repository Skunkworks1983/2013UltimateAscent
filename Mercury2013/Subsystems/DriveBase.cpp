#include "DriveBase.h"
#include "../Commands/Drivebase/TankDrive.h"

DriveBase::DriveBase() :
	Subsystem("DriveBase") {
	printf("Creating drive base...\t");
	motorLeft = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_LEFT_2));

	motorRight = new DualLiveSpeed(new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT),
			new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_RIGHT_2));

	shiftSolenoid = new SolenoidPair(DRIVE_SHIFT);

	leftEncoder = new Encoder(DRIVE_ENCODER_LEFT);
	leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	leftEncoder->Start();

	rightEncoder = new Encoder(DRIVE_ENCODER_RIGHT);
	rightEncoder->SetDistancePerPulse(DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	rightEncoder->Start();

	gyro = new Gyro(DRIVE_GYRO);

	leftDiddler = new OnboardDigitalTrigger(
			new DigitalInput(DRIVE_LEFT_DIDDLER), false);
	rightDiddler = new OnboardDigitalTrigger(
			new DigitalInput(DRIVE_RIGHT_DIDDLER), false);

	LiveWindow::GetInstance()->AddActuator("DriveBase", "Left Motor", motorLeft);
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Right Motor",
			motorRight);
	LiveWindow::GetInstance()->AddActuator("DriveBase", "Shifter",
			shiftSolenoid);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "LeftEncoder",
			leftEncoder);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "RightEncoder",
			rightEncoder);
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
		rightEncoder->SetDistancePerPulse(DRIVE_ENCODER_INCH_PER_TICK_LOW);
	} else {
		leftEncoder->SetDistancePerPulse(-DRIVE_ENCODER_INCH_PER_TICK_HIGH);
		rightEncoder->SetDistancePerPulse(DRIVE_ENCODER_INCH_PER_TICK_HIGH);
	}
	leftEncoder->Reset();
	rightEncoder->Reset();
}

void DriveBase::setMotorScalingFactor(float f) {
	if (f < -1.0) {
		f = -1.0;
	} else if (f > 1.0) {
		f = 1.0;
	}
	((TankDrive*) GetDefaultCommand())->setMotorScalingFactor(f);
}

void DriveBase::reset() {
	leftEncoder->Reset();
	rightEncoder->Reset();

	gyro->Reset();
}

bool DriveBase::isLowGear() {
	return shiftSolenoid->Get();
}

Trigger *DriveBase::getLeftDiddler() {
	return leftDiddler;
}

Trigger *DriveBase::getRightDiddler() {
	return rightDiddler;
}
