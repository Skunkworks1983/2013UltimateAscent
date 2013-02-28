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
	updateStability = 0;

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
	switch (controlScheme) {
	case kPower:
	case kPowerBang:
	case kPowerBangNoWait:
	case kPowerNoWait:
		if (armed) {
			frontMotor->Set(SHOOTER_MOTOR_FRONT_SPEED);
			middleMotor->Set(SHOOTER_MOTOR_MIDDLE_SPEED);
			rearMotor->Set(SHOOTER_MOTOR_REAR_SPEED);
			timeTillShootReady = getCurrentMillis() + SHOOTER_ARM_TIME;
		}
		break;
	case kSpeed:
		if (armed) {
			controlLoop->StartPeriodic(SHOOTER_MOTOR_UPDATE_SPEED);
		} else {
			controlLoop->Stop();
		}
		break;
	}
	if (!armed) {
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
			if (controlScheme == kPowerBang || controlScheme
					== kPowerBangNoWait) {
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
	switch (controlScheme) {
	case kSpeed:
		return updateStability > SHOOTER_MOTOR_RPM_STABILITY;
	case kPowerNoWait:
	case kPowerBangNoWait:
		return true;
	default:
		return getCurrentMillis() > timeTillShootReady;
	}
}

void Shooter::InitDefaultCommand() {
}

void Shooter::callUpdateMotors(void *shooter) {
	((Shooter*) shooter)->updateMotors();
}

void Shooter::updateMotor(AnalogChannel *src, SpeedController *dst,
		float target) {
	float offset = target - SHOOTER_ENCODER_CONVERT(src->GetAverageValue());
	dst->Set(offset < 0 ? 1.0 : -1.0);
	if (fabs(offset) < SHOOTER_MOTOR_RPM_THRESHOLD) {
		updateStability++;
	} else {
		updateStability = 0;
	}
}

void Shooter::updateMotors() {
	if (controlScheme == kSpeed) {
		updateMotor(frontSpeed, frontMotor, SHOOTER_MOTOR_FRONT_RPM);
		updateMotor(frontSpeed, frontMotor, SHOOTER_MOTOR_MIDDLE_RPM);
		updateMotor(frontSpeed, frontMotor, SHOOTER_MOTOR_REAR_RPM);
	}
}
