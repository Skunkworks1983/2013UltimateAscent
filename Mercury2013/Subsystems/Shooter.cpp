#include "Shooter.h"

Shooter::Shooter() : Subsystem("Shooter") {
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
