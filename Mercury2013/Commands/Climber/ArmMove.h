#ifndef __ARM_MOVE_H
#define __ARM_MOVE_H
#include "WPILib.h"
#include "CommandBase.h"
#include "../Subsystems/Climber.h"

class ArmMove: public CommandBase {
public:
	ArmMove();
	~ArmMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif