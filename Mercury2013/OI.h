#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	enum DriverStationLight {
		kLightClimberHook1 = 1,
		kLightClimberHook2 = 2,
		kLightClimberHook3 = 3,
		kLightClimberHook4 = 4
	};
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;

	DriverStation *driverStation;
	DriverStationLCD *driverStationLCD;
	DriverStationEnhancedIO *driverStationEIO;

	ButtonScheduler *shiftScheduler;
	ButtonScheduler *distanceScheduler;

public:
	OI();

	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
	void setLightState(DriverStationLight light, bool state);
};

#endif
