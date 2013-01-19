#include "Shoot.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
}

void Shoot::Initialize() {

}

void Shoot::Execute() {

}

bool Shoot::IsFinished() {
	return false;
}

void Shoot::End() {

}

void Shoot::Interrupted() {

}

bool Shoot::IsInterruptible() {
	return false;
}
