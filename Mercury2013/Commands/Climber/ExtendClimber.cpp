#include "ExtendClimber.h" 

ExtendClimber::ExtendClimber(bool position) :
	CommandBase(CommandBase::createNameFromFloat("ExtendClimber", position & 1)) {
	Requires(climber);
	this->position = position;
	SetTimeout(((double) CLIMBER_PNEUMATIC_TIME) / 1000.0);
}

void ExtendClimber::Initialize() {

}

void ExtendClimber::Execute() {
	climber->setClimberPneumatic(position);
}

bool ExtendClimber::IsFinished() {
	return IsTimedOut() && (climber->getClimberPneumatic() == position);
}

void ExtendClimber::End() {

}

void ExtendClimber::Interrupted() {

}
