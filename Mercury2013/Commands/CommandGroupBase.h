#ifndef __COMMAND_GROUP_BASE_H
#define __COMMAND_GROUP_BASE_H

#include "Commands/CommandGroup.h"

class CommandGroupBase: public Command {
public:
	CommandGroupBase(const char *name);
	static void init();
};

#endif
