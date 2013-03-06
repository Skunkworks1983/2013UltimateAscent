#include "OI.h"
#include "Robotmap.h"

#include "Commands/Automatic/ShooterSlotLoad.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Commands/Shooter/FlushShooter.h"
#include "Commands/Shooter/ChangeShooterPitch.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Commands/Drivebase/Shift.h"
#include "Commands/Collector/MoveCollectorArm.h"
#include "Commands/CommandStarter.h"
#include "Commands/CommandCanceler.h"
#include "Commands/Collector/Collect.h"
#include "Commands/Collector/EjectDisks.h"
#include "Utils/ValueChangeTrigger.h"

OI::OI() {
	driveJoystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	driveJoystickRight = new Joystick(OI_JOYSTICK_RIGHT);

	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	driverStationEIO = &(driverStation->GetEnhancedIO());

	shiftButton = new JoystickButton(driveJoystickLeft, 1);

	shootButton = new DigitalIOButton(5);
	spinupButton = new DigitalIOButton(10);
	tuneShooterButton = new DigitalIOButton(8);

	armUpButton = new DigitalIOButton(3);
	armMidButton = new DigitalIOButton(11);
	armDownButton = new DigitalIOButton(1);
	armChangeTrigger = new ValueChangeTrigger(OI::getCollectorTargetPitch, 5);

	collectorSlotButton = new DigitalIOButton(13);

	autoCollectCommand = new Collect(false);
	collectButton = new JoystickButton(driveJoystickRight, 1);
	ejectButton = new JoystickButton(driveJoystickRight, 3);

	shooterToThing = new DigitalIOButton(16);
	
	
#define PUT_DEFAULT(val) (Preferences::GetInstance()->PutFloat(#val, val))
	PUT_DEFAULT(SHOOTER_MOTOR_FRONT_SPEED);
	PUT_DEFAULT(SHOOTER_MOTOR_MIDDLE_SPEED);
	PUT_DEFAULT(SHOOTER_MOTOR_REAR_SPEED);

	PUT_DEFAULT(SHOOTER_MOTOR_FRONT_BANG_SPEED);
	PUT_DEFAULT(SHOOTER_MOTOR_MIDDLE_BANG_SPEED);
	PUT_DEFAULT(SHOOTER_MOTOR_REAR_BANG_SPEED);
}

Joystick *OI::getDriveJoystickLeft() {
	return driveJoystickLeft;
}

Joystick *OI::getDriveJoystickRight() {
	return driveJoystickRight;
}

void OI::registerButtonSchedulers() {
	shiftButton->WhenPressed(new Shift(Shift::kToggle));

	shootButton->WhenReleased(new Shoot());
	spinupButton->WhenPressed(new ArmShooter(ArmShooter::kOn));
	spinupButton->WhenReleased(new ArmShooter(ArmShooter::kOff));

	collectButton->WhenPressed(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	collectButton->WhileHeld(autoCollectCommand);
	collectButton->WhenReleased(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	collectButton->WhenReleased(new CommandCanceler(autoCollectCommand));
	
	ejectButton->WhenPressed(new EjectDisks(Collector::kForward));
	armChangeTrigger->WhenActive(
			new CommandStarter(OI::createChangeCollectorPitch));
	collectorSlotButton->WhenPressed(new ShooterSlotLoad());
	shooterToThing->WhenPressed(
			new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_BACK));
	tuneShooterButton->WhenPressed(new TunePitchEncoder());
}

double OI::getCollectorTargetPitch() {
	if (CommandBase::oi == NULL) {
		return 0.0;
	}
	if (!CommandBase::oi->armUpButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_UP;
	} else if (!CommandBase::oi->armMidButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_MID;
	} else if (!CommandBase::oi->armDownButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_DOWN;
	}/* else if (armOverrideButton->Get()) {
	 targetCollectorPitch = OI_GET_COLLLECTOR_MANUAL_ANGLE;
	 }*/
	return CommandBase::oi->targetCollectorPitch;
}

Command *OI::createChangeCollectorPitch() {
	return new MoveCollectorArm(getCollectorTargetPitch());
}

Command* OI::createChangePitchFromOI() {
	double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
			OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
	return new ChangeShooterPitch(OI_SHOOTER_ANGLE_CONVERT(val));
}
