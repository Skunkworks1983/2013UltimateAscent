#ifndef SHIFT_H
#define SHIFT_H

#include "../CommandBase.h"

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
