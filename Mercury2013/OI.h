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
	
	//Shooter Stuff
	Button *shootButton;
	Button *spinupButton;
	Button *tuneShooterButton;
	Button *shooterToThing;
	
	//Collector Arm Stuff
	Button *armUpButton;
	Button *armMidButton;
	Button *armDownButton;
	double targetCollectorPitch;
	Trigger *armChangeTrigger;
	
	Button *collectorSlotButton;
	
	Button *collectButton;
	Button *ejectButton;
public:
	OI();

	static Command* createChangePitchFromOI();
	static Command* createChangeCollectorPitch();
	static double getCollectorTargetPitch();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
};

#endif
