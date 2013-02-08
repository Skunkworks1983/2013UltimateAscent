#include "Shooter.h"
#include <math.h>

Shooter::Shooter() :
	Subsystem("Shooter") {
	// TODO shooterMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR);
	// TODO pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);
	// TODO speedEncoder = new Encoder(SHOOTER_SPEED_ENCODER_PORTS, false, Encoder::k4X);
	// TODO pitchPot = new AnalogChannel(SHOOTER_PITCH_POT_PORT);

	motorUpdateLoop = new Notifier(Shooter::callUpdateMotors,this);

	armed = false;
}

Shooter::~Shooter() {
	delete shooterMotor;
	delete pitchMotor;
	delete speedEncoder;
	delete pitchPot;

	delete motorUpdateLoop;
	LiveWindow::GetInstance()->AddSensor("DriveBase", "SpeedEncoder",
			speedEncoder);
	LiveWindow::GetInstance()->AddSensor("DriveBase", "PitchPot",
			pitchPot);
}

void Shooter::startUpdateLoop() {
	motorUpdateLoop->StartPeriodic(SHOOTER_MOTOR_UPDATE_SPEED);
}

void Shooter::endUpdateLoop() {
	motorUpdateLoop->Stop();
}

void Shooter::InitDefaultCommand() {
	// No default command.  The update loop is a seperate task.
}

void Shooter::setTargetPitch(float degree) {
	targetPitch = degree;
}

float Shooter::getCurrentPitch() {
	// TODO Conversion
	return pitchPot->GetValue();
}

void Shooter::setPitchMotorSpeed(float speed) {
	pitchMotor->Set(speed);
}

bool Shooter::isPitchStable() {
	return pitchStability >= SHOOTER_PITCH_STABILITY;
}

float Shooter::getCurrentSpeed() {
	return speedEncoder->GetRate(); // TODO Conversion
}

void Shooter::setTargetSpeed(float rpm) {
	targetSpeed = rpm;
}

float Shooter::getTargetSpeed() {
	return targetSpeed;
}

bool Shooter::isSpeedStable() {
	return speedStability >= SHOOTER_SPEED_STABILITY;
}

bool Shooter::isArmed() {
	return armed;
}

void Shooter::setArmed(bool armed) {
	if (this->armed && !armed) {
		speedEncoder->Stop();
	} else if (!this->armed && armed) {
		speedEncoder->Start();
	}
	this->armed = armed;
}

void Shooter::callUpdateMotors(void* shooter) {
	((Shooter*) shooter)->updateMotors();
}

void Shooter::updateMotors() {
	if (armed && targetSpeed > SHOOTER_SPEED_THRESHOLD) { // If target speed is close to zero, don't do any processing
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
}
