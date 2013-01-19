#include "ArmMove.h"

ArmMove::ArmMove() {
	
}

ArmMove::~ArmMove() {
	
}

void ArmMove::Initialize() {
	
}

void ArmMove::Execute() {
	for (int i = 0; i < 2; i++) {
		bool hooked = false;
		while (hooked == false) {
			climber->setArmsMotor(.25);
			if (climber->getPosition() >= 100) { //TODO actuall number har
				while ((climber->getSwitch(1) == false) and (climber->getSwitch(2) == false)) {
					climber->setArmsMotor(-.25);
					hooked = true;
				}
			}
		}
	}
}

bool ArmMove::IsFinished() {
	
}

void ArmMove::End() {
	
}

void ArmMove::Interrupted() {
	
}
