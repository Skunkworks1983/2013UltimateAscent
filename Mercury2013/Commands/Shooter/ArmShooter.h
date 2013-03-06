#ifndef __CMD_ARM_SHOOTER_H
#define __CMD_ARM_SHOOTER_H

#include "../CommandBase.h"

/**
 * @brief Arms or disarms the Shooter wheel
 * 
 * Either arms or disarms the main shooter wheel.
 * This does not require an exclusive lock on the shooter.
 * @author Mark Old
 */
class ArmShooter: public CommandBase {
public:
	/**
	 * Different arming methods.
	 */
	enum ArmType {
		/**
		 * Disarms the shooter.
		 */
		kOff,
		/**
		 * Arms the shooter.
		 */
		kOn,
		/**
		 * Toggle between armed and disarmed.
		 */
		kToggle
	};
private:
	bool enabled;
	ArmType armType;
public:
	/**
	 * @brief Creates a shooter arm command.
	 * 
	 * Creates a command that will use the specified arming style to arm the shooter.
	 * @param armType the arming style
	 */
	ArmShooter(ArmType armType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
