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
#include "Commands/Climber/HokeyPokey.h"
#include "Commands/Climber/ExtendClimber.h"
#include "Utils/ValueChangeTrigger.h"
#include "Utils/AnalogRangeIOButton.h"

#define OI_SHOOTER_ANGLE_ANALOG		6
#define OI_COLLECTOR_ANGLE_ANALOG	4

OI::OI() {
	driveJoystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	driveJoystickRight = new Joystick(OI_JOYSTICK_RIGHT);

	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	driverStationEIO = &(driverStation->GetEnhancedIO());

	shiftButton = new JoystickButton(driveJoystickLeft, 1);

	shootButton = new DigitalIOButton(16);
	spinupButton = new DigitalIOButton(14);
	shooterAngleOverrideButton = new DigitalIOButton(1);
	shooterPowerOverrideButton = new DigitalIOButton(5);

	shooterHighButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG, 2.625,
			2.825);//2.725
	shooterMidHighButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG,
			2.045, 2.245);// 2.145
	shooterMidLowButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG,
			1.406, 1.606);//1.506
	shooterLowButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG, 0.629,
			0.829);//0.729
	shooterAngleChangeTrigger = new ValueChangeTrigger(
			OI::getShooterTargetPitch, 0.125);

	armUpButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG, 2.625,
			2.825);//2.725
	armDownButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG, .625,
			.825);//.725
	collectorOverrideButton = new DigitalIOButton(12);
	armChangeTrigger = new ValueChangeTrigger(OI::getCollectorTargetPitch, 5);

	collectorSlotButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG,
			2.045, 2.245);//2.145
	shooterCollectorButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG,
			1.402, 1.602);//1.502

	autoCollectCommand = new Collect(false);
	collectButton = new JoystickButton(driveJoystickRight, 1);
	ejectButton = new JoystickButton(driveJoystickRight, 3);

	pokeyStickButton = new DigitalIOButton(7);
	climberRackButton = new DigitalIOButton(3);

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
	collectButton->WhenPressed(autoCollectCommand);
	collectButton->WhenReleased(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	collectButton->WhenReleased(new CommandCanceler(autoCollectCommand));

	ejectButton->WhenPressed(new EjectDisks(Collector::kForward));
	armChangeTrigger->WhenActive(
			new CommandStarter(OI::createChangeCollectorPitch));
	shooterAngleChangeTrigger->WhenActive(
			new CommandStarter(OI::createChangePitchFromOI));

	pokeyStickButton->WhenPressed(new HokeyPokey(true));
	pokeyStickButton->WhenReleased(new HokeyPokey(false));
	climberRackButton->WhenPressed(new ExtendClimber(true));
	climberRackButton->WhenReleased(new ExtendClimber(false));
}

double OI::getCollectorTargetPitch() {
	if (CommandBase::oi == NULL) {
		return 0.0;
	}
	if (CommandBase::oi->armUpButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_UP;
	} else if (CommandBase::oi->armDownButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_DOWN;
	} else if (!CommandBase::oi->collectorOverrideButton->Get()) {
		CommandBase::oi->targetCollectorPitch = OI_COLLECTOR_ANGLE_CONVERT(
				DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(3));
		if (CommandBase::oi->targetCollectorPitch < -1) {
			CommandBase::oi->targetCollectorPitch = -1;
		} else if (CommandBase::oi->targetCollectorPitch > 90) {
			CommandBase::oi->targetCollectorPitch = 90;
		}
	}
	return CommandBase::oi->targetCollectorPitch;
}

double OI::getShooterTargetPitch() {
	if (CommandBase::oi == NULL) {
		return 0.0;
	}
	if (CommandBase::oi->shooterHighButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_HIGH;
	} else if (CommandBase::oi->shooterMidHighButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_MIDHIGH;
	} else if (CommandBase::oi->shooterMidLowButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_MIDLOW;
	} else if (CommandBase::oi->shooterLowButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_LOW;
	} else if (!CommandBase::oi->shooterAngleOverrideButton->Get()) {
		CommandBase::oi->targetShooterPitch = OI_SHOOTER_ANGLE_CONVERT(
				DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(1))
				/ 270.0;
	}
	return CommandBase::oi->targetShooterPitch;
}

Command *OI::createChangeCollectorPitch() {
	return new MoveCollectorArm(getCollectorTargetPitch());
}

Command* OI::createChangePitchFromOI() {
	return new ChangeShooterPitch(OI::getShooterTargetPitch());
}
