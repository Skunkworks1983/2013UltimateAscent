#include "Collect.h"
#include "../../Utils/Time.h"

Collect::Collect(double timeout) :
	CommandBase(CommandBase::createNameFromFloat("Collect", timeout)) {
	Requires(collector);
	if (timeout < 0.0) {
		//Default timeout
		timeout = COLLECTOR_COLLECT_TIMEOUT;
	}
	SetTimeout(timeout / 1000.0);
	SetInterruptible(true);
}

Collect::~Collect() {

}

void Collect::Initialize() {
	gotOne = -1;
}

void Collect::Execute() {
	collector->setCollectorMotor(Collector::kForward);
	if (collector->getFrisbeeSensorCount() != 0 && collectorArms->getAngle()
			<= COLLECTOR_PITCH_LIGHT_LOW) {
		if (gotOne < 0.0) {
			gotOne = getCurrentMillis();
		}
	} else {
		gotOne = -1.0;
	}
}

bool Collect::IsFinished() {
	return (collector->getFrisbeeSensorCount() != 0 && gotOne > 0.0 && gotOne
			+ COLLECTOR_COLLECT_STOP_DELAY < getCurrentMillis())
			|| IsTimedOut();
}

void Collect::End() {
	collector->setCollectorMotor(Collector::kStop);
	collector->updateFrisbeeCache(collector->getFrisbeeSensorCount());
}

void Collect::Interrupted() {
	collector->setCollectorMotor(Collector::kStop);
	collector->updateFrisbeeCache(collector->getFrisbeeSensorCount());
}
