#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);
	collectorPitchMotor = COLLECTOR_PITCH_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);
}

Collector::~Collector() {
	delete pitchPot;
	delete collectorEncoder;
}

void Collector::setCollectorState(bool state) {
	if (state == true){
		collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
	}else
	{
		collectorMotor->Set(0);
	}
}

bool Collector::isUp() {
	return currentPosition;
}

Encoder* Collector::getCollectorEncoder() {
	return collectorEncoder;
}

float Collector::getRealPosition(){
	return pitchPot->GetVoltage();				//TODO
}

void Collector::setCollectorPitchMotor(float speed){
	collectorPitchMotor->Set(speed);
}

void Collector::setCollectorSpeed(float speed){
	collectorMotor->Set(speed);
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
