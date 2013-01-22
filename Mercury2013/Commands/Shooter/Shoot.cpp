#include "Shoot.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
	Requires(collector);
}

void Shoot::Initialize() {

}

void Shoot::Execute() {
	// shooter->setTargetSpeed(SHOOTER_TARGET_RPM);  TODO
}

bool Shoot::IsFinished() {
	return false;
}

void Shoot::End() {

}

void Shoot::Interrupted() {

}
