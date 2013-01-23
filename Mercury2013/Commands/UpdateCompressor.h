#ifndef UPDATECOMPRESSOR_COMMAND_H
#define UPDATECOMPRESSOR_COMMAND_H

#include "CommandBase.h"

/**
 * Updates the state of the compressor according to Pneumatics::isBelowPressure.
 * Is never finished, is always interruptible, and is the default command for the pneumatics system.
 * @author Westin Miller
 */
class UpdateCompressor: public CommandBase {
public:
	UpdateCompressor();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
