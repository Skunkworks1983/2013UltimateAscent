#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	pitchEncoder = new AnalogChannel(COLLECTOR_PITCH_POT);
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

void Collector::changePosition(bool position) {
}

bool Collector::getPosition() {
	return currentPosition;
}

Encoder *Collector::getCollectorEncoder() {
	return collectorEncoder;
}

float getRealPosition(){
	
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
