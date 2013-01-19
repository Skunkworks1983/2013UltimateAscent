#ifndef TURN_DEGREE_H
#define TURN_DEGREE_H 
#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
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






