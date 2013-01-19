#include "Collect.h"

Collect::Collect(State state) {
	Requires(collector);
	this->mode = state;
}

Collect::~Collect() {

}

void Collect::Initialize() {

}

void Collect::Execute() {
	switch (mode) {
	case on:
		collector->setCollectorState(true);
		break;
	case off:
		collector->setCollectorState(false);
		break;
	case toggle:
		if (collector->isUp() == true) {
			collector->setCollectorSpeed(false);
		} else {
			collector->setCollectorState(true);
		}
		break;
	default:
		collector->setCollectorState(true);
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
