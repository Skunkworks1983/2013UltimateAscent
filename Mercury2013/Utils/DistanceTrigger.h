#ifndef __DISTANCE_TRIGGER_H__
#define __DISTANCE_TRIGGER_H__

#include "Buttons/Trigger.h"
#include "WPILib.h"

class DistanceTrigger: public Trigger {
private:
	Encoder *srcA;
	Encoder *srcB;
	double lowerRange;
public:
	DistanceTrigger(double lowerRange, Encoder *srcA, Encoder *srcB = NULL);
	virtual ~DistanceTrigger();
	virtual bool Get();
};

#endif

