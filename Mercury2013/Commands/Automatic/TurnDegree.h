#ifndef TURN_DEGREE_H
#define TURN_DEGREE_H 
#include "../CommandBase.h"

/**
 * @brief Uses the drive base and it's gyroscope to turn a certain amount.
 * 
 * This command requires an exclusive lock on the drive base, as well as a gyroscope.
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
	float m_angleTurned;
	float m_targetAngle;
	float m_count;
};
#endif
//Gyro,angle turned, target angle, count, 
