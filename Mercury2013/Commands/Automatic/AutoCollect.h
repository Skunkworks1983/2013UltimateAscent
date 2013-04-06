#ifndef __CMD_AUTO_COLLECT_H
#define __CMD_AUTO_COLLECT_H
#include "WPILib.h"

class AutoCollect: public CommandGroup {
public:
	AutoCollect();
	~AutoCollect();
	virtual void End();
};
#endif
