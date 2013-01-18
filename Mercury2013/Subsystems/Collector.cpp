#include "Collector.h"

Collector::Collector() :
	startingAngle = getPitchEncoder();
}

Collector::~Collector() {	
	delete pitchEncoder;
	delete collectorEncoder;
}

void Collector::startCollector() {
	collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
}

void Collector::stopCollector() {
	collectorMotor->Set(0);
}

void Collector::changePitch(float angle) {
	
	collectorMotor->Set()
}

Encoder *DriveBase::getCollectorEncoder() {
	return collectorEncoder;
}

Encoder *DriveBase::getPitchEncoder() {
	return pitchEncoder;
}

void DriveBase::InitDefaultCommand() {
	// TODO Something
}