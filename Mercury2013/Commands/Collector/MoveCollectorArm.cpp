#include "MoveCollectorArm.h"

MoveCollectorArm::MoveCollectorArm(float goal) :
	CommandBase("MoveCollectorArm") {
	Requires(collector);
	this->goal = goal;
}

MoveCollectorArm::~MoveCollectorArm() {
}

void MoveCollectorArm::Initialize() {
	collector->setPIDState(true);
	collector->setSetpoint(goal);
}

void MoveCollectorArm::Execute() {
	//Wait for the PID controller...
}

bool MoveCollectorArm::IsFinished() {
	if ((goal > COLLECTOR_SHOOTER_INTERFERENCE_LOW && shooterPitch->getCurrentPitch() >= SHOOTER_PITCH_UPPER_LIMIT)) {
		return true;
	} else {
		return collector->isPIDDone();
	}
}

void MoveCollectorArm::End() {
	collector->setPIDState(false);
}

void MoveCollectorArm::Interrupted() {
	collector->setPIDState(false);
}
