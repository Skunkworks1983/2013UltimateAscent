#include "CommandCanceler.h"
#include "WPILib.h"

CommandCanceler::CommandCanceler(Command *sys) :
	CommandBase("CommandStarter") {
	this->cancel = sys;
}

CommandCanceler::~CommandCanceler() {
}

void CommandCanceler::Initialize() {
	Scheduler::GetInstance()->Remove(cancel);
}

void CommandCanceler::Execute() {
}

bool CommandCanceler::IsFinished() {
	return true;
}

void CommandCanceler::End() {
}

void CommandCanceler::Interrupted() {
}
