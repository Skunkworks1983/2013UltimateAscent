#ifndef __CMD_SHOOTER_SLOT_LOAD_H
#define __CMD_SHOOTER_SLOT_LOAD_H

#include "WPILib.h"
#include "../CommandBase.h"

class ShooterSlotLoad: public CommandBase {
private:
	CommandGroup loadWithCollectorUp;
	CommandGroup loadWithCollectorDown;
public:
	ShooterSlotLoad();
	~ShooterSlotLoad();
	virtual void Initialize();
	virtual void Execute();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsFinished();
};

#endif
