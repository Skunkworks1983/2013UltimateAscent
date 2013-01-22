#include "Shooter.h"
#include <math.h>

Shooter::Shooter() :
	Subsystem("Shooter") {
	shooterMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR);
	pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);
	speedEncoder = new Encoder(SHOOTER_SPEED_ENCODER_PORTS, false, Encoder::k4X);
	pitchPot = new AnalogChannel(SHOOTER_PITCH_POT_PORT);
	
	motorUpdateLoop = new Notifier(Shooter::callUpdateMotors,this);
}

Shooter::~Shooter() {
	delete shooterMotor;
	delete pitchMotor;
	delete speedEncoder;
	delete pitchPot;

	delete motorUpdateLoop;
}

void Shooter::startUpdateLoop() {
	motorUpdateLoop->StartPeriodic(SHOOTER_MOTOR_UPDATE_SPEED);
}

void Shooter::endUpdateLoop() {
	motorUpdateLoop->Stop();
}

void Shooter::InitDefaultCommand() {
	//No default command.  The update loop is a seperate task.
}

void Shooter::setTargetPitch(float degree) {
	targetPitch = degree;
}

float Shooter::getCurrentPitch() {
	//TODO Conversion
	return pitchPot->GetValue();
}

bool Shooter::isPitchStable() {
	return pitchStability >= SHOOTER_PITCH_STABILITY;
}

float Shooter::getCurrentSpeed() {
	return speedEncoder->GetRate(); //TODO Conversion
}

void Shooter::setTargetSpeed(float rpm) {
	targetSpeed = rpm;
}

bool Shooter::isSpeedStable() {
	return speedStability >= SHOOTER_SPEED_STABILITY;
}

void Shooter::callUpdateMotors(void* shooter) {
	((Shooter*) shooter)->updateMotors();
}

void Shooter::updateMotors() {
	if (targetSpeed > SHOOTER_SPEED_THRESHOLD) {
		float speedOffset = targetSpeed - getCurrentSpeed();
		if (speedOffset > 0) {
			shooterMotor->Set(1);
		} else if (speedOffset < 0) {
			shooterMotor->Set(-1);
		} else {
			shooterMotor->Set(0);
		}
		if (fabs(speedOffset) < SHOOTER_SPEED_THRESHOLD) {
			speedStability++;
		} else {
			speedStability = 0;
		}
	}

	float pitchOffset = targetPitch - getCurrentPitch();
	if (fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		pitchMotor->Set(0);
		pitchStability++;
	} else {
		pitchMotor->Set(pitchOffset < 0 ? 1 : -1);
		pitchStability = 0;
	}
}
