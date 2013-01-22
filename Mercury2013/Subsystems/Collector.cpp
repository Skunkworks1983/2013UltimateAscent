#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);
	collectorPitchMotor = COLLECTOR_PITCH_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);
	low = new DigitalInput(COLLECTOR_IR_LOW_CHANNEL);
	mid = new DigitalInput(COLLECTOR_IR_MID_CHANNEL);
	high = new DigitalInput(COLLECTOR_IR_HIGH_CHANNEL);
}

Collector::~Collector() {
	delete pitchPot;
	delete collectorEncoder;
	delete low;
	delete mid;
	delete high;
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

int Collector::getSense(int height){
	switch(height){
	case 0:
		return low->Get() &1;
		break;
	case 1:
		return mid->Get() &1;
		break;
	case 2:
		return high->Get() &1;
		break;
	default:
		return false;
	}
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
