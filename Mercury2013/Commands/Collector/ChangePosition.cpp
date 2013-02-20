#include "ChangePosition.h"

ChangePosition::ChangePosition(float goal) :
	CommandBase("ChangePosition") {
	Requires(collector);
	this->goal = goal;
}

ChangePosition::~ChangePosition() {
}

void ChangePosition::Initialize() {
	collector->setPIDState(true);
	collector->setSetpoint(goal);
}

void ChangePosition::Execute() {
	//Wait for the PID controller...
}

bool ChangePosition::IsFinished() {
	return collector->isPIDDone();
}

void ChangePosition::End() {
	collector->setPIDState(false);
}

void ChangePosition::Interrupted() {
	collector->setPIDState(false);
}
