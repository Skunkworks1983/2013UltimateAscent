#include "Climber.h"
#include <math.h>

Climber::Climber() :
		Subsystem("Climber") {
	printf("Creating Climber...\t");
	sliderMotor = new DualLiveSpeed(
			CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_1),
			CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_2));
	sliderEncoder = new Encoder(CLIMBER_SLIDER_ENCODER, false, Encoder::k4X);
	sliderEncoder->SetPIDSourceParameter(Encoder::kRate);

	sliderEncoder->Reset();
	sliderEncoder->Start();

	/*	 hookButton1 = new DigitalInput(CLIMBER_HOOK_BUTTON_1);
	 hookButton2 = new DigitalInput(CLIMBER_HOOK_BUTTON_2);
	 */
	pokey = new SolenoidPair(CLIMBER_POKEY);
	sliderBrake = new SolenoidPair(CLIMBER_BRAKE);
	/*

	 velocityController = new PIDController(CLIMBER_SLIDER_VP,
	 CLIMBER_SLIDER_VI, CLIMBER_SLIDER_VD, sliderEncoder,
	 new DualPIDOutput(sliderMotor1, sliderMotor2));
	 velocityController->SetInputRange(-CLIMBER_SLIDER_MAX_VELOCITY,
	 CLIMBER_SLIDER_MAX_VELOCITY);
	 velocityController->SetOutputRange(-1, 1);
	 velocityController->SetContinuous(true);
	 SmartDashboard::PutData("Velocity Controller", velocityController);

	 climberSaftey = new Notifier(Climber::callSaftey, this);
	 climberSaftey->StartPeriodic(CLIMBER_SAFTEY_PERIOD);*/

	// Live window registration
	LiveWindow::GetInstance()->AddActuator("Climber", "Slider Motor",
			sliderMotor);
	LiveWindow::GetInstance()->AddActuator("Climber", "Slider Brake",
			sliderBrake);
	LiveWindow::GetInstance()->AddActuator("Climber", "Pokey Stick",
			pokey);
	LiveWindow::GetInstance()->AddSensor("Climber", "Slider Encoder",
			sliderEncoder);
	printf("Done!");
}

Climber::~Climber() {
	delete velocityController;
	delete climberSaftey;

	delete sliderEncoder;
	delete sliderMotor;

	delete hookButton1;
	delete hookButton2;

	delete pokey;

	delete sliderBrake;
}

void Climber::callSaftey(void *param) {
	((Climber*) param)->saftey();
}

void Climber::saftey() {
	if (fabs(sliderEncoder->GetRate()) > CLIMBER_SLIDER_CUTOFF_VELOCITY) {
		// Dear god, stop it please.
		velocityController->Disable();
		setBrakeState(true);
	}
}

void Climber::setPokey(bool pos) {
	pokey->Set(pos);
}

bool Climber::getPokey(int num) {
	return pokey->Get();
}

bool Climber::getButton(int num) {
	switch (num) {
	case 1:
		return hookButton1->Get();

	case 2:
		return hookButton2->Get();
	}
	return false;
}

void Climber::setBrakeState(bool isBraking) {
	sliderBrake->Set(isBraking);
}

bool Climber::getBrakeState() {
	return sliderBrake->Get();
}

Climber::SliderState Climber::getSliderState() {
	if (PIDGet() >= 1.0 - CLIMBER_SLIDER_TOLERANCE) {
		return kUp;
	} else if (PIDGet() <= CLIMBER_SLIDER_TOLERANCE) {
		return kDown;
	} else {
		return kOther;
	}
}

double Climber::PIDGet() {
	return sliderEncoder->GetDistance();
}

void Climber::PIDWrite(float speed) {
	velocityController->SetSetpoint(speed);
}

void Climber::setVelocityPIDState(bool state) {
	if (state) {
		velocityController->Reset();
		if (!velocityController->IsEnabled()) {
			velocityController->Enable();
		}
	} else {
		velocityController->Disable();
	}
}
