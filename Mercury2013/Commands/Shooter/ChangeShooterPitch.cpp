#include "ChangeShooterPitch.h"
#include <math.h>

ChangeShooterPitch::ChangeShooterPitch(float targetPitch) :
	CommandBase("ChangeShooterPitch") {
	Requires(shooterPitch);
	SetInterruptible(true);
	this->targetPitch = targetPitch;
	this->outOfBounds = false;
}

void ChangeShooterPitch::Initialize() {
}

void ChangeShooterPitch::Execute() {
	double tmpTarget = targetPitch;
	if (targetPitch < 0) {
		if (DriverStation::GetInstance()->GetEnhancedIO().GetDigital(15)) {
			return;
		}
		double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
				OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
		tmpTarget = OI_SHOOTER_ANGLE_CONVERT(val);
	}
	if (collectorArms->getAngle() > COLLECTOR_SHOOTER_INTERFERENCE_LOW
			&& collectorArms->getAngle() < COLLECTOR_SHOOTER_INTERFERENCE_HIGH
			&& tmpTarget > SHOOTER_COLLECTOR_INTERFERENCE_LOW && tmpTarget
			< SHOOTER_COLLECTOR_INTERFERENCE_HIGH) {
		outOfBounds = true;
		return;
	}
	float pitchOffset = shooterPitch->getCurrentPitch() - tmpTarget;
	if (fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		shooterPitch->setPitchMotorSpeed(0);
		outOfBounds = true;
	} else {
		outOfBounds = !shooterPitch->setPitchMotorSpeed(
				pitchOffset < 0 ? 1 : -1);
	}
}

bool ChangeShooterPitch::IsFinished() {
	return !shooterPitch->isPitchTuned() || (outOfBounds && targetPitch >= 0.0);
}

void ChangeShooterPitch::End() {
	shooterPitch->setPitchMotorSpeed(0);
}

void ChangeShooterPitch::Interrupted() {
	shooterPitch->setPitchMotorSpeed(0);
}
