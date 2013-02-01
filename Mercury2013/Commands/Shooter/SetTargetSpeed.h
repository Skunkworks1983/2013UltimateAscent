#ifndef __CMD_SHOOT_SETTARGETSPEED_H
#define __CMD_SHOOT_SETTARGETSPEED_H

#include "../CommandBase.h"

/**
 * @brief Set the target RPM for the Shooter
 * 
 * Sets the target RPM on the main Shooter wheel.
 * This does not require an exclusive lock on the Shooter.
 * @author Mark Old
 */
class SetTargetSpeed: public CommandBase {
	float targetSpeed;
public:
	/**
	 * @brief Creates a command to set the Shooter speeds
	 * 
	 * Creates a command that will set the target speed of the Shooter to the given speed.
	 * Note, this will not actually arm the Shooter, use the ArmShooter command for that.
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
