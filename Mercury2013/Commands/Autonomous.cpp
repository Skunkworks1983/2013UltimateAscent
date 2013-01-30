#include "Autonomous.h" 
#include "Automatic/DriveDistance.h"
#include "Automatic/TurnDegree.h"

Autonomous::Autonomous() : CommandGroup("Autonomous") {
	// Add the autonomous sequence
	AddSequential(new DriveDistance(24));
	AddSequential(new TurnDegree(90));
	AddSequential(new DriveDistance(24));
	AddSequential(new TurnDegree(90));
	AddSequential(new DriveDistance(24));
	AddSequential(new TurnDegree(90));
	AddSequential(new DriveDistance(24));
	AddSequential(new TurnDegree(90));
}

Autonomous::~Autonomous() {

}
