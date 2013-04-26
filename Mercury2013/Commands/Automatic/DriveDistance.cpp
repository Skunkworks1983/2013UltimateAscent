#include <math.h>
#include "../../Utils/Math.h"
#include "DriveDistance.h"
#include "../../Robotmap.h"

// TODO Fix the side-to-side drift.  Gyro?
DriveDistance::DriveDistance(float targetDistance, float tStable, float tThresh) :
			CommandBase(
					CommandBase::createNameFromFloat("DriveDistance",
							targetDistance)) {
	Requires(driveBase);
	this->targetDistance = targetDistance;
	this->tStable = tStable;
	this->threshold = tThresh;
	this->reset = true;
	this->minSpeed = AUTO_DRIVE_DIST_SPEED_MIN;
	this->maxSpeed = AUTO_DRIVE_DIST_SPEED_MAX;
}

DriveDistance *DriveDistance::setResetEncoder(bool r) {
	this->reset = r;
	return this;
}

DriveDistance *DriveDistance::setOutputRange(float min, float max) {
	this->minSpeed = min;
	this->maxSpeed = max;
	return this;
}

void DriveDistance::Initialize() {
	if (!reset) {
		targetDistance = ((targetDistance
				- driveBase->getLeftEncoder()->GetDistance()) + (targetDistance
				- driveBase->getRightEncoder()->GetDistance())) / 2.0;
	}
	driveBase->getLeftEncoder()->Reset();
	driveBase->getRightEncoder()->Reset();
	driveBase->getGyro()->Reset();
	stability = 0;
}

void DriveDistance::Execute() {
	leftDistanceRemaining = targetDistance
			- driveBase->getLeftEncoder()->GetDistance();
	rightDistanceRemaining = targetDistance
			- driveBase->getRightEncoder()->GetDistance();
	float lSpeed = getSpeedFor(leftDistanceRemaining,
			driveBase->getLeftEncoder()->GetRate());
	float rSpeed = getSpeedFor(rightDistanceRemaining,
			driveBase->getRightEncoder()->GetRate());
#if 1 /* USE GYRO STRAIGHT*/
	float curve = driveBase->getGyro()->GetAngle() * fsign(
			(rSpeed + lSpeed) / 2.0);
	float ratio = 1.0 - (fabs(curve) / 2.0);
	if (curve < 0.0) {
		rSpeed *= ratio;
	} else if (curve > 0.0) {
		lSpeed *= ratio;
	}
#else
	lSpeed *= fmax(
			fmin(
					(AUTO_DRIVE_DIST_CATCHUP - (rightDistanceRemaining
									- leftDistanceRemaining))
					/ AUTO_DRIVE_DIST_CATCHUP, 1.0), 0.0);
	rSpeed *= fmax(
			fmin(
					(AUTO_DRIVE_DIST_CATCHUP - (leftDistanceRemaining
									- rightDistanceRemaining))
					/ AUTO_DRIVE_DIST_CATCHUP, 1.0), 0.0);
#endif
	driveBase->setSpeed(lSpeed, rSpeed);
	if ((fabs(leftDistanceRemaining) <= threshold) || (fabs(
			rightDistanceRemaining) <= threshold)) {
		stability++;
	} else {
		stability = 0;
	}
}

float DriveDistance::getSpeedFor(float distanceRemaining, float speed) {
	if (fabs(distanceRemaining) <= threshold) {
		return 0.0;//-speed / AUTO_DRIVE_DIST_SLOW_DOWN;
	}

	float speedScaleFactor = fabs(distanceRemaining)
			/ AUTO_DRIVE_DIST_SLOW_DOWN;
	return fmin(maxSpeed, ((maxSpeed - minSpeed) * speedScaleFactor) + minSpeed)
			* fsign(distanceRemaining);
}

bool DriveDistance::IsFinished() {
	return stability >= tStable;
}

void DriveDistance::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void DriveDistance::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}
