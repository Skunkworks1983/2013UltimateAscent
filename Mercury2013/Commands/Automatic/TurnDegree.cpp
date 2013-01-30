#include <math.h>
#include "../../Utils/Math.h"
#include "TurnDegree.h"
#include "../../Robotmap.h"

TurnDegree::TurnDegree(float targetAngle) {
	Requires(driveBase);
	m_targetAngle = targetAngle;
}

void TurnDegree::Initialize() {
	driveBase->getGyro()->Reset();
	m_angleRemaining = 0;
}

void TurnDegree::Execute() {
	m_angleRemaining = m_targetAngle - driveBase->getGyro()->GetAngle();

	float turnScaleFactor = fabs(m_angleRemaining) / AUTO_TURN_SLOW_DOWN;

	float turnSpeed = fmin(AUTO_TURN_SPEED_MAX,
			(AUTO_TURN_SPEED_RANGE * turnScaleFactor) + AUTO_TURN_SPEED_MIN)
			* fsign(m_angleRemaining);
	if (fabs(m_angleRemaining) <= AUTO_TURN_GYRO_THRESHOLD) {
		turnSpeed = 0;
	}
	
	driveBase->setSpeed(turnSpeed, -turnSpeed);
}

bool TurnDegree::IsFinished() {
	return fabs(m_angleRemaining) <= AUTO_TURN_GYRO_THRESHOLD;
}

void TurnDegree::End() {
	driveBase->setSpeed(0.0, 0.0);
}

void TurnDegree::Interrupted() {
	driveBase->setSpeed(0.0, 0.0);
}

