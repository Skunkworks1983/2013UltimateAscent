#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() : Subsystem("Collector") {
	pitchEncoder = new Encoder(PITCH_ENCODER_CHANNEL_A, PITCH_ENCODER_CHANNEL_B, false, Encoder::k4X);
	pitchEncoder->Reset();
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
	
	if (pitchEncoder->GetDistance() <= angle){
		collectorMotor->Set(.5);
	} else {
		collectorMotor->Set(0);
	}
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
