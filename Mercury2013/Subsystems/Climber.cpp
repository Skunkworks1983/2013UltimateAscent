#include "Climber.h"

Climber::Climber() {

}

Climber::~Climber() {
	delete armsEncoder;
	delete armsMotor;

	delete arm1Hook1;
	delete arm1Hook2;
	delete arm1Hook3;

	delete arm2Hook1;
	delete arm2Hook2;
	delete arm2Hook3;

	delete arm1Button;
	delete arm2Button;
}

void Climber::extendArm(double distance) {
	
}

void Climber::retractArm(double distance) {
	
}

void Climber::latchHook() {
	
}

void Climber::unlatchHook() {
	
}

bool Climber::getButton() {
	return false;
}

double Climber::getDistance() {
	return false;
}

//TODO: Need pokey stick thingies
