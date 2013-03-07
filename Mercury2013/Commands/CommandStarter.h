#ifndef __CMD_COMMANDSTARTER_H
#define __CMD_COMMANDSTARTER_H

#include "CommandBase.h"

typedef Command* (*CreateCommand)();
class CommandStarter: public CommandBase {
private:
	CreateCommand create;
public:
	CommandStarter(CreateCommand createFunc);
	~CommandStarter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
