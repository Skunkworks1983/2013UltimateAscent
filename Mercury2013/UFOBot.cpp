#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Automatic/TurnDegree.h"
#include "Utils/Scripting.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);

	chooser = Scripting::generateAutonomousModes(AUTO_SCRIPT_LOCATIONS);
	SmartDashboard::PutData("Autonomous modes", chooser);
//	SmartDashboard::PutData(Scheduler::GetInstance());
}

void UFOBot::AutonomousInit() {
	DefaultInit();
	Scheduler::GetInstance()->RemoveAll();
	((ScriptLoader*) chooser->GetSelected())->startCommand();
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
	DefaultInit();
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
