#ifndef __CLIMB_H
#define __CLIMB_H

#include "../CommandGroupBase.h"
#include "ArmMove.h"
//TODO TODO TODO MAKE THIS A GROUP TODO TODO TODO
/**
 *
 *
 * @author ExampleAuthor
 */
class Climb: public CommandBase {
public:
	Climb();
	~Climb();
	
	/**  Will probably check the other commands to make sure that everthing is 
	 * climb-tastic
	 */
	virtual void Initialize();
	
	/**  Will execute all of the different commands and move all of the 
	 * required parts, will get the robot from the bottom of the pyramid to the 
	 * top
	 */
	virtual void Execute();
	
	/**  Will check that it is indead at the top of the pyramid before it stops
	 */
	virtual bool IsFinished();
	
	/**  Stops the motors and secures the robot on top of the pyramid, should 
	 * have something for flipping over (god forbid)
	 */
	virtual void End();
	
	/**  Incase the climberr is interrupted, it will look at what stage it is 
	 * at and figures out what to do
	 */
	virtual void Interrupted();
};

#endif
