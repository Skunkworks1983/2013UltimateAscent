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
	Command *autoCollectCommand;

	Button *shiftButton;
	Button *driveDirectionButton;
	
	//Shooter Stuff
	Button *lightButton;
	Button *shootButton;
	Button *spinupButton;
	Button *shooterNoWait;
	
	//CollectorArms Arm Stuff
	Button *armUpButton;
	Button *armDownButton;
	Button *collectorOverrideButton;
	double targetCollectorPitch;
	Trigger *armChangeTrigger;
	
	//Shooter Angle Stuff
	Button *shooterHighButton;
	Button *shooterMiddleButton;
	Button *shooterLowButton;
	Button *shooterZeroButton;
	Button *shooterAngleOverrideButton;
	Trigger *shooterAngleChangeTrigger;
	double targetShooterPitch;
	Button *shooterPowerOverrideButton;
	
	//Pre-configured collector shooter unisons
	Button *collectorSlotButton;
	Button *shooterCollectorButton;
	
	//Climber
	Button *pokeyStickButton;
	Button *climberRackButton;
	
	Button *collectButton;
	Button *ejectButton;
public:
	OI();

	static Command* createChangePitchFromOI(void *arg);
	static Command* createChangeCollectorPitch(void *arg);
	static double getCollectorTargetPitch();
	static double getShooterTargetPitch();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();

	void registerButtonSchedulers();
};

#endif
