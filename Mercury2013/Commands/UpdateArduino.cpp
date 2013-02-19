#include "UpdateArduino.h"

UpdateArduino::UpdateCompressor() {
	Requires(arduino);
	SetInterruptible(true);
}

void UpdateArduino::Initialize() {
	arduino->Arduino(Arduino::kSerial, 9600);
}

void UpdateArduino::Execute() {
	printf("%s\n", arduino->GetData());
}

bool UpdateArduino::IsFinished() {
	return arduino->IsValid();
}

void UpdateArduino::End() {
}

void UpdateArduino::Interrupted() {
}
