#include "Autonomous.h"

#include "../Shooter/ArmShooter.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/Shoot.h"

Autonomous *Autonomous::createJustShootFront() {
	Autonomous *cmd = new Autonomous("Autonomous-JustShootPyraFront");
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_PYRAMID_FRONT));

	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new ArmShooter(ArmShooter::kOff));
	return cmd;
}

Autonomous *Autonomous::createJustShootBack() {
	Autonomous *cmd = new Autonomous("Autonomous-JustShootPyraBack");
	cmd->AddSequential(new ArmShooter(ArmShooter::kOn));
	cmd->AddSequential(new ChangeShooterPitch(.520)); //.55 = Natural back
	cmd->AddSequential(new WaitUntilCommand(9.0));

	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());
	cmd->AddSequential(new Shoot());

	cmd->AddSequential(new ArmShooter(ArmShooter::kOff));
	cmd->AddSequential(new ChangeShooterPitch(0.0));
	return cmd;
}

