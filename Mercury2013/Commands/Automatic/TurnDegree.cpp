#include <math.h>
#include "../../Utils/Math.h"
#include "TurnDegree.h"
#include "../../Robotmap.h"

TurnDegree::TurnDegree(float targetAngle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	// TurnDegree 
	Requires(driveBase);
	m_targetAngle = targetAngle;
	if (m_targetAngle >= 0)
		m_direction = 1;
	else
		m_direction = -1;
}

// Called just before this Command runs the first time
void TurnDegree::Initialize() {
	//	reset local varabes
	driveBase->getGyro()->Reset();
	m_count = 0;
	m_angleTurned = 0;
	m_angleRemaining = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnDegree::Execute() {
	float signSpeed = AUTO_TURN_GYRO_SIGN_SPEED;

	m_angleRemaining = m_targetAngle - driveBase->getGyro()->GetAngle();

	float turnScaleFactor = fabs(m_angleRemaining) / AUTO_TURN_SLOW_DOWN;

	float turnSpeed = fmin(AUTO_TURN_SPEED_MAX,
			(AUTO_TURN_SPEED_RANGE * turnScaleFactor) + AUTO_TURN_SPEED_MIN)
			* fsign(m_angleRemaining);
	if (fabs(m_angleRemaining) <= AUTO_TURN_GYRO_THRESHOLD) {
		turnSpeed = 0;
	}

	driveBase->setSpeed(turnSpeed, -turnSpeed);
	

//	/** Compute remaining angle.
//	 * If angle remaining is greater than ___ degrees, continue with motor on/maintaining speed. 
//	 * If angle remaining is lesser than ___ degrees, turn the motor off.  
//	 * When less than the degrees desired, motor off until practically no power at full stop on target angle.
//	 */
//	//Executes the angle command in order to go to the given angle.
//	//m_angleTurned = driveBase->getGyro()->GetAngle();
//	//if ((fabs(m_targetAngle) - fabs(m_angleTurned)) < 0)
//		//signSpeed = -1;
//	else
//		signSpeed = AUTO_TURN_GYRO_SIGN_SPEED;
//
//	//if angle traveled is greater than or equal to the target angle, motors are set to null
//	if (fabs(m_angleTurned) >= fabs(m_targetAngle)) {
//		CommandBase::driveBase->setSpeed(0, 0);
//	} else {
//		CommandBase::driveBase->setSpeed(
//				-1 * signSpeed * AUTO_TURN_GYRO_SIGN_HALF,
//				signSpeed * AUTO_TURN_GYRO_SIGN_HALF);
	// }
}


// Make this return true when this Command no longer needs to run execute()
bool TurnDegree::IsFinished() {
	return m_angleTurned >= m_targetAngle;
	/*return false;
	 m_angleTurned < m_targetAngle;
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

