#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Buttons/PressedButtonScheduler.h"

#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Commands/Shooter/FlushShooter.h"
#include "Commands/Shooter/ChangePitch.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Commands/Drivebase/Shift.h"
#include "Commands/Collector/ChangePosition.h"
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
	/*flushScheduler = new ReleasedButtonScheduler(false, new DigitalIOButton(1),
	 new FlushShooter());*/

	changePositionScheduler = /*new ReleasedButtonScheduler(
	 false,
	 new AnalogChangeTrigger(OI_SHOOTER_ANGLE_PROVIDER_CHANNEL, 0.01,
	 new DigitalIOButton(15)),
	 new CommandStarter(OI::createChangePitchFromOI));*/
	new ReleasedButtonScheduler(false, new DigitalIOButton(15),
			new CommandStarter(OI::createChangePitchFromOI));
	tuneShooterScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(8), new TunePitchEncoder());

	armUpScheduler = new ReleasedButtonScheduler(false, new DigitalIOButton(3),
			new ChangePosition(COLLECTOR_PITCH_UP));
	armMidScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(11), new ChangePosition(COLLECTOR_PITCH_MID));
	armDownScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(1), new ChangePosition(COLLECTOR_PITCH_DOWN));
	collectScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickRight, 1), new Collect());
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
	//flushScheduler->Start();
	//changePositionScheduler->Start();
	tuneShooterScheduler->Start();

	collectScheduler->Start();
	armUpScheduler->Start();
	armMidScheduler->Start();
	armDownScheduler->Start();
}

void OI::setLightState(DriverStationLight light, bool state) {
	driverStationEIO->SetDigitalOutput(light, state);
}

Command* OI::createChangePitchFromOI() {
	double val = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(OI_SHOOTER_ANGLE_PROVIDER_CHANNEL);
	return new ChangePitch(
			OI_SHOOTER_ANGLE_CONVERT(val));
}
