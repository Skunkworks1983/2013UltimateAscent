#ifndef __CMD_CLIMB_HOKEYPOKEY_H
#define __CMD_CLIMB_HOKEYPOKEY_H
#include "WPILib.h"
#include "../CommandBase.h"
#include "../../Subsystems/Climber.h"

/**
 * @brief Accesses the Climber to raise and lower the pokey sticks
 *
 * @author Connor Barlow, Mark Old
 */
class HokeyPokey: public CommandBase {
private:
	bool position;
public:
	HokeyPokey(bool position);	
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
