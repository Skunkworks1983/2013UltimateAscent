#ifndef __ANALOGCHANGE_TRIGGER_H__
#define __ANALOGCHANGE_BUTTON_H__

#include "Buttons/Trigger.h"

class AnalogChangeTrigger: public Trigger {
private:
	double changeThreshold;
	int port;
	double lastValue;
public:
	AnalogChangeTrigger(int port, double changeThreshold);
	virtual ~AnalogChangeTrigger();
	virtual bool Get();
};

#endif

