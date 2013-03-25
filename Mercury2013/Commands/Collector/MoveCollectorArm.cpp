#include "MoveCollectorArm.h"

MoveCollectorArm::MoveCollectorArm(float goal) :
	CommandBase(CommandBase::createNameFromFloat("MoveCollectorArm", goal)) {
	Requires(collectorArms);
	this->goal = goal;
}

MoveCollectorArm::~MoveCollectorArm() {
}

void MoveCollectorArm::Initialize() {
	collectorArms->setPIDState(true);
	collectorArms->setSetpoint(goal);
	stability = 0;
}

void MoveCollectorArm::Execute() {
	//Wait for the PID controller...
	if (collectorArms->isPIDDone()) {
		stability++;
	} else {
		stability = 0;
	}
}

bool MoveCollectorArm::IsFinished() {
	//(Shooter interferes && (Passing positive || Passing negative))
	if (shooterPitch->getCurrentPitch() > SHOOTER_COLLECTOR_INTERFERENCE_LOW
			&& shooterPitch->getCurrentPitch()
					< SHOOTER_COLLECTOR_INTERFERENCE_HIGH && ((goal
			> COLLECTOR_SHOOTER_INTERFERENCE_LOW && collectorArms->getAngle()
			< COLLECTOR_SHOOTER_INTERFERENCE_HIGH) || (goal
			< COLLECTOR_SHOOTER_INTERFERENCE_HIGH && collectorArms->getAngle()
			> COLLECTOR_SHOOTER_INTERFERENCE_LOW))) {
		return true;
	} else {
		return stability >= COLLECTOR_PITCH_STABILITY;
	}
}

void MoveCollectorArm::End() {
	collectorArms->setPIDState(false);
}

void MoveCollectorArm::Interrupted() {
	collectorArms->setPIDState(false);
}
