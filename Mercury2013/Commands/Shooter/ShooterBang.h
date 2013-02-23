#ifndef __CMD_SHOOTER_BANG_H
#define __CMD_SHOOTER_BANG_H

#include "../CommandBase.h"

/**
 * @brief Shifts the DriveBase
 * 
 * Shifts the DriveBase using the given shifting style.
 * This does not require an exclusive lock on the DriveBase.
 * @author Westin Miller
 */
class ShooterBang: public CommandBase {
public:
	/**
	 * Different shifting styles.
	 */
	enum ControlType {
		/**
		 * Shifts to low gear.
		 */
		kOff,
		/**
		 * Shifts to high gear.
		 */
		kOn,
		/**
		 * Toggle between low and high gears.
		 */
		kToggle
	};
private:
	bool enableShooterBang;
	ControlType controlType;
public:
	/**
	 * Creates a shifting command that uses the given shifting style.
	 * 
	 * @see ControlType
	 * @param shiftingType the shifting type
	 */
	ShooterBang(ControlType shiftingType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
