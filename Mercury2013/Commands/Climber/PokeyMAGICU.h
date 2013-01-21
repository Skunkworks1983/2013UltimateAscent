#ifndef __POKEY_MAGIKU_H
#define __POKEY_MAGIKU_H
#include "WPILib.h"
#include "../CommandBase.h"
#include "../../Subsystems/Climber.h"

class Pokey : public CommandBase {
public:
	Pokey();
	~Pokey();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
