#ifndef __CMD_AUTONOMOUS_H
#define __CMD_AUTONOMOUS_H

#include "WPILib.h"

class Autonomous: public CommandGroup {
public:
	static Autonomous *createCollectPyraFront();
	static Autonomous *createJustShootFront();
public:
	Autonomous();
	Autonomous(char *style);
	Autonomous(int argc, char **argv);
	virtual void Initialize();
	~Autonomous();
};

#endif
