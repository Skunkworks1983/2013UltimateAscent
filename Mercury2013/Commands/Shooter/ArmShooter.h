#ifndef SHOOT_COMMAND_H
#define SHOOT_COMMAND_H

#include "../CommandBase.h"

/**
 * Either arms or disarms the main shooter wheel.
 * This does not require an exclusive lock on the shooter.
 * @author Mark Old
 */
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
