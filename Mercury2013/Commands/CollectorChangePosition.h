#ifndef COLLECT_CHANGE_POSITION_H
#define COLLECT_CHANGE_POSITION_H

#include "CommandBase.h"

class CollectChangePosition: public CommandBase {
public:
	CollectChangePosition();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsInterruptible();
};

#endif
