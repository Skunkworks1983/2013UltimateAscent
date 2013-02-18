#include "Shooter.h"
#include <math.h>
#include "../Utils/Time.h"
#include "../Utils/SolenoidPair.h"

Shooter::Shooter() :
	Subsystem("Shooter") {
	printf("Creating Shooter...\t");
	frontMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_FRONT);
	middleMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_MIDDLE);
	rearMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR_REAR);

	pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);

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
			pitchEncoder);
	LiveWindow::GetInstance()->AddActuator("Shooter", "Pitch Motor",
			pitchMotor);
	printf("Done!\n");
	

	Preferences::GetInstance()->PutFloat(
					"SHOOTER_MOTOR_FRONT_SPEED",SHOOTER_MOTOR_FRONT_SPEED);
	Preferences::GetInstance()->PutFloat(
					"SHOOTER_MOTOR_MIDDLE_SPEED",SHOOTER_MOTOR_MIDDLE_SPEED);
	Preferences::GetInstance()->PutFloat(
					"SHOOTER_MOTOR_REAR_SPEED",SHOOTER_MOTOR_REAR_SPEED);
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
		frontMotor->Set(
				Preferences::GetInstance()->GetFloat(
						"SHOOTER_MOTOR_FRONT_SPEED"));
		//SHOOTER_MOTOR_FRONT_SPEED);
		middleMotor->Set(
				Preferences::GetInstance()->GetFloat(
						"SHOOTER_MOTOR_MIDDLE_SPEED"));
		//SHOOTER_MOTOR_MIDDLE_SPEED);
		rearMotor->Set(
				Preferences::GetInstance()->GetFloat(
						"SHOOTER_MOTOR_REAR_SPEED"));
		//SHOOTER_MOTOR_REAR_SPEED);
		timeTillShootReady = getCurrentMillis() + SHOOTER_ARM_TIME;
	} else {
		frontMotor->Set(0);
		middleMotor->Set(0);
		rearMotor->Set(0);
	}
}

bool Shooter::isArmed() {
	return fabs(frontMotor->Get()) > 0 || fabs(middleMotor->Get()) > 0
			|| fabs(rearMotor->Get()) > 0;
}

void Shooter::shoot(bool shooting) {
	if (shootSolenoid->Get() != shooting && (!shooting || readyToShoot())) {
		shootSolenoid->Set(shooting);
		timeTillShootReady = getCurrentMillis() + SHOOTER_WAIT_TIME;
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

void Shooter::setPitchMotorSpeed(float speed) {
	pitchMotor->Set(speed);
}

float Shooter::getCurrentPitch() {
	// TODO Conversion
	return pitchEncoder->GetDistance();
}

void Shooter::InitDefaultCommand() {

}

