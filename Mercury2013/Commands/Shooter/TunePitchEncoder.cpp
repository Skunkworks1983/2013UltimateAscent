#include "TunePitchEncoder.h"
#include <math.h>

TunePitchEncoder::TunePitchEncoder() :
	CommandBase("TunePitchEncoder") {
	Requires(shooterPitch);
	SetInterruptible(false);
	SetRunWhenDisabled(true);
}

void TunePitchEncoder::Initialize() {

}

void TunePitchEncoder::ExternalRun() {
	Execute();
	if (IsFinished()) {
		End();
	}
}

void TunePitchEncoder::Execute() {
	shooterPitch->setPitchMotorSpeed(-1.0);
}

bool TunePitchEncoder::IsFinished() {
	return shooterPitch->isPitchGrounded();
}

void TunePitchEncoder::End() {
	//Forces the shooter to reset it
	shooterPitch->setPitchMotorSpeed(-1.0);
	shooterPitch->setPitchMotorSpeed(0);
}

void TunePitchEncoder::Interrupted() {
	shooterPitch->setPitchMotorSpeed(-1.0);
	shooterPitch->setPitchMotorSpeed(0);
}
