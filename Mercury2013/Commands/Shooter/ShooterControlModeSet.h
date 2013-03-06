#ifndef __CMD_SHOOTER_CONTROL_MODE_SET_H
#define __CMD_SHOOTER_CONTROL_MODE_SET_H

#include "../CommandBase.h"

/**
 * @brief Changes the shooter mode
 * 
 * Changes the shooter control mode to the given mode.
 * This does not require an exclusive lock on the shooter.
 * @author Westin Miller
 */
class ShooterControlModeSet: public CommandBase {
private:
	Shooter::ControlType controlType;
public:
	/**
	 * Creates a shooter control mode changing command.
	 * @param sControlType the control mode
	 */
	ShooterControlModeSet(Shooter::ControlType sControlType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
