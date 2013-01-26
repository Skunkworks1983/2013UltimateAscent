#include <math.h>
#include "../../Utils/Math.h"
#include "DriveDistance.h"
#include "../../Robotmap.h"

DriveDistance::DriveDistance(float targetDistance) {
	Requires(driveBase);
	this->targetDistance = targetDistance;
}

void DriveDistance::Initialize() {
	driveBase->getLeftEncoder()->Reset();
	driveBase->getRightEncoder()->Reset();
}

void DriveDistance::Execute() {
	leftDistanceRemaining = targetDistance
			- driveBase->getLeftEncoder()->GetDistance();
	rightDistanceRemaining = targetDistance
			- driveBase->getRightEncoder()->GetDistance();

	driveBase->setSpeed(getSpeedFor(leftDistanceRemaining),
			getSpeedFor(rightDistanceRemaining));
}

float DriveDistance::getSpeedFor(float distanceRemaining) {
	if (fabs(distanceRemaining) <= AUTO_DIST_THRESHOLD) {
		return 0.0;
	}
	
	float speedScaleFactor = fabs(distanceRemaining) / AUTO_DIST_SLOW_DOWN;
	return fmin(
			AUTO_DRIVE_DIST_SPEED_MAX,
			(AUTO_DRIVE_DIST_SPEED_RANGE * speedScaleFactor)
					+ AUTO_DRIVE_DIST_SPEED_MIN) * fsign(distanceRemaining);
}

bool DriveDistance::IsFinished() {
	return (fabs(leftDistanceRemaining) <= AUTO_DIST_THRESHOLD) && (fabs(
			rightDistanceRemaining) <= AUTO_DIST_THRESHOLD);
}

void DriveDistance::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void DriveDistance::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}
