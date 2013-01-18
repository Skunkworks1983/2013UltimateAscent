#include "Collector.h"

Collector::Collector() : Subsystem("Collector") {
	// startAngle = getPitchEncoder(); TODO
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
	collectorMotor->Set(angle);
}

Encoder *Collector::getCollectorEncoder() {
	return collectorEncoder;
}

Encoder *Collector::getPitchEncoder() {
	return pitchEncoder;
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
