#include "Shooter.h"
#include <math.h>
#include "../Utils/Math.h"
#include "../Utils/Time.h"
#include "../Utils/SolenoidPair.h"

Shooter::Shooter() :
	Subsystem("Shooter") {
	printf("Creating Shooter...\t");
	frontMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_FRONT);
	middleMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_MIDDLE);
	rearMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_REAR);

	pitchMotor = new SHOOTER_PITCH_MOTOR_TYPE(SHOOTER_PITCH_MOTOR);

	pitchEncoder = new Encoder(SHOOTER_PITCH_ENCODER, false, Encoder::k4X);
	pitchEncoder->SetDistancePerPulse(SHOOTER_PITCH_DEGREES_PER_PULSE);
	pitchEncoder->Reset();
	pitchEncoder->Start();

	pitchLimitSwitch = new DigitalInput(SHOOTER_PITCH_LIMIT_SWITCH);

	shootSolenoid = new SolenoidPair(SHOOTER_PNEUMATIC);

	timeTillShootReady = 0;

	LiveWindow::GetInstance()->AddSensor("Shooter", "Pitch Encoder",
			pitchEncoder);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Pitch Limit Switch",
			pitchLimitSwitch);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Shoot Solenoid",
			shootSolenoid);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Pitch Motor",
			pitchMotor);

	tunedEncoder = false;
	printf("Done!\n");
}

Shooter::~Shooter() {
	delete frontMotor;
	delete middleMotor;
	delete rearMotor;

	delete pitchLimitSwitch;
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
	return fabs(frontMotor->Get()) > 0 || fabs(middleMotor->Get()) > 0 || fabs(
			rearMotor->Get()) > 0;
}

void Shooter::shoot(bool shooting) {
	if (shootSolenoid->Get() != shooting && (!shooting || readyToShoot())) {
		shootSolenoid->Set(shooting);
		timeTillShootReady = getCurrentMillis() + SHOOTER_WAIT_TIME;
		if (shooting) {
			frontMotor->Set(SHOOTER_MOTOR_FRONT_BANG_SPEED);
			middleMotor->Set(SHOOTER_MOTOR_MIDDLE_BANG_SPEED);
			rearMotor->Set(SHOOTER_MOTOR_REAR_BANG_SPEED);
		} else {
			frontMotor->Set(SHOOTER_MOTOR_FRONT_SPEED);
			middleMotor->Set(SHOOTER_MOTOR_MIDDLE_SPEED);
			rearMotor->Set(SHOOTER_MOTOR_REAR_SPEED);
		}
	}
}

void Shooter::flush(bool flushing) {
	if (!shootSolenoid->Get() && !isArmed()) {
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

bool Shooter::setPitchMotorSpeed(float direction) {
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

float Shooter::getCurrentPitch() {
	return pitchEncoder->GetDistance();
}

bool Shooter::isPitchGrounded() {
	return pitchLimitSwitch->Get() & 1;
}

void Shooter::InitDefaultCommand() {
}

