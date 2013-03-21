#include "SetScalingFactor.h"
#include <math.h>

SetScalingFactor::SetScalingFactor(float factor) :
	CommandBase("SetScalingFactor") {
	this->scalingFactor = factor;
}

void SetScalingFactor::Initialize() {
	if (fabs(driveBase->getLeftEncoder()->GetRate()) < DRIVE_SCALING_MINSPEED
			&& fabs(driveBase->getRightEncoder()->GetRate())
					< DRIVE_SCALING_MINSPEED) {
		driveBase->setMotorScalingFactor(this->scalingFactor);
	}
}

void SetScalingFactor::Execute() {
}

bool SetScalingFactor::IsFinished() {
	return true;
}

void SetScalingFactor::End() {
}

void SetScalingFactor::Interrupted() {
}
