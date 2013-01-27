#ifndef DRIVE_DISTANCE_H
#define DRIVE_DISTANCE_H
#include "../../Subsystems/DriveBase.h" 
#include "../CommandBase.h"

/**
 * @brief Uses the DriveBase and it's encoders to drive a certain distance.
 * 
 * This command requires an exclusive lock on the DriveBase, as well as encoders.
 * @author Owen Mattson
 */
class DriveDistance: public CommandBase {
private:
	float targetDistance;
	float leftDistanceRemaining;
	float rightDistanceRemaining;
	/**
	 * @brief Calculates the motor speed for the given remaining distance.
	 * 
	 * @param remainingDistance the remaining distance, in inches
	 * @return the motor speed
	 */
	float getSpeedFor(float remainingDistance);
public:
	/**
	 * @brief Creates a command to drive a certain distance.
	 * 
	 * Creates a drive distance command that will drive the specified distance,
	 * then stop, in a direction specified by the sign.
	 * @param targetDistance the target distance, in inches
	 */
	DriveDistance(float targetDistance);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif
