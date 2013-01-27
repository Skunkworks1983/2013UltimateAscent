#ifndef TANKDRIVE_COMMAND_H
#define TANKDRIVE_COMMAND_H

#include "../CommandBase.h"

/**
 * @brief A command implementing a tank style drive system for DriveBase.
 * 
 * Basic tank drive implementation for the DriveBase subsystem.
 * This requires an exclusive lock on the drive base, and is also the default command for it.
 * @author Westin Miller
 */
class TankDrive: public CommandBase {
public:
	TankDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
