#ifndef SHIFT_H
#define SHIFT_H

#include "../CommandBase.h"

/**
 * @brief Shifts the DriveBase
 * 
 * Shifts the DriveBase using the given shifting style.
 * This does not require an exclusive lock on the DriveBase.
 * @author Westin Miller
 */
class Brake: public CommandBase {
private:
	bool isBraking;
public:
	/**
	 * Creates a braking command that either brakes or unbrakes.
	 * 
	 * @param isBraking whether we are braking or not
	 */
	Brake(bool isBraking);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
