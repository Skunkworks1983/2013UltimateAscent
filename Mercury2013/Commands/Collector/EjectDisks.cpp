#include "EjectDisks.h"
#include "../../Utils/Time.h"
#include "../../Subsystems/Collector.h"
#include "FlagControl.h"

EjectDisks::EjectDisks(Collector::MotorDirection dir) :
	CommandBase(CommandBase::createNameFromFloat("EjectDisks", dir)) {
	Requires(collector);
	//SetTimeout(((double) EJECTDISKS_SERVO_TIMEOUT) / 1000.0);
	SetTimeout(((double) EJECTDISKS_EJECT_TIMEOUT) / 1000.0);
	SetInterruptible(true);
	this->dir = dir;
}

EjectDisks::~EjectDisks() {

}

void EjectDisks::Initialize() {
	startTime = getCurrentMillis();
}

void EjectDisks::Execute() {
	int frisbeeCount = collector->getCachedFrisbeeSensorCount();
	if (frisbeeCount == 2 && dir == Collector::kForward) {
		//collector->setFrisbeeStop(true);
	} else {
		//collector->setFrisbeeStop(false);
	}
	collector->setCollectorMotor(
			(getCurrentMillis() - startTime < EJECTDISKS_EJECT_TIMEOUT) ? dir
					: Collector::kStop);
}

bool EjectDisks::IsFinished() {
	return IsTimedOut();
}

void EjectDisks::End() {
	Scheduler::GetInstance()->AddCommand(
			new FlagControl(FlagControl::kFlagAutoDown));
	collector->setCollectorMotor(Collector::kStop);
	collector->updateFrisbeeCache(0);
}

void EjectDisks::Interrupted() {
	collector->setFrisbeeStop(false);
	collector->setCollectorMotor(Collector::kStop);
	collector->updateFrisbeeCache(0);
}
