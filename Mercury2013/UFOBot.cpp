#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Automatic/TurnDegree.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Utils/Scripting.h"
#include "Utils/Time.h"
#include "Subsystems/CollectorArmController.h"
#include "Subsystems/CollectorArms.h"
#include "Subsystems/Collector.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);
	chooser = Scripting::generateAutonomousModes(AUTO_SCRIPT_LOCATIONS);
	SmartDashboard::PutData("Autonomous modes", chooser);
	SmartDashboard::PutData(Scheduler::GetInstance());

	printVersion();
}

void UFOBot::AutonomousInit() {
	DefaultInit();
	Scheduler::GetInstance()->RemoveAll();
	((ScriptRunner*) chooser->GetSelected())->startCommand();
}
void UFOBot::AutonomousPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
	motorSaftey();
}

void UFOBot::DefaultInit() {
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::driveBase->reset();
	CommandBase::driveBase->shift(false);
	CommandBase::driveBase->setMotorScalingFactor(1.0);
	if (!CommandBase::shooterPitch->isPitchTuned()) {
		Scheduler::GetInstance()->AddCommand(new TunePitchEncoder());
	}
	Scheduler::GetInstance()->AddCommand(new UpdateOI());
}

void UFOBot::TeleopInit() {
	DefaultInit();
	CommandBase::oi->registerButtonSchedulers();
}

void UFOBot::TeleopPeriodic() {
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
	motorSaftey();
	SmartDashboard::PutNumber("Loops Per Second", GetLoopsPerSec());
}

void UFOBot::DisabledInit() {
}
void UFOBot::DisabledPeriodic() {
	motorSaftey();
	printVersion();
}

void UFOBot::printVersion() {
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line1, 1,
			"Version 1.12");
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line2, 1,
			"Thurs-Ellensburg");
	DriverStationLCD::GetInstance()->UpdateLCD();
}

void UFOBot::TestInit() {
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
	motorSaftey();
}

void UFOBot::motorSaftey() {
	if (CommandBase::shooterPitch != NULL) {
		CommandBase::shooterPitch->motorSafety();
	}
}
