#ifndef __CMD_COLLECT_CHANGEPOSITION_H
#define __CMD_COLLECT_CHANGEPOSITION_H

#include "../CommandBase.h"
/**
 * @brief Change collector position command
 * 
 * Todo:  Collector: 1 motor, 1 speed, 1 encoder, 1 light sensor for stopping motor
 * 
 * 
 * 
 * Command that takes a position
 * then changes the collectors position
 * to the argument sent
 * true is up, false is down
 * @author Ross Bajocich
 */
class ChangePosition: public CommandBase {
public:
	enum ChangeType {
		kUp, kDown, kToggle
	};
private:
	PIDController *controller;
	ChangeType goal;
	Collector::CollectorState targetState;
public:
	ChangePosition(ChangeType goal);
	~ChangePosition();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
