#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);
}

void UFOBot::AutonomousInit() {
	DefualtInit();
	Scheduler::GetInstance()->RemoveAll();
}
void UFOBot::AutonomousPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::DefaultInit() {
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::driveBase->reset();
	Scheduler::GetInstance()->AddCommand(new UpdateOI());
}

void UFOBot::TeleopInit() {
	DefualtInit();
	CommandBase::oi->registerButtonSchedulers();
}

void UFOBot::TeleopPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TestInit() {
	lw->SetEnabled(true);
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
}
