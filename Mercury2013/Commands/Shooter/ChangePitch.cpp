#include "ChangePitch.h"
#include <math.h>

ChangePitch::ChangePitch(float targetPitch) :
	CommandBase("ChangePitch") {
	Requires(shooter);
	pitchStability = 0;
	this->targetPitch = targetPitch;
}

void ChangePitch::Initialize() {

}

void ChangePitch::Execute() {
	float pitchOffset = targetPitch - shooter->getCurrentPitch();
	if (fabs(pitchOffset) < SHOOTER_PITCH_THRESHOLD) {
		shooter->setPitchMotorSpeed(0);
		pitchStability++;
	} else {
		shooter->setPitchMotorSpeed(pitchOffset < 0 ? 1 : -1);
		pitchStability = 0;
	}
}

bool ChangePitch::IsFinished() {
	return pitchStability >= SHOOTER_PITCH_STABILITY;
}

void ChangePitch::End() {
	shooter->setPitchMotorSpeed(0);
}

void ChangePitch::Interrupted() {

}
