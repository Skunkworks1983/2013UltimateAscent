#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/OI/UpdateOI.h"

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
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::oi->registerButtonSchedulers();
	CommandBase::driveBase->reset();
	Scheduler::GetInstance()->AddCommand(new UpdateOI());
}

void UFOBot::TeleopPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
}
