#include "Climber.h"

Climber::Climber() {
	/*armsEncoder = new Encoder(ARM_ENCODER_1, ARM_ENCODER_2, false, Encoder::k4X);
	armsMotor = new SpeedController();
	
	arm1Switch = new DigitalInput(ARM_SWITCH_1);
	arm2Switch = new DigitalInput(ARM_SWITCH_2);*/
}

Climber::~Climber() {
	delete armsEncoder;
	delete armsMotor;

	delete arm1Switch;
	delete arm2Switch;
}

void Climber::moveMotor(double dist) {
	
}

void Climber::movePokey(bool pos) {
	
}

double Climber::getPosition() {
	return false;
}

bool getPokey() {
	return false;
}

bool Climber::getSwitch() {
	return false;
}


//TODO: Need pokey stick thingies
