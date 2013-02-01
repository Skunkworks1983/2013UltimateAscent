#include "Climber.h"

Climber::Climber() :
	Subsystem("Climber") {
	// TODO sliderEncoder = new Encoder(CLIMBER_SLIDER_ENCODER_1, CLIMBER_SLIDER_ENCODER_2, false, Encoder::k4X);
	// TODO sliderMotor1 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_1);
	// TODO sliderMotor2 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_2);

	// TODO sliderEncoder->Reset();

	// TODO hookButton1 = new DigitalInput(CLIMBER_HOOK_BUTTON_1);
	// TODO hookButton2 = new DigitalInput(CLIMBER_HOOK_BUTTON_2);

	// TODO pokey1 = new Solenoid(CLIMBER_POKEY_1);
	// TODO pokey2 = new Solenoid(CLIMBER_POKEY_2);

	// TODO sliderBrake = new Solenoid(CLIMBER_BRAKE);
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
}

void Climber::movePokey(bool pos) {
	pokey1->Set(pos);
	pokey1->Set(pos);
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

Climber::SliderState Climber::getSliderState() {
	if (PIDGet() >= 1.0 - CLIMBER_SLIDER_TOLERANCE) {
		return kUp;
	} else if (PIDGet() <= CLIMBER_SLIDER_TOLERANCE) {
		return kDown;
	} else {
		return kOther;
	}
}

double Climber::PIDGet() {
	return sliderEncoder->GetDistance();
}

void Climber::PIDWrite(float speed) {
	sliderMotor1->Set(speed);
	sliderMotor2->Set(speed);
}

// TODO: Need pokey stick thingies
