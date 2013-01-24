#ifndef __HOKEY_POKEY_H
#define __HOKEY_POKEY_H
#include "WPILib.h"
#include "../CommandBase.h"
#include "../../Subsystems/Climber.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class HokeyPokey: public CommandBase {
public:
	HokeyPokey();
	~HokeyPokey();
	
	/**  
	 */
	virtual void Initialize();
	
	/**  
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
