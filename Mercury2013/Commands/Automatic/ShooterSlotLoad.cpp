#include "ShooterSlotLoad.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Shooter/ChangeShooterPitch.h"

ShooterSlotLoad::ShooterSlotLoad() :
	CommandBase("ShooterSlotLoad"), loadWithCollectorUp("ShooterSlotLoad--Up"),
			loadWithCollectorDown("ShooterSlotLoad--Down") {
	loadWithCollectorUp.AddSequential(
			new ChangeShooterPitch(SHOOTER_PITCH_SLOT_COLLECT));

	loadWithCollectorDown.AddSequential(new ChangeShooterPitch(0.0));
	loadWithCollectorDown.AddSequential(
			new MoveCollectorArm(COLLECTOR_PITCH_UP));
	loadWithCollectorDown.AddSequential(
			new ChangeShooterPitch(SHOOTER_PITCH_SLOT_COLLECT));
}
ShooterSlotLoad::~ShooterSlotLoad() {
}
void ShooterSlotLoad::Initialize() {
	if (collectorArms->getAngle() > COLLECTOR_SHOOTER_INTERFERENCE_HIGH) {
		loadWithCollectorUp.Start();
	} else {
		loadWithCollectorDown.Start();
	}
}
void ShooterSlotLoad::Execute() {
}
void ShooterSlotLoad::End() {
}
void ShooterSlotLoad::Interrupted() {
}
bool ShooterSlotLoad::IsFinished() {
	return true;
}
