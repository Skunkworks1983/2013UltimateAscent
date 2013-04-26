#ifndef __CMD_AUTONOMOUS_H
#define __CMD_AUTONOMOUS_H

#include "WPILib.h"

class Autonomous: public CommandGroup {
public:
	static Autonomous *createCollect4PyraFront();
	static Autonomous *createJustShootFront();
	static Autonomous *createJustShootBack();
	static Autonomous *createCollect6PyraInner();
	static Autonomous *createCollect5PyraOuter();
	static Autonomous *createCollect6PyraInner4Chunk();
public:
	Autonomous();
	Autonomous(char *style);
	Autonomous(int argc, char **argv);
	virtual void Initialize();
	~Autonomous();
};

#endif
