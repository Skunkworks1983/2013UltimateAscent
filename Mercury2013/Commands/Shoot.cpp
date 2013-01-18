#include "Shoot.h"

Shoot::Shoot() {
	// Requires(Shooter); TODO
}

void Shoot::Initialize() {
	
}

void Shoot::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Shoot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
}
