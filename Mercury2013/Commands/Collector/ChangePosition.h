#ifndef _CHANGE_POSITION_H
#define _CHANGE_POSITION_H

#include "../CommandBase.h"

class ChangePosition: public CommandBase {
private:
	bool position;
	float speed;
	bool isFinished;
public:
	ChangePosition(bool position);
	~ChangePosition();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
