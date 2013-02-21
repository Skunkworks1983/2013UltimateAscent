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
	double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
	targetPitch
			= OI_SHOOTER_ANGLE_CONVERT(val);
	float pitchOffset = shooterPitch->getCurrentPitch() - targetPitch;
	if (fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		shooterPitch->setPitchMotorSpeed(0);
		outOfBounds = true;
	} else {
		outOfBounds = !shooterPitch->setPitchMotorSpeed(pitchOffset < 0 ? 1 : -1);
	}
}

bool ChangeShooterPitch::IsFinished() {
	return false;//outOfBounds;
}

void ChangeShooterPitch::End() {
	shooterPitch->setPitchMotorSpeed(0);
}

void ChangeShooterPitch::Interrupted() {
	shooterPitch->setPitchMotorSpeed(0);
}
