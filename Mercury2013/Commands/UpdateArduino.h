#ifndef __CMD_UPDATE_ARDUINO_H
#define __CMD_UPDATE_ARDUINO_H

#include "CommandBase.h"

/**
 * @brief Controls the compressor defined in the Pneumatics subsystem.
 * 
 * Updates the state of the compressor according to Pneumatics::isBelowPressure.
 * Is never finished, is always interruptible, and is the default command for the pneumatics system.
 * @author Westin Miller
 */
class UpdateArduino: public CommandBase {
public:
	UpdateArduino();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
