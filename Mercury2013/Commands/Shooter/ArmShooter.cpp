#include "ArmShooter.h"
#include "../../Utils/Time.h"

ArmShooter::ArmShooter(ArmType armType) :
	CommandBase("ArmShooter") {
	Requires(shooter);
	this->armType = armType;
}

void ArmShooter::Initialize() {
	switch (armType) {
	case kOn:
		enabled = true;
		break;
	case kOff:
		enabled = false;
		break;
	case kToggle:
		enabled = !shooter->isArmed();
		break;
	default:
		enabled = false;
	}
}

void ArmShooter::Execute() {
	shooter->setArmed(enabled);
}

bool ArmShooter::IsFinished() {
	return shooter->isArmed() == enabled;
}

void ArmShooter::End() {

}

void ArmShooter::Interrupted() {

}
