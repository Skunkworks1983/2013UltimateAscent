#include "Collect.h"

Collect::Collect(bool timesOut) :
	CommandBase("Collect") {
	Requires(collector);
	SetTimeout(timesOut ? ((double) COLLECTOR_COLLECT_TIMEOUT) / 1000.0 : 999999999.0);
	SetInterruptible(true);
}

Collect::~Collect() {

}

void Collect::Initialize() {
}

void Collect::Execute() {
	collector->setCollectorMotor(Collector::kForward);
}

bool Collect::IsFinished() {
	return collector->getFrisbeeSensorCount() != 0 || IsTimedOut();
}

void Collect::End() {
	collector->setCollectorMotor(Collector::kStop);
}

void Collect::Interrupted() {
	collector->setCollectorMotor(Collector::kStop);
}
