#include "CommandStarter.h"
#include "WPILib.h"

CommandStarter::CommandStarter(CreateCommand create, ArgumentProvider *argP) :
	CommandBase("CommandStarter") {
	this->create = create;
	this->arg = argP;
}

CommandStarter::~CommandStarter() {
}

void CommandStarter::Initialize() {
	Command *cmd;
	if (arg != NULL) {
		cmd = create(arg->getArgument());
	} else {
		cmd = create(NULL);
	}
	Scheduler::GetInstance()->AddCommand(cmd);
}

void CommandStarter::Execute() {
}

bool CommandStarter::IsFinished() {
	return false;
}

void CommandStarter::End() {
}

void CommandStarter::Interrupted() {
}
