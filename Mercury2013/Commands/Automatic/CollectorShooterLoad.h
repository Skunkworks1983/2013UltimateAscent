#ifndef __CMD_COLLECTOR_SHOOT_LOAD_H
#define __CMD_COLLECTOR_SHOOT_LOAD_H

#include "WPILib.h"

class CollectorShooterLoad: public CommandGroup {
private:
	CommandGroup *jiggleShooter;
	Command *lowerCollector;
public:
	CollectorShooterLoad();
	~CollectorShooterLoad();
	virtual void End();
};
#endif
