#ifndef _ROBOT_GLOBAL_H
#define _ROBOT_GLOBAL_H

#include "WPILib.h"
#include "driveBase.h"
#include "shifter.h"
#include "shooter.h"
#include "climber.h"
#include "collector.h"

class RobotGlobal {
	public:
		DriveBase *theDriveBase;
		Shooter *theShooter;
		Climber *theClimber;
		Collecter *theCollector;
		
		void emergencyStop();
		void runAuto(float timeInSeconds);
		
		bool isOperatorControl();
		bool isAutonomous();
		bool isDisabled();
		bool isEnabled();
};

#endif