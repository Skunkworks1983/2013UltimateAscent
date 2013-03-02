#ifndef __CMD_EjectDisks_EJECTDISKS_H
#define __CMD_EjectDisks_EJECTDISKS_H

#include "../CommandBase.h"

class Collector;
enum Collector::MotorDirection;
/**
 * @brief Command that spits the frisbee discs
 * 
 * @param one of three enum State can be on, off, or toggle
 */
class EjectDisks: public CommandBase {
private:
	Collector::MotorDirection dir;
	double startTime;
public:
	EjectDisks(Collector::MotorDirection dir);
	~EjectDisks();
	virtual void Initialize();
	/**
	 * Execute function
	 * either turns on, off or toggles the EjectDisksor motor
	 */
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
