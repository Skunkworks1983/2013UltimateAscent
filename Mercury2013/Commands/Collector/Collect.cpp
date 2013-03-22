#include "Collect.h"
#include "../../Utils/Time.h"

Collect::Collect(bool timesOut) :
	CommandBase(CommandBase::createNameFromFloat("Collect", timesOut & 1)) {
	Requires(collector);
	SetTimeout(
			timesOut ? ((double) COLLECTOR_COLLECT_TIMEOUT) / 1000.0
					: 999999999.0);
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
