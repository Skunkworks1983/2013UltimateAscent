#include "Collect.h"

Collect::Collect() {
	Requires(driveBase);
}

void Collect::Initialize() {
}

void Collect::Execute() {
	if (position != getPosition()){
			collectorPitchMotor->Set();
		}
}

bool Collect::IsFinished() {
	return true;
}

void Collect::End() {
}

void Collect::Interrupted() {
}

bool Collect::IsInterruptible() {
	return false;
}
