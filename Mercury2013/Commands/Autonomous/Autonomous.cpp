#include "Autonomous.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Automatic/CollectorShooterLoad.h"
#include "../Collector/Collect.h"
#include "../Collector/EjectDisks.h"
#include "../Collector/MoveCollectorArm.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"

Autonomous::Autonomous() :
	CommandGroup("Autonomous") {
	AddSequential(new MoveCollectorArm(0));
	AddParallel(new DriveDistance(22));
	AddSequential(new Collect(false));
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	AddSequential(new EjectDisks(Collector::kForward));
	AddParallel(new MoveCollectorArm(10));
	AddSequential(new ArmShooter(ArmShooter::kOn));
	AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));
	AddSequential(new DriveDistance(-18));

	for (int i = 0; i < 4; i++) {
		AddSequential(new Shoot());
		AddSequential(new WaitCommand(.65));
	}
	
	AddSequential(new ArmShooter(ArmShooter::kOff));
	AddParallel(new ChangeShooterPitch(0));
	AddSequential(new DriveDistance(12));
}

Autonomous::Autonomous(int argc, char **argv) :
	CommandGroup("Autonomous") {
	int i = 0;
	char typeA = '0', typeB = '0', cmdType = '0';
	float arg = 0.0;
	for (i = 0; i < argc; i++) {
		if (argv[i][0] == '#') {
			continue;
		}
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
			use = new Collect(arg >= 1.0);
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
		case AUTO_SCRIPT_CHARMASK('c','a'):
			use = new CollectorShooterLoad();
			break;
		case AUTO_SCRIPT_CHARMASK('c','e'):
			use = new EjectDisks((Collector::MotorDirection) ((int) arg));
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
				AddParallel(use);
				break;
			default:
				break;
			}
		}
	}
}

Autonomous::~Autonomous() {

}
