#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Buttons/PressedButtonScheduler.h"

#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Commands/Shooter/FlushShooter.h"
#include "Commands/Shooter/ChangeShooterPitch.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Commands/Drivebase/Shift.h"
#include "Commands/Collector/MoveCollectorArm.h"
#include "Commands/CommandStarter.h"
#include "Commands/Collector/Collect.h"
#include "Commands/Collector/EjectDisks.h"

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
	collectButton = new JoystickButton(driveJoystickRight, 1);
	ejectButton = new JoystickButton(driveJoystickRight, 3);

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

	shootButton->WhenPressed(new Shoot());
	spinupButton->WhenPressed(new ArmShooter(ArmShooter::kOn));
	spinupButton->WhenReleased(new ArmShooter(ArmShooter::kOff));

	collectButton->WhenPressed(new Collect());
	ejectButton->WhenPressed(new EjectDisks(Collector::kForward));
}

Command* OI::createChangePitchFromOI() {
	double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
			OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
	return new ChangeShooterPitch(OI_SHOOTER_ANGLE_CONVERT(val));
}
