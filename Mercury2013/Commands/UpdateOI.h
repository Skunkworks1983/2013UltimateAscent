#ifndef __CMD_UPDATEOI_H
#define __CMD_UPDATEOI_H

#include "../CommandBase.h"

/**
 * @brief Updates lights and dashboard outputs on the driver station interface.
 *  
 * @author Westin Miller
 */
class UpdateOI: public CommandBase {
public:
	UpdateOI();
	~UpdateOI();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
