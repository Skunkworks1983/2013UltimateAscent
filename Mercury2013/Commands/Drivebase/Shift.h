#ifndef SHIFT_H
#define SHIFT_H

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
	enum ShiftType {
		kLow, kHigh, kToggle
	};
private:
	bool toLowGear;
	ShiftType toGear;
public:
	Shift(ShiftType shiftingType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
