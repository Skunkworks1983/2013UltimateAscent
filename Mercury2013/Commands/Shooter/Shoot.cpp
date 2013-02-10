#include "Shoot.h"
#include "../../Utils/Time.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
	SetTimeout(((double) SHOOTER_SHOOT_TIME + SHOOTER_WAIT_TIME) / 1000.0);
}

void Shoot::Initialize() {
	startTime = getCurrentMillis();
}

void Shoot::Execute() {
	shooter->shoot(getCurrentMillis() < startTime + SHOOTER_SHOOT_TIME);
}

bool Shoot::IsFinished() {
	return IsTimedOut();
}

void Shoot::End() {

}

void Shoot::Interrupted() {
	shooter->shoot(false);
}
