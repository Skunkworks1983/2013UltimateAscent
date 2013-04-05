#include "Autonomous.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Automatic/CollectorShooterLoad.h"
#include "../Collector/Collect.h"
#include "../Collector/EjectDisks.h"
#include "../Collector/MoveCollectorArm.h"

#include "../CommandStarter.h"
#include "../CommandCanceler.h"
#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"
#include "../WaitForTrigger.h"

Autonomous::Autonomous() :
	CommandGroup("Autonomous-Blank") {
}

Autonomous::Autonomous(char *style) :
	CommandGroup(style) {
}

Autonomous *Autonomous::createCollect5PyraOuter() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect5PyraOuter");

	// Drive and collect block
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));

	//Now shoot the 3
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new DriveDistance(-48));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddSequential(new DriveDistance(60));
	cmd->AddSequential(new Collect(7500.0));

	//Put into shooter block
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	cmd->AddSequential(new EjectDisks(Collector::kForward));
	cmd->AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_SIDE, true));

	//Now shoot the 4
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	//Now we need to collect moar
	//Get to the start of the other autonomous program...
	cmd->AddSequential(new ChangeShooterPitch(0));
	cmd->AddSequential(new ArmShooter(ArmShooter::kOff));
	return cmd;
}

Autonomous *Autonomous::createCollect6PyraInner() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect6PyraInner");

	// Drive and collect block
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	CommandBase *driveLong = new DriveDistance(84);
	cmd->AddParallel(driveLong);
	cmd->AddParallel(new Collect(7500.0));
	cmd->AddSequential(
			new WaitForTrigger(CommandBase::driveBase->getLeftWhisker(),
					CommandBase::driveBase->getRightWhisker()));
	cmd->AddSequential(new CommandCanceler(driveLong));

	//Put into shooter block
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	cmd->AddSequential(new EjectDisks(Collector::kForward));
	cmd->AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddSequential(
			new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT, true));

	//Now shoot the 4
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(createCollect4PyraFront());
	return cmd;
}
Autonomous *Autonomous::createCollect4PyraFront() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect4PyraFront");
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddParallel(new DriveDistance(11));
	cmd->AddSequential(new Collect(7500.0));
	// TODO cancel the drive command and cache the distances to reverse it
	// @see CommandCanceler and DriveDistance::invertDriveCommand
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	cmd->AddSequential(new EjectDisks(Collector::kForward));
	cmd->AddParallel(new MoveCollectorArm(10));
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));
	cmd->AddSequential(new DriveDistance(-11));

	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new ArmShooter(ArmShooter::kOff));
	cmd->AddSequential(new ChangeShooterPitch(0));
	return cmd;
}

Autonomous *Autonomous::createJustShootFront() {
	Autonomous *cmd = new Autonomous("Autonomous-JustShootPyraFront");
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new MoveCollectorArm(10));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));

	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new ArmShooter(ArmShooter::kOff));
	return cmd;
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
			use = new Collect(arg);
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

void Autonomous::Initialize() {
	CommandBase::shooter->setControlScheme(SHOOTER_DEFAULT_CONTROL);
	CommandBase::shooter->setWaitScheme(SHOOTER_DEFAULT_WAIT);
}
