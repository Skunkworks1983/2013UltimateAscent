#include "DiddlerDrive.h"
#include <math.h>

DiddlerDrive::DiddlerDrive(float speed) :
	CommandBase("DiddlerDrive") {
	Requires(driveBase);
	SetInterruptible(true);
	this->speed = speed;
}

void DiddlerDrive::Initialize() {
	leftSide = false;
	rightSide = false;
	stability = 0;
	lStable = driveBase->getLeftDiddler()->Get() ? 5 : 0;
	rStable = driveBase->getRightDiddler()->Get() ? 5 : 0;
}

void DiddlerDrive::Execute() {
	if (driveBase->getLeftDiddler()->Get()) {
		if (lStable++ == 5) {
			leftSide = !leftSide;
		}
	} else {
		lStable = 0;
	}
	if (driveBase->getRightDiddler()->Get()) {
		if (rStable++ == 5) {
			rightSide = !rightSide;
		}
	} else {
		rStable = 0;
	}

	lastLeft = driveBase->getLeftDiddler()->Get();
	lastRight = driveBase->getRightDiddler()->Get();
	float lSpeed = leftSide ? -speed : speed;
	float rSpeed = rightSide ? -speed : speed;
	driveBase->setSpeed(driveBase->getLeftDiddler()->Get() ? 0.0 : lSpeed,
			driveBase->getRightDiddler()->Get() ? 0.0 : rSpeed);
	if (driveBase->getLeftDiddler()->Get()
			&& driveBase->getRightDiddler()->Get()) {
		stability++;
	} else {
		stability = 0;
	}
}

bool DiddlerDrive::IsFinished() {
	return stability > 25;
}

void DiddlerDrive::End() {
	driveBase->setSpeed(0, 0);
}

void DiddlerDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}
