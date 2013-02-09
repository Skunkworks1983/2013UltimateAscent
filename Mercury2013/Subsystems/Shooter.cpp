#include "Shooter.h"
#include <math.h>

Shooter::Shooter() :
	Subsystem("Shooter") {
	// TODO frontMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_FRONT);
	// TODO middleMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_MIDDLE);
	// TODO rearMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_REAR);

	// TODO pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);
	// TODO pitchPot = new AnalogChannel(SHOOTER_PITCH_POT_PORT);
	
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
	delete pitchPot;
	
	delete shooterExtended;
	delete shooterDextended;

	LiveWindow::GetInstance()->AddSensor("DriveBase", "PitchPot", pitchPot);
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
	return pitchPot->GetValue();
}



