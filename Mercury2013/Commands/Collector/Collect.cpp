#include "Collect.h"

Collect::Collect() :
	CommandBase("Collect") {
	Requires(collector);
	SetTimeout(((double) COLLECTOR_COLLECT_TIMEOUT) / 1000.0);
	SetInterruptible(true);
}

Collect::~Collect() {

}

void Collect::Initialize() {
}

void Collect::Execute() {
	collector->setCollectorMotor(true);
}

bool Collect::IsFinished() {
	return /*TODO collector->getFrisbeeSensorCount() != 0 &&*/ IsTimedOut();
}

void Collect::End() {
	collector->setCollectorMotor(false);
}

void Collect::Interrupted() {
	collector->setCollectorMotor(false);
}
