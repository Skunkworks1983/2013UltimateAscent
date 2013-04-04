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
		printf("State %d\n", waitFor->Get());
		return waitFor->Get() == waitForState;
	} else {
		printf("State %d\t%d\n", secondLol->Get(), waitFor->Get());
		return secondLol->Get() == waitForState && waitFor->Get()
				== waitForState;
	}
}

void WaitForTrigger::End() {
	printf("Finished\n");
}

void WaitForTrigger::Interrupted() {
}
