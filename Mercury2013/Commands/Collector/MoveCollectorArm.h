#ifndef __CMD_COLLECT_CHANGEPOSITION_H
#define __CMD_COLLECT_CHANGEPOSITION_H

#include "../CommandBase.h"
/**
 * @brief Change collector position command
 * 
 * Todo:  CollectorArms: 1 motor, 1 speed, 1 encoder, 1 light sensor for stopping motor
 * 
 * 
 * 
 * Command that takes a position
 * then changes the collectors position
 * to the argument sent
 * true is up, false is down
 * @author Ross Bajocich
 */
class MoveCollectorArm: public CommandBase {
private:
	PIDController *controller;
	float goal;
public:
	MoveCollectorArm(float goal);
	~MoveCollectorArm();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
