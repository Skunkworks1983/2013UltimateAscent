#ifndef __DRIVEDIST_PID_CONTROL_H
#define __DRIVEDIST_PID_CONTROL_H

class DrivePIDDistance;

class DriveDistPIDLeft: public PIDSource, public PIDOutput {
private:
	DrivePIDDistance *backend;
public:
	DriveDistPIDLeft(DrivePIDDistance *back);
	virtual void PIDWrite(float f);
	virtual double PIDGet();
};

class DriveDistPIDRight: public PIDSource, public PIDOutput {
private:
	DrivePIDDistance *backend;
public:
	DriveDistPIDRight(DrivePIDDistance *back);
	virtual void PIDWrite(float f);
	virtual double PIDGet();
};
#endif
