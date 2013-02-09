#include "Shoot.h"
#include "../../Utils/Time.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
}

void Shoot::Initialize() {
	startTime = getCurrentMillis();
	shooter->shoot();
}

void Shoot::Execute() {
	
}

bool Shoot::IsFinished() {
	return startTime + SHOOTER_SHOOT_TIME <= getCurrentMillis();
}

void Shoot::End() {
	shooter->deShoot();
}

void Shoot::Interrupted() {
	shooter->deShoot();
}
