#ifndef __CLIMB_H
#define __CLIMB_H

#include "ArmMove.h"
/**
 * @brief This command group will handle all of the subsystems in the Climber to make them work in sync and in order
 *
 * @author Connor Barlow
 */
class Climb: public CommandGroup {
public:
	Climb();
	~Climb();
};

#endif
