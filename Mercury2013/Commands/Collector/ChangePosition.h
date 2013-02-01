#ifndef __CMD_COLLECT_CHANGEPOSITION_H
#define __CMD_COLLECT_CHANGEPOSITION_H

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
