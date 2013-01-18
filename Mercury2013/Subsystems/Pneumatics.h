#ifndef _SHIFTER_H
#define _SHIFTER_H

#include "WPILib.h"

class Pneumatics : public Subsystem {
private:
	DigitalInput *compressorSwitch;
	Relay *compressorRelay;
public:
	Pneumatics();
	~Pneumatics();
	
	bool isBelowPressure();
	void setCompressorState(bool state);
	
	virtual void InitDefaultCommand();
};

#endif
