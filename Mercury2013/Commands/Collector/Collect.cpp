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
		if (collector->getSense(0) == false){
			collector->setCollectorState(true);
		}
		break;
	case off:
		if (collector->getSense(0) == false){
			collector->setCollectorState(false);
		}
		break;
	case toggle:
		if (collector->isUp() == true) && (collector->getSense(0) == false){
			collector->setCollectorSpeed(false);
		} else {
			if (collector->getSense(0) == false){
				collector->setCollectorState(true);
			}
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
