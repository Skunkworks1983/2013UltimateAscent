#include "Climber.h"

Climber::Climber() :
	Subsystem("Climber") {
	/*sliderEncoder = new Encoder(CLIMBER_SLIDER_ENCODER_1,
			CLIMBER_SLIDER_ENCODER_2, false, Encoder::k4X);
	sliderEncoder->SetPIDSourceParameter(Encoder::kRate);

	sliderMotor1 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_1);
	sliderMotor2 = CLIMBER_SLIDER_MOTOR_CREATE(CLIMBER_SLIDER_MOTOR_2);

	sliderEncoder->Reset();
	sliderEncoder->Start();

	hookButton1 = new DigitalInput(CLIMBER_HOOK_BUTTON_1);
	hookButton2 = new DigitalInput(CLIMBER_HOOK_BUTTON_2);

	pokey = new DoubleSolenoid(CLIMBER_POKEY_UP, CLIMBER_POKEY_DOWN);
	sliderBrake = new DoubleSolenoid(CLIMBER_BRAKE_ACTIVE,
			CLIMBER_BRAKE_UNACTIVE);

	// Live window registration
	LiveWindow::GetInstance()->AddActuator("Climber", "Slider Brake",
			sliderBrake);
	LiveWindow::GetInstance()->AddSensor("Climber", "Slider Encoder",
			sliderEncoder);
	LiveWindow::GetInstance()->AddActuator("Climber", "Slider Brake",
			sliderBrake);

	velocityController = new PIDController(CLIMBER_SLIDER_VP,
			CLIMBER_SLIDER_VI, CLIMBER_SLIDER_VD, sliderEncoder,
			new DualPIDOutput(sliderMotor1, sliderMotor2));
	velocityController->SetInputRange(-CLIMBER_SLIDER_MAX_VELOCITY,
			CLIMBER_SLIDER_MAX_VELOCITY);
	velocityController->SetOutputRange(-1, 1);
	velocityController->SetContinuous(true);
	SmartDashboard::PutData("Velocity Controller", velocityController);*/
}

Climber::~Climber() {
	delete velocityController;

	delete sliderEncoder;
	delete sliderMotor1;
	delete sliderMotor2;

	delete hookButton1;
	delete hookButton2;

	delete pokey;

	delete sliderBrake;
}

void Climber::setPokey(bool pos) {
	pokey->Set(pos ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
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
	sliderBrake->Set(
			isBraking ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
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
	}else{
		velocityController->Disable();
	}
}
