#include "SlowTankDrive.h"

SlowTankDrive::SlowTankDrive() :
	CommandBase("SlowTankDrive") {
	Requires(driveBase);
	SetInterruptible(true);
}

void SlowTankDrive::Initialize() {
	speed = 0.0;
	driveBase->getLeftEncoder()->Reset();
	driveBase->getRightEncoder()->Reset();
}

void SlowTankDrive::Execute() {
	//Divides the input of the motors by 10.
	//Pootis.
	driveBase->setSpeed(speed, -speed);

	if ((driveBase->getLeftEncoder() != 0) || (driveBase->getRightEncoder() != 0)){
		SmartDashboard::PutNumber("THE FINAL NUMBER YOU WANT IS THIS", (double)speed);
		isFinished = true;
	}else{
		speed += .00005;
	}
	SmartDashboard::PutNumber("Speed being passed", (double)speed);
}

bool SlowTankDrive::IsFinished() {
return isFinished;
}

void SlowTankDrive::End() {
	driveBase->setSpeed(0, 0);
}

void SlowTankDrive::Interrupted() {
	driveBase->setSpeed(0, 0);
}
