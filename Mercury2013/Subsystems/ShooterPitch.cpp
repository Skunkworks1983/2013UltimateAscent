#include "ShooterPitch.h"
#include "../Utils/Math.h"
#include "../RobotMap.h"
#include "../Commands/Shooter/ChangeShooterPitch.h"
#include "../Commands/Shooter/TunePitchEncoder.h"
#include "../Utils/JankyAngle.h"
#include "../Utils/StallableMotor.h"

ShooterPitch::ShooterPitch() :
	Subsystem("ShooterPitch") {
	printf("Creating ShooterPitch...\t");

	pitchMotorBackend = new SHOOTER_PITCH_MOTOR_TYPE(SHOOTER_PITCH_MOTOR);

	pitchEncoder = new Encoder(SHOOTER_PITCH_ENCODER, false, Encoder::k4X);
	pitchEncoder->SetDistancePerPulse(SHOOTER_PITCH_DEGREES_PER_PULSE);
	pitchEncoder->Reset();
	pitchEncoder->SetMinRate(SHOOTER_PITCH_DEGREES_PER_PULSE * 256);
	pitchEncoder->Start();
	motorSpeedCache = 0.0;

	pitchPot = new AnalogChannel(SHOOTER_PITCH_POT);

	pitchLimitSwitch = new DigitalInput(SHOOTER_PITCH_LIMIT_SWITCH);

	pitchMotor = new StallableMotor(pitchMotorBackend, pitchEncoder);

	LiveWindow::GetInstance()->AddSensor("Shooter Pitch", "Pitch Encoder",
			pitchEncoder);
	LiveWindow::GetInstance()->AddSensor("Shooter Pitch", "Pitch Limit Switch",
			pitchLimitSwitch);
	/*LiveWindow::GetInstance()->AddActuator("Shooter Pitch", "Pitch Motor",
			pitchMotorBackend);*/
	LiveWindow::GetInstance()->AddSensor("Shooter Pitch", "Analog Pitch",pitchPot);

	tunedEncoder = isPitchGrounded();
	printf("Done!\n");
}

ShooterPitch::~ShooterPitch() {
	delete pitchLimitSwitch;
	delete pitchMotor;
	delete pitchEncoder;
	delete pitchPot;
	delete pitchMotorBackend;
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
		motorSpeedCache = 0.0;
		return false;
	} else if (speed > 0.0 && pitchEncoder->GetDistance()
			> SHOOTER_PITCH_UPPER_LIMIT) {
		pitchMotor->Set(0);
		motorSpeedCache = 0.0;
		return false;
	} else if (tunedEncoder || speed < 0.0) {
		pitchMotor->Set(-speed);
		motorSpeedCache = -speed;
	}
	return true;
}

bool ShooterPitch::isPitchTuned() {
	return tunedEncoder;
}
float ShooterPitch::getCurrentPitch() {
	return pitchEncoder->GetDistance();
}

float ShooterPitch::getRealPitch() {

	return SHOOTER_PITCH_POT_CONVERT(pitchPot->GetAverageVoltage());
}

float ShooterPitch::getMathPitch() {
	return (moreJankyAngle(
			(pitchEncoder->GetDistance() / SHOOTER_PITCH_DEGREES_PER_PULSE
					/ 360.0 / 8.0) + 2) * 180.0) / PI;
}

bool ShooterPitch::isPitchGrounded() {
	return pitchLimitSwitch->Get() & 1;
}

void ShooterPitch::motorSafety() {
	if (isPitchGrounded()) {
		pitchEncoder->Reset();
		if (motorSpeedCache > 0.0) {//pitchMotor->Get() > 0.0) {
			pitchMotor->Set(0);
		}
	}
	pitchMotor->updateController();
}

void ShooterPitch::InitDefaultCommand() {
	//SetDefaultCommand(new ChangeShooterPitch(-1));
}

