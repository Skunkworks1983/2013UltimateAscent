#include "UFOBot.h"
#include "Commands/CommandBase.h"
#include "Commands/UpdateOI.h"
#include "Commands/Autonomous/Autonomous.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Automatic/TurnDegree.h"
#include "Utils/Scripting.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void UFOBot::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();
	GetWatchdog().SetEnabled(true);

	chooser = new SendableChooser();

	DIR * dp;
	struct dirent * ep;
	dp = opendir(AUTO_SCRIPT_LOCATIONS);
	bool isDefault = true;
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			char * fileName = new char[50];
			sprintf(fileName, "%s%s", AUTO_SCRIPT_LOCATIONS, ep->d_name);
			printf("%s\n", fileName);

			if (isDefault) {
				chooser->AddDefault(ep->d_name, fileName);
				isDefault = false;
			} else {
				chooser->AddObject(ep->d_name, fileName);
			}
		}
		(void) closedir(dp);
	} else {
		printf("SOMETHING IS VERY, VERY WRONG\n");
	}
	delete dp;
	delete ep;

	SmartDashboard::PutData("Autonomous modes", chooser);
}

void UFOBot::AutonomousInit() {
	DefaultInit();
	char *fName = (char*) chooser->GetSelected();
	Scheduler::GetInstance()->RemoveAll();
	int size = 0;
	char *rawData = Scripting::readFromFile(fName, size);
	Scheduler::GetInstance()->AddCommand(
			Scripting::createCommand(size, rawData));
	delete rawData;
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
