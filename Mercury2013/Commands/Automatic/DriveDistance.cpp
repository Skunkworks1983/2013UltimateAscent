#include <math.h>
#include "../../Utils/Math.h"
#include "DriveDistance.h"
#include "../../Robotmap.h"

DriveDistance::DriveDistance(float targetDistance) :
			CommandBase(
					CommandBase::createNameFromFloat("DriveDistance",
							targetDistance)) {
	Requires(driveBase);
	this->targetDistance = targetDistance;
	this->reset = true;
}

DriveDistance *DriveDistance::setResetEncoder(bool r) {
	this->reset = r;
	return this;
}

void DriveDistance::Initialize() {
	if ((~reset) & 1) {
		targetDistance = ((targetDistance
				- driveBase->getLeftEncoder()->GetDistance()) + (targetDistance
				- driveBase->getRightEncoder()->GetDistance())) / 2.0;
	}
	driveBase->getLeftEncoder()->Reset();
	driveBase->getRightEncoder()->Reset();
	stability = 0;
}

void DriveDistance::Execute() {
	leftDistanceRemaining = targetDistance
			- driveBase->getLeftEncoder()->GetDistance();
	rightDistanceRemaining = targetDistance
			- driveBase->getRightEncoder()->GetDistance();
	float lDiff = min(
			(AUTO_DRIVE_DIST_CATCHUP - fabs(
					leftDistanceRemaining - rightDistanceRemaining))
					/ AUTO_DRIVE_DIST_CATCHUP, 1.0);
	float rDiff = min(
			(AUTO_DRIVE_DIST_CATCHUP - fabs(
					rightDistanceRemaining - leftDistanceRemaining))
					/ AUTO_DRIVE_DIST_CATCHUP, 1.0);
	driveBase->setSpeed(getSpeedFor(leftDistanceRemaining) * lDiff,
			getSpeedFor(rightDistanceRemaining) * rDiff);

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

Command *DriveDistance::invertDriveCommand(void *arg) {
	DriveDistance *orig = (DriveDistance*) arg;
	float leftD = -(orig->targetDistance - orig->leftDistanceRemaining);
	float rightD = -(orig->targetDistance - orig->rightDistanceRemaining);
	return new DriveDistance((leftD + rightD) / 2.0);
}
