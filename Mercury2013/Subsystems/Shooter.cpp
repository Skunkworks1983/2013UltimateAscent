#include "Shooter.h"
#include <math.h>
#include "../Utils/Time.h"

Shooter::Shooter() :
	Subsystem("Shooter") {
	// TODO frontMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_FRONT);
	// TODO middleMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_MIDDLE);
	// TODO rearMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_REAR);

	// TODO pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);

	// TODO pitchEncoder = new Encoder(SHOOTER_PITCH_ENCODER, false, Encoder::k4x);
	// TODO pitchEncoder->SetDistancePerPulse(SHOOTER_PITCH_DEGREES_PER_PULSE);
	// TODO pitchEncoder->Reset();

	// TODO shootSolenoid = new DoubleSolenoid(SHOOTER_EXTENDED, SHOOTER_DEXTENDED);

	timeTillShootReady = 0;
}

Shooter::~Shooter() {
	delete frontMotor;
	delete middleMotor;
	delete rearMotor;

	delete pitchMotor;
	delete pitchEncoder;

	delete shootSolenoid;
}

void Shooter::setArmed(bool armed) {
	if (armed) {
		frontMotor->Set(SHOOTER_MOTOR_FRONT_SPEED);
		middleMotor->Set(SHOOTER_MOTOR_MIDDLE_SPEED);
		rearMotor->Set(SHOOTER_MOTOR_REAR_SPEED);
		timeTillShootReady = getCurrentMillis() + SHOOTER_ARM_TIME;
	} else {
		frontMotor->Set(0);
		middleMotor->Set(0);
		rearMotor->Set(0);
	}
}

bool Shooter::isArmed() {
	return ((frontMotor->Get() > 0) && (middleMotor->Get() > 0)
			&& (rearMotor->Get() > 0));
}

void Shooter::shoot(bool shooting) {
	if (shootSolenoid->Get() != (shooting ? DoubleSolenoid::kForward
			: DoubleSolenoid::kReverse) && (!shooting || readyToShoot())) {
		shootSolenoid->Set(
				shooting ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
		timeTillShootReady = getCurrentMillis() + SHOOTER_WAIT_TIME;
	}
}

void Shooter::flush(bool flushing) {
	if ((shootSolenoid->Get() == DoubleSolenoid::kReverse) && !isArmed()) {
		if (flushing) {
			rearMotor->Set(SHOOTER_MOTOR_FLUSH_SPEED);
		} else {
			rearMotor->Set(0);
		}
	}
}

bool Shooter::readyToShoot() {
	return getCurrentMillis() > timeTillShootReady;
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

