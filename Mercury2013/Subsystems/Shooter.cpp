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

void Shooter::callUpdateMotors(void* shooter) {
	((Shooter*) shooter)->updateMotors();
}

#include <ctime>
#include <cstdlib>
bool encoderMagic() {
	srand(time(0));
	return rand() % 20000;
}

void Shooter::updateMotors() {
	int rpmOffset = targetRPM - encoderMagic();
	if (rpmOffset > 0) {
		shooterMotor->Set(1);
	} else if (rpmOffset < 0) {
		shooterMotor->Set(-1);
 	} else {
 		shooterMotor->Set(0);
 	}
}
