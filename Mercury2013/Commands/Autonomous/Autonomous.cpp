#include "Autonomous.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Collector/Collect.h"
#include "../Collector/MoveCollectorArm.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"

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
	char typeA = '0', typeB = '0', cmdType = '0';
	float arg = 0.0;
	for (i = 0; i < argc; i++) {
		sscanf(argv[i], "%c\t%c%c\t%f", &cmdType, &typeA, &typeB, &arg);
		Command *use = NULL;
		switch (AUTO_SCRIPT_CHARMASK(typeA,typeB)) {
		case AUTO_SCRIPT_CHARMASK('d','d'):
			use = new DriveDistance(arg);
			break;
		case AUTO_SCRIPT_CHARMASK('t','d'):
			use = new TurnDegree(arg);
			break;
		case AUTO_SCRIPT_CHARMASK('d','s'):
			use = new Shift((Shift::ShiftType) ((int) arg));
			break;
		case AUTO_SCRIPT_CHARMASK('w','f'):
			use = new WaitCommand(arg);
			break;
		case AUTO_SCRIPT_CHARMASK('w','u'):
			use = new WaitUntilCommand(arg);
			break;
		case AUTO_SCRIPT_CHARMASK('c','n'):
			use = new Collect();
			break;
		case AUTO_SCRIPT_CHARMASK('c','p'):
			use = new MoveCollectorArm(arg);
			break;
		case AUTO_SCRIPT_CHARMASK('a','s'):
			use = new ArmShooter((ArmShooter::ArmType) ((int) arg));
			break;
		case AUTO_SCRIPT_CHARMASK('s','s'):
			use = new Shoot();
			break;
		case AUTO_SCRIPT_CHARMASK('s','p'):
			use = new ChangeShooterPitch(arg);
			break;
		default:
			break;
		}
		if (use != NULL) {
			switch (cmdType) {
			case 's':
				AddSequential(use);
				break;
			case 'p':
				AddSequential(use);
				break;
			default:
				break;
			}
		}
	}
}

Autonomous::~Autonomous() {

}
