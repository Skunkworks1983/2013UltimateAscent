#include "Climb.h"

Climb::Climb() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

Climb::~Climb() {
	
}

// Called just before this Command runs the first time
void Climb::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Climb::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {
}
