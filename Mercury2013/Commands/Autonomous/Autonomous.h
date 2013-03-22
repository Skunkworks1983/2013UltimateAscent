#ifndef __CMD_AUTONOMOUS_H
#define __CMD_AUTONOMOUS_H

#include "WPILib.h"

class Autonomous: public CommandGroup {
public:
	static Autonomous *createDefault();
	static Autonomous *createJustShoot();
public:
	Autonomous();
	Autonomous(char *style);
	Autonomous(int argc, char **argv);
	~Autonomous();
};

#endif
