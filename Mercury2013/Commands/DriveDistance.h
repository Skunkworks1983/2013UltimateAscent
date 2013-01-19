#ifndef DRIVE_DISTANCE_H
#define DRIVE_DISTANCE_H
#include "../Subsystems/DriveBase.h" 
#include "CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveDistance: public CommandBase {
public:
	DriveDistance();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();	
	float targetDistance;
private:
	float m_distanceDriven;
	float m_targetDistance;
	int m_counter;
};
#endif
