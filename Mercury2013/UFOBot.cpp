#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Buttons/ReleasedButtonScheduler.h"
#include "Buttons/ButtonScheduler.h"

#include "Commands/Shift.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);
}

void UFOBot::AutonomousInit() {
}
void UFOBot::AutonomousPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TeleopInit() {
	(new ReleasedButtonScheduler(false,
					new JoystickButton(CommandBase::oi->getDriveJoystickLeft(),1),
					new Shift(Shift::kToggle)))->Start();
}

void UFOBot::TeleopPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
}
