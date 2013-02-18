#include "TunePitchEncoder.h"
#include <math.h>

TunePitchEncoder::TunePitchEncoder() :
	CommandBase("TunePitchEncoder") {
	Requires(shooter);
}

void TunePitchEncoder::Initialize() {

}

void TunePitchEncoder::Execute() {
	shooter->setPitchMotorSpeed(-1.0);
}

bool TunePitchEncoder::IsFinished() {
	return shooter->isPitchGrounded();
}

void TunePitchEncoder::End() {
	//Forces the shooter to reset it
	shooter->setPitchMotorSpeed(-1.0);
	shooter->setPitchMotorSpeed(0);
}

void TunePitchEncoder::Interrupted() {
	shooter->setPitchMotorSpeed(0);
}
