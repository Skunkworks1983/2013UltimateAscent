#include "Autonomous.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "Commands/WaitCommand.h"

Autonomous::Autonomous() :
	CommandGroup("Autonomous") {
	// Add the autonomous sequence
	AddSequential(new DriveDistance(24));
	//Magi-collect
	AddSequential(new DriveDistance(-24));
	//Magi-shoot
	AddSequential(new DriveDistance(12));
	AddSequential(new TurnDegree(-90));
	AddSequential(new DriveDistance(84));
	AddSequential(new TurnDegree(-90));
	AddSequential(new DriveDistance(84));
}

Autonomous::Autonomous(int argc, char **argv) :
	CommandGroup("Autonomous") {
	int i = 0;
	char type = '0';
	float arg = 0.0;
	for (i = 0; i < argc; i++) {
		sscanf(argv[i], "%c\t%f", &type, &arg);
		switch (type) {
		case 'd':
			AddSequential(new DriveDistance(arg));
			break;
		case 't':
			AddSequential(new TurnDegree(arg));
			break;
		case 'w':
			AddSequential(new WaitCommand(arg));
		default:
			break;
		}
	}
}

Autonomous::~Autonomous() {

}
