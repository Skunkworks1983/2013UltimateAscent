#ifndef __CMD_COLLECT_COLLECT_H
#define __CMD_COLLECT_COLLECT_H

#include "../CommandBase.h"
/**
 * @brief Collect command that turns on, off or toggle for the collector
 * 
 * @param one of three enum State can be on, off, or toggle
 */
class Collect: public CommandBase {
public:
	Collect(ControlType ctrlType);
	~Collect();
	virtual void Initialize();
	/**
	 * Execute function
	 * either turns on, off or toggles the collector motor
	 */
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
