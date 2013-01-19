#ifndef SHOOT_COMMAND_H
#define SHOOT_COMMAND_H

#include "CommandBase.h"

class Shoot: public CommandBase {
public:
	Shoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsInterruptible();
};

#endif
