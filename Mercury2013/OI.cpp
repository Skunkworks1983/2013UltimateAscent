#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Commands/Automatic/DriveDistance.h"
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
	distanceScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickLeft, 11),
			new DriveDistance(60, DriveDistance::linear));
}

Joystick *OI::getDriveJoystickLeft() {
	return driveJoystickLeft;
}

Joystick *OI::getDriveJoystickRight() {
	return driveJoystickRight;
}

void OI::registerButtonSchedulers() {
	shiftScheduler->Start();
	distanceScheduler->Start();
}

void OI::setLightState(DriverStationLight light, bool state) {
	driverStationEIO->SetDigitalOutput(light, state);
}
