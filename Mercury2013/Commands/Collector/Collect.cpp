#include "Collect.h"

Collect::Collect() {
	Requires(collector);
	SetTimeout(((double) COLLECTOR_COLLECT_TIMEOUT) / 1000.0);
	SetInterruptible(true);
}

Collect::~Collect() {

}

void Collect::Initialize() {
}

void Collect::Execute() {
	collector->setCollectorMotor(collector->getFrisbeeSensorCount() != 0);
}

bool Collect::IsFinished() {
	return collector->isSpinnerOn() && !IsTimedOut();
}

void Collect::End() {
	collector->setCollectorMotor(false);
}

void Collect::Interrupted() {
	collector->setCollectorMotor(false);
}
