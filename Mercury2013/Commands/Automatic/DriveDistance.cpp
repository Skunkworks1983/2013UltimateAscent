#include <math.h>
#include "../../Utils/Math.h"
#include "DriveDistance.h"
#include "../../Robotmap.h"

DriveDistance::DriveDistance(float targetDistance) :
	CommandBase(CommandBase::createNameFor("DriveDistance", targetDistance)) {
	Requires(driveBase);
	this->targetDistance = targetDistance;
}

void DriveDistance::Initialize() {
	driveBase->getLeftEncoder()->Reset();
	driveBase->getRightEncoder()->Reset();
	stability = 0;
}

void DriveDistance::Execute() {
	leftDistanceRemaining = targetDistance
			- driveBase->getLeftEncoder()->GetDistance();
	rightDistanceRemaining = targetDistance
			- driveBase->getRightEncoder()->GetDistance();

	driveBase->setSpeed(getSpeedFor(leftDistanceRemaining),
			getSpeedFor(rightDistanceRemaining));

	if ((fabs(leftDistanceRemaining) <= AUTO_DRIVE_DIST_THRESHOLD) && (fabs(
			rightDistanceRemaining) <= AUTO_DRIVE_DIST_THRESHOLD)) {
		stability++;
	} else {
		stability = 0;
	}
}

float DriveDistance::getSpeedFor(float distanceRemaining) {
	if (fabs(distanceRemaining) <= AUTO_DRIVE_DIST_THRESHOLD) {
		return 0.0;
	}

	float speedScaleFactor = fabs(distanceRemaining)
			/ AUTO_DRIVE_DIST_SLOW_DOWN;
	return fmin(
			AUTO_DRIVE_DIST_SPEED_MAX,
			(AUTO_DRIVE_DIST_SPEED_RANGE * speedScaleFactor)
					+ AUTO_DRIVE_DIST_SPEED_MIN) * fsign(distanceRemaining);
}

bool DriveDistance::IsFinished() {
	return stability >= AUTO_DRIVE_DIST_STABILITY;
}

void DriveDistance::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void DriveDistance::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}
