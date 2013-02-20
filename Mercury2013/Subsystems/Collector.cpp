#include "Collector.h"
#include <math.h>

Collector::Collector() :
	Subsystem("Collector") {
	printf("Creating Collector...");
	pitchPotLeft = new AnalogChannel(COLLECTOR_PITCH_POT_LEFT);
	pitchPotRight = new AnalogChannel(COLLECTOR_PITCH_POT_RIGHT);
	collectorPitchMotorLeft = new COLLECTOR_PITCH_MOTOR_TYPE(
			COLLECTOR_PITCH_MOTOR_LEFT);
	collectorPitchMotorRight = new COLLECTOR_PITCH_MOTOR_TYPE(
			COLLECTOR_PITCH_MOTOR_RIGHT);
	collectorMotor = new COLLECTOR_MOTOR_TYPE(COLLECTOR_MOTOR);

#ifdef COLLECTOR_FRISBEE_CHN_3
	frisbeeSensors = new DigitalInput*[3];
	frisbeeSensors[2] = new DigitalInput(COLLECTOR_FRISBEE_CHN_3);
#define COLLECTOR_FRISBEE_CHN_CNT 3
#else
	frisbeeSensors = new DigitalInput*[2];
#define COLLECTOR_FRISBEE_CHN_CNT 2
#endif
	frisbeeSensors[0] = new DigitalInput(COLLECTOR_FRISBEE_CHN_1);
	frisbeeSensors[1] = new DigitalInput(COLLECTOR_FRISBEE_CHN_2);

	pitchPIDLeft = new PIDController(COLLECTOR_PITCH_P, COLLECTOR_PITCH_I,
			COLLECTOR_PITCH_D, pitchPotLeft, collectorPitchMotorLeft);
	pitchPIDLeft->SetAbsoluteTolerance(
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_TOLERANCE));
	pitchPIDLeft->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN,
			COLLECTOR_PITCH_MOTOR_SPEED_UP);
	pitchPIDLeft->SetInputRange(
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_POT_MIN),
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_POT_MAX));

	pitchPIDRight = new PIDController(COLLECTOR_PITCH_P, COLLECTOR_PITCH_I,
			COLLECTOR_PITCH_D, pitchPotLeft, collectorPitchMotorRight);
	pitchPIDRight->SetAbsoluteTolerance(
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_TOLERANCE));
	pitchPIDRight->SetOutputRange(COLLECTOR_PITCH_MOTOR_SPEED_DOWN,
			COLLECTOR_PITCH_MOTOR_SPEED_UP);
	pitchPIDRight->SetInputRange(
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_POT_MIN),
			COLLECTOR_PITCH_INVERT(COLLECTOR_PITCH_POT_MAX));

	SmartDashboard::PutData("Collector Pitch PID (Left)", pitchPIDLeft);
	SmartDashboard::PutData("Collector Pitch PID (Right)", pitchPIDRight);

	LiveWindow::GetInstance()->AddActuator("Collector", "Angle POT (Left)",
			pitchPotLeft);
	LiveWindow::GetInstance()->AddActuator("Collector", "Angle Motor (Left)",
			collectorPitchMotorLeft);
	LiveWindow::GetInstance()->AddSensor("Collector", "Pitch POT (Left)",
			pitchPotLeft);

	LiveWindow::GetInstance()->AddActuator("Collector", "Angle POT (Right)",
			pitchPotRight);
	LiveWindow::GetInstance()->AddActuator("Collector", "Angle Motor (Right)",
			collectorPitchMotorRight);
	LiveWindow::GetInstance()->AddSensor("Collector", "Pitch POT (Right)",
			pitchPotRight);

	LiveWindow::GetInstance()->AddActuator("Collector", "Collect Motor",
			collectorMotor);
	printf("Done\n");
}

Collector::~Collector() {
	delete pitchPotLeft;
	delete collectorPitchMotorLeft;
	delete pitchPotRight;
	delete collectorPitchMotorRight;
	delete collectorMotor;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		delete frisbeeSensors[i];
	}
	delete frisbeeSensors;
}

void Collector::setSetpoint(float angle) {
	pitchPIDLeft->SetSetpoint(COLLECTOR_PITCH_INVERT(angle));
	pitchPIDRight->SetSetpoint(COLLECTOR_PITCH_INVERT(angle));
}

void Collector::setPIDState(bool enabled) {
	pitchPIDLeft->Reset();
	if (pitchPIDLeft->IsEnabled()) {
		if (!enabled) {
			pitchPIDLeft->Disable();
		}
	} else if (enabled) {
		pitchPIDLeft->Enable();
	}

	pitchPIDRight->Reset();
	if (pitchPIDRight->IsEnabled()) {
		if (!enabled) {
			pitchPIDRight->Disable();
		}
	} else if (enabled) {
		pitchPIDRight->Enable();
	}

	if (!enabled) {
		killPitchMotors();
	}
}

bool Collector::isPIDDone() {
	return pitchPIDLeft->OnTarget() && pitchPIDRight->OnTarget();
}

double Collector::getRawAngle() {
	return (COLLECTOR_PITCH_CONVERT(pitchPotLeft->GetAverageValue())
			+ COLLECTOR_PITCH_CONVERT(pitchPotRight->GetAverageValue())) / 2.0;
}

int Collector::getFrisbeeSensorCount() {
	int count = 0;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		count += (frisbeeSensors[i]->Get() & 1);
	}
	return count;
}

void Collector::setCollectorMotor(bool state) {
	collectorMotor->Set(state ? COLLECTOR_MOTOR_SPEED : 0);
}

bool Collector::isSpinnerOn() {
	return fabs(collectorMotor->Get()) > 0;
}

void Collector::killPitchMotors() {
	collectorPitchMotorLeft->Set(0);
	collectorPitchMotorRight->Set(0);
}

void Collector::InitDefaultCommand() {
}
