#ifndef __CMD_CHANGE_PITCH_H
#define __CMD_CHANGE_PITCH_H

#include "../CommandBase.h"

/**
 * @brief Changes the pitch of the shooter
 * 
 * Changes the position of the shooter
 * This does require an exclusive lock on the shooter.
 * @author Mark Old
 */
class ChangeShooterPitch: public CommandBase {
private:
	float targetPitch;
	bool waitForCollector;
	int stability;
public:
	ChangeShooterPitch(float targetPitch, bool waitForCollector = true);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
