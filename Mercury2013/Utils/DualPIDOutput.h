#ifndef __DUALPIDOUTPUT_H
#define __DUALPIDOUTPUT_H
#include "WPILib.h"

class DualPIDOutput: public PIDOutput {
private:
	PIDOutput *PIDOutput1;
	PIDOutput *PIDOutput2;
public:
	DualPIDOutput(PIDOutput* PIDOutput1, PIDOutput* PIDOutput2);
	virtual ~DualPIDOutput();
	virtual void PIDWrite(float output);
};

#endif
