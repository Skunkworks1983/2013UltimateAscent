#ifndef __SYS_SHOOTER_PITCH_H // TODO
#define __SYS_SHOOTER_PITCH_H // TODO

#include "WPILib.h"
#include "../RobotMap.h"

/**
 * @brief ShooterPitchPitch subsystem
 * 
 * The subsystem that controls the shooter pitch.
 * Contains a single motor, encoder, and limit switch.
 * @author Mark Old
 */
class ShooterPitch: public Subsystem {
private:
	SHOOTER_PITCH_MOTOR_TYPE *pitchMotor;
	Encoder *pitchEncoder;
	DigitalInput *pitchLimitSwitch;
	
	bool tunedEncoder;
public:
	ShooterPitch();
	~ShooterPitch();

	float getCurrentPitch();
	float getRealPitch();
	bool setPitchMotorSpeed(float f);
	bool isPitchGrounded();
	bool isPitchTuned();
	
	virtual void InitDefaultCommand();
};

#endif
