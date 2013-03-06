#include "FlushShooter.h"
#include "../../Utils/Time.h"

FlushShooter::FlushShooter() :
	CommandBase("FlushShooter") {
	Requires(shooter);
	SetTimeout(((double) SHOOTER_FLUSH_TIME) / 1000.0);
}

void FlushShooter::Initialize() {
	
}

void FlushShooter::Execute() {
	shooter->flush(true);
}

bool FlushShooter::IsFinished() {
	return IsTimedOut();
}

void FlushShooter::End() {
	shooter->flush(false);
}

void FlushShooter::Interrupted() {
	shooter->flush(false);
}
