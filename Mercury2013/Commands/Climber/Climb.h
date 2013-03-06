#ifndef __CMD_CLIMB_CLIMB_H
#define __CMD_CLIMB_CLIMB_H

#include "WPILib.h"
/**
 * @brief This command group will handle all of the subsystems in the Climber to make them work in sync and in order
 *
 *Todo Two tandem motors, one speed, Two directions, mechanically linked motors, 80lb. constant force spring
 *
 * @author Connor Barlow
 */
class Climb: public CommandGroup {
public:
	Climb();
	~Climb();
};

#endif
