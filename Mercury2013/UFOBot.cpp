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
	debugEnabled = false;
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
}

void UFOBot::DisabledInit() {
}
void UFOBot::DisabledPeriodic() {
	motorSaftey();
}

void UFOBot::TestInit() {
	lw->SetEnabled(true);
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

void UFOBot::printDebug(){
	using std::cout;
	if(debugEnabled == true){
		
		//print timestamp
		std::cout << getCurrentMillis() << ", ";
		//print collector information
		cout << CommandBase::collectorArms->getLeftAngle() << ", ";
		cout << CommandBase::collectorArms->getRightAngle() << ", ";
		cout << CommandBase::collector->getSpinnerDirection() << endl;
		
		/*
		//print timestamp
		outstream << getCurrentMillis() << ", ";
		//prints collector information
		outstream << CommandBase::collectorArms->getLeftAngle() << ", ";
		outstream << CommandBase::collectorArms->getRightAngle() << ", ";
		outstream << CommandBase::collector->getSpinnerDirection() << endl;
		*/
		
	}else{
		cout << "Format: Timestamp, collectorArmLeft, collectorArmRight, spinnerDirection";
		debugEnabled = true;
		//outstream.open(name);		//Not working
	}
}

void UFOBot::createDebug(){
	/**
	 * This function gets called only once
	 * It runs through each file inside /Debug/ and finds the next file in order
	 * This will be used for Debug documentation
	 * @author Ross Bajocich
	 */
	int number = 48;		//it is 48 because of ASCI character asignment
	name = "Debug_Data_";
	while(true){
		name = name + (char)number + ".csv";
		ifstream myFile("/Debug/name.csv");
		if(!myFile){
			outstream.open("/Debug/name.csv");
			break;
		}else{
			number++;
		}
	}
}
