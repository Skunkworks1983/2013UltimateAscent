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

public:
	enum SlopeType {flat, linear, quadratic};

private:
	SlopeType m_SlopeType;
	float m_distanceDriven;
	float m_distanceDrivenRight;
	float m_distanceDrivenLeft;
	float m_targetDistance;
	float m_distanceRemaining;
	float m_leftDistanceRemaining;
	float m_rightDistanceRemaining;

	float m_direction; //forward (+1) or backwards (-1)
	int m_counter;
	int m_count;
	int m_speed;
	float m_cachedLinearSpeed;
	DriveBase m_driveBase;
	void ExecuteLinear();
	void ExecuteFlat();
	void ExecuteQuadratic(float leftDist, float rightDist);

public:
	DriveDistance(float targetDistance, SlopeType MySlope);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};
#endif
