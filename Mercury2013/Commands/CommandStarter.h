#ifndef __CMD_COMMANDSTARTER_H
#define __CMD_COMMANDSTARTER_H

#include "CommandBase.h"

typedef Command* (*CreateCommand)();
class CommandStarter: public CommandBase {
private:
	CreateCommand create;
	Command *orders;
	bool waitForRequirements;
public:
	CommandStarter(CreateCommand createFunc, bool waitForRequirements = false);
	~CommandStarter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
