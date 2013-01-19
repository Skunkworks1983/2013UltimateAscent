#include "CollectorChangePosition.h"

CollectorChangePosition::CollectorChangePosition() {
	Requires(collector);
}

void CollectorChangePosition::Initialize() {
}

void CollectorChangePosition::Execute() {
	
}

bool CollectorChangePosition::IsFinished() {
	return true;
}

void CollectorChangePosition::End() {
}

void CollectorChangePosition::Interrupted() {
}

bool CollectorChangePosition::IsInterruptible() {
	return false;
}
