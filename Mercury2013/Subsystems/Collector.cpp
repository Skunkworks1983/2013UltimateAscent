#include "Collector.h"
#include <math.h>
#include "CollectorArms.h"

Collector::Collector() :
	Subsystem("Collector") {
	printf("Creating Collector...");
	collectorMotor = new COLLECTOR_MOTOR_TYPE(COLLECTOR_MOTOR);
	leftArmController = new LeftArmController(this);
	rightArmController = new RightArmController(this);

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

	LiveWindow::GetInstance()->AddActuator("Collector", "Collect Motor",
			collectorMotor);
	printf("Done\n");
}

Collector::~Collector() {
	delete collectorMotor;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		delete frisbeeSensors[i];
	}
	delete frisbeeSensors;
}

void Collector::setSetpoint(float angle) {
	leftArmController->setSetpoint(angle);
	rightArmController->setSetpoint(angle);
}

void Collector::setPIDState(bool enabled) {
	leftArmController->setPIDState(enabled);
	rightArmController->setPIDState(enabled);
}

bool Collector::isPIDDone() {
	return leftArmController->isPIDDone() && rightArmController->isPIDDone();
}

double Collector::getLeftAngle() {
	return leftArmController->PIDGet();
}

double Collector::getRightAngle() {
	return rightArmController->PIDGet();
}

double Collector::getRawAngle() {
	return (getLeftAngle() + getRightAngle()) / 2.0;
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
	leftArmController->PIDWrite(0);
	rightArmController->PIDWrite(0);
}

void Collector::InitDefaultCommand() {
}
