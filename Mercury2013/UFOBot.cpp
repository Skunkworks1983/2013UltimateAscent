#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Automatic/TurnDegree.h"
#include "Commands/Autonomous/Scriptreader.h"

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);
	chooser = new SendableChooser();
	chooser->AddDefault("DriveDistance", new DriveDistance(2));
	chooser->AddObject("TurnDegree", new TurnDegree(90));
	
	chooser->AddDefault("Test1", new ScriptReader("test1.txt"));
	chooser->AddObject("Test2", new ScriptReader("test2.txt"));
	chooser->AddObject("Test3", new ScriptReader("test3.txt"));

SmartDashboard::PutData("Autonomous modes", chooser);
}

void UFOBot::AutonomousInit() {
	DefaultInit();
	int argc = 0;
	char ** argv = new char*[AUTO_SCRIPT_MAXLINES];
//	autonomousCommand = (Command *) chooser->GetSelected();
//	autonomousCommand->Start();
	scriptReader = (ScriptReader *) chooser->GetSelected();
	scriptReader->ReadScript(&argc, argv);
	Scheduler::GetInstance()->RemoveAll();
//	CommandBase::oi->getAutonomousConfig(argc, argv);
	Scheduler::GetInstance()->AddCommand(new Autonomous(argc,argv));
	for (argc = 0; argc < AUTO_SCRIPT_MAXLINES; argc++){
		delete argv[argc];
	}
	delete argv;
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
