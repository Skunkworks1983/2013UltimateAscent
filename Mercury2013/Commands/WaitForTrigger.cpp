#include "WaitForTrigger.h"
#include "WPILib.h"

WaitForTrigger::WaitForTrigger(Trigger *waitFor, Trigger *s, bool waitForState) :
	CommandBase("WaitForTrigger") {
	this->waitFor = waitFor;
	this->secondLol = s;
	this->waitForState = waitForState;
}

WaitForTrigger::~WaitForTrigger() {
}

void WaitForTrigger::Initialize() {
}

void WaitForTrigger::Execute() {
}

bool WaitForTrigger::IsFinished() {
	if (secondLol == NULL) {
		return waitFor->Get() == waitForState;
	} else {
		return secondLol->Get() == waitForState && waitFor->Get()
				== waitForState;
	}
}

void WaitForTrigger::End() {
}

void WaitForTrigger::Interrupted() {
}
