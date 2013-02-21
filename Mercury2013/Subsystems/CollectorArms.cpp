#include "CollectorArms.h"
#include "Collector.h"
#include "../Utils/Math.h"
#include <math.h>

ArmController::ArmController(Collector *collect,
		COLLECTOR_PITCH_MOTOR_TYPE *motor, AnalogChannel *pot) {
	this->motor = motor;
	this->pot = pot;
	this->collect = collect;
	pid = new PIDController(COLLECTOR_PITCH_P, COLLECTOR_PITCH_I,
			COLLECTOR_PITCH_D, this, this);
	pid->SetAbsoluteTolerance(COLLECTOR_PITCH_TOLERANCE);
	pid->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN,
			COLLECTOR_PITCH_MOTOR_SPEED_UP);
	pid->SetInputRange(COLLECTOR_PITCH_POT_MIN, COLLECTOR_PITCH_POT_MAX);
}

ArmController::~ArmController() {
	delete motor;
	delete pot;
	delete pid;
}

double ArmController::PIDGet() {
	return COLLECTOR_PITCH_CONVERT(pot->GetAverageValue());
}

void ArmController::setPIDState(bool enabled) {
	pid->Reset();
	if (pid->IsEnabled()) {
		if (!enabled) {
			pid->Disable();
		}
	} else if (enabled) {
		pid->Enable();
	}

	if (!enabled) {
		PIDWrite(0);
	}
}

void ArmController::setSetpoint(float f) {
	pid->SetSetpoint(f);
}

bool ArmController::isPIDDone() {
	return pid->OnTarget();
}

LeftArmController::LeftArmController(Collector *collect) :
			ArmController(collect,
					new COLLECTOR_PITCH_MOTOR_TYPE(COLLECTOR_PITCH_MOTOR_LEFT),
					new AnalogChannel(COLLECTOR_PITCH_POT_LEFT)) {
	SmartDashboard::PutData("Left Collector Arm", pid);
}

void LeftArmController::PIDWrite(float f) {
	float diff = min(
			(COLLECTOR_PITCH_CATCHUP - fabs(
					collect->getLeftAngle() - collect->getRightAngle()))
					/ COLLECTOR_PITCH_CATCHUP, 1.0);
	motor->Set(-f * diff);
}

RightArmController::RightArmController(Collector *collect) :
			ArmController(
					collect,
					new COLLECTOR_PITCH_MOTOR_TYPE(COLLECTOR_PITCH_MOTOR_RIGHT),
					new AnalogChannel(COLLECTOR_PITCH_POT_RIGHT)) {
	SmartDashboard::PutData("Right Collector Arm", pid);
}

void RightArmController::PIDWrite(float f) {
	float diff = min(
			(COLLECTOR_PITCH_CATCHUP - fabs(
					collect->getRightAngle() - collect->getLeftAngle()))
					/ COLLECTOR_PITCH_CATCHUP, 1.0);
	motor->Set(f * diff);
}
