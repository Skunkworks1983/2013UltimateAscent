#include "ChangePitch.h"
#include <math.h>

ChangePitch::ChangePitch(float targetPitch) :
	CommandBase("ChangePitch") {
	Requires(shooter);
	this->targetPitch = targetPitch;
	this->outOfBounds = false;
}

void ChangePitch::Initialize() {

}

void ChangePitch::Execute() {
	targetPitch
			= OI_SHOOTER_ANGLE_CONVERT(DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(OI_SHOOTER_ANGLE_PROVIDER_CHANNEL));
	float pitchOffset = shooter->getCurrentPitch() - targetPitch;
	if (fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		shooter->setPitchMotorSpeed(0);
		outOfBounds = true;
	} else {
		outOfBounds = !shooter->setPitchMotorSpeed(pitchOffset < 0 ? 1 : -1);
	}
}

bool ChangePitch::IsFinished() {
	return false;//outOfBounds;
}

void ChangePitch::End() {
	shooter->setPitchMotorSpeed(0);
}

void ChangePitch::Interrupted() {
	shooter->setPitchMotorSpeed(0);
}
