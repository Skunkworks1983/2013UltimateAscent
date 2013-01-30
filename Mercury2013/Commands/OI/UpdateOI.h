#ifndef __UPDATE_LIGHTS_H
#define __UPDATE_LIGHTS_H

#include "../CommandBase.h"

/**
 * @brief Updates lights on the driver station interface.
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
