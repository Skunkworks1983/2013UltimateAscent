#include "UpdateCompressor.h"

UpdateCompressor::UpdateCompressor() {
	Requires(pneumatics);
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

bool UpdateCompressor::IsInterruptible() {
	return true;
}
