#ifndef __CMD_SHOOTER_TUNE_PITCH_H
#define __CMD_SHOOTER_TUNE_PITCH_H

#include "../CommandBase.h"

class TunePitchEncoder: public CommandBase {
public:
	TunePitchEncoder();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void ExternalRun();
};

#endif
