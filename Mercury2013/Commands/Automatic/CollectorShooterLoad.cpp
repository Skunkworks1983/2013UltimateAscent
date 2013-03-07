#include "CollectorShooterLoad.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Collector/Collect.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Collector/EjectDisks.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"
#include "../../Subsystems/Collector.h"

CollectorShooterLoad::CollectorShooterLoad() :
	CommandGroup("CollectorShooterLoad") {
	AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_COLLECT));
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	AddSequential(new EjectDisks(Collector::kForward));
}

CollectorShooterLoad::~CollectorShooterLoad() {

}
