#include "Collector.h"
#include <math.h>
#include "CollectorArms.h"

Collector::Collector() :
	Subsystem("Collector") {
	printf("Creating Collector...");
	collectorMotor = new COLLECTOR_MOTOR_TYPE(COLLECTOR_MOTOR);
	frisbeeStop = new Servo(COLLECTOR_FRISBEE_STOP);
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
	delete frisbeeStop;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		delete frisbeeSensors[i];
	}
	delete frisbeeSensors;
}

int Collector::getFrisbeeSensorCount() {
	int count = 0;
	for (int i = 0; i < COLLECTOR_FRISBEE_CHN_CNT; i++) {
		count += (~(frisbeeSensors[i]->Get()) & 1);
	}
	return count;
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
}

void Collector::setFrisbeeStop(bool enabled) {
	if (enabled) {
		frisbeeStop->SetAngle(COLLECTOR_FRISBEE_STOP_UP);
	} else {
		frisbeeStop->SetAngle(COLLECTOR_FRISBEE_STOP_DOWN);
	}
}

Collector::MotorDirection Collector::getSpinnerDirection() {
	float clampSpeed = collectorMotor->Get() / COLLECTOR_MOTOR_SPEED;
	if (clampSpeed < 0.0) {
		return kReverse;
	} else if (clampSpeed > 0.0) {
		return kForward;
	} else {
		return kStop;
	}
}

void Collector::InitDefaultCommand() {
}
