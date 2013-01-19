#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);
}

Collector::~Collector() {
	delete pitchPot;
	delete collectorEncoder;
}

void Collector::startCollector() {
	collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
}

void Collector::stopCollector() {
	collectorMotor->Set(0);
}

bool Collector::getPosition() {
	return currentPosition;
}

Encoder *Collector::getCollectorEncoder() {
	return collectorEncoder;
}

float getRealPosition(){
	return 0; 					//TODO
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
