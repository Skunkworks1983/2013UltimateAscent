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
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;

	DriverStation *driverStation;
	DriverStationLCD *driverStationLCD;
	DriverStationEnhancedIO *driverStationEIO;

	Button *shiftButton;
	
	Button *shootButton;
	Button *spinupButton;
	Button *tuneShooterButton;
	Button *ejectButton;
	
	Button *armUpButton;
	Button *armMidButton;
	Button *armDownButton;
	Button *collectButton;

public:
	OI();

	static Command* createChangePitchFromOI();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
};

#endif
