#ifndef __CMD_COMMANDCANCEL_H
#define __CMD_COMMANDCANCEL_H

#include "CommandBase.h"

class Subsystem;
class CommandCanceler: public CommandBase {
private:
	CommandBase *cancel;
	bool canceled;
public:
	CommandCanceler(CommandBase *cancel);
	~CommandCanceler();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
