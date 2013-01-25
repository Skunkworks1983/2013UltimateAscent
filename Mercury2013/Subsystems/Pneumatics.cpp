#include "Pneumatics.h"

#include "../Robotmap.h"
#include "../Commands/UpdateCompressor.h"

Pneumatics::Pneumatics() :
	Subsystem("Pneumatics") {
	compressorRelay = new Relay(COMPRESSOR_RELAY);
	compressorSwitch = new DigitalInput(1, 0);//COMPRESSOR_SWITCH);
}

Pneumatics::~Pneumatics() {
	delete compressorRelay;
	delete compressorSwitch;
}

bool Pneumatics::isBelowPressure() {
	printf("%d\n", compressorSwitch->Get());
	return (~compressorSwitch->Get()) & 1;
}

void Pneumatics::setCompressorState(bool active) {
	compressorRelay->Set(active ? Relay::kForward : Relay::kOff);
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new UpdateCompressor());
}
