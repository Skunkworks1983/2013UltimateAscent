#include <math.h>
#include "DriveDistance.h"

DriveDistance::DriveDistance(float targetDistance) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	// DriveDistance 
	Requires(driveBase);
	this->m_targetDistance = targetDistance;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	//	reset leftEncoder();
	CommandBase::driveBase->getLeftEncoder()->Reset();
	//	reset rightEncoder();	
	CommandBase::driveBase->getRightEncoder()->Reset();
	//putting all encoders to 0
	this->m_counter = 0;
	this->m_distanceDriven = 0;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	/** Compute remaining distance.
	 * If distance remaining is greater than ___ inches, continue with motor on/maintaining speed. 
	 * If distance remaining is lesser than ___ inches, turn the motor off.  
	 * When less than the inches desired, motor off until practically no power at full stop on target destination.
	 */
	
	if(this->m_distanceDriven == this->m_targetDistance) 
	
	//Executes the distance command in order to go to the given distance.
	float leftDist = CommandBase::driveBase->getLeftEncoder()->GetDistance();
	//While driving the robot reads encoders in order to know how far it has traveled
	float rightDist = CommandBase::driveBase->getRightEncoder()->GetDistance();
	//Upon execution, the motors will continue to run until encoders realize DriveDistance=Finished
	//	CommandBase::driveBase->SetSpeed(fmin(1, (distance - leftDist)/24), fmin(1,
	//					(distance - rightDist)/24));
	//Set motors to half power, let them go until you are within a certain distance.
	//	if (fabs(leftDist - distance) < AUTO_DIST_THRESHOLD ||fabs(rightDist - distance) < AUTO_DIST
	//TODO MAKE THIS UNBROKEN: REFER TO DRIVEDISTANCE.CPP in FRC UTILITIES
	//if distanceTraveled<targetDistance turn motors on
	//else turn motor off		
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	return false;
	//Return true when the distance you've traveled reaches the distance you've been requested to travel.
	//Snap out of the loop and hop into the DriveDistance void
}

// Called once after isFinished returns true.
void DriveDistance::End() {
	//Sets both motors to Zero, ends the program.
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run.
void DriveDistance::Interrupted() {
	//Stops loop, in case of emergency, it will pop it out no matter the distance.	
}
