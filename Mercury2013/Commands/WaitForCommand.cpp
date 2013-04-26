#include "WaitForCommand.h"
#include "WPILib.h"

WaitForCommand::WaitForCommand(Command *waitFor) :
	CommandBase("WaitForCommand") {
	this->waitFor = waitFor;
}

WaitForCommand::~WaitForCommand() {
}

void WaitForCommand::Initialize() {
}

void WaitForCommand::Execute() {
}

bool WaitForCommand::IsFinished() {
	return !waitFor->IsRunning();
}

void WaitForCommand::End() {
}

void WaitForCommand::Interrupted() {
}
