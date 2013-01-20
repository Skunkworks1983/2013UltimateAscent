#include "Shift.h"

Shift::Shift(ShiftType toGear) {
	//It requires the drive base, but we don't need a lock on it.
	this->toGear = toGear;
	toLowGear = false;
}

void Shift::Initialize() {
	switch (toGear) {
	case kLow:
		toLowGear = true;
		break;
	case kHigh:
		toLowGear = false;
		break;
	case kToggle:
		toLowGear = !driveBase->isLowGear();
		break;
	default:
		toLowGear = true;
		break;
	}
}

void Shift::Execute() {
	driveBase->shift(toLowGear & 1);
}

bool Shift::IsFinished() {
	return driveBase->isLowGear() == toLowGear;
}

void Shift::End() {
}

void Shift::Interrupted() {
}

bool Shift::IsInterruptible() {
	return true;
}
