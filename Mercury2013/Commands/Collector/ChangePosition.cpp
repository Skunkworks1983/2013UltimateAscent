#include "ChangePosition.h"

ChangePosition::ChangePosition(ChangeType goal) :
	CommandBase("ChangePosition") {
	Requires(collector);
	this->goal = goal;
}

ChangePosition::~ChangePosition() {
}

void ChangePosition::Initialize() {
	collector->setPIDState(true);
	switch (goal) {
	case kUp:
		targetState = Collector::kUp;
		collector->setSetpoint(COLLECTOR_PITCH_UP);
		break;
	case kDown:
		targetState = Collector::kDown;
		collector->setSetpoint(COLLECTOR_PITCH_DOWN);
		break;
	case kToggle:
		targetState = (collector->getArmState() & 1) ? Collector::kDown
				: Collector::kUp;
		collector ->setSetpoint(
				(collector->getArmState() & 1) ? COLLECTOR_PITCH_DOWN
						: COLLECTOR_PITCH_UP);
		break;
	default:
		collector->setPIDState(false);
		break;
	}
}

void ChangePosition::Execute() {
	//Wait for the PID controller...
}

bool ChangePosition::IsFinished() {
	return collector->isPIDDone() || collector->getArmState() == targetState;
}

void ChangePosition::End() {
	collector->setPIDState(false);
	collector->PIDWrite(0);
}

void ChangePosition::Interrupted() {
	collector->setPIDState(false);
	collector->PIDWrite(0);
}
