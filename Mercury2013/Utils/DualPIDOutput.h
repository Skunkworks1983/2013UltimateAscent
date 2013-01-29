#ifndef __DUAL_PID_OUTPUT_H
#define __DUAL_PID_OUTPUT_H
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
