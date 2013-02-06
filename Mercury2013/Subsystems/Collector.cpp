#include "Collector.h"
#include "../Robotmap.h"

Collector::Collector() :
	Subsystem("Collector") {
	// TODO pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);	//potentionmeter for colelctor pitch
	// TODO collectorPitchMotor = COLLECTOR_PITCH_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);	//collector pitch motor
	// TODO collectorMotor = COLLECTOR_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);
	// TODO IRLow = new DigitalInput(COLLECTOR_IR_LOW_CHANNEL);	//IR sensor near or on floor
	// TODO IRMid = new DigitalInput(COLLECTOR_IR_MID_CHANNEL);	//IR sensor inside middle of robot
	// TODO IRHigh = new DigitalInput(COLLECTOR_IR_HIGH_CHANNEL);	//IR sensor next to shooter?
}

Collector::~Collector() {
	delete pitchPot;
	delete collectorEncoder;
	delete IRLow;
	delete IRMid;
	delete IRHigh;
}

void Collector::setCollectorState(bool state) {
	// Sets motor speed to a DEFINE value, turns motor off if false
	if (state == true){
		collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
	}else
	{
		collectorMotor->Set(0);
	}
}

bool Collector::isUp() {
	// If colelctor is in up position (true is up)
	return m_isUp;
}

Encoder* Collector::getCollectorEncoder() {
	// Returns pointer to colelctor encoder
	return collectorEncoder;
}

float Collector::getRealPosition(){
	// TODO Returns the real potentiometer reading
	return pitchPot->GetVoltage();
}

void Collector::setCollectorPitchMotor(float speed){
	// Sets collector pitch motor speed
	collectorPitchMotor->Set(speed);
}

void Collector::setCollectorSpeed(float speed){
	// Sets the collector speed NOT SURE IF IMPLEMENTED
	collectorMotor->Set(speed);
}

int Collector::getSense(int height){
	// Returns the IR sensor's feedback depending on what argument is (0==low, 1==mid, 2==high)
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
