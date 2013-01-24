#include "Climber.h"

Climber::Climber() {
	armsEncoder = new Encoder(ARM_ENCODER_1, ARM_ENCODER_2, false, Encoder::k4X);
	armsMotor = ARM_MOTOR_CREATE(ARM_MOTOR);
	
	arm1Button = new DigitalInput(ARM_BUTTON_1);
	arm2Button = new DigitalInput(ARM_BUTTON_2);
	
	armsEncoder->Reset();
	
	pokey1 = new Solenoid(POKEY_1);
	pokey2 = new Solenoid(POKEY_2);
}

Climber::~Climber() {
	delete armsEncoder;
	delete armsMotor;

	delete arm1Button;
	delete arm2Button;
}

void Climber::movePokey(bool pos) {
	pokey1->Set(pos);
	pokey1->Set(pos);
}

void Climber::setArmsMotor(float speed) {
	armsMotor->Set(speed);
}

float Climber::getPosition() {
	return false;
}

bool Climber::getPokey(int num) {
	switch(num) {
	case 1:
		return pokey1->Get();
		
	case 2:
		return pokey2->Get();
	}
	return false;
}

bool Climber::getButton(int num) {
	switch(num) {
	case 1:
		return arm1Button->Get();
	
	case 2:
		return arm2Button->Get();
	}
	return false;
}


//TODO: Need pokey stick thingies
