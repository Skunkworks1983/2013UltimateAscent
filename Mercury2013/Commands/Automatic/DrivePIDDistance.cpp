#include "DrivePIDDistance.h"
#include <math.h>
#include "../../Utils/Math.h"
#include "../../Robotmap.h"

DrivePIDDistance::DrivePIDDistance(float targetDistance, float tStable,
		float tThresh) :
			CommandBase(
					CommandBase::createNameFromFloat("DrivePIDDistance",
							targetDistance)) {
	Requires(CommandBase::driveBase);
	this->tStable = tStable;

	leftControl = new DriveDistPIDLeft(this);
	pidLeft = new PIDController(0.5, 0.002, 0.75, leftControl, leftControl);
	pidLeft->SetInputRange(-targetDistance, targetDistance * 2.0);
	pidLeft->SetOutputRange(-AUTO_DRIVE_DIST_SPEED_MAX,
			AUTO_DRIVE_DIST_SPEED_MAX);
	pidLeft->SetAbsoluteTolerance(tThresh);
	pidLeft->SetSetpoint(targetDistance);

	rightControl = new DriveDistPIDRight(this);
	pidRight = new PIDController(0.5, 0.002, 0.75, rightControl,
			rightControl);
	pidRight->SetInputRange(-targetDistance, targetDistance * 2.0);
	pidRight->SetOutputRange(-AUTO_DRIVE_DIST_SPEED_MAX,
			AUTO_DRIVE_DIST_SPEED_MAX);
	pidRight->SetAbsoluteTolerance(tThresh);
	pidRight->SetSetpoint(targetDistance);
}

DrivePIDDistance::~DrivePIDDistance() {
	delete pidLeft;
	delete pidRight;
	delete leftControl;
	delete rightControl;
}

DrivePIDDistance *DrivePIDDistance::setOutputRange(float min, float max) {
	pidLeft->SetOutputRange(min, max);
	pidRight->SetOutputRange(min, max);
	return this;
}

void DrivePIDDistance::Initialize() {
	pidLeft->Reset();
	pidLeft->Enable();
	pidRight->Reset();
	pidRight->Enable();
	CommandBase::driveBase->getLeftEncoder()->Reset();
	CommandBase::driveBase->getRightEncoder()->Reset();
	stability = 0;
}

void DrivePIDDistance::Execute() {
}

double DrivePIDDistance::getLeft() {
	return CommandBase::driveBase->getLeftEncoder()->GetDistance();
}
double DrivePIDDistance::getRight() {
	return CommandBase::driveBase->getRightEncoder()->GetDistance();
}
int li;
void DrivePIDDistance::writeLeft(float f) {
	if (driveCorrection < 0.0) {
		f *= -driveCorrection;
	}
	driveBase->setLeftSpeed(f);
	if (li++ > 10) {
		li = 0;
	}
}
void DrivePIDDistance::writeRight(float f) {
	if (driveCorrection > 0.0) {
		f *= driveCorrection;
	}
	driveBase->setRightSpeed(f);
}

bool DrivePIDDistance::IsFinished() {
	float sideError = pidLeft->GetError() - pidRight->GetError();
	driveCorrection = fmin(
			fmax(
					(AUTO_DRIVE_DIST_CATCHUP - fabs(sideError))
							/ AUTO_DRIVE_DIST_CATCHUP, 0.0), 1.0) * fsign(
			sideError);
	if (pidLeft->OnTarget() && pidRight->OnTarget()) {
		stability++;
	} else {
		stability = 0;
	}
	return stability >= tStable;
}

void DrivePIDDistance::End() {
	pidLeft->Reset();
	pidRight->Reset();
}

void DrivePIDDistance::Interrupted() {
	End();
}

DriveDistPIDLeft::DriveDistPIDLeft(DrivePIDDistance *back) {
	this->backend = back;
}
void DriveDistPIDLeft::PIDWrite(float f) {
	backend->writeLeft(f);
}
double DriveDistPIDLeft::PIDGet() {
	return backend->getLeft();
}
DriveDistPIDRight::DriveDistPIDRight(DrivePIDDistance *back) {
	this->backend = back;
}
void DriveDistPIDRight::PIDWrite(float f) {
	backend->writeRight(f);
}
double DriveDistPIDRight::PIDGet() {
	return backend->getRight();
}

