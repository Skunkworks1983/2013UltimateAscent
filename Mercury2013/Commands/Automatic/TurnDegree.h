#ifndef __CMD_AUTO_TURNDEGREE_H
#define __CMD_AUTO_TURNDEGREE_H
#include "../CommandBase.h"

/**
 * @brief Uses the DriveBase and it's gyroscope to turn a certain amount.
 * 
 * This command requires an exclusive lock on the DriveBase, as well as a gyroscope.
 * @author Owen Mattson
 */
class TurnDegree: public CommandBase {
public:
	TurnDegree(float targetDistance);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float targetAngle;
	float angleRemaining;
};
#endif
// Gyro,angle turned, target angle, count, 
