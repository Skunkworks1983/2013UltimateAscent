#ifndef DRIVE_DISTANCE_H
#define DRIVE_DISTANCE_H
#include "../../Subsystems/DriveBase.h" 
#include "../CommandBase.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveDistance: public CommandBase {

private:
	//todo add more modes
	enum SlopeType {flat, linear, quadratic};
	SlopeType m_SlopeType;
	float m_distanceDriven;
	float m_targetDistance;
	int m_counter;
	int m_count;
	DriveBase m_driveBase;
	void ExecuteLinear();
	void ExecuteFlat();
	void ExecuteQuadratic();
	

public:
	DriveDistance(float targetDistance, SlopeType MySlope);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif
