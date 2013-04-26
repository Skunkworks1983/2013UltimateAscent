#include "Autonomous.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ArmShooter.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Collector/Collect.h"
#include "../Collector/EjectDisks.h"
#include "../Automatic/DriveDistance.h"
#include "../Drivebase/Shift.h"

Autonomous *Autonomous::createCollect4PyraFront() {
	Autonomous *cmd = new Autonomous("Autonomous-Collect4PyraFront");
	cmd->AddSequential(new Shift(Shift::kHigh));
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	cmd->AddParallel(new DriveDistance(34.54));
	cmd->AddSequential(new Collect(7500.0));
	// TODO cancel the drive command and cache the distances to reverse it
	// @see CommandCanceler and DriveDistance::invertDriveCommand
	cmd->AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	cmd->AddSequential(new EjectDisks(Collector::kForward));
	cmd->AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));
	cmd->AddSequential(new DriveDistance(-36));
	//cmd->AddSequential((new DriveDistance(-1.0))->setResetEncoder(false));

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
