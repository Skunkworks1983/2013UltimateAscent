#include "Climber.h"

Climber::Climber() :
	Subsystem("Climber") {
	//TODO armsEncoder = new Encoder(ARM_ENCODER_1, ARM_ENCODER_2, false, Encoder::k4X);
	//TODO armsMotor = ARM_MOTOR_CREATE(ARM_MOTOR);
	
	sliderMotors = new DualPIDOutput(sliderMotor1, sliderMotor2);

	//TODO arm1Button = new DigitalInput(ARM_BUTTON_1);

	//TODO armsEncoder->Reset();

	//TODO pokey1 = new Solenoid(POKEY_1);
	//TODO pokey2 = new Solenoid(POKEY_2);
	
	//TODO sliderPID = new PIDController(CLIMBER_SLIDER_P, CLIMBER_SLIDER_I, CLIMBER_SLIDER_D, sliderEncoder , sliderMotors);
}

Climber::~Climber() {
	delete sliderEncoder;
	delete sliderMotor1;
	delete sliderMotor2;

	delete hookButton1;
	delete hookButton2;

	delete pokey1;
	delete pokey2;
	delete sliderBrake;
	
	delete sliderPID;
}

void Climber::movePokey(bool pos) {
	pokey1->Set(pos);
	pokey1->Set(pos);
}

void Climber::setSliderMotors(float speed) { // TODO MAYBE SEPERATE THIS
	sliderMotor1->Set(speed);
	sliderMotor2->Set(speed);
}

float Climber::getPosition() {
	return false;
}

bool Climber::getPokey(int num) {
	switch (num) {
	case 1:
		return pokey1->Get();

	case 2:
		return pokey2->Get();
	}
	return false;
}

bool Climber::getButton(int num) {
	switch (num) {
	case 1:
		return hookButton1->Get();

	case 2:
		return hookButton2->Get();
	}
	return false;
}

void Climber::setBrakeState(bool isBraking) {
	this->cachedBrakeState = isBraking; // TODO ACTUALLY DO SOMETHING
}

bool Climber::getBrakeState() {
	return this->cachedBrakeState;
}

//TODO: Need pokey stick thingies
