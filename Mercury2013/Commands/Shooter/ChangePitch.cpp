#include "ChangePitch.h"
#include <math.h>

ChangePitch::ChangePitch(float targetPitch) :
	CommandBase("ChangePitch") {
	Requires(shooterPitch);
	SetInterruptible(true);
	this->targetPitch = targetPitch;
	this->outOfBounds = false;
}

void ChangePitch::Initialize() {

}

void ChangePitch::Execute() {
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

bool ChangePitch::IsFinished() {
	return false;//outOfBounds;
}

void ChangePitch::End() {
	shooterPitch->setPitchMotorSpeed(0);
}

void ChangePitch::Interrupted() {
	shooterPitch->setPitchMotorSpeed(0);
}
