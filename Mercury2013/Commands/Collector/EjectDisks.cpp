#include "EjectDisks.h"
#include "../../Utils/Time.h"
#include "../../Subsystems/Collector.h"

EjectDisks::EjectDisks(Collector::MotorDirection dir) :
	CommandBase("EjectDisks") {
	Requires(collector);
	SetTimeout(((double) EJECTDISKS_SERVO_TIMEOUT) / 1000.0);
	SetInterruptible(true);
	this->dir = dir;
}

EjectDisks::~EjectDisks() {

}

void EjectDisks::Initialize() {
	startTime = getCurrentMillis();
}

void EjectDisks::Execute() {
	int frisbeeCount = collector->getFrisbeeSensorCount();
	if (frisbeeCount == 2) {
		collector->setFrisbeeStop(true);
	} else if (frisbeeCount < 2) {
		collector->setFrisbeeStop(false);
	}
	collector->setCollectorMotor(
			(getCurrentMillis() - startTime < EJECTDISKS_EJECT_TIMEOUT) ? dir
					: Collector::kStop);
}

bool EjectDisks::IsFinished() {
	return IsTimedOut();
}

void EjectDisks::End() {
	collector->setFrisbeeStop(false);
}

void EjectDisks::Interrupted() {
	collector->setFrisbeeStop(false);
}
