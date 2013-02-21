#include "Climber.h"
#include <math.h>

Climber::Climber() :
		Subsystem("Climber") {
	printf("Creating Climber...\t");
	pokeySolenoid = new SolenoidPair(CLIMBER_POKEY);
	climberSolenoid = new SolenoidPair(CLIMBER_PNEUMATIC);

	LiveWindow::GetInstance()->AddActuator("Climber", "Pokey Stick",
			pokeySolenoid);
	LiveWindow::GetInstance()->AddSensor("Climber", "Climber Solenoid",
			climberSolenoid);
	printf("Done!");
}

Climber::~Climber() {
	delete pokeySolenoid;
	delete climberSolenoid;
}

void Climber::setPokey(bool position) {
	pokeySolenoid->Set(position);
}

bool Climber::getPokey() {
	return pokeySolenoid->Get();
}

void Climber::setClimberPneumatic(bool position) {
	climberSolenoid->Set(position);
}

bool Climber::getClimberPneumatic() {
	return climberSolenoid->Get();
}

void Climber::InitDefaultCommand() {

}
