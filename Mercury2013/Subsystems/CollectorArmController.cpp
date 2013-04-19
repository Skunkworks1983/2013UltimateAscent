#include "CollectorArmController.h"
#include "CollectorArms.h"
#include "../Utils/Math.h"
#include <math.h>

ArmController::ArmController(char *name, CollectorArms *collect,
		COLLECTOR_PITCH_MOTOR_TYPE *motor, AnalogChannel *pot) {
	this->motor = motor;
	this->pot = pot;
	this->collect = collect;
	pid = new PIDController(COLLECTOR_PITCH_P, COLLECTOR_PITCH_I,
			COLLECTOR_PITCH_D, this, this);
	pid->SetAbsoluteTolerance(COLLECTOR_PITCH_TOLERANCE);
	pid->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN_NEAR,
			COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR);
	pid->SetInputRange(COLLECTOR_PITCH_POT_MIN, COLLECTOR_PITCH_POT_MAX);

	LiveWindow::GetInstance()->AddActuator(name, "PID", pid);
	LiveWindow::GetInstance()->AddActuator(name, "Motor", motor);
	LiveWindow::GetInstance()->AddSensor(name, "Analog Input", pot);
}

ArmController::~ArmController() {
	delete motor;
	delete pot;
	delete pid;
}

void ArmController::updatePIDOutput() {
	if (fabs(pid->GetError()) < COLLECTOR_PITCH_ERROR_90 && pid->GetSetpoint()
			== COLLECTOR_PITCH_UP) {
		pid->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN_NEAR,
				COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR_90);
	} else if (fabs(pid->GetError()) > COLLECTOR_PITCH_ERROR_NEAR) {
		pid->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN_FAR,
				COLLECTOR_PITCH_MOTOR_SPEED_UP_FAR);
	} else {
		pid->SetOutputRange(
				COLLECTOR_PITCH_MOTOR_SPEED_DOWN_NEAR,
				PIDGet() > (COLLECTOR_PITCH_UP - (COLLECTOR_PITCH_ERROR_NEAR)) ? COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR_90
						: COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR);
	}
}
float ArmController::getOutput() {
	return pid->Get();
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
	updatePIDOutput();
	pid->SetSetpoint(f);
}

bool ArmController::isPIDDone() {
	return pid->OnTarget();
}

LeftArmController::LeftArmController(CollectorArms *collect) :
			ArmController("LeftCollectorArm", collect,
					new COLLECTOR_PITCH_MOTOR_TYPE(COLLECTOR_PITCH_MOTOR_LEFT),
					new AnalogChannel(COLLECTOR_PITCH_POT_LEFT)) {
}

LeftArmController::~LeftArmController() {
}

void LeftArmController::PIDWrite(float f) {
	updatePIDOutput();
	float diff = min(
			(COLLECTOR_PITCH_CATCHUP - fabs(
					collect->getLeftAngle() - collect->getRightAngle()))
					/ COLLECTOR_PITCH_CATCHUP, 1.0);
	motor->Set(-f * diff);
}

RightArmController::RightArmController(CollectorArms *collect) :
			ArmController(
					"RightCollectorArm",
					collect,
					new COLLECTOR_PITCH_MOTOR_TYPE(COLLECTOR_PITCH_MOTOR_RIGHT),
					new AnalogChannel(COLLECTOR_PITCH_POT_RIGHT)) {
}

RightArmController::~RightArmController() {
}

void RightArmController::PIDWrite(float f) {
	updatePIDOutput();
	float diff = min(
			(COLLECTOR_PITCH_CATCHUP - fabs(
					collect->getRightAngle() - collect->getLeftAngle()))
					/ COLLECTOR_PITCH_CATCHUP, 1.0);
	motor->Set(f * diff);
}
