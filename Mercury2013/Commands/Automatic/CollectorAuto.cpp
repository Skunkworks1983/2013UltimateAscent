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
	// Add the autonomous sequence
	
	/**
	 * You nub
	 * 
	 * Here are the commands ill cahnge these comments later
	 **/
	
	/*
	 * -Move forward a bit maybe
	 * -Turn on collector
	 * -stop collector
	 * -move collector arm to up position
	 * -move shooter arm to correct catch postion
	 * -move collector arm to CORRECT_POSITION
	 * -THROW UP ALLLLL YOUR FRISBIE
	 * -move shooter to down position
	 * -move collector to down position
	 * -LOOP
	 */
	
	AddSequential(new MoveCollectorArm(DOWN)); //possibly not used
	AddSequential(new DriveDistance(24));
	AddSequential(new Collect());
	AddSequential(new MoveCollectorArm(UP_POSITION));
	AddSequential(new ChangeShooterPitch(CORRECT_POSITION));
	AddSequential(new EjectDisk());
	AddSequential(new ChangeShooterPitch(DOWN));
	AddSequential(new MoveCollectorArm(DOWN));
}

CollectorAuto::~CollectorAuto() {

}
