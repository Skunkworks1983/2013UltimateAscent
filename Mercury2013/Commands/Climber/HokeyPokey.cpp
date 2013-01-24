#include "HokeyPokey.h" 

HokeyPokey::HokeyPokey() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

HokeyPokey::~HokeyPokey() {
	
}

// Called just before this Command runs the first time
void HokeyPokey::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void HokeyPokey::Execute() {
	//Here call the collector to do the movey thingy
	
}

// Make this return true when this Command no longer needs to run execute()
bool HokeyPokey::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void HokeyPokey::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HokeyPokey::Interrupted() {
	
}
