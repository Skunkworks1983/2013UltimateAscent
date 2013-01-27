#include "UFOBot.h"
#include "Commands/CommandBase.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);
}

void UFOBot::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
}
void UFOBot::AutonomousPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TeleopInit() {
	CommandBase::oi->registerButtonSchedulers();
	Scheduler::GetInstance()->RemoveAll();
}

void UFOBot::TeleopPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
}
