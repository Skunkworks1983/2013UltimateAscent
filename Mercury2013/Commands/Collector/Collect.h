#ifndef __CMD_COLLECT_COLLECT_H
#define __CMD_COLLECT_COLLECT_H

#include "../CommandBase.h"

class Collect: public CommandBase {
private:
	enum State {on, off, toggle};
	State mode;
public:
	Collect(State state);
	~Collect();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
