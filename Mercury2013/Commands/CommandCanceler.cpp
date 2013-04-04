#include "CommandCanceler.h"
#include "WPILib.h"

CommandCanceler::CommandCanceler(Command *sys) :
	CommandBase("CommandStarter") {
	this->cancel = sys;
}

CommandCanceler::~CommandCanceler() {
}

void CommandCanceler::Initialize() {
	this->canceled = false;
	Scheduler::GetInstance()->Remove(cancel);
	this->canceled = true;
	cancel->Cancel();
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
