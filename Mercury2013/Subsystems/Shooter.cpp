#include "Shooter.h"
#include <math.h>

Shooter::Shooter() :
	Subsystem("Shooter") {
	// TODO frontMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_FRONT);
	// TODO middleMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_MIDDLE);
	// TODO rearMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_REAR);

	// TODO pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);
	
	// TODO pitchEncoder = new Encoder(SHOOTER_PITCH_ENCODER, false, Encoder::k4x);
	// TODO pitchEncoder->SetDistancePerPulse(SHOOTER_PITCH_DEGREES_PER_PULSE);
	// TODO pitchEncoder->Reset();
	
	// TODO shooterExtended = new Solenoid(SHOOTER_EXTENDED);
	// TODO shooterDextended = new Solenoid(SHOOTER_DEXTENDED);

	cachedArmState = false;
	cachedShootState = false;
}

Shooter::~Shooter() {
	delete frontMotor;
	delete middleMotor;
	delete rearMotor;

	delete pitchMotor;
	delete pitchEncoder;
	
	delete shooterExtended;
	delete shooterDextended;

	LiveWindow::GetInstance()->AddSensor("DriveBase", "Pitch Encoder", pitchEncoder);
}

void Shooter::setArmed(bool armed) {
	if (armed) {
		frontMotor->Set(SHOOTER_MOTOR_FRONT_SPEED);
		middleMotor->Set(SHOOTER_MOTOR_MIDDLE_SPEED);
		rearMotor->Set(SHOOTER_MOTOR_REAR_SPEED);
	} else {
		frontMotor->Set(0);
		middleMotor->Set(0);
		rearMotor->Set(0);
	}
	this->cachedArmState = armed;
}

bool Shooter::isArmed() {
	return cachedArmState;
}

void Shooter::shoot(bool shooting) {
	if (shooting != cachedShootState) {
		shooterExtended->Set(shooting);
		shooterDextended->Set(!shooting);
		cachedShootState = shooting;
	}
}

void Shooter::setPitchMotorSpeed(float speed) {
	pitchMotor->Set(speed);
}

float Shooter::getCurrentPitch() {
	// TODO Conversion
	return pitchEncoder->GetDistance();
}

void Shooter::InitDefaultCommand() {
	
}

