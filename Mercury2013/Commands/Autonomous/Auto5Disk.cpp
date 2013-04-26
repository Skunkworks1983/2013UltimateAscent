#include "Autonomous.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ArmShooter.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Collector/Collect.h"
#include "../Collector/EjectDisks.h"
#include "../Automatic/DriveDistance.h"
#include "../Drivebase/Shift.h"
#include "../Automatic/DiddlerDrive.h"

Autonomous *Autonomous::createCollect5PyraOuter() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect5PyraOuter");

	// Drive and collect block
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_BACK));

	//Now shoot the 3
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new ChangeShooterPitch(0));
	cmd->AddSequential(new DriveDistance(-12));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddParallel(new DriveDistance(18));
	cmd->AddSequential(new Collect(7500.0));

	//Put into shooter block
	cmd->AddSequential(new DiddlerDrive(-0.5));
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
