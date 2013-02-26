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

	shootSolenoid = new SolenoidPair(SHOOTER_PNEUMATIC);

	timeTillShootReady = 0;
	controlScheme = kPowerBang;

	// Speed Control
	frontSpeed = new AnalogChannel(SHOOTER_ENCODER_FRONT);
	middleSpeed = new AnalogChannel(SHOOTER_ENCODER_MIDDLE);
	rearSpeed = new AnalogChannel(SHOOTER_ENCODER_REAR);
	controlLoop = new Notifier(Shooter::callUpdateMotors, this);

	LiveWindow::GetInstance()->AddActuator("Shooter", "Shoot Solenoid",
			shootSolenoid);

	printf("Done!\n");
}

Shooter::~Shooter() {
	delete frontMotor;
	delete middleMotor;
	delete rearMotor;

	delete frontSpeed;
	delete middleSpeed;
	delete rearSpeed;
	delete controlLoop;

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

void Shooter::setControlScheme(ControlType type) {
	controlScheme = type;
}

Shooter::ControlType Shooter::getControlScheme() {
	return controlScheme;
}

bool Shooter::isArmed() {
	return fabs(frontMotor->Get()) > 0 || fabs(middleMotor->Get()) > 0 || fabs(
			rearMotor->Get()) > 0;
}

void Shooter::shoot(bool shooting) {
	if (shootSolenoid->Get() != shooting && (!shooting || readyToShoot())) {
		shootSolenoid->Set(shooting);
		if (isArmed()) {
			timeTillShootReady = getCurrentMillis() + SHOOTER_WAIT_TIME;
			if (controlScheme == kPowerBang) {
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

void Shooter::InitDefaultCommand() {
}

void Shooter::callUpdateMotors(void *shooter) {
	((Shooter*) shooter)->updateMotors();
}

void Shooter::updateMotors() {
	if (controlScheme == kSpeed) {
		//TODO
	}
}
