#include "EjectDisks.h"

EjectDisks::EjectDisks() :
	CommandBase("EjectDisks") {
	Requires(collector);
	SetTimeout(((double) EJECTDISKS_EJECT_TIMEOUT) / 1000.0);
	SetInterruptible(true);
}

EjectDisks::~EjectDisks() {

}

void EjectDisks::Initialize() {
}

void EjectDisks::Execute() {
	collector->setCollectorMotor(true);
}

bool EjectDisks::IsFinished() {
	return collector->getFrisbeeSensorCount() == 0 || IsTimedOut();
}

void EjectDisks::End() {
	collector->setCollectorMotor(false);
}

void EjectDisks::Interrupted() {
	collector->setCollectorMotor(false);
}
