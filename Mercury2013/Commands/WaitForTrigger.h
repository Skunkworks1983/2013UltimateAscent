#ifndef __CMD_WAITFORTRIGGER_H
#define __CMD_WAITFORTRIGGER_H

#include "CommandBase.h"

class WaitForTrigger: public CommandBase {
private:
	Trigger *waitFor;
	Trigger *secondLol;
	bool waitForState;
public:
	WaitForTrigger(Trigger *waitFor, Trigger *second = NULL,
			bool waitForState = true);
	~WaitForTrigger();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
