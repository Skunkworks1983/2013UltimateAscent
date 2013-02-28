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
#include "Utils/AnalogChangeTrigger.h"

OI::OI() {
	driveJoystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	driveJoystickRight = new Joystick(OI_JOYSTICK_RIGHT);

	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	driverStationEIO = &(driverStation->GetEnhancedIO());

	shiftScheduler
			= new ReleasedButtonScheduler(false,
					new JoystickButton(driveJoystickLeft, 1),
					new Shift(Shift::kToggle));

	shootScheduler = new ReleasedButtonScheduler(false, new DigitalIOButton(5),
			new Shoot());
	spinupScheduler = new PressedButtonScheduler(false,
			new DigitalIOButton(10), new ArmShooter(ArmShooter::kOn));
	spindownScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(10), new ArmShooter(ArmShooter::kOff));
	
	tuneShooterScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(8), new TunePitchEncoder());

	armUpScheduler = new ReleasedButtonScheduler(false, new DigitalIOButton(3),
			new MoveCollectorArm(COLLECTOR_PITCH_UP));
	armMidScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(11), new MoveCollectorArm(COLLECTOR_PITCH_MID));
	armDownScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(1), new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	collectScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickRight, 1), new Collect());

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
	shiftScheduler->Start();

	shootScheduler->Start();
	spinupScheduler->Start();
	spindownScheduler->Start();
	tuneShooterScheduler->Start();

	collectScheduler->Start();
	armUpScheduler->Start();
	armMidScheduler->Start();
	armDownScheduler->Start();
}

Command* OI::createChangePitchFromOI() {
	double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
			OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
	return new ChangeShooterPitch(OI_SHOOTER_ANGLE_CONVERT(val));
}
