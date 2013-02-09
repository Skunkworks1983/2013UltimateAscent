#ifndef __OI_H
#define __OI_H

#include "WPILib.h"

/**
 * @brief Driver station interface
 * 
 * Interface for the driver station.
 * Turning LEDs on/off.
 * Getting button/joystick/etc states.
 */
class OI {
public:
	enum DriverStationLight {
		kLightClimberHook1 = 1,
		kLightClimberHook2 = 2,
		kLightClimberHook3 = 3,
		kLightClimberHook4 = 4
	};
	bool hasStashedAuto;
	
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;

	DriverStation *driverStation;
	DriverStationLCD *driverStationLCD;
	DriverStationEnhancedIO *driverStationEIO;

	ButtonScheduler *shiftScheduler;
	ButtonScheduler *shootScheduler;
	ButtonScheduler *spinupScheduler;

public:
	OI();

	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
	void setLightState(DriverStationLight light, bool state);
	
	void getAutonomousConfig(int &argc, char ** argv);
};

#endif
