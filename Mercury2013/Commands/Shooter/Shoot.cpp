#include "Shoot.h"
#include "../../Utils/Time.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
}

void Shoot::Initialize() {
	startTime = getCurrentMillis();
	shooter->shoot(true);
}

void Shoot::Execute() {
	if (getCurrentMillis() >= startTime + SHOOTER_SHOOT_TIME) {
		shooter->shoot(false);
	}
}

bool Shoot::IsFinished() {
	return getCurrentMillis() >= startTime + SHOOTER_SHOOT_TIME + SHOOTER_WAIT_TIME;
}

void Shoot::End() {
	
}

void Shoot::Interrupted() {
	shooter->shoot(false);
}
