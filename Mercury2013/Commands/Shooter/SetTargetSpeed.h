#ifndef SET_TARGET_SPEED_COMMAND_H
#define SET_TARGET_SPEED_COMMAND_H

#include "../CommandBase.h"

class SetTargetSpeed: public CommandBase {
	float targetSpeed;
public:
	SetTargetSpeed(float targetSpeed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
