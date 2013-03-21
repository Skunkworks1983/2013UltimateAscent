#include "ChangeShooterPitch.h"
#include <math.h>

ChangeShooterPitch::ChangeShooterPitch(float targetPitch, bool waitForCollector) :
	CommandBase("ChangeShooterPitch") {
	Requires(shooterPitch);
	SetInterruptible(true);
	this->targetPitch = targetPitch;
	if (this->targetPitch < 0.01){
		this->targetPitch = -10.0;
	}
	if (this->targetPitch > 1.0) {
		this->targetPitch = 1.0;
	}
	this->outOfBounds = false;
	this->waitForCollector = waitForCollector;
}

void ChangeShooterPitch::Initialize() {
}

void ChangeShooterPitch::Execute() {
	if (collectorArms->getAngle() > COLLECTOR_SHOOTER_INTERFERENCE_LOW
			&& collectorArms->getAngle() < COLLECTOR_SHOOTER_INTERFERENCE_HIGH
			&& targetPitch > SHOOTER_COLLECTOR_INTERFERENCE_LOW && targetPitch
			< SHOOTER_COLLECTOR_INTERFERENCE_HIGH) {
		outOfBounds = !waitForCollector;
		return;
	}
	float pitchOffset = shooterPitch->getCurrentPitch() - targetPitch;
	if (pitchOffset > 0 && fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		shooterPitch->setPitchMotorSpeed(0);
		outOfBounds = true;
	} else {
		outOfBounds = !shooterPitch->setPitchMotorSpeed(
				pitchOffset < 0 ? 1 : -1);
	}
}

bool ChangeShooterPitch::IsFinished() {
	return !shooterPitch->isPitchTuned() || outOfBounds;
}

void ChangeShooterPitch::End() {
	shooterPitch->setPitchMotorSpeed(0);
}

void ChangeShooterPitch::Interrupted() {
	shooterPitch->setPitchMotorSpeed(0);
}
