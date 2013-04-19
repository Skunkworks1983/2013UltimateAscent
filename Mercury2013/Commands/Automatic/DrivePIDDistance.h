#ifndef __CMD_AUTO_DRIVEPIDDISTANCE_H
#define __CMD_AUTO_DRIVEPIDDISTANCE_H
#include "../../Subsystems/DriveBase.h" 
#include "../CommandBase.h"
#include "DriveDistPIDControl.h"

class DrivePIDDistance: public CommandBase {
private:
	float tStable;
	int stability;
	float driveCorrection;
	PIDController *pidLeft;
	PIDController *pidRight;
	DriveDistPIDLeft *leftControl;
	DriveDistPIDRight *rightControl;
public:
	DrivePIDDistance(float targetDistance,
			float tStable = AUTO_DRIVE_DIST_STABILITY,
			float tThreshold = AUTO_DRIVE_DIST_THRESHOLD);
	~DrivePIDDistance();
	DrivePIDDistance *DrivePIDDistance::setOutputRange(float min, float max);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	double getRight();
	double getLeft();
	void writeRight(float f);
	void writeLeft(float f);
};
#endif
