#ifndef COLLECT_H
#define COLLECT_H

#include "CommandBase.h"

class Collect: public CommandBase {
public:
	Collect();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsInterruptible();
};

#endif
