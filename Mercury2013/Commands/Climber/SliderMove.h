#ifndef __CMD_CLIMB_SLIDERMOVE_H
#define __CMD_CLIMB_SLIDERMOVE_H
#include "WPILib.h"
#include "../CommandBase.h"

/**
 * @brief Moves the two arms, using methods in Climber to check and move upward
 * 
 * @author Connor Barlow
 */
class SliderMove: public CommandBase {
private:
	PIDController *pidController;
	bool destExtend;

public:
	SliderMove(bool destIsExtended);
	~SliderMove();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
