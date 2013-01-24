#ifndef __ARM_MOVE_H
#define __ARM_MOVE_H
#include "WPILib.h"
#include "../CommandBase.h"
#include "../../Subsystems/Climber.h"

class ArmMove : public CommandBase { 
public:
	ArmMove();
	~ArmMove();
	
	/**  Will hopeuflly initialize any necessary variables later as they 
	 * appear, probably motors and things.
	 */
	virtual void Initialize();
	
	/**  Contains logic to move arms up one level in an execute, will probably 
	 * run a single time per execute later, but has simple logic to check if it
	 * is up a level and what to do then.
	 */
	virtual void Execute();
	
	/**  Checks to see if done
	 */
	virtual bool IsFinished();
	
	/**  Just stops the motors to stabalize the robot
	 */
	virtual void End();
	
	/**  Will probably contain some safety to stop if interrupted (which would
	 * be awful IMHO)
	 */
	virtual void Interrupted();
};

#endif
