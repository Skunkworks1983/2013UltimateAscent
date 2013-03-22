#include "Shooter.h"
#include <math.h>
#include "../Utils/Math.h"
#include "../Utils/Time.h"
#include "../Utils/SolenoidPair.h"

char* Shooter::getControlTypeName(ControlType type) {
	switch (type) {
	case kPower:
		return "Power";
	case kPowerBang:
		return "PowerBang";
	default:
		return "Unknown";
	}
}
char* Shooter::getWaitTypeName(WaitType type) {
	switch (type) {
	case kSpeed:
		return "Speed";
	case kTime:
		return "Time";
	case kNone:
		return "None";
	default:
		return "Unknown";
	}
}

Shooter::Shooter() :
	Subsystem("Shooter") {
	printf("Creating Shooter...\t");
	frontMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_FRONT);
	middleMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_MIDDLE);
	rearMotor = new SHOOTER_MOTOR_TYPE(SHOOTER_MOTOR_REAR);

	shootSolenoid = new SolenoidPair(SHOOTER_PNEUMATIC);

	timeTillShootReady = 0;
	controlScheme = SHOOTER_DEFAULT_CONTROL;
	waitScheme = SHOOTER_DEFAULT_WAIT;

	// Speed Control
	frontSpeed = new AnalogChannel(SHOOTER_ASPEED_FRONT);
	rearSpeed = new AnalogChannel(SHOOTER_ASPEED_REAR);

	lightController = new Relay(SHOOTER_LIGHT);

	LiveWindow::GetInstance()->AddActuator("Shooter", "Shoot Solenoid",
			shootSolenoid);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Front Motor", frontMotor);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Middle Motor",
			middleMotor);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Rear Motor", rearMotor);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Light", lightController);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Analog Rear Speed",
			rearSpeed);
	LiveWindow::GetInstance()->AddSensor("Shooter", "Analog Front Speed",
			frontSpeed);
	
	armState = false;

	printf("Done!\n");
}

Shooter::~Shooter() {
	delete frontMotor;
	delete middleMotor;
	delete rearMotor;

	delete frontSpeed;
	delete rearSpeed;

	delete shootSolenoid;
	delete lightController;
}

void Shooter::setLight(bool state) {
	lightController->Set(state ? Relay::kForward : Relay::kOff);
}

bool Shooter::isLightOn() {
	return lightController->Get() == Relay::kForward;
}

void Shooter::setArmed(bool armed) {
	switch (controlScheme) {
	case kPower:
	case kPowerBang:
		if (armed) {
			frontMotor->Set(SHOOTER_MOTOR_FRONT_SPEED);
			middleMotor->Set(SHOOTER_MOTOR_MIDDLE_SPEED);
			rearMotor->Set(SHOOTER_MOTOR_REAR_SPEED);
			timeTillShootReady = getCurrentMillis() + SHOOTER_ARM_TIME;
		}
		break;
	default:
		armed = false;
	}
	if (!armed) {
		frontMotor->Set(0);
		middleMotor->Set(0);
		rearMotor->Set(0);
	}
	armState = armed;
}

void Shooter::setControlScheme(ControlType type) {
	controlScheme = type;
}

Shooter::ControlType Shooter::getControlScheme() {
	return controlScheme;
}

void Shooter::setWaitScheme(WaitType type) {
	waitScheme = type;
}

Shooter::WaitType Shooter::getWaitScheme() {
	return waitScheme;
}

bool Shooter::isArmed() {
	/*return fabs(frontMotor->Get()) > 0 || fabs(middleMotor->Get()) > 0 || fabs(
			rearMotor->Get()) > 0;*/
	return armState;
}

void Shooter::shoot(bool shooting) {
	if (!isArmed()) {
		return; //TODO Better
	}
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
	switch (waitScheme) {
	case kSpeed:
		return getFrontSpeed() > SHOOTER_MOTOR_FRONT_RPM && getRearSpeed()
				> SHOOTER_MOTOR_REAR_RPM;
	case kTime:
		return getCurrentMillis() > timeTillShootReady;
	case kNone:
	default:
		return true;
	}
}

double Shooter::getFrontSpeed() {
	return SHOOTER_ASPEED_CONVERT(frontSpeed->GetAverageVoltage());
}

double Shooter::getRearSpeed() {
	return SHOOTER_ASPEED_CONVERT(rearSpeed->GetAverageVoltage());
}

void Shooter::InitDefaultCommand() {
}
