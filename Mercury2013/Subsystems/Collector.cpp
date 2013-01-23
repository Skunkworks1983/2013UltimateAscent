#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);	//potentionmeter for colelctor pitch
	collectorPitchMotor = COLLECTOR_PITCH_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);	//collector pitch motor
	collectorMotor = COLLECTOR_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);
	IRLow = new DigitalInput(COLLECTOR_IR_LOW_CHANNEL);	//IR sensor near or on floor
	IRMid = new DigitalInput(COLLECTOR_IR_MID_CHANNEL);	//IR sensor inside middle of robot
	IRHigh = new DigitalInput(COLLECTOR_IR_HIGH_CHANNEL);	//IR sensor next to shooter?
}

Collector::~Collector() {
	/* deleting of the objects created above */
	delete pitchPot;
	delete collectorEncoder;
	delete IRLow;
	delete IRMid;
	delete IRHigh;
}

void Collector::setCollectorState(bool state) {
	/* Sets motor speed to a DEFINE value, turns motor off if false */
	if (state == true){
		collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
	}else
	{
		collectorMotor->Set(0);
	}
}

bool Collector::isUp() {
	//if colelctor is in up position (true is up)
	return currentPosition;
}

Encoder* Collector::getCollectorEncoder() {
	//returns pointer to colelctor encoder
	return collectorEncoder;
}

float Collector::getRealPosition(){
	// returns the real potentiometer reading TODO
	return pitchPot->GetVoltage();				//TODO
}

void Collector::setCollectorPitchMotor(float speed){
	//sets collector pitch motor speed
	collectorPitchMotor->Set(speed);
}

void Collector::setCollectorSpeed(float speed){
	//sets the collector speed NOT SURE IF IMPLEMENTED
	collectorMotor->Set(speed);
}

int Collector::getSense(int height){
	// returns the IR sensor's feedback depending on what argument is (0==low, 1==mid, 2==high)
	switch(height){
	case 0:
		return IRLow->Get() &1;
		break;
	case 1:
		return IRMid->Get() &1;
		break;
	case 2:
		return IRHigh->Get() &1;
		break;
	default:
		return 0;
	}
}

void Collector::InitDefaultCommand() {
	// TODO Something
}
