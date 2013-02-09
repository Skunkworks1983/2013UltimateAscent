#ifndef __CMD_SHOOT_H
#define __CMD_SHOOT_H

#include "../CommandBase.h"

/**
 * @brief Fires a disc
 * 
 * Moves a pneumatic arm to fire a disc
 * Requires an exclusive lock on the shooter
 * @author Mark Old
 */
class Shoot: public CommandBase {
private:
	double startTime;
public:
	Shoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
