#ifndef __CMD_WAITFORCOMMAND_H
#define __CMD_WAITFORCOMMAND_H

#include "CommandBase.h"

class WaitForCommand: public CommandBase {
private:
	Command *waitFor;
public:
	WaitForCommand(Command *waitFor);
	~WaitForCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
