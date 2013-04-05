#include "DiddlerDrive.h"
#include <math.h>

DiddlerDrive::DiddlerDrive(float speed) :
	CommandBase("DiddlerDrive") {
	Requires(driveBase);
	SetInterruptible(true);
	this->speed = speed;
}

void DiddlerDrive::Initialize() {
}

void DiddlerDrive::Execute() {
	driveBase->setSpeed(speed, speed);
}

bool DiddlerDrive::IsFinished() {
	return driveBase->getLeftDiddler()->Get()
			|| driveBase->getRightDiddler()->Get();
}

void DiddlerDrive::End() {
	driveBase->setSpeed(0, 0);
}

void DiddlerDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}
