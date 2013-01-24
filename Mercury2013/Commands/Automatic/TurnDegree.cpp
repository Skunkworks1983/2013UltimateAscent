#include <math.h>
#include "TurnDegree.h"
#include "../../Robotmap.h"

TurnDegree::TurnDegree(float targetAngle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	// TurnDegree 
	Requires(driveBase);
	this->m_targetAngle = targetAngle;
}

// Called just before this Command runs the first time
void TurnDegree::Initialize() {
	//	reset gyro
	driveBase->getGyro()->Reset();
	this->m_count = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnDegree::Execute() {
	float signSpeed = AUTO_TURN_GYRO_SIGN_SPEED;
	/** Compute remaining angle.
	 * If angle remaining is greater than ___ degrees, continue with motor on/maintaining speed. 
	 * If angle remaining is lesser than ___ degrees, turn the motor off.  
	 * When less than the degrees desired, motor off until practically no power at full stop on target angle.
	 */
	//Executes the angle command in order to go to the given angle.
	this->m_angleTurned = driveBase->getGyro()->GetAngle();
	if ((fabs(this->m_targetAngle) - fabs(this->m_angleTurned)) < 0)
		signSpeed = -1;
	else
		signSpeed = AUTO_TURN_GYRO_SIGN_SPEED
;
	//if angle traveled is greater than or equal to the target angle, motors are set to null
	if (fabs(this->m_angleTurned) >= fabs(this->m_targetAngle)) {
		this->CommandBase::driveBase->setSpeed(0, 0);
	} else {
		this->CommandBase::driveBase->setSpeed(-1 * signSpeed * AUTO_TURN_GYRO_SIGN_HALF,
				signSpeed * AUTO_TURN_GYRO_SIGN_HALF);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnDegree::IsFinished() {
	return this->m_angleTurned >= this->m_targetAngle;
	/*return false;
	this->m_angleTurned < this->m_targetAngle;
*/
	//Return true when the angle you've traveled reaches the angle you've been requested to travel.
	//Snap out of the loop and into the TurnDegree end
}

// Called once after isFinished returns true.
void TurnDegree::End() {
	//Sets both motors to Zero, ends the program.
	driveBase->setSpeed(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run.
void TurnDegree::Interrupted() {
	//Stops loop, in case of emergency, it will pop it out no matter angleTurned.
	driveBase->setSpeed(0.0, 0.0);
}

