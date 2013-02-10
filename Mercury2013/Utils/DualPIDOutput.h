#ifndef __DUALPIDOUTPUT_H
#define __DUALPIDOUTPUT_H
#include "WPILib.h"

/**
 * Utility class that writes a single PID output value to two objects.
 * @author Mark Old
 */
class DualPIDOutput: public PIDOutput {
private:
	PIDOutput *PIDOutput1;
	PIDOutput *PIDOutput2;
public:
	/**
	 * Creates a PID Output the will write to two seperate PID outputs.
	 * @param PIDOutput1
	 * @param PIDOutput2
	 */
	DualPIDOutput(PIDOutput* PIDOutput1, PIDOutput* PIDOutput2);
	virtual ~DualPIDOutput();
	virtual void PIDWrite(float output);
};

#endif
