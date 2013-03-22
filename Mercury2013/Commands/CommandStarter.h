#ifndef __CMD_COMMANDSTARTER_H
#define __CMD_COMMANDSTARTER_H

#include "CommandBase.h"

typedef Command* (*CreateCommand)(void *arg);
class CommandStarter: public CommandBase {
private:
	void *arg;
	CreateCommand create;
	Command *orders;
	bool waitForRequirements;
public:
	CommandStarter(CreateCommand createFunc, void *arg = NULL,
			bool waitForRequirements = false);
	~CommandStarter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
