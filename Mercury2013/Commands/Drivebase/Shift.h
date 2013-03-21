#ifndef __CMD_DRIVEBASE_SHIFT_H
#define __CMD_DRIVEBASE_SHIFT_H

#include "../CommandBase.h"

/**
 * @brief Shifts the DriveBase
 * 
 * Shifts the DriveBase using the given shifting style.
 * This does not require an exclusive lock on the DriveBase.
 * @author Westin Miller
 */
class Shift: public CommandBase {
public:
	/**
	 * Different shifting styles.
	 */
	enum ShiftType {
		/**
		 * Shifts to low gear.
		 */
		kLow,
		/**
		 * Shifts to high gear.
		 */
		kHigh,
		/**
		 * Toggle between low and high gears.
		 */
		kToggle
	};
private:
	bool toLowGear;
	ShiftType toGear;
public:
	/**
	 * Creates a shifting command that uses the given shifting style.
	 * 
	 * @see ShiftType
	 * @param shiftingType the shifting type
	 */
	Shift(ShiftType shiftingType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
