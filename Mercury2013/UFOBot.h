#ifndef __UFOBOT_H
#define __UFOBOT_H

#include "WPILib.h"

/**
 * @brief Main robot class
 * 
 * Initialization functions (Init functions).
 * Looping functions (Periodic functions).
 */
class UFOBot: public IterativeRobot {
private:
	double lastLoopCall;
	double sumRate;
	LiveWindow *lw;
	SendableChooser *chooser;
	void printVersion();
	int cache;
public:
	virtual void RobotInit();
	void updateRealLoopsPerSecond();

	/**
	 * @brief Common initialization code.
	 * 
	 * Code that runs on both autonomous and teleop init.
	 */
	inline void DefaultInit();

	virtual void AutonomousInit();

	virtual void AutonomousPeriodic();

	virtual void TeleopInit();

	virtual void TeleopPeriodic();

	virtual void TestInit();

	virtual void TestPeriodic();

	virtual void DisabledInit();

	virtual void DisabledPeriodic();

	void motorSaftey();
};

START_ROBOT_CLASS(UFOBot)
#endif
