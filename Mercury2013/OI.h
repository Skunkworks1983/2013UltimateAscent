#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driveJoystickLeft;
	Joystick *driveJoystickRight;
	
	ButtonScheduler *shiftScheduler;
public:
	OI();
	
	Joystick *getDriveJoystickLeft();
	Joystick *getDriveJoystickRight();
	
	void registerButtonSchedulers();
};

#endif
