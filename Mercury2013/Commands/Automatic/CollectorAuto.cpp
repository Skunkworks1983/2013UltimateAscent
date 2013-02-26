#include "CollectorAuto.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"
#include "../Collector/Collect.h"
#include "../Collector/MoveCollectorArm.h"

#include "../Shooter/Shoot.h"
#include "../Shooter/ChangeShooterPitch.h"
#include "../Shooter/ArmShooter.h"
#include "../Drivebase/Shift.h"

CollectorAuto::CollectorAuto() :
	CommandGroup("CollectorAuto") {
	
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_DOWN)); //probably not used
	AddSequential(new DriveDistance(24));
	AddSequential(new Collect());
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_UP));
	AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_COLLECT));
	//AddSequential(new EjectDisks());
	AddSequential(new ChangeShooterPitch(SHOOTER_PITCH_UPPER_LIMIT));
	AddSequential(new MoveCollectorArm(COLLECTOR_PITCH_DOWN));
}

CollectorAuto::~CollectorAuto() {

}
