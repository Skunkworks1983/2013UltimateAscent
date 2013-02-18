#ifndef __CMD_COMMANDSTARTER_H
#define __CMD_COMMANDSTARTER_H

#include "../Utils/ArgumentProvider.h"
#include "CommandBase.h"

typedef Command* (*CreateCommand)(void *param);
class CommandStarter: public CommandBase {
private:
	CreateCommand create;
	ArgumentProvider *arg;
	bool scheduled;
public:
	CommandStarter(CreateCommand createFunc, ArgumentProvider *arg = NULL);
	~CommandStarter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
