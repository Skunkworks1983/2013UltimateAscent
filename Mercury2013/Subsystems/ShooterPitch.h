#ifndef __SYS_SHOOTER_PITCH_H // TODO
#define __SYS_SHOOTER_PITCH_H // TODO

#include "WPILib.h"
#include "../RobotMap.h"

/**
 * @brief ShooterPitchPitch subsystem
 * 
 * The subsystem that controls the shooter pitch.
 * Contains a single motor, encoder, and limit switch.
 * @author Mark Old, Westin Miller
 */
class StallableMotor;
class ShooterPitch: public Subsystem {
private:
	SHOOTER_PITCH_MOTOR_TYPE *pitchMotor;
	//StallableMotor *pitchMotor;
	Encoder *pitchEncoder;
	DigitalInput *pitchLimitSwitch;
	AnalogChannel *pitchPot;
	
	float motorSpeedCache;
	bool tunedEncoder;
public:
	ShooterPitch();
	~ShooterPitch();

	float getCurrentPitch();
	float getRealPitch();
	float getMathPitch();
	bool setPitchMotorSpeed(float f, float error);
	bool isPitchGrounded();
	bool isPitchTuned();
	
	void motorSafety();
	
	virtual void InitDefaultCommand();
};

#endif
