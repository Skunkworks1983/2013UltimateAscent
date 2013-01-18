#ifndef __UFOBOT_H
#define __UFOBOT_H

#include "WPILib.h"

class UFOBot : public IterativeRobot {
private:
	LiveWindow *lw;

public:
	virtual void RobotInit();
	
	virtual void AutonomousInit();
	
	virtual void AutonomousPeriodic();
	
	virtual void TeleopInit();
	
	virtual void TeleopPeriodic();
	
	virtual void TestPeriodic();
};

START_ROBOT_CLASS(UFOBot);
#endif
