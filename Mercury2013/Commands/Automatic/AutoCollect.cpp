#include "AutoCollect.h" 
#include "WPILib.h"
#include "../Collector/Collect.h"
#include "CollectorShooterLoad.h"
#include "../Collector/MoveCollectorArm.h"

AutoCollect::AutoCollect() :
	CommandGroup("AutoCollect") {
	AddParallel(new MoveCollectorArm(COLLECTOR_PITCH_FLOOR));
	AddSequential(new Collect(-1));
}

AutoCollect::~AutoCollect() {
}

void AutoCollect::End() {
	if (CommandBase::collector->getFrisbeeSensorCount() > 0) {
		(new CollectorShooterLoad())->Start();
	} else {
		(new MoveCollectorArm(COLLECTOR_PITCH_DOWN))->Start();
	}
}
