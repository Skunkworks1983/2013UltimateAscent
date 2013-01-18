#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class TankDrive: public CommandBase {
public:
	TankDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual bool IsInterruptible();
};

#endif
