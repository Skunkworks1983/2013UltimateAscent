#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Commands/Shooter/FlushShooter.h"
#include "Commands/Drivebase/Shift.h"

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
	shootScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(11), new Shoot());
	spinupScheduler = new ReleasedButtonScheduler(false,
			new DigitalIOButton(3), new ArmShooter(ArmShooter::kToggle));
	shootScheduler = new ReleasedButtonScheduler(false, new DigitalIOButton(1),
			new FlushShooter());
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
	flushScheduler->Start();
}

void OI::setLightState(DriverStationLight light, bool state) {
	driverStationEIO->SetDigitalOutput(light, state);
}
