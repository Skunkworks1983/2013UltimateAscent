#include "FlagControl.h"
#include "../../Utils/Time.h"

FlagControl::FlagControl(FlagControlType type) :
	CommandBase("Collect") {
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
		this->destinationState = collector->getFrisbeeStop();
		break;
	case kFlagAutoDown:
		break;
	default:
		this->destinationState = false;
	}
}

void FlagControl::Execute() {
	if (controlType == kFlagAutoDown) {
		if (shooterPitch->getRealPitch() > SHOOTER_PITCH_FRISBEE_SLIDE) {
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
	return collector->getFrisbeeSensorCount() != 0 || IsTimedOut();
}

void FlagControl::End() {
	collector->setCollectorMotor(Collector::kStop);
}

void FlagControl::Interrupted() {
	collector->setCollectorMotor(Collector::kStop);
}
