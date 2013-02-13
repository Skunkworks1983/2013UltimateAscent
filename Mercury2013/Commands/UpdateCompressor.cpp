#include "UpdateCompressor.h"

UpdateCompressor::UpdateCompressor() :
	CommandBase("UpdateCompressor") {
	Requires(pneumatics);
	SetInterruptible(true);
}

void UpdateCompressor::Initialize() {

}

void UpdateCompressor::Execute() {
	pneumatics->setCompressorState(pneumatics->isBelowPressure());
}

bool UpdateCompressor::IsFinished() {
	return false;
}

void UpdateCompressor::End() {
	pneumatics->setCompressorState(false);
}

void UpdateCompressor::Interrupted() {
	pneumatics->setCompressorState(false);
}
