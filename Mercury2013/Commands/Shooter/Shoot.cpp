#include "Shoot.h"
#include "../../Utils/Time.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
	SetTimeout(((double) SHOOTER_SHOOT_TIME) / 1000.0);
	SetInterruptible(false);
}

void Shoot::Initialize() {

}

void Shoot::Execute() {
	shooter->shoot(true);
}

bool Shoot::IsFinished() {
	return IsTimedOut();
}

void Shoot::End() {
	shooter->shoot(false);
}

void Shoot::Interrupted() {
	shooter->shoot(false);
}
