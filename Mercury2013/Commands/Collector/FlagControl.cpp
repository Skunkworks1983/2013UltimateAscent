#include "FlagControl.h"
#include "../../Utils/Time.h"

FlagControl::FlagControl(FlagControlType type) :
	CommandBase(CommandBase::createNameFromFloat("FlagControl", type)) {
	this->controlType = type;
}

FlagControl::~FlagControl() {
}

void FlagControl::Initialize() {
	this->complete = false;
	this->anglePassed = -1.0;
	switch (controlType) {
	case kFlagUp:
		this->destinationState = true;
		break;
	case kFlagDown:
		this->destinationState = false;
		break;
	case kFlagToggle:
		this->destinationState = !collector->getFrisbeeStop();
		break;
	case kFlagAutoDown:
		anglePassed = -1.0;
		break;
	default:
		this->destinationState = false;
	}
}

void FlagControl::Execute() {
	if (controlType == kFlagAutoDown) {
		if (shooterPitch->getCurrentPitch() > SHOOTER_PITCH_FRISBEE_SLIDE) {
			if (anglePassed < 0) {
				anglePassed = getCurrentMillis();
			}
		}
		if (anglePassed > 0.0 && getCurrentMillis() - anglePassed
				>= SHOOTER_PITCH_FRISBEE_SLIDE_SPEED) {
			collector->setFrisbeeStop(false);
			complete = true;
		}
	} else {
		collector->setFrisbeeStop(destinationState);
		complete = collector->getFrisbeeStop() == destinationState;
	}
}

bool FlagControl::IsFinished() {
	return complete;
}

void FlagControl::End() {
}

void FlagControl::Interrupted() {
}
