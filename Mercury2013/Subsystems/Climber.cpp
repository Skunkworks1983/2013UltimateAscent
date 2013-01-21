#include "Climber.h"

Climber::Climber() {
	armsEncoder = new Encoder(ARM_ENCODER_1, ARM_ENCODER_2, false, Encoder::k4X);
	armsMotor = ARM_MOTOR_CREATE(ARM_MOTOR);
	
	arm1Button = new DigitalInput(ARM_BUTTON_1);
	arm2Button = new DigitalInput(ARM_BUTTON_2);
	
	armsEncoder->Reset();
}

Climber::~Climber() {
	delete armsEncoder;
	delete armsMotor;

	delete arm1Button;
	delete arm2Button;
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

bool Climber::getButton(int num) {
	return false;
}


//TODO: Need pokey stick thingies
