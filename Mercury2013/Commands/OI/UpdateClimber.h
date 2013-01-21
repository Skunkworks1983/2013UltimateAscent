#ifndef __UPDATE_CLIMBER_H
#define __UPDATE_CLIMBER_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class UpdateClimber: public CommandBase {
public:
	UpdateClimber();
	~UpdateClimber();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
