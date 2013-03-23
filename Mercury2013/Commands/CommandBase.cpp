#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) :
	Command(name) {
}

CommandBase::CommandBase() :
	Command() {
}

CommandBase *CommandBase::makeInterruptible(bool state) {
	SetInterruptible(state);
	return this;
}

char *CommandBase::createNameFromFloat(char *base, float target) {
	char *buf = new char[32];
	snprintf(buf, 32, "%s_%f", base, target);
	return buf;
}
char *CommandBase::createNameFromString(char *base, const char *arg) {
	char *buf = new char[32];
	snprintf(buf, 32, "%s_%s", base, arg);
	return buf;
}

// Initialize a single static instance of all of your subsystems to NULL
Shooter *CommandBase::shooter = NULL;
DriveBase *CommandBase::driveBase = NULL;
Collector *CommandBase::collector = NULL;
CollectorArms *CommandBase::collectorArms = NULL;
OI *CommandBase::oi = NULL;
Pneumatics *CommandBase::pneumatics = NULL;
Climber *CommandBase::climber = NULL;
ShooterPitch *CommandBase::shooterPitch = NULL;
bool CommandBase::subsystems = false;

void CommandBase::init() {
	if (subsystems) {
		return;
	}
	subsystems = true;
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	pneumatics = new Pneumatics();
	shooter = new Shooter();
	driveBase = new DriveBase();
	collector = new Collector();
	collectorArms = new CollectorArms();
	climber = new Climber();
	shooterPitch = new ShooterPitch();
	oi = new OI();
}
