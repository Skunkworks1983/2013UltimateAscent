#ifndef DRIVE_DISTANCE_H
#define TURN_DEGREE_H
#include "../Subsystems/DriveBase.h" 
#include "CommandBase.h"
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
	int m_counter;
	int m_count;
	DriveBase m_driveBase;
};
#endif
//Gyro,angle turned, target angle, count, 






