#ifndef SET_TARGET_SPEED_COMMAND_H
#define SET_TARGET_SPEED_COMMAND_H

#include "../CommandBase.h"

/**
 * @brief Set the target RPM for the Shooter
 * 
 * Sets the target RPM on the main shooter wheel.
 * This does not require an exclusive lock on the shooter.
 * @author Mark Old
 */
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
