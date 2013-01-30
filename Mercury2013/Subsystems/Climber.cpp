#include "Climber.h"

Climber::Climber() :
	Subsystem("Climber") {
	// TODO sliderEncoder = new Encoder(CLIMBER_SLIDER_ENCODER_1, CLIMBER_SLIDER_ENCODER_2, false, Encoder::k4X);
	// TODO sliderMotor1 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_1);
	// TODO sliderMotor2 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_2);
	sliderMotors = new DualPIDOutput(sliderMotor1, sliderMotor2);
	
	// TODO sliderEncoder->Reset();

	// TODO hookButton1 = new DigitalInput(CLIMBER_HOOK_BUTTON_1);
	// TODO hookButton2 = new DigitalInput(CLIMBER_HOOK_BUTTON_2);

	// TODO pokey1 = new Solenoid(CLIMBER_POKEY_1);
	// TODO pokey2 = new Solenoid(CLIMBER_POKEY_2);
	
	// TODO sliderBrake = new Solenoid(CLIMBER_BRAKE);
	
	sliderPID = new PIDController(CLIMBER_SLIDER_P, CLIMBER_SLIDER_I, CLIMBER_SLIDER_D, sliderEncoder , sliderMotors);
}

Climber::~Climber() {
	delete sliderEncoder;
	delete sliderMotor1;
	delete sliderMotor2;
	delete sliderMotors;

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
