#ifndef __CMD_COLLECTOR_DEBUG_H
#define __CMD_COLLECTOR_DEBUG_H

#include "../CommandBase.h"
#include <fstream>

/**
 * @brief Updates lights and dashboard outputs on the driver station interface.
 *  
 * @author Westin Miller
 */
class CollectorDebug: public CommandBase {
private:
	ofstream fileOut;
public:
	CollectorDebug();
	~CollectorDebug();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
