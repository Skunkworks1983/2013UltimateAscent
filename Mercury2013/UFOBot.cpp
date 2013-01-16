#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/ExampleCommand.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	autonomousCommand = new ExampleCommand();
	lw = LiveWindow::GetInstance();
}

void UFOBot::AutonomousInit() {
	autonomousCommand->Start();
}
void UFOBot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void UFOBot::TeleopInit() {
	autonomousCommand->Cancel();
}

void UFOBot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void UFOBot::TestPeriodic() {
	lw->Run();
}
