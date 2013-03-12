#include "CollectorArms.h"
#include <math.h>
#include "CollectorArmController.h"

CollectorArms::CollectorArms() :
	Subsystem("Collector") {
	printf("Creating Collector...");
	leftArmController = new LeftArmController(this);
	rightArmController = new RightArmController(this);
	printf("Done\n");
}

CollectorArms::~CollectorArms() {
	delete leftArmController;
	delete rightArmController;
}

void CollectorArms::setSetpoint(float angle) {
	leftArmController->setSetpoint(angle);
	rightArmController->setSetpoint(angle);
}

void CollectorArms::setPIDState(bool enabled) {
	leftArmController->setPIDState(enabled);
	rightArmController->setPIDState(enabled);
}

bool CollectorArms::isPIDDone() {
	return leftArmController->isPIDDone() && rightArmController->isPIDDone();
}

double CollectorArms::getLeftAngle() {
	return leftArmController->PIDGet();
}

double CollectorArms::getRightAngle() {
	return rightArmController->PIDGet();
}

float CollectorArms::getLeftOutput() {
	return rightArmController->getOutput();
}
float CollectorArms::getRightOutput() {
	return leftArmController->getOutput();
}

double CollectorArms::getAngle() {
	return (getLeftAngle() + getRightAngle()) / 2.0;
}

void CollectorArms::killPitchMotors() {
	leftArmController->PIDWrite(0);
	rightArmController->PIDWrite(0);
}

void CollectorArms::InitDefaultCommand() {
}
