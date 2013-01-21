#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;
	
	DriverStationEnhancedIO *eIEIO;
	
	ButtonScheduler *shiftScheduler;
	
public:
	OI();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();
	
	void registerButtonSchedulers();
	void setLightStates(DigitalInput input);
};

#endif
