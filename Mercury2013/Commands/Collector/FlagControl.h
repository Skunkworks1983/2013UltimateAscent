#ifndef __CMD_COLLECT_FLAG_H
#define __CMD_COLLECT_FLAG_H

#include "../CommandBase.h"
class FlagControl: public CommandBase {
public:
	enum FlagControlType {
		kFlagAutoDown, kFlagDown, kFlagUp, kFlagToggle
	};
private:
	FlagControlType controlType;
	bool destinationState;
	bool complete;
	double anglePassed;
public:
	FlagControl(FlagControlType controlType);
	~FlagControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
