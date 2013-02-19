#include "UpdateArduino.h"

UpdateArduino::UpdateArduino() {
	Requires(arduino);
	SetInterruptible(true);
}

void UpdateArduino::Initialize() {

}

void UpdateArduino::Execute() {
	printf("%s\n", arduino->GetData().c_str());
}

bool UpdateArduino::IsFinished() {
	return arduino->IsValid();
}

void UpdateArduino::End() {
}

void UpdateArduino::Interrupted() {
}
