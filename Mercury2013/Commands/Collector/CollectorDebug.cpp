#include "CollectorDebug.h"
#include "WPILib.h"
#include "../../Utils/Time.h"

CollectorDebug::CollectorDebug() :
	CommandBase("CollectorDebug") {
}

CollectorDebug::~CollectorDebug() {

}

void CollectorDebug::Initialize() {
	char *filename = new char[50];
	sprintf(filename, "collector_debug_%f", getCurrentMillis());
	fileOut.open(filename);
	fileOut
			<< "Time (millis), Left Position, Right Position, Left Power, Right Power\n";
}

void CollectorDebug::Execute() {
	fileOut << getCurrentMillis() << ",";
	fileOut << CommandBase::collectorArms->getLeftAngle() << ",";
	fileOut << CommandBase::collectorArms->getRightAngle() << ",";
	fileOut << CommandBase::collectorArms->getLeftOutput() << ",";
	fileOut << CommandBase::collectorArms->getRightOutput() << "\n";
}

bool CollectorDebug::IsFinished() {
	return false;
}

void CollectorDebug::End() {
	fileOut.close();
}

void CollectorDebug::Interrupted() {
	fileOut.close();
}
