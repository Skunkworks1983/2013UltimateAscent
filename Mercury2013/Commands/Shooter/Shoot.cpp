#include "Shoot.h"
#include "../../Utils/Time.h"

Shoot::Shoot() :
	CommandBase("Shoot") {
	Requires(shooter);
	Requires(pneumatics);
	SetInterruptible(false);
}

void Shoot::Initialize() {
	shotTime = -1.0;
}

void Shoot::Execute() {
	if (shooter->readyToShoot()) {
		shooter->shoot(true);
		shotTime = getCurrentMillis();
	}
}

bool Shoot::IsFinished() {
	return (shotTime > 0.0 && shotTime + SHOOTER_SHOOT_TIME
			< getCurrentMillis()) || !shooter->isArmed();
}

void Shoot::End() {
	shooter->shoot(false);
}

void Shoot::Interrupted() {
	shooter->shoot(false);
}
