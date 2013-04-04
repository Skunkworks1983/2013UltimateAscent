#ifndef __ONBOARD_DIGITAL_TRIGGER_H__
#define __ONBOARD_DIGITAL_TRIGGER_H__

#include "Buttons/Trigger.h"
#include "WPILib.h"

class OnboardDigitalTrigger: public Trigger {
private:
	DigitalInput *source;
	bool expected;
public:
	OnboardDigitalTrigger(DigitalInput *src, bool expected = true);
	virtual ~OnboardDigitalTrigger();
	virtual bool Get();
};

#endif

