#include "HokeyPokey.h" 

HokeyPokey::HokeyPokey(bool position) :
	CommandBase(CommandBase::createNameFromFloat("ClimberPokey", position & 1)) {
	Requires(climber);
	this->position = position;
	SetTimeout(((double) HOKEY_POKEY_TIME) / 1000.0);
	SetInterruptible(false);
}

void HokeyPokey::Initialize() {
	
}

void HokeyPokey::Execute() {
	climber->setPokey(position);
}

bool HokeyPokey::IsFinished() {
	return IsTimedOut() && (climber->getPokey() == position);
}

void HokeyPokey::End() {

}

void HokeyPokey::Interrupted() {

}
