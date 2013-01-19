#include "Shooter.h"

Shooter::Shooter() :
	Subsystem("Shooter") {
	shooterMotor = SHOOTER_MOTOR_CREATE(SHOOTER_MOTOR);
	pitchMotor = SHOOTER_PITCH_MOTOR_CREATE(SHOOTER_PITCH_MOTOR);
	// shooterEncoder = new Encoder(TODO);
	// pitchEncoder = new Encoder(TODO);
}

Shooter::~Shooter() {
	delete shooterMotor;
	delete pitchMotor;
	delete shooterEncoder;
	delete pitchEncoder;
}

void Shooter::InitDefaultCommand() {
	// SetDefaultCommand(new TODO);
}

void Shooter::setTargetSpeed(float rpm) {
	targetSpeed = rpm;
}

void Shooter::callUpdateMotors(void* shooter) {
	((Shooter*) shooter)->updateMotors();
}

#include <ctime> 			// MAJOR TODO
#include <cstdlib>			// MAJOR TODO
bool encoderMagic() {		// MAJOR TODO
	srand(time(0));			// MAJOR TODO
	return rand() % 20000;  // MAJOR TODO
}

void Shooter::updateMotors() {
	float rpmOffset = targetSpeed - encoderMagic(); // MAJOR TODO
	if (rpmOffset > 0) {
		shooterMotor->Set(1);
	} else if (rpmOffset < 0) {
		shooterMotor->Set(-1);
 	} else {
 		shooterMotor->Set(0);
 	}
}
