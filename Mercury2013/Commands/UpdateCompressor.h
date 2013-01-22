#ifndef UPDATECOMPRESSOR_COMMAND_H
#define UPDATECOMPRESSOR_COMMAND_H

#include "CommandBase.h"

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
