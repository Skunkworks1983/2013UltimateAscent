#include "ChangeShooterPitch.h"
#include <math.h>

ChangeShooterPitch::ChangeShooterPitch(float targetPitch, bool waitForCollector) :
			CommandBase(
					CommandBase::createNameFromFloat("ChangeShooterPitch",
							targetPitch)) {
	Requires(shooterPitch);
	SetInterruptible(true);
	this->targetPitch = targetPitch;
	if (this->targetPitch < 0.01) {
		this->targetPitch = -10.0;
	}
	if (this->targetPitch > 1.0) {
		this->targetPitch = 1.0;
	}
	this->waitForCollector = waitForCollector;
}

void ChangeShooterPitch::Initialize() {
	this->stability = 0;
}

void ChangeShooterPitch::Execute() {
	if (collectorArms->getAngle() > COLLECTOR_SHOOTER_INTERFERENCE_LOW
			&& collectorArms->getAngle() < COLLECTOR_SHOOTER_INTERFERENCE_HIGH
			&& targetPitch > SHOOTER_COLLECTOR_INTERFERENCE_LOW && targetPitch
			< SHOOTER_COLLECTOR_INTERFERENCE_HIGH) {
		stability = waitForCollector ? 0 : SHOOTER_PITCH_STABILITY;
		return;
	}
	float pitchOffset = shooterPitch->getCurrentPitch() - targetPitch;
	if (fabs(pitchOffset) <= SHOOTER_PITCH_THRESHOLD) {
		if (fabs(pitchOffset) <= SHOOTER_PITCH_THRESHOLD / 1.25) {
			shooterPitch->setPitchMotorSpeed(0, -1.0);
		} else {
			shooterPitch ->setPitchMotorSpeed(pitchOffset < 0 ? 1 : -1,
					fabs(pitchOffset));
		}
		stability++;
	} else if (targetPitch <= 0.0 && shooterPitch->isPitchGrounded()) {
		shooterPitch->setPitchMotorSpeed(0, -1.0);
		stability = SHOOTER_PITCH_STABILITY;
	} else {
		stability = shooterPitch->setPitchMotorSpeed(pitchOffset < 0 ? 1 : -1,
				fabs(pitchOffset)) ? 0 : SHOOTER_PITCH_STABILITY;
	}
}

bool ChangeShooterPitch::IsFinished() {
	return !shooterPitch->isPitchTuned() || stability
			>= SHOOTER_PITCH_STABILITY;
}

void ChangeShooterPitch::End() {
	printf("End of shooter pitch..\n");
	shooterPitch->setPitchMotorSpeed(0, 0);
}

void ChangeShooterPitch::Interrupted() {
	printf("End of shooter pitch..\n");
	shooterPitch->setPitchMotorSpeed(0, 0);
}
