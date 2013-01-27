#ifndef __HOKEY_POKEY_H
#define __HOKEY_POKEY_H
#include "WPILib.h"
#include "../CommandBase.h"
#include "../../Subsystems/Climber.h"

/**
 * @brief Accesses the Climber to raise and lower the pokey sticks
 *
 * @author Connor Barlow
 */
class HokeyPokey: public CommandBase {
public:
	HokeyPokey();
	~HokeyPokey();
	
	/**  
	 */
	virtual void Initialize();
	
	/**  Doesn't actually do anything, not necessary
	 */
	virtual void Execute();
	
	/**  
	 */
	virtual bool IsFinished();
	
	/**  
	 */
	virtual void End();
	
	/**  
	 */
	virtual void Interrupted();
};

#endif
