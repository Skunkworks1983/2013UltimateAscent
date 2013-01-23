#ifndef SHOOT_COMMAND_H
#define SHOOT_COMMAND_H

#include "../CommandBase.h"

class ArmShooter: public CommandBase {
public:
	enum ArmType {
		kOn, kOff, kToggle
	};
private:
	bool enabled;
	ArmType armType;
public:
	ArmShooter(ArmType armType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
