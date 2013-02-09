#include "ArmShooter.h"
#include "../../Utils/Time.h"

ArmShooter::ArmShooter(ArmType armType) :
	CommandBase("ArmShooter") {
	Requires(shooter);
	this->armType = armType;
}

void ArmShooter::Initialize() {
	startTime = getCurrentMillis();
	switch(armType) {
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
	return (getCurrentMillis() >= startTime + SHOOTER_ARM_TIME) && (shooter->isArmed() == enabled);
}

void ArmShooter::End() {

}

void ArmShooter::Interrupted() {

}
