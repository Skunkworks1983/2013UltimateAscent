#include "CommandCanceler.h"
#include "WPILib.h"

CommandCanceler::CommandCanceler(CommandBase *sys) :
	CommandBase("CommandStarter") {
	this->cancel = sys;
}

CommandCanceler::~CommandCanceler() {
}

void CommandCanceler::Initialize() {
	this->canceled = false;
	Scheduler::GetInstance()->Remove(cancel);
	cancel->forceKillCommand();
	this->canceled = true;
}

void CommandCanceler::Execute() {
}

bool CommandCanceler::IsFinished() {
	return canceled;
}

void CommandCanceler::End() {
}

void CommandCanceler::Interrupted() {
}
