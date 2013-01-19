#include "Climber.h"

Climber::Climber() {
	armsEncoder = new Encoder(ARM_ENCODER_1, ARM_ENCODER_2, false, Encoder::k4X);
	armsMotor = ARM_MOTOR_CREATE(ARM_MOTOR);
	
	arm1Switch = new DigitalInput(ARM_SWITCH_1);
	arm2Switch = new DigitalInput(ARM_SWITCH_2);
	
	armsEncoder->Reset();
}

Climber::~Climber() {
	delete armsEncoder;
	delete armsMotor;

	delete arm1Switch;
	delete arm2Switch;
}

void Climber::moveMotor(float dist) {
	
}

void Climber::movePokey(bool pos) {
	
}

void Climber::setArmsMotor(float speed) {
	armsMotor->Set(speed);
}

float Climber::getPosition() {
	return false;
}

bool getPokey() {
	return false;
}

bool Climber::getSwitch(int num) {
	return false;
}


//TODO: Need pokey stick thingies
