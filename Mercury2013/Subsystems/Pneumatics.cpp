#include "Pneumatics.h"

#include "../Robotmap.h"
#include "../Commands/UpdateCompressor.h"

Pneumatics::Pneumatics() :
	Subsystem("Pneumatics") {
	printf("Creating Pneumatics...");
	compressorRelay = new Relay(COMPRESSOR_RELAY);
	compressorSwitch = new DigitalInput(COMPRESSOR_SWITCH);
	
	LiveWindow::GetInstance()->AddSensor("Pneumatics", "Compressor State", compressorSwitch);
	LiveWindow::GetInstance()->AddActuator("Pneumatics", "Compressor Relay", compressorRelay);
	
	printf("Done!\n");
}

Pneumatics::~Pneumatics() {
	delete compressorRelay;
	delete compressorSwitch;
}

bool Pneumatics::isBelowPressure() {
	return (~compressorSwitch->Get()) & 1;
}

void Pneumatics::setCompressorState(bool active) {
	compressorRelay->Set(active ? Relay::kForward : Relay::kOff);
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new UpdateCompressor());
}
