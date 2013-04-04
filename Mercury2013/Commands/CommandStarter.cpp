#include "CommandStarter.h"
#include "WPILib.h"

CommandStarter::CommandStarter(CreateCommand create, void *arg,
		bool waitForRequirements) :
	CommandBase("CommandStarter") {
	this->create = create;
	this->waitForRequirements = waitForRequirements;
	this->arg = arg;
	this->orders = NULL;
}

CommandStarter::CommandStarter(Command *orders, bool waitForRequirements) :
	CommandBase("CommandStarter") {
	this->orders = orders;
	this->waitForRequirements = waitForRequirements;
	this->arg = NULL;
	this->create = NULL;
}

CommandStarter::~CommandStarter() {
}

void CommandStarter::Initialize() {
	if (this->create != NULL && this->orders == NULL) {
		this->orders = create(arg);
	}
}

void CommandStarter::Execute() {
	if (orders != NULL) {
		if (waitForRequirements) {
			for (SubsystemSet::iterator itr = orders->GetRequirements().begin(); itr
					!= orders->GetRequirements().end(); itr++) {
				Subsystem *sys = *(itr);
				if (sys != NULL && sys->GetCurrentCommand() != NULL
						&& sys->GetCurrentCommand() != sys->GetDefaultCommand()) {
					return;
				}
			}
		}
		Scheduler::GetInstance()->AddCommand(orders);
		orders = NULL;
	}
}

bool CommandStarter::IsFinished() {
	return orders == NULL;
}

void CommandStarter::End() {
}

void CommandStarter::Interrupted() {
}
