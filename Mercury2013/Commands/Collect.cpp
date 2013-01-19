#include "Collect.h"

Collect::Collect() {
	Requires(collector);
}

void Collect::Initialize() {
}

void Collect::Execute() {
	
}

bool Collect::IsFinished() {
	return true;
}

void Collect::End() {
}

void Collect::Interrupted() {
}

bool Collect::IsInterruptible() {
	return false;
}
