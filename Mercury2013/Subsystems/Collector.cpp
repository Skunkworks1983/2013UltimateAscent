#include "Collector.h"
#include "../Robotmap.h"
#include <math.h>

Collector::Collector() :
	Subsystem("Collector") {
	// TODO pitchPot = new AnalogChannel(COLLECTOR_PITCH_POT);		//potentionmeter for colelctor pitch
	// TODO collectorPitchMotor = COLLECTOR_PITCH_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);	//collector pitch motor
	// TODO collectorMotor = COLLECTOR_MOTOR_CREATE(COLLECTOR_PITCH_MOTOR);				//actual collector motor

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

	pitchPID = new PIDController(COLLECTOR_PITCH_P, COLLECTOR_PITCH_I,
			COLLECTOR_PITCH_D, this, this);
	pitchPID->SetAbsoluteTolerance(COLLECTOR_PITCH_TOLERANCE);
	SmartDashboard::PutData("Collector Pitch PID", pitchPID);
}

Collector::~Collector() {
	delete pitchPot;
	delete collectorPitchMotorA;
	delete collectorPitchMotorB;
	delete collectorMotor;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		delete frisbeeSensors[i];
	}
	delete frisbeeSensors;
}

void Collector::setSetpoint(float angle) {
	pitchPID->SetSetpoint(angle);
}

void Collector::setPIDState(bool enabled) {
	pitchPID->Reset();
	if (pitchPID->IsEnabled()) {
		if (!enabled) {
			pitchPID->Disable();
		}
	} else if (enabled) {
		pitchPID->Enable();
	}
}

bool Collector::isPIDDone() {
	return pitchPID->OnTarget();
}

Collector::CollectorState Collector::getArmState() {
	if (fabs(getRawAngle() - COLLECTOR_PITCH_UP) < COLLECTOR_PITCH_TOLERANCE) {
		return Collector::kUp;
	} else if (fabs(getRawAngle() - COLLECTOR_PITCH_DOWN)
			< COLLECTOR_PITCH_TOLERANCE) {
		return Collector::kDown;
	} else if (fabs(getRawAngle() - COLLECTOR_PITCH_DOWN) < fabs(
			getRawAngle() - COLLECTOR_PITCH_UP)) {
		return Collector::kOtherDown;
	} else {
		return Collector::kOtherUp;
	}
}

double Collector::getRawAngle() {
	return COLLECTOR_PITCH_CONVERT(pitchPot->GetVoltage());
}

void Collector::PIDWrite(float val) {
	collectorPitchMotorA->Set(val);
	collectorPitchMotorB->Set(val);
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
	return collectorMotor->Get() > 0;
}

double Collector::PIDGet() {
	return getRawAngle();
}

void Collector::InitDefaultCommand() {
}
