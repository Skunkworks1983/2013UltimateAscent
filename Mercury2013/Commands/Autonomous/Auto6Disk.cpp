#include "Autonomous.h"

#include "../WaitForCommand.h"
#include "../Shooter/Shoot.h"
#include "../Shooter/ArmShooter.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Collector/Collect.h"
#include "../Collector/EjectDisks.h"
#include "../Automatic/DriveDistance.h"
#include "../Drivebase/Shift.h"

Autonomous *Autonomous::createCollect6PyraInner() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect6PyraInner");

	// Drive and collect block
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddSequential(
			new DriveDistance(-9.42, AUTO_DRIVE_DIST_STABILITY / 3.0,
					AUTO_DRIVE_DIST_THRESHOLD * 1.5));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	CommandGroup *bgCollect = new CommandGroup();
	bgCollect->AddSequential(new Collect(7500.0));
	bgCollect->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	cmd->AddParallel(bgCollect);
	cmd->AddSequential(
			(new DriveDistance(76.25))->setOutputRange(
					AUTO_DRIVE_DIST_SPEED_MIN, .75));

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

	//cmd->AddSequential(createCollect4PyraFront());

	cmd->AddParallel(
			(new DriveDistance(24.0))->setOutputRange(
					AUTO_DRIVE_DIST_SPEED_MIN, .65));
	cmd->AddParallel(new ChangeShooterPitch(0.0, true));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddSequential(new Collect(7500.0));
	cmd->AddSequential(new ChangeShooterPitch(0.0, true));

	CommandGroup *putIntoShooter = new CommandGroup();
	putIntoShooter->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	putIntoShooter->AddSequential(new EjectDisks(Collector::kForward));

	putIntoShooter->AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	putIntoShooter->AddSequential(new ArmShooter(ArmShooter::kOn));
	putIntoShooter->AddParallel(
			new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT, true));
	putIntoShooter->AddSequential(
			new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));
	cmd->AddParallel(putIntoShooter);
	cmd->AddSequential(
			(new DriveDistance(-24.0))->setOutputRange(
					AUTO_DRIVE_DIST_SPEED_MIN, .65));
	cmd->AddSequential(new WaitForCommand(putIntoShooter));

	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
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
