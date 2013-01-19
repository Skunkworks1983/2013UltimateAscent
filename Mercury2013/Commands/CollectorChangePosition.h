#ifndef COLLECTOR_CHANGE_POSITION_H
#define COLLECTOR_CHANGE_POSITION_H

#include "CommandBase.h"

class CollectorChangePosition: public CommandBase {
private:
	float speed;
public:
	CollectorChangePosition();
	virtual void Initialize();
	virtual void Execute(bool);
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsInterruptible();
};

#endif
