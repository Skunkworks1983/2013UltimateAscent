#include "Autonomous.h" 
#include "Automatic/DriveDistance.h"
#include "Automatic/TurnDegree.h"

Autonomous::Autonomous() :
	CommandGroup("Autonomous") {
	// Add the autonomous sequence
	AddSequential(new DriveDistance(24));
	//Magi-collect
	AddSequential(new DriveDistance(-24));
	//Magi-shoot
	AddSequential(new DriveDistance(12));
	AddSequential(new TurnDegree(90));
	AddSequential(new DriveDistance(60));
	AddSequential(new TurnDegree(90));
	AddSequential(new DriveDistance(60));
}

Autonomous::~Autonomous() {

}
