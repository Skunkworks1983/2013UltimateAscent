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
	collector->setSetpoint(COLLECTOR_PITCH_FLOOR);
	collector->setCollectorMotor(Collector::kForward);
}

bool Collect::IsFinished() {
	if ((collector->getFrisbeeSensorCount() != 0 || IsTimedOut()) == true) {
		collector->setSetpoint(COLLECTOR_PITCH_FLOOR);
		collector->setSetpoint(COLLECTOR_PITCH_DOWN);
		if (collector->getRawAngle() == COLLECTOR_PITCH_DOWN) {
			return true;
		}
	}
	return false;
}

void Collect::End() {
	collector->setCollectorMotor(Collector::kStop);
}

void Collect::Interrupted() {
	collector->setCollectorMotor(Collector::kStop);
}
