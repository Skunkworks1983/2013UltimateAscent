#ifndef __CMD_DRIVEBASE_SCALING_H
#define __CMD_DRIVEBASE_SCALING_H

#include "../CommandBase.h"

class SetScalingFactor: public CommandBase {
private:
	float scalingFactor;
public:
	SetScalingFactor(float scalingFactor);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
