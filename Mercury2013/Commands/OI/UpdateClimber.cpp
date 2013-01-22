#include "UpdateClimber.h"

UpdateClimber::UpdateClimber() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

UpdateClimber::~UpdateClimber() {
	
}

// Called just before this Command runs the first time
void UpdateClimber::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void UpdateClimber::Execute() {
	//oi->setLightStates(climber->getButton(1));
	//oi->setLightStates(climber->getButton(2));
}

// Make this return true when this Command no longer needs to run execute()
bool UpdateClimber::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void UpdateClimber::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdateClimber::Interrupted() {
	
}
