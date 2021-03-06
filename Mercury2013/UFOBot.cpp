#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Automatic/TurnDegree.h"
#include "Commands/Shooter/TunePitchEncoder.h"
#include "Commands/Shooter/ArmShooter.h"
#include "Utils/Scripting.h"
#include "Utils/Time.h"
#include "Subsystems/CollectorArmController.h"
#include "Subsystems/CollectorArms.h"
#include "Subsystems/Collector.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	chooser = Scripting::generateAutonomousModes(AUTO_SCRIPT_LOCATIONS);
	SmartDashboard::PutData("Autonomous modes", chooser);
	SmartDashboard::PutData(Scheduler::GetInstance());
	SetPeriod(50.0 / 1000.0);

	GetWatchdog().SetEnabled(true);
	GetWatchdog().SetExpiration(1);
	printVersion();
	cache = 0;
	sumRate = 0.0;
	registeredButtons = false;
}

void UFOBot::updateRealLoopsPerSecond() {
	double passed = getCurrentMillis() - lastLoopCall;
	lastLoopCall = getCurrentMillis();
	double rate = 999999.0;
	if (passed > 0.0) {
		rate = 1000.0 / passed;
	}
	sumRate *= 0.75;
	sumRate += rate * 0.25;
#if (DEBUG_LEVEL>=DEBUG_INFO)
	if (++cache > OI_DASH_UPDATE_SPEED) {
		cache = 0;
		SmartDashboard::PutNumber("Loops per Second", sumRate);
	}
#endif
}
void UFOBot::AutonomousInit() {
	DefaultInit();
	Scheduler::GetInstance()->RemoveAll();
	((ScriptRunner*) chooser->GetSelected())->startCommand();
}
void UFOBot::AutonomousPeriodic() {
	updateRealLoopsPerSecond();
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
	motorSaftey();
}

void UFOBot::DefaultInit() {
	sumRate = 0.0;
	printVersion();
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::driveBase->reset();
	CommandBase::driveBase->shift(false);
	CommandBase::driveBase->setMotorScalingFactor(1.0);
	CommandBase::shooter->setArmed(false);
	CommandBase::climber->setPokey(false);
	CommandBase::climber->setClimberPneumatic(false);
	if (!CommandBase::shooterPitch->isPitchTuned()) {
		Scheduler::GetInstance()->AddCommand(new TunePitchEncoder());
	}
	Scheduler::GetInstance()->AddCommand(new UpdateOI());
}

void UFOBot::TeleopInit() {
	DefaultInit();
	if (!registeredButtons) {
		CommandBase::oi->registerButtonSchedulers();
		registeredButtons = true;
	}
}

void UFOBot::TeleopPeriodic() {
	updateRealLoopsPerSecond();
	GetWatchdog().Feed();
	Scheduler::GetInstance()->Run();
	motorSaftey();
}

void UFOBot::DisabledInit() {
}
void UFOBot::DisabledPeriodic() {
	updateRealLoopsPerSecond();
	printVersion();
}

void UFOBot::printVersion() {
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line1, 1,
			"Version 1.7.2");
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line2, 1,
			"Friday's Hot Curry");
	DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line3, 1,
			"%s %s", __TIME__, __DATE__);
	DriverStationLCD::GetInstance()->UpdateLCD();
}

void UFOBot::TestInit() {
}

void UFOBot::TestPeriodic() {
	GetWatchdog().Feed();
	lw->Run();
}

void UFOBot::motorSaftey() {
	if (CommandBase::shooterPitch != NULL) {
		CommandBase::shooterPitch->motorSafety();
	}
}

