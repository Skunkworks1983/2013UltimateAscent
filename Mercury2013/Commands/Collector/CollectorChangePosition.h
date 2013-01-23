#ifndef COLLECTOR_CHANGE_POSITION_H
#define COLLECTOR_CHANGE_POSITION_H

#include "../CommandBase.h"

class CollectorChangePosition: public CommandBase {
private:
	float left;
	bool position;
	float speed;
	bool isFinished;
public:
	CollectorChangePosition(bool position);
	~CollectorChangePosition();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
