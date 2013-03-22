#include "Collector.h"
#include <math.h>
#include "CollectorArms.h"

Collector::Collector() :
	Subsystem("Collector") {
	printf("Creating Collector...");
	collectorMotor = new COLLECTOR_MOTOR_TYPE(COLLECTOR_MOTOR);
	frisbeeSensors = new DigitalInput*[2];
	frisbeeSensors[0] = new DigitalInput(COLLECTOR_FRISBEE_CHN_1);
	frisbeeSensors[1] = new DigitalInput(COLLECTOR_FRISBEE_CHN_2);
	cachedFrisbees = 0;
	cachedDirection = kStop;

	LiveWindow::GetInstance()->AddActuator("Collector", "Collect Motor",
			collectorMotor);

#ifdef COLLECTOR_FRISBEE_STOP
	frisbeeStop = new Servo(COLLECTOR_FRISBEE_STOP);
	LiveWindow::GetInstance()->AddActuator("Collector", "Servo Flag",
			frisbeeStop);
#endif

	LiveWindow::GetInstance()->AddSensor("Colletor", "Frisbee Sensor 1",
			frisbeeSensors[0]);
	LiveWindow::GetInstance()->AddSensor("Colletor", "Frisbee Sensor 2",
			frisbeeSensors[1]);
	printf("Done\n");
}

Collector::~Collector() {
	delete collectorMotor;
#ifdef COLLECTOR_FRISBEE_STOP
	delete frisbeeStop;
#endif
	for (int i = 0; i < 2; i++) {
		delete frisbeeSensors[i];
	}
	delete frisbeeSensors;
}

int Collector::getFrisbeeSensorCount() {
	int count = 0;
	for (int i = 0; i < 2; i++) {
		count += (~(frisbeeSensors[i]->Get()) & 1);
	}
	return count;
}

int Collector::getCachedFrisbeeSensorCount() {
	return cachedFrisbees;
}

void Collector::updateFrisbeeCache(int v) {
	cachedFrisbees = v;
}

void Collector::setCollectorMotor(Collector::MotorDirection state) {
	switch (state) {
	case kForward:
		collectorMotor->Set(COLLECTOR_MOTOR_SPEED);
		break;
	case kReverse:
		collectorMotor->Set(-COLLECTOR_MOTOR_SPEED);
		break;
	case kStop:
	default:
		collectorMotor->Set(0);
	}
	cachedDirection = state;
}

void Collector::setFrisbeeStop(bool enabled) {
#ifdef COLLECTOR_FRISBEE_STOP
	if (enabled) {
		frisbeeStop->SetAngle(COLLECTOR_FRISBEE_STOP_UP);
	} else {
		frisbeeStop->SetAngle(COLLECTOR_FRISBEE_STOP_DOWN);
	}
#endif
}

bool Collector::getFrisbeeStop() {
#ifdef COLLECTOR_FRISBEE_STOP
	return fabs(frisbeeStop->GetAngle() - COLLECTOR_FRISBEE_STOP_UP) < fabs(
			frisbeeStop->GetAngle() - COLLECTOR_FRISBEE_STOP_DOWN);
#else
	return false;
#endif
}

Collector::MotorDirection Collector::getSpinnerDirection() {
	return cachedDirection;
}

void Collector::InitDefaultCommand() {
}
