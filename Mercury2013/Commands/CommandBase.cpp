#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) :
	Command(name) {
}

CommandBase::CommandBase() :
	Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Shooter *CommandBase::shooter = NULL;
DriveBase *CommandBase::driveBase = NULL;
OI *CommandBase::oi = NULL;
Pneumatics *CommandBase::pneumatics = NULL;

void CommandBase::init() {
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	pneumatics = new Pneumatics();
	shooter = new Shooter();
	driveBase = new DriveBase();
	oi = new OI();
}
