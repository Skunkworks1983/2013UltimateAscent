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
	return collector->isPIDDone();
}

void MoveCollectorArm::End() {
	collector->setPIDState(false);
}

void MoveCollectorArm::Interrupted() {
	collector->setPIDState(false);
}
