#include "HokeyPokey.h" 

HokeyPokey::HokeyPokey() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

HokeyPokey::~HokeyPokey() {
	
}

// Called just before this Command runs the first time
void HokeyPokey::Initialize() {
	climber->movePokey(true);
}

// Called repeatedly when this Command is scheduled to run
void HokeyPokey::Execute() {
	//Here call the collector to do the movey thingy
	
}

// Make this return true when this Command no longer needs to run execute()
bool HokeyPokey::IsFinished() {
	if (climber->getButton(1) == true && climber->getButton(2) == true) {
		return true;
	}
	
	else {
		return false;
	}
}

// Called once after isFinished returns true
void HokeyPokey::End() {
	climber->movePokey(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HokeyPokey::Interrupted() {
	
}
