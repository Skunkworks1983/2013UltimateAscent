#ifndef __UPDATE_LIGHTS_H
#define __UPDATE_LIGHTS_H

#include "../CommandBase.h"

/**
 * @brief Updates lights on the driver station interface.
 *  
 * @author Westin Miller
 */
class UpdateLights: public CommandBase {
public:
	UpdateLights();
	~UpdateLights();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
