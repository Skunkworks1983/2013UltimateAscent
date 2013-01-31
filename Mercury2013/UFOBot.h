#ifndef __UFOBOT_H
#define __UFOBOT_H

#include "WPILib.h"

/**
 * @brief Main robot class
 * 
 * Initialization functions (Init functions).
 * Looping functions (Periodic functions).
 */
class UFOBot : public IterativeRobot {
private:
	LiveWindow *lw;

public:
	virtual void RobotInit();
	
	virtual void AutonomousInit();
	
	virtual void AutonomousPeriodic();
	
	virtual void TeleopInit();
	
	virtual void TeleopPeriodic();
	
	virtual void TestInit();
	
	virtual void TestPeriodic();
};

START_ROBOT_CLASS(UFOBot);
#endif
