#include "StallableMotor.h"
#include <math.h>
#include "Time.h"

StallableMotor::StallableMotor(SpeedController *backend, Encoder *stallEncoder,
		double stallTimeTreshold) {
	this->backend = backend;
	this->stallEncoder = stallEncoder;
	this->stallTimeThreshold = stallTimeThreshold;
	this->cacheSpeed = 0;
	this->cacheSyncGroup = 0;
	this->stallStart = -1.0;
	this->stalled = false;
}

bool StallableMotor::isStalled() {
	return stalled;
}

void StallableMotor::updateController() {
	//Update stall state
	this->stalled = false;
	if (stallEncoder->GetStopped() && fabs(cacheSpeed) > 0.0) {
		if (stallStart < 0.0) {
			stallStart = getCurrentMillis();
		} else if (getCurrentMillis() - stallStart > stallTimeThreshold) {
			this->stalled = true;
		}
	}

	if (stalled) {
		backend->Set(0, cacheSyncGroup);
	} else {
		backend->Set(cacheSpeed, cacheSyncGroup);
	}
}

void StallableMotor::Set(float speed, UINT8 syncGroup) {
	this->cacheSpeed = speed;
	this->cacheSyncGroup = syncGroup;
}

float StallableMotor::Get() {
	return cacheSpeed;
}

void StallableMotor::Disable() {
	this->cacheSpeed = 0.0;
	this->backend->Disable();
}

void StallableMotor::PIDWrite(float speed) {
	this->cacheSpeed = speed;
}

