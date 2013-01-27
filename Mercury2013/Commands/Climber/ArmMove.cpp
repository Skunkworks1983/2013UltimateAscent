#include "ArmMove.h"

ArmMove::ArmMove() {

}

ArmMove::~ArmMove() {

}

void ArmMove::Initialize() {
	
}

void ArmMove::Execute() {
	bool hooked = false;
	while (hooked == false) {
		climber->setArmsMotor(.25);
		if (climber->getPosition() >= 100) { //TODO actuall number har
			while ((climber->getButton(1) == false)
					and (climber->getButton(2) == false)) {
						climber->setArmsMotor(-.25);								
			}
				
			hooked = true;
			climber->setArmsMotor(0);
		}
	}
}

bool ArmMove::IsFinished() {
	return false;
}

void ArmMove::End() {
	climber->setArmsMotor(0);
}

void ArmMove::Interrupted() {
	climber->setArmsMotor(0);
}
