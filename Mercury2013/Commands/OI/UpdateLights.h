#ifndef __UPDATE_LIGHTS_H
#define __UPDATE_LIGHTS_H

#include "../CommandBase.h"

class UpdateLights: public CommandBase {
public:
	UpdateLights();
	~UpdateLights();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
