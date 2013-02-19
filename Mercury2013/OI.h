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
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;

	DriverStation *driverStation;
	DriverStationLCD *driverStationLCD;
	DriverStationEnhancedIO *driverStationEIO;

	ButtonScheduler *shiftScheduler;
	
	ButtonScheduler *shootScheduler;
	ButtonScheduler *spinupScheduler;
	ButtonScheduler *spindownScheduler;
	ButtonScheduler *flushScheduler;
	ButtonScheduler *changePositionScheduler;
	ButtonScheduler *tuneShooterScheduler;
	
	ButtonScheduler *armUpScheduler;
	ButtonScheduler *armMidScheduler;
	ButtonScheduler *armDownScheduler;
	ButtonScheduler *collectScheduler;

public:
	OI();

	static Command* createChangePitchFromOI();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
	void setLightState(DriverStationLight light, bool state);
};

#endif
