#include "CommandStarter.h"
#include "WPILib.h"

CommandStarter::CommandStarter(CreateCommand create) :
	CommandBase("CommandStarter") {
	this->create = create;
}

CommandStarter::~CommandStarter() {
}

void CommandStarter::Initialize() {
	Scheduler::GetInstance()->AddCommand(create());
}

void CommandStarter::Execute() {
}

bool CommandStarter::IsFinished() {
	return true;
}

void CommandStarter::End() {
}

void CommandStarter::Interrupted() {
}
