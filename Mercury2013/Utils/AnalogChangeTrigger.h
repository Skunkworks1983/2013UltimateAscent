#ifndef __ANALOGCHANGE_TRIGGER_H__
#define __ANALOGCHANGE_BUTTON_H__

#include "Buttons/Trigger.h"
#define OI_POT_GENERIC_CONVERT(val)			((.0858 * val * val * val) - (.5267 * val * val) + (1.081* val) + .0754)

class AnalogChangeTrigger: public Trigger {
private:
	double changeThreshold;
	int port;
	double lastValue;
	Trigger *active;
public:
	AnalogChangeTrigger(int port, double changeThreshold,
			Trigger *active = NULL);
	virtual ~AnalogChangeTrigger();
	virtual bool Get();
};

#endif

