#include <math.h>
#include "DriveDistance.h"
DriveDistance::DriveDistance(float targetDistance, SlopeType MySlope) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	// DriveDistance 
	Requires(driveBase);
	m_targetDistance = targetDistance;
}
// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	//	reset leftEncoder();
	driveBase->getLeftEncoder()->Reset();
	//	reset rightEncoder();	
	driveBase->getRightEncoder()->Reset();
	//putting all encoders to 0
	m_counter = 0;
	//not really using this counter.
	m_distanceDriven = 0;
	//resetting distance driven to 0  
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	//ExecuteFlat();

	switch (m_SlopeType) {
	case flat:
		ExecuteFlat();
	case linear:
		ExecuteLinear();
		break;
	case quadratic:
		ExecuteQuadratic();
		break;
	default:
		ExecuteFlat();
	}
}
void DriveDistance::ExecuteFlat() {
	/** Compute remaining distance.
	 * If distance remaining is greater than ___ inches, continue with motor on/maintaining speed. 
	 * If distance remaining is lesser than ___ inches, turn the motor off.  
	 * When less than the inches desired, motor off until practically no power at full stop on target destination.
	 */
	//Executes the distance command in order to go to the given distance.
	float leftDist = driveBase->getLeftEncoder()->GetDistance();
	//While driving the robot reads encoders in order to know how far it has traveled
	float rightDist = driveBase->getRightEncoder()->GetDistance();
	m_distanceDriven = (leftDist + rightDist) / 2;
	//if distance traveled is greater than or equal to the target distance, motors are set to null
	if (m_distanceDriven >= m_targetDistance) {
		driveBase->setSpeed(0, 0);
	} else {
		driveBase->setSpeed(0.5, 0.5);
	}
	//if dist traveled is less than target distance, the motors will trundle along with half power
}
void DriveDistance::ExecuteLinear() {
	/** Compute remaining distance.
	 * If distance remaining is greater than ___ inches, continue with motor on/maintaining speed. 
	 * If distance remaining is lesser than ___ inches, turn the motor off.  
	 * When less than the inches desired, motor off until practically no power at full stop on target destination.
	 *If distanceDriven = 0 setSpeed (0.25, 0.25)
	 *add .002 every rotation
	 *Maximum speed = 50
	 */
	if (m_distanceDriven <= 0)
		driveBase->setSpeed(0.25, 0.25);
	//if (m_distanceDriven > 0)
	//	driveBase
	//^Todo^ make speeds not zero please

	//Executes the distance command in order to go to the given distance.
	float leftDist = driveBase->getLeftEncoder()->GetDistance();
	//While driving the robot reads encoders in order to know how far it has traveled
	float rightDist = driveBase->getRightEncoder()->GetDistance();
	//m_distanceDriven = (leftDist + rightDist) / 2;
	//if distance traveled is greater than or equal to the target distance, motors are set to null
	if (m_distanceDriven >= m_targetDistance) {
		driveBase->setSpeed(0, 0);
	} else {
		driveBase->setSpeed(0.5, 0.5);
	}
	//if dist traveled is less than target distance, the motors will trundle along with half power
}
void DriveDistance::ExecuteQuadratic() {
	/** Compute remaining distance.
	 * If distance remaining is greater than ___ inches, continue with motor on/maintaining speed. 
	 * If distance remaining is lesser than ___ inches, turn the motor off.  
	 * When less than the inches desired, motor off until practically no power at full stop on target destination.
	 */
	//Executes the distance command in order to go to the given distance.
	float leftDist = driveBase->getLeftEncoder()->GetDistance();
	//While driving the robot reads encoders in order to know how far it has traveled
	float rightDist = driveBase->getRightEncoder()->GetDistance();
	m_distanceDriven = (leftDist + rightDist) / 2;
	//if distance traveled is greater than or equal to the target distance, motors are set to null
	if (m_distanceDriven >= m_targetDistance) {
		driveBase->setSpeed(0, 0);
	} else {
		driveBase->setSpeed(0.5, 0.5);
	}
	//if dist traveled is less than target distance, the motors will trundle along with half power
}
// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	return m_distanceDriven >= m_targetDistance;
	//Return true when the distance you've traveled reaches the distance you've been requested to travel.
	//Snap out of the loop and hop into the DriveDistance void
}

// Called once after isFinished returns true.
void DriveDistance::End() {
	//Sets both motors to Zero, ends the program.
	driveBase->setSpeed(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run.
void DriveDistance::Interrupted() {
	//Stops loop, in case of emergency, it will pop it out no matter the distance.
	driveBase->setSpeed(0.0, 0.0);
	//no matter what happens, Interrupt will kill the speed
}
