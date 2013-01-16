#ifndef _ROBOT_GLOBAL_H
#define _ROBOT_GLOBAL_H

#include "WPILib.h"
#include "Subsystems/DriveBase.h"
#include "Subsystems/Shifter.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Collector.h"

class RobotGlobal {
	public:
		DriveBase *theDriveBase;
		Shooter *theShooter;
		Climber *theClimber;
		Collector *theCollector;
		
		void emergencyStop();
		void runAuto(float timeInSeconds);
		
		bool isOperatorControl();
		bool isAutonomous();
		bool isDisabled();
		bool isEnabled();
};

#endif