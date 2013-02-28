#include "CollectorAuto.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Collector/Collect.h"
#include "../Collector/MoveCollectorArm.h"
#include "../Collector/EjectDisks.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"

CollectorAuto::CollectorAuto() :
	CommandGroup("CollectorAuto") {
	AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_COLLECT));
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_MID));
	AddSequential(new EjectDisks());
}

CollectorAuto::~CollectorAuto() {

}
