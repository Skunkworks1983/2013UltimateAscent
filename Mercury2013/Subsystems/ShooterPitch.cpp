#include "ShooterPitch.h"
#include "../Utils/Math.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/ChangeShooterPitch.h"

ShooterPitch::ShooterPitch() :
	Subsystem("ShooterPitch") {
	printf("Creating ShooterPitch...\t");

	pitchMotor = new SHOOTER_PITCH_MOTOR_TYPE(SHOOTER_PITCH_MOTOR);

	pitchEncoder = new Encoder(SHOOTER_PITCH_ENCODER, false, Encoder::k4X);
	pitchEncoder->SetDistancePerPulse(SHOOTER_PITCH_DEGREES_PER_PULSE);
	pitchEncoder->Reset();
	pitchEncoder->Start();

	pitchLimitSwitch = new DigitalInput(SHOOTER_PITCH_LIMIT_SWITCH);

	LiveWindow::GetInstance()->AddSensor("ShooterPitch", "Pitch Encoder",
			pitchEncoder);
	LiveWindow::GetInstance()->AddSensor("ShooterPitch", "Pitch Limit Switch",
			pitchLimitSwitch);
	LiveWindow::GetInstance()->AddActuator("ShooterPitch", "Pitch Motor",
			pitchMotor);

	tunedEncoder = isPitchGrounded();
	printf("Done!\n");
}

ShooterPitch::~ShooterPitch() {
	delete pitchLimitSwitch;
	delete pitchMotor;
	delete pitchEncoder;
}

bool ShooterPitch::setPitchMotorSpeed(float direction) {
	float speed = fsign(direction);
	if (pitchEncoder->GetDistance() < SHOOTER_PITCH_SLOWDOWN_RANGE && speed
			< 0.0) {
		speed *= SHOOTER_PITCH_SLOWDOWN_SPEED;
	} else {
		speed *= SHOOTER_PITCH_SPEED;
	}
	if (speed < 0.0 && isPitchGrounded()) {
		pitchMotor->Set(0);
		pitchEncoder->Reset();
		tunedEncoder = true;
		return false;
	} else if (speed > 0.0 && pitchEncoder->GetDistance()
			> SHOOTER_PITCH_UPPER_LIMIT) {
		pitchMotor->Set(0);
		return false;
	} else if (tunedEncoder || speed < 0.0) {
		pitchMotor->Set(-speed);
	}
	return true;
}

float ShooterPitch::getCurrentPitch() {
	return pitchEncoder->GetDistance();
}

bool ShooterPitch::isPitchGrounded() {
	return pitchLimitSwitch->Get() & 1;
}

void ShooterPitch::InitDefaultCommand() {
	SetDefaultCommand(new ChangeShooterPitch(getCurrentPitch()));
}

