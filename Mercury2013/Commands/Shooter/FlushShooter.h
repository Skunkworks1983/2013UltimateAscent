#ifndef __CMD_FLUSH_SHOOTER_H
#define __CMD_FLUSH_SHOOTER_H

#include "../CommandBase.h"

/**
 * @brief Flushes the shooter of frisbees
 * 
 * Runs the last wheel of the shooter in reverse to eject a lodged frisbee
 * Requires an exclusive lock on the shooter
 * @author Mark Old
 */
class FlushShooter: public CommandBase {
public:
	FlushShooter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
