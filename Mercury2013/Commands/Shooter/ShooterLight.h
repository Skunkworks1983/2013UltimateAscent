#ifndef __CMD_SHOOTER_LIGHT_H
#define __CMD_SHOOTER_LIGHT_H

#include "../CommandBase.h"

class ShooterLight: public CommandBase {
public:
	enum LightType {
		kOff,
		kOn,
		kToggle
	};
private:
	bool toLightState;
	LightType controlType;
public:
	ShooterLight(LightType controlType);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
