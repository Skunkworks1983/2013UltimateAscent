#include "SliderMove.h"

SliderMove::SliderMove(bool destIsExtended) {
	Requires(climber);
	destExtend = destIsExtended;
	pidController = new PIDController(CLIMBER_SLIDER_P, CLIMBER_SLIDER_I,
			CLIMBER_SLIDER_D, climber, climber);
	pidController->SetInputRange(0, CLIMBER_SLIDER_MAX_RANGE);
	pidController->SetOutputRange(-CLIMBER_SLIDER_MAX_VELOCITY,
			CLIMBER_SLIDER_MAX_VELOCITY);
}

SliderMove::~SliderMove() {
	delete pidController;
}

void SliderMove::Initialize() {
	pidController->Enable();
	pidController->SetSetpoint(destExtend ? CLIMBER_SLIDER_MAX_RANGE : 0.0);
}

void SliderMove::Execute() {
	// The pid stuff
}

bool SliderMove::IsFinished() {
	return climber->getSliderState() == (destExtend ? Climber::kUp
			: Climber::kDown);
}

void SliderMove::End() {
	pidController->Disable();
}

void SliderMove::Interrupted() {
	pidController->Disable();
}
