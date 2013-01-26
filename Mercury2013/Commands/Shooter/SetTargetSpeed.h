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
	/**
	 * @brief Creates a command to set the shooter speeds
	 * 
	 * Creates a command that will set the target speed of the shooter to the given speed.
	 * Note, this will not actually arm the shooter, use the ArmShooter command for that.
	 * @param targetSpeed the target RPM
	 */
	SetTargetSpeed(float targetSpeed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
