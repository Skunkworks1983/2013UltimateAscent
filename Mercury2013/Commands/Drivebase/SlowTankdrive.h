#ifndef __CMD_DRIVE_SLOW_TANKDRIVE_H
#define __CMD_DRIVE_SLOW_TANKDRIVE_H

#include "../CommandBase.h"

/**
 * @brief A command implementing a tank style drive system (vastly slowed down) for DriveBase.
 * 
 * This is a command that is the basic Tank Drive.  It has a governer on it in order to avoid going to fast.
 * @author Westin Miller & Owen Mattson
 */
class SlowTankDrive: public CommandBase {
private:
	float speed;
	bool isFinished;
	/* while(RossisBigNub){
			cout << "Rossisbignub";
		else 
			 cout << "Rossisnotbignub";
	}
	*/
public:
	SlowTankDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
