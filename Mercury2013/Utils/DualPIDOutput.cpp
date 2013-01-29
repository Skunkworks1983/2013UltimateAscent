#include "DualPIDOutput.h"

DualPIDOutput::DualPIDOutput(PIDOutput* PIDOutput1, PIDOutput* PIDOutput2) {
	this->PIDOutput1 = PIDOutput1;
	this->PIDOutput2 = PIDOutput2;
}

DualPIDOutput::~DualPIDOutput() {
	delete PIDOutput1;
	delete PIDOutput2;
}

void DualPIDOutput::PIDWrite(float output) {
	PIDOutput1->PIDWrite(output);
	PIDOutput2->PIDWrite(output);
}
