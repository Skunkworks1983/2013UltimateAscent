#include "OI.h"
#include "Robotmap.h"

#include "Commands/Automatic/ShooterSlotLoad.h"
#include "Commands/Automatic/CollectorShooterLoad.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Commands/Shooter/FlushShooter.h"
#include "Commands/Shooter/ChangeShooterPitch.h"
#include "Commands/Shooter/ShooterControlModeSet.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Commands/Shooter/ShooterLight.h"
#include "Commands/Drivebase/Shift.h"
#include "Commands/Drivebase/SetScalingFactor.h"
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
	driveDirectionButton = new DigitalIOButton(4);

	shooterNoWait = new DigitalIOButton(5);
	lightButton = new DigitalIOButton(2);
	shootButton = new DigitalIOButton(16);
	spinupButton = new DigitalIOButton(14);
	shooterAngleOverrideButton = new DigitalIOButton(1);
	shooterPowerOverrideButton = new DigitalIOButton(5);

	shooterHighButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG, 2.625,
			2.825);//2.725
	shooterMiddleButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG,
			2.045, 2.245);// 2.145
	shooterLowButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG,
			1.406, 1.606);//1.506
	shooterZeroButton = new AnalogRangeIOButton(OI_SHOOTER_ANGLE_ANALOG, 0.629,
			0.829);//0.729
	shooterAngleChangeTrigger = new ValueChangeTrigger(
			OI::getShooterTargetPitch, OI_SHOOTER_ANGLE_DELTA);

	armUpButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG, 2.625,
			2.825);//2.725
	armDownButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG, .625,
			.825);//.725
	collectorOverrideButton = new DigitalIOButton(12);
	armChangeTrigger = new ValueChangeTrigger(OI::getCollectorTargetPitch,
			OI_COLLECTOR_ANGLE_DELTA);

	collectorSlotButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG,
			2.045, 2.245);//2.145
	shooterCollectorButton = new AnalogRangeIOButton(OI_COLLECTOR_ANGLE_ANALOG,
			1.402, 1.602);//1.502

	autoCollectCommand = new Collect(false);
	collectButton = new JoystickButton(driveJoystickRight, 1);
	ejectButton = new JoystickButton(driveJoystickRight, 3);

	pokeyStickButton = new DigitalIOButton(7);
	climberRackButton = new DigitalIOButton(3);
}

Joystick *OI::getDriveJoystickLeft() {
	return driveJoystickLeft;
}

Joystick *OI::getDriveJoystickRight() {
	return driveJoystickRight;
}

void OI::registerButtonSchedulers() {
	shiftButton->WhenReleased(new Shift(Shift::kToggle));
	driveDirectionButton->WhenPressed(new SetScalingFactor(-1.0));
	driveDirectionButton->WhenReleased(new SetScalingFactor(1.0));

	lightButton->WhenPressed(new ShooterLight(ShooterLight::kOn));
	lightButton->WhenReleased(new ShooterLight(ShooterLight::kOff));

	shootButton->WhileHeld(new Shoot());
	spinupButton->WhenPressed(new ArmShooter(ArmShooter::kOn));
	spinupButton->WhenReleased(new ArmShooter(ArmShooter::kOff));

	shooterNoWait->WhenPressed(
			new ShooterControlModeSet(ShooterControlModeSet::CONTROL_NOCHANGE,
					Shooter::kNone));
	shooterNoWait->WhenReleased(
			new ShooterControlModeSet(ShooterControlModeSet::CONTROL_NOCHANGE,
					Shooter::SHOOTER_DEFAULT_WAIT));

	armDownButton->WhenPressed(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	armDownButton->WhenPressed(autoCollectCommand);
	armDownButton->WhenReleased(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	armDownButton->WhenReleased(new CommandCanceler(autoCollectCommand));

	ejectButton->WhenPressed(new EjectDisks(Collector::kReverse));
	armChangeTrigger->WhenActive(
			new CommandStarter(OI::createChangeCollectorPitch));
	shooterAngleChangeTrigger->WhenActive(
			new CommandStarter(OI::createChangePitchFromOI));

	pokeyStickButton->WhenPressed(new HokeyPokey(true));
	pokeyStickButton->WhenReleased(new HokeyPokey(false));
	climberRackButton->WhenPressed(new ExtendClimber(true));
	climberRackButton->WhenReleased(new ExtendClimber(false));

	collectorSlotButton->WhenPressed(new ShooterSlotLoad());
	shooterCollectorButton->WhenPressed(new CollectorShooterLoad());
}

double OI::getCollectorTargetPitch() {
	if (CommandBase::oi == NULL) {
		return 0.0;
	}
	if (CommandBase::oi->armUpButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_UP;
		return FORCE_VALUE_CHANGE;
	}/* else if (CommandBase::oi->armDownButton->Get()) {
		CommandBase::oi->targetCollectorPitch = COLLECTOR_PITCH_DOWN;
		return FORCE_VALUE_CHANGE;
	}*/ else if (!CommandBase::oi->collectorOverrideButton->Get()) {
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
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_PYRAMID_SIDE;
		return FORCE_VALUE_CHANGE;
	} else if (CommandBase::oi->shooterMiddleButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_PYRAMID_FRONT;
		return FORCE_VALUE_CHANGE;
	} else if (CommandBase::oi->shooterLowButton->Get()) {
		CommandBase::oi->targetShooterPitch = SHOOTER_PITCH_PYRAMID_BACK;
		return FORCE_VALUE_CHANGE;
	} else if (CommandBase::oi->shooterZeroButton->Get()) {
		CommandBase::oi->targetShooterPitch = -25;//SHOOTER_PITCH_PYRAMID_BACK;
		return FORCE_VALUE_CHANGE;
	} else if (!CommandBase::oi->shooterAngleOverrideButton->Get()) {
		CommandBase::oi->targetShooterPitch = OI_SHOOTER_ANGLE_CONVERT(
				DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(1))
				/ 180.0;
	}
	return CommandBase::oi->targetShooterPitch;
}

Command *OI::createChangeCollectorPitch() {
	return new MoveCollectorArm(getCollectorTargetPitch());
}

Command* OI::createChangePitchFromOI() {
	return new ChangeShooterPitch(OI::getShooterTargetPitch());
}
