#ifndef __VALUE_CHANGE_TRIGGER_H__
#define __VALUE_CHANGE_TRIGGER_H__

#include "Buttons/Trigger.h"

#define FORCE_VALUE_CHANGE			-100.0

typedef double (*GET_DOUBLE)();

class ValueChangeTrigger: public Trigger {
private:
	GET_DOUBLE getValue;
	double changeThreshold;
	double lastValue;
public:
	ValueChangeTrigger(GET_DOUBLE getValue, double changeThreshold);
	virtual ~ValueChangeTrigger();
	virtual bool Get();
};

#endif

